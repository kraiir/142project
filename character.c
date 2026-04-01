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

    // Check if they are on the exact same tile FIRST
    if (player_y == minotaur_y && player_x == minotaur_x) {
        return CAUGHT_PLAYER;
    }

    if (player_y != minotaur_y && player_x != minotaur_x) return SEES_NOTHING;

    // Same Column
    if (player_x == minotaur_x) {
        int start = (player_y < minotaur_y) ? player_y : minotaur_y;
        int end = (player_y < minotaur_y) ? minotaur_y : player_y;
        for (int i = start + 1; i < end; i++) {
            if (map[i * width + player_x] == WALL) return SEES_NOTHING;
        }
        return (player_y < minotaur_y) ? UP : DOWN;
    }

    // Same Row
    if (player_y == minotaur_y) {
        int start = (player_x < minotaur_x) ? player_x : minotaur_x;
        int end = (player_x < minotaur_x) ? minotaur_x : player_x;
        for (int i = start + 1; i < end; i++) {
            if (map[player_y * width + i] == WALL) return SEES_NOTHING;
        }
        return (player_x < minotaur_x) ? LEFT : RIGHT;
    }
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
    else return MOVED_INVALID_DIRECTION;

    if (next_y < 0 || next_y >= height || next_x < 0 || next_x >= width) {
        return MOVED_WALL; // Treat the "void" outside the map as a wall
    }

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

    // Fail fix
    if (charge_direction != UP && charge_direction != DOWN &&
        charge_direction != LEFT && charge_direction != RIGHT) {
        return MOVED_INVALID_DIRECTION;
    }

    for (int i = 0; i < MINOTAUR_CHARGE_STEP_SIZE; i++) {
        // We need to check if the NEXT step would land on the player
        // OR let move_character do it and then update the map.
        int status = move_character(y, x, charge_direction, MINOTAUR);

        if (status == MOVED_WALL) {
            int wall_y = *y, wall_x = *x;
            if (charge_direction == UP) wall_y--;
            else if (charge_direction == DOWN) wall_y++;
            else if (charge_direction == LEFT) wall_x--;
            else if (charge_direction == RIGHT) wall_x++;

            if (wall_y >= 0 && wall_y < height && wall_x >= 0 && wall_x < width) {
                map[(*y * width) + *x] = EMPTY;
                map[(wall_y * width) + wall_x] = MINOTAUR;
                *y = wall_y;
                *x = wall_x;
            }
            return MOVED_WALL;
        }

        // Caught player
        if (*y == player_y && *x == player_x) {
            // Ensure the map shows the Minotaur is now standing where the player was
            map[(*y * width) + *x] = MINOTAUR;
            return CAUGHT_PLAYER; // Stop immediately and return the correct code
        }
    }
    return MOVED_OKAY;
}