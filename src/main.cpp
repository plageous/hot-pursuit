#include <bn_core.h>
#include <bn_display.h>
#include <bn_keypad.h>
#include <bn_rect.h>
#include <bn_size.h>
#include <bn_string.h>
#include <bn_sprite_ptr.h>
#include <bn_sprite_text_generator.h>
#include <bn_random.h>

#include "Enemy.h"
#include "common_fixed_8x16_font.h"
#include "Player.h"
#include "ScoreDisplay.h"
#include "Powerup.h"

// Width and height of the the player bounding box
static constexpr bn::size PLAYER_SIZE = {8, 8};
static constexpr bn::size ENEMY_SIZE = {8, 8};

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

// Number of characters required to show two of the longest numer possible in an int (-2147483647)
static constexpr int MAX_SCORE_CHARS = 22;

// Score location
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

// High score location
static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

//Power up const 
static constexpr int POWERUP_SPAWN_TIME = 300;
static constexpr int IMMUNITY_TIME = 180;

// random number generator instance
static bn::random rng = bn::random();

/**
 * Creates a rectangle centered at a sprite's location with a given size.
 * sprite the sprite to center the box around
 * box_size the dimensions of the bounding box
 */
bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size) {
    return bn::rect(sprite.x().round_integer(),
                    sprite.y().round_integer(),
                    box_size.width(),
                    box_size.height());
}

int main() {
    bn::core::init();

    // Create a new score display
    ScoreDisplay scoreDisplay = ScoreDisplay();

    // Create a player and initialize it
    // TODO: we will move the initialization logic to a constructor.
    Player player = Player(50,52, 4.5, PLAYER_SIZE);

    //add power up variables

    PowerUp powerup;  
    
    bool powerup_spawned = false;

    int global_frame_counter = 0;

    bool immunity_active = false;
    int immunity_counter = 0;

   // Create a vector of enemies (capacity 8, change if you want more)
    bn::vector<Enemy, 8> enemies;

    //Start with 1 enem
    enemies.push_back(Enemy(
        rng.get_int(MIN_X, MAX_X),
        rng.get_int(MIN_Y, MAX_Y),
        1,
        ENEMY_SIZE
    ));

    int frame_counter = 0;
    static constexpr int SPAWN_RATE = 180;

    while(true) {
        player.update();

        frame_counter++;

        //power up logic 
        global_frame_counter++;

        if(!powerup_spawned && global_frame_counter >= POWERUP_SPAWN_TIME) {
            powerup.spawn(rng.get_int(MIN_X, MAX_X), rng.get_int(MIN_Y, MAX_Y));
            powerup_spawned = true;
        }

        //power up pickup
        powerup.update();

        if(powerup.is_active() && powerup.get_bounding_box().intersects(player.bounding_box)) {
            immunity_active = true;
            immunity_counter = IMMUNITY_TIME;
            powerup.destroy();
        }

        //power up timer
        if(immunity_active) {
        --immunity_counter;
        if(immunity_counter <= 0) {
            immunity_active = false;
        }
    }
        //if the player has immunity, make the player sprite blink
        if(immunity_active) {
            player.sprite.set_visible((immunity_counter / 5) % 2);
        } else {
            player.sprite.set_visible(true);
        }

        // Spawn new enemy every 3 if there's room
        if(frame_counter >= SPAWN_RATE) {
            frame_counter = 0;

            if(enemies.size() < enemies.max_size()) {
                enemies.push_back(Enemy(
                    rng.get_int(MIN_X, MAX_X),
                    rng.get_int(MIN_Y, MAX_Y),
                    1,
                    ENEMY_SIZE
                ));
            }
        }

        bool caught = false;

        // Update each enemy + check collision against player
        for(Enemy& enemy : enemies) {
            enemy.update(player);

            if(enemy.bounding_box.intersects(player.bounding_box) && !immunity_active) {
                caught = true;
                break;
            }
        }
         if(caught) {
            scoreDisplay.resetScore();

            player.sprite.set_x(44);
            player.sprite.set_y(22);
            player.bounding_box = create_bounding_box(player.sprite, player.size);
            
            //reset power up 
            powerup.destroy();
            powerup_spawned = false;
            global_frame_counter = 0;
            immunity_active = false;
            immunity_counter = 0;
            player.sprite.set_visible(true);

            // Keep only one enemy
            if(enemies.size() > 1) {
                Enemy survivor = enemies.front();
                enemies.clear();
                enemies.push_back(survivor);
            }

            // Move surviving enemy to random location
            enemies.front().sprite.set_x(rng.get_int(MIN_X, MAX_X));
            enemies.front().sprite.set_y(rng.get_int(MIN_Y, MAX_Y));
            enemies.front().bounding_box =
                create_bounding_box(enemies.front().sprite, ENEMY_SIZE);
        }
        else {
            scoreDisplay.update();
        }

        bn::core::update();
    }
}