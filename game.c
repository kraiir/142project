// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "game.h"

extern char * map;
extern int height;
extern int width;

int check_win(int player_y, int player_x) {
    // Returns an integer meaning two options: either you win or you keep going
    if (player_y < 0 || player_y >= height || player_x < 0 || player_x >= width) {
        // Checks if the position is above or below the top/bottom row, same for sides
        //This would mean the player escaped the box
        return YOU_WIN;
    }
    return KEEP_GOING;
}

int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // Returns an integer meaning two options: either you lose or you keep going
    if (player_y == minotaur_y && player_x == minotaur_x) {
        //Checks if both the x and y position of the player equal that of the minotaur
        //If they're both equal, then the minotaur is touching the player
        return YOU_LOSE;
    }
    return KEEP_GOING;
}
