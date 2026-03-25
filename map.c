// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

#define BUFFER_SIZE 10


extern char *map;
extern int width, height;
extern int player_y, player_x;
extern int minotaur_y, minotaur_x;

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param c
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case MINOTAUR:
            change_text_colour(MAGENTA);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        default:
            change_text_colour(WHITE);
    }
    printf("%c", c);
}

void print_map(void){
    // Print the map given in the global map variable
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++)
        {
            // Using nested loops goes through rows and columns to go to every point on the array
            if (y == player_y && x == player_x) {
                // Checks if the current part of the map has the same coordinates as where the player should be
                printc(PLAYER);
            }
            else if (y == minotaur_y && x == minotaur_x) {
                // Checks if the current part of the map has the same coordinates as where the minotaur should be
                // Only if the player isn't already at the location
                printc(MINOTAUR);
            }
            else {
                // If neither is on, then copies what was there previously (wall or blank)
                for (int col = 0; col < width; col++){

                }
                char tile = map[(y * width) + x];
                printc(tile);
            }
            if (COL < width - 1)
            {
                printf(" ");
            }
            // Adds a space between each part per formatting
        }
        printf("\n");
        // Adds a new line between each part per formatting
    }
}

void print_revealed_map(int player_y, int player_x) {
    // Only the map within PLAYER_VISION_DISTANCE of the player (including diagonals) should be printed
}

int locate_character(char character, int* character_y, int* character_x) {
    for (int i = 0; i < (width * height); i++) {
        if (map[i] == character) {
            *character_y = i / width;
            *character_x = i % width;
            return FOUND_CHARACTER;
        }
    }
    return CHARACTER_NOT_FOUND;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    return NULL;
}