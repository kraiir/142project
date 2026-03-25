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

    //same row/col
    if (player_x == minotaur_x) {
        int start, end;
        char direction;
        // Determine who is further up the map to set the loop range
        if (player_y < minotaur_y) {
            start = player_y;
            end = minotaur_y;
            direction = UP;
        } else {
            start = minotaur_y;
            end = player_y;
            direction = DOWN;
        }

        // Check every tile between them for a wall
        for (int i = start + 1; i < end; i++) {
            if (map[(i * width) + player_x] == WALL) {
                return SEES_NOTHING;
            }
        }
        return direction;
    }

    // 2. Check if they are in the same row
    if (player_y == minotaur_y) {
        int start, end;
        char direction;

        // Determine who is further left to set the loop range
        if (player_x < minotaur_x) {
            start = player_x;
            end = minotaur_x;
            direction = LEFT;
        } else {
            start = minotaur_x;
            end = player_x;
            direction = RIGHT;
        }

        // Check every tile between them for a wall
        for (int i = start + 1; i < end; i++) {
            if (map[(player_y * width) + i] == WALL) {
                return SEES_NOTHING;
            }
        }
        return direction;
    }

    // If they aren't in the same row or column, the Minotaur sees nothing
    return SEES_NOTHING;
}

int move_character(int * y, int * x, char direction, char character) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    // calculate the new coordinates to use on success (store in local variables)
    // check if the new coordinates point to a wall
    // at this point, the move is known to be valid (OK direction and not a wall)
    // remove character from the old position and replace with EMPTY
    // set character in the new position in map
    // update the x/y coordinate pointers

    int next_y = *y;
    int next_x = *x;

    if (direction == UP) next_y--;
    else if (direction == DOWN) next_y++;
    else if (direction == LEFT) next_x--;
    else if (direction == RIGHT) next_x++;

    // Boundary check to prevent the "+1y" wrap-around bug
    if (next_y < 0 || next_y >= height || next_x < 0 || next_x >= width) return MOVED_WALL;

    if (map[(next_y * width) + next_x] == WALL) {
        return MOVED_WALL;
    }

    // Update map: clear old, set new
    map[(*y * width) + *x] = EMPTY;
    map[(next_y * width) + next_x] = character;

    // Update pointers
    *y = next_y;
    *x = next_x;

    return MOVED_OKAY;
}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates

    // Charge for up to 2 steps
    for (int i = 0; i < MINOTAUR_CHARGE_STEP_SIZE; i++) {
        int status = move_character(y, x, charge_direction, MINOTAUR);

        if (status == MOVED_WALL) {
            int wall_y = *y;
            int wall_x = *x;

            //guess wall dir
            if (charge_direction == UP) wall_y--;
            else if (charge_direction == DOWN) wall_y++;
            else if (charge_direction == LEFT) wall_x--;
            else if (charge_direction == RIGHT) wall_x++;

            // BREAK AND MOVE: 1 step smash
            map[(*y * width) + *x] = EMPTY;
            map[(wall_y * width) + wall_x] = MINOTAUR;
            *y = wall_y;
            *x = wall_x;

            return MOVED_WALL; // Returns to main.c to reset charge
        }

        // If caught player during charge
        if (*y == player_y && *x == player_x) return MOVED_OKAY;
    }
    return MOVED_OKAY;
}