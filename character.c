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
    // check if they are on the exact same tile FIRST

    // check same coords
    if (player_y == minotaur_y && player_x == minotaur_x) {
        return CAUGHT_PLAYER;
    }

    // aren't in straight line if xy not match
    if (player_y != minotaur_y && player_x != minotaur_x) return SEES_NOTHING;

    // same column
    if (player_x == minotaur_x) { //if same x is in a straight line
        int start, end;
        if (player_y < minotaur_y) { //lower y means player is higher up, so minotaur must move up to reach
            start = player_y;
            end = minotaur_y;
        } else { //minotaur move down
            start = minotaur_y;
            end = player_y;
        }

        //check tiles for any walls
        for (int i = start + 1; i < end; i++) {
            if (map[i * width + player_x] == WALL) { //if wall then see nothing
                return SEES_NOTHING;
            }
        }

        //if no wall, return the direction minotaur move
        if (player_y < minotaur_y) {
            return UP;
        } else {
            return DOWN;
        }
    }

    // same row?
    if (player_y == minotaur_y) {
        int start, end;
        if (player_x < minotaur_x) { //player is more left
            start = player_x;
            end = minotaur_x;
        } else {
            start = minotaur_x; //minotaur more left
            end = player_x;
        }

        for (int i = start + 1; i < end; i++) { //check for walls between
            if (map[player_y * width + i] == WALL) {
                return SEES_NOTHING;
            }
        }

        if (player_x < minotaur_x) { //player more left
            return LEFT; //direction is left
        } else {
            return RIGHT; //if not then direction is right
        }
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

    // declaring and initializing next variables with current coords
    int next_y = *y;
    int next_x = *x;

    // calculate next x or y based on moving direction.
    if (direction == UP) {
        next_y--;
    } else if (direction == DOWN) {
        next_y++;
    } else if (direction == LEFT) {
        next_x--;
    } else if (direction == RIGHT) {
        next_x++;
    } else {
        // error if invalid direction
        return MOVED_INVALID_DIRECTION;
    }

    if (next_y < 0 || next_y >= height || next_x < 0 || next_x >= width) {
        return MOVED_WALL; // treat outside the map as a wall
    }

    if (map[(next_y * width) + next_x] == WALL) { //see if next tile is wall
        return MOVED_WALL;
    }

    // update map
    map[(*y * width) + *x] = EMPTY; //clear old character position
    map[(next_y * width) + next_x] = character; //set new character position

    // update pointers
    *y = next_y;
    *x = next_x;

    return MOVED_OKAY;
}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // call move_character twice or until a wall is hit
    // when the wall is hit, move the Minotaur into the wall in the direction it is charging
    // calculate the new coordinates

    //error if charge direction not in expected directions
    if (charge_direction != UP && charge_direction != DOWN &&
        charge_direction != LEFT && charge_direction != RIGHT) {
        return MOVED_INVALID_DIRECTION;
    }

    //minotaur move 2 times
    for (int i = 0; i < MINOTAUR_CHARGE_STEP_SIZE; i++) {
        //move 1 tile in charge direction
        int status = move_character(y, x, charge_direction, MINOTAUR);

        //hits wall during charge
        if (status == MOVED_WALL) {
            int wall_y = *y;
            int wall_x = *x;

            //if charge (direction) then get the wall y and x to remove
            if (charge_direction == UP) {
                wall_y--;
            } else if (charge_direction == DOWN) {
                wall_y++;
            } else if (charge_direction == LEFT) {
                wall_x--;
            } else if (charge_direction == RIGHT) {
                wall_x++;
            }

            //check if wall within bound of map
            if (wall_y >= 0 && wall_y < height && wall_x >= 0 && wall_x < width) {
                // remove minotaur from its current position
                map[(*y * width) + *x] = EMPTY;
                //replace the wall with minotaur
                map[(wall_y * width) + wall_x] = MINOTAUR;
                // update the minotaur's coordinates to the new wall position
                *y = wall_y;
                *x = wall_x;
            }
            return MOVED_WALL;
        }

        // caught player
        if (*y == player_y && *x == player_x) {
            // minotaur is now at where player was
            map[(*y * width) + *x] = MINOTAUR;
            return CAUGHT_PLAYER; // return that player was caught
        }
    }
    return MOVED_OKAY; //okay if move without hitting wall or player just in case
}