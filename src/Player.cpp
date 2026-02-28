#include "Player.h"
#include "bn_sprite_items_dot.h"
#include <bn_keypad.h>
#include <bn_display.h>

extern bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

Player::Player(int starting_x, int starting_y, bn::fixed spd, bn::size sz) :
    sprite(bn::sprite_items::dot.create_sprite(starting_x, starting_y)),
    speed(spd),
    size(sz),
    bounding_box(create_bounding_box(sprite, size))
{
}

void Player::update() {
    if(bn::keypad::right_held() && sprite.x() <= MAX_X)
        sprite.set_x(sprite.x() + speed);

    if(bn::keypad::left_held() && sprite.x() >= MIN_X)
        sprite.set_x(sprite.x() - speed);

    if(bn::keypad::up_held() && sprite.y() >= MIN_Y)
        sprite.set_y(sprite.y() - speed);

    if(bn::keypad::down_held() && sprite.y() <= MAX_Y)
        sprite.set_y(sprite.y() + speed);

    bounding_box = create_bounding_box(sprite, size);
}