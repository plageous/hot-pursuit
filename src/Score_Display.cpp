#include "ScoreDisplay.h"

#include <bn_string.h>
#include "common_fixed_8x16_font.h"

// Score display positions
static constexpr int SCORE_X = 70;
static constexpr int SCORE_Y = -70;

static constexpr int HIGH_SCORE_X = -70;
static constexpr int HIGH_SCORE_Y = -70;

ScoreDisplay::ScoreDisplay() :
    score(0),
    high_score(0),
    score_sprites(),
    text_generator(common::fixed_8x16_sprite_font)
{
}

void ScoreDisplay::update() {
    score++;

    if(score > high_score) {
        high_score = score;
    }

    score_sprites.clear();

    show_number(SCORE_X, SCORE_Y, score);
    show_number(HIGH_SCORE_X, HIGH_SCORE_Y, high_score);
}

void ScoreDisplay::resetScore() {
    score = 0;
}

void ScoreDisplay::show_number(int x, int y, int number) {
    bn::string<MAX_SCORE_CHARS> number_string =
        bn::to_string<MAX_SCORE_CHARS>(number);

    text_generator.generate(x, y, number_string, score_sprites);
}