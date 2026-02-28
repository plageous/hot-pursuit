#ifndef POWERUP_H
#define POWERUP_H

#include <bn_sprite_ptr.h>
#include <bn_rect.h>
#include <bn_size.h>

class PowerUp {
public:
    PowerUp();                 // starts inactive/invisible
    void spawn(int x, int y);   // activate + move + show once

    void update();
    void destroy();

    bool is_active() const;
    bn::rect get_bounding_box() const;

private:
    bn::sprite_ptr sprite;
    bn::rect bounding_box;
    bool active;
};

#endif