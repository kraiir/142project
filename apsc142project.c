// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

// Don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and character.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "character.h"

void update_minotaur(int player_y, int player_x, int *minotaur_y, int *minotaur_x, char *charge_direction);

void print_map();
int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x);
int check_win(int player_y, int player_x);
int move_character(int * y, int * x, char direction, char character_symbol);
int locate_character(char character, int * character_y, int * character_x);
int charge_minotaur(int *minotaur_y, int *minotaur_x, int player_y, int player_x, char charge_direction);
char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x);
char *load_map(char * filename, int * map_height, int * map_width);
void print_revealed_map(int player_y, int player_x);

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
char *map = NULL;
// width and height store the width and height of map
int width, height;

/**
 * This is the hardcoded map used for labs 1-3.
 * Once you implement load_map in lab 4 you should remove this map, as it cannot be used for the
 * final version of the project.
 * The map's dimensions are 11x12
 */
#define HARDCODED_WIDTH 11
#define HARDCODED_HEIGHT 12
char hardcoded_map[] = {
    WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL,
    WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,
    WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL,
    WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL,
    WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL,
    WALL, EMPTY, EMPTY, EMPTY, EMPTY, PLAYER, EMPTY, EMPTY, WALL, EMPTY, WALL,
    WALL, EMPTY, WALL, EMPTY, WALL, WALL, WALL, EMPTY, WALL, EMPTY, WALL,
    WALL, EMPTY, WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, WALL,
    WALL, EMPTY, WALL, WALL, EMPTY, WALL, EMPTY, WALL, WALL, EMPTY, WALL,
    WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL, EMPTY, EMPTY, MINOTAUR, EMPTY, WALL,
    WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL,
    WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL
};
// You are NOT allowed to add more global variables!
// The globals that are included in the starter code provide a convenient way to share information
// between the many functions that all need access to the same data, but all other data must be
// passed using function arguments.  If you add new globals, the autograder tests will fail to run
// and you will not receive a good mark.

/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PLAYER when no player is found on the map
 *   ERR_NO_MINOTAUR when no Minotaur is found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    // This ensures that printf writes to the console immediately, instead of buffering
    // If you remove this, you will not be able to rely on printf to work if your program crashes
    setbuf(stdout, NULL);

    // The Minotaur's current charge direction. When this is equal to SEES_NOTHING, the Minotaur
    // should randomly move around 1 tile per turn
    char charge_direction = SEES_NOTHING;

    // Set the width and height for the hardcoded map
    width = HARDCODED_WIDTH;
    height = HARDCODED_HEIGHT;
    // Use the hardcoded map by setting the global map variable equal to it
    map = hardcoded_map;

    // Eventually, the player position should be determined from the map, however, hardcode it for now
    int player_y = 5;
    int player_x = 5;

    // We also need the Minotaur position. Again, hardcode the starting position for now.
    int minotaur_y = 9;
    int minotaur_x = 8;

    // Loop until we hit the end of input
    // Input holds the user input
    char input = 0;
    while (input != EOF && input != 4) {
        // Print the map
        print_map();

        // Get a character - blocks until one is input
        input = getch();

        // update the minotaur
        update_minotaur(player_y, player_x, &minotaur_y, &minotaur_x, &charge_direction);

        // move the player only if they haven't been caught
        if (check_loss(player_y, player_x, minotaur_y, minotaur_x) == KEEP_GOING) {
            move_character(&player_y, &player_x, input, PLAYER);
        }
    } // quit if we hit the end of input

    // You must return the correct error code from defines.h from main depending on what happened
    return NO_ERROR;
}

void update_minotaur(int player_y, int player_x, int *minotaur_y, int *minotaur_x, char *charge_direction) {

    // If a charge is not in progress, see if the Minotaur can see the player
    if (*charge_direction == SEES_NOTHING) {
        char sight_direction = sees_player(player_y, player_x, *minotaur_y, *minotaur_x);
        if (sight_direction == CAUGHT_PLAYER) {
            return;
        }

        // If the Minotaur cannot see the player, move randomly
        if (sight_direction == SEES_NOTHING) {
            // get a random direction, keeping track of if we already tried it
            char tried_directions[] = {0, 0, 0, 0};
            char direction_map[] = {UP, LEFT, DOWN, RIGHT};
            int move_result;
            do {
                // get a random direction
                int direction_int = rand() % 4;
                // set that we tried the direction
                tried_directions[direction_int] = 1;
                // get the input direction to move
                char direction = direction_map[direction_int];
                // try it!
                move_result = move_character(minotaur_y, minotaur_x, direction, MINOTAUR);
                // if we try all the directions, bail out - we can't move
            } while (move_result != MOVED_OKAY &&
                     (!tried_directions[0] || !tried_directions[1] || !tried_directions[2] || !tried_directions[3]));
        } else {
            // The Minotaur sees the player, so initiate a charge
            *charge_direction = sight_direction;
        }
    }
    // If the Minotaur sees the player and hasn't caught them, we call the charge function
    if (!(*charge_direction == SEES_NOTHING || *charge_direction == CAUGHT_PLAYER)) {
        // Once the Minotaur hits a wall, the charge is ended. This is indicated by charge_minotaur returning
        // a MOVED_WALL return value
        int move_result = charge_minotaur(minotaur_y, minotaur_x, player_y, player_x, *charge_direction);
        if (move_result == MOVED_WALL) {
            *charge_direction = SEES_NOTHING;
        }
    }
}
