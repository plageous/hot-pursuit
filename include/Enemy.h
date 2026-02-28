#ifndef ENEMY_H
#define ENEMY_H

#include <bn_sprite_ptr.h>
#include <bn_fixed.h>
#include <bn_size.h>
#include <bn_rect.h>

class Player;

class Enemy {
public:
    Enemy(int starting_x, int starting_y, bn::fixed speed, bn::size size);
    void update(Player& player);

    bn::sprite_ptr sprite;
    bn::fixed speed;
    bn::size size;
    bn::rect bounding_box;
};

#endif