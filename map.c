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

            if (c != EMPTY) {
                c = ' ';
            }
    }
    printf("%c", c);
}

void print_map(void) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Pull the character (WALL or EMPTY) from the array
            char tile = map[(y * width) + x];
            printc(tile);

            // Space between columns
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
    FILE *fp = fopen(filename, "r"); //make a file pointer
    if (fp == NULL) {
        return NULL;
    }

    int rows = 0;
    int cols = 0;
    char line[1024]; //buffer to load map

    // find dimensions
    while (fgets(line, sizeof(line), fp)) {
        if (rows == 0) {
            // symbols are at indices 0, 3, 6... (because of the 2 spaces)
            // count how many characters are in the first line
            int line_len = 0;
            while (line[line_len] != '\n' && line[line_len] != '\r' && line[line_len] != '\0') {
                line_len++;
            }
            // ex: if length is 13 (W  W  W  W  W), (13+2)/3 = 5 symbols
            cols = (line_len + 2) / 3;
        }
        rows++;
    }
    fclose(fp); // close the file after counting

    if (rows == 0 || cols == 0) {
        return NULL;
    }

    // allocate memory
    char *new_map = (char *)malloc(rows * cols * sizeof(char));
    if (new_map == NULL) {
        return NULL;
    }

    // reopen and fill
    fp = fopen(filename, "r"); // reopening resets the file pointer to the start
    int r = 0;
    while (fgets(line, sizeof(line), fp) && r < rows) {
        // Only process non-empty lines
        if (line[0] != '\n' && line[0] != '\r') {
            for (int c = 0; c < cols; c++) {
                int char_index = c * 3;

                // 1. Check if the index is within the string we just read
                // 2. Make sure it's a valid symbol (not \0, \n, or \r)
                if (line[char_index] != '\0' && line[char_index] != '\n' && line[char_index] != '\r') {
                    new_map[r * cols + c] = line[char_index];
                } else {
                    // If the line is too short, fill the rest with EMPTY (' ')
                    // This ensures no "invisible" 0s are stored in your map
                    new_map[r * cols + c] = EMPTY;
                }
                // We use c * 3 to land exactly on the symbol
                // We also check to make sure we don't read past the end of 'line'
                //new_map[r * cols + c] = line[c * 3];
            }
            r++;
        }
    }
    fclose(fp);

    // set pass by reference values
    *map_height = rows;
    *map_width = cols;

    return new_map;
}