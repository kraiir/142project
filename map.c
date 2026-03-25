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

void print_map(void) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // USE ELSE IF to ensure only ONE character is printed per coordinate



            // Pull the character (WALL or EMPTY) from the array
            char tile = map[(y * width) + x];
            printc(tile);


            // Space between columns - only use ONE or TWO spaces
            if (x < width - 1) {
                printf(" ");
            }
        }
        printf("\n");
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