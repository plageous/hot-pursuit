#ifndef SCORE_DISPLAY_H
#define SCORE_DISPLAY_H

#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_sprite_text_generator.h>

class ScoreDisplay {
public:
    ScoreDisplay();
    void update();
    void resetScore();

private:
    void show_number(int x, int y, int number);

    int score;
    int high_score;

    static constexpr int MAX_SCORE_CHARS = 22;

    bn::vector<bn::sprite_ptr, MAX_SCORE_CHARS> score_sprites;
    bn::sprite_text_generator text_generator;
};

#endif