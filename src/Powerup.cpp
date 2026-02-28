#include "Powerup.h"

#include "bn_sprite_items_dot.h"   // or your powerup sprite item
// If create_bounding_box lives elsewhere, include that header instead of extern:
extern bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

static constexpr bn::size POWERUP_SIZE = {8, 8};

PowerUp::PowerUp() :
    sprite(bn::sprite_items::dot.create_sprite(0, 0)),
    bounding_box(create_bounding_box(sprite, POWERUP_SIZE)),
    active(false)
{
    sprite.set_visible(false);     // inactive at start
}

void PowerUp::spawn(int x, int y) {
    sprite.set_x(x);
    sprite.set_y(y);
    sprite.set_visible(true);

    active = true;
    bounding_box = create_bounding_box(sprite, POWERUP_SIZE);
}

void PowerUp::update() {
    if(active) {
        bounding_box = create_bounding_box(sprite, POWERUP_SIZE);
    }
}

void PowerUp::destroy() {
    sprite.set_visible(false);
    active = false;
}

bool PowerUp::is_active() const {
    return active;
}

bn::rect PowerUp::get_bounding_box() const {
    return bounding_box;
}