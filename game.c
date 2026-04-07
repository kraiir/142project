// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "game.h"

#include <stdio.h>

extern char * map;
extern int height;
extern int width;

int check_win(int player_y, int player_x) {
    //if player escaped = win
    if (player_y <= 0 || player_y >= height - 1 || player_x <= 0 || player_x >= width - 1) {
        return YOU_WIN;
    }
    return KEEP_GOING;
}

int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    //if player and minotaur same position = lose
    if (player_y == minotaur_y && player_x == minotaur_x) {
        return YOU_LOSE;
    }
    return KEEP_GOING;
}
