// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "character.h"

extern char * map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // check to see if the Minotaur has caught the player
    // check if neither the x nor y coordinate is the same as the player
    // if there's a wall in between, they can't see
    // if one of them is the same, check if the path in between is clear
    return SEES_NOTHING;
}

int move_character(int * y, int * x, char direction, char character) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    // calculate the new coordinates to use on success (store in local variables)
    // check if the new coordinates point to a wallg
    // at this point, the move is known to be valid (OK direction and not a wall)
    // remove character from the old position and replace with EMPTY
    // set character in the new position in map
    // update the x/y coordinate pointers
    return MOVED_OKAY;
}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates
    return MOVED_OKAY;
}
