#include "Enemy.h"
#include "Player.h"
#include "bn_sprite_items_mouse.h"
#include <bn_display.h>

extern bn::rect create_bounding_box(bn::sprite_ptr sprite, bn::size box_size);

static constexpr int MIN_Y = -bn::display::height() / 2;
static constexpr int MAX_Y = bn::display::height() / 2;
static constexpr int MIN_X = -bn::display::width() / 2;
static constexpr int MAX_X = bn::display::width() / 2;

Enemy::Enemy(int x, int y, bn::fixed spd, bn::size sz) :
    sprite(bn::sprite_items::mouse.create_sprite(x, y)),
    speed(spd),
    size(sz),
    bounding_box(create_bounding_box(sprite, size))
{
}

void Enemy::update(Player& player) {
    if(player.sprite.x() > sprite.x())
        sprite.set_x(sprite.x() + speed);

    if(player.sprite.x() < sprite.x())
        sprite.set_x(sprite.x() - speed);

    if(player.sprite.y() > sprite.y())
        sprite.set_y(sprite.y() + speed);

    if(player.sprite.y() < sprite.y())
        sprite.set_y(sprite.y() - speed);

    bounding_box = create_bounding_box(sprite, size);
}