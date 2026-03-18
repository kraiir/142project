// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

/** Functions required to be implemented **/

/**
 * Prints the map using the global variables defined in apsc142project.c.
 * Preconditions: the map, width, and height globals can be
 * assumed to be valid.
 */
void print_map(void);

/**
 * Prints the partially revealed map using the global variables defined in apsc142project.c.
 * The map will only be revealed in regions which are within PLAYER_VISION_DISTANCE.
 * Preconditions: the map, width, and height globals can be
 * assumed to be valid. The player_y and player_x variables
 * can assumed to be valid and updated to the player's current
 * position.
 */
void print_revealed_map(int player_y, int player_x);


/**
 * Loads a map file into an array allocated dynamically to store it.
 * The function must allocate space using malloc/realloc and load
 * the map file contents into it.  The return value is the pointer
 * to the allocated and populated memory, and the height/width values
 * that are returned via the map_height/map_width pass-by-reference
 * parameters.
 *
 * The function can assume that the parameters are valid pointers, but
 * it should not assume that the file exists.  The map file format
 * is #__#__# ... __# where the # are symbols and _ represent whitespace
 * which should be ignored.  That is, the function can assume that
 * symbols are each separated by two spaces.  The function MAY NOT
 * assume that the map is a specific size; it must properly load any
 * size map in the correct format.  It can assume that the only valid
 * symbols are PLAYER, MINOTAUR, WALL, and EMPTY as defined in
 * defines.h.  The function can assume that the map is a rectangle with
 * boundary walls around the map perimeter.
 *
 * On error, the function should return NULL and should not write to
 * map_height or map_width.
 *
 * For example, if the map file contains the map:
 * W  W  W  W  W
 * W  P        W
 * W        M  W
 * W  W  W  W  W
 * Then the function should return a dynamically allocated array:
 * {'W', 'W', 'W', 'W', 'W', 'W', 'P', ' ', ' ', 'W', 'W', ' ', ' ', 'M', 'W', 'W', 'W', 'W', 'W', 'W'}
 * and set *map_height = 4, *map_width = 5.
 *
 * @param filename A string containing the map file name to read
 * @param map_height A pointer to where the map height should be stored
 * @param map_width A pointer to where the map width should be stored
 * @return A pointer to the loaded map, or NULL on error
 */
char * load_map(char * filename, int * map_height, int *map_width);


/**
 * Attempt to find a character, given by the parameter character, in the map.
 * The function can assume the map, character_y, and character_x are all valid.
 * If the character can be found, the character_x and character_y pointers to its
 * position.
 *
 * Return CHARACTER_NOT_FOUND if the character is not in the map and CHARACTER_FOUND
 * if they are.
 *
 * @param character_y The y position of the found character
 * @param character_x The x position of the found character
 * @param character The character to find
 *
 * @return One of CHARACTER_NOT_FOUND or FOUND_CHARACTER
 */
#define CHARACTER_NOT_FOUND 0
#define FOUND_CHARACTER 1
int locate_character(char character, int* character_y, int* character_x);

/** Other function prototypes can go below here **/


#endif //PROJECT_MAP_H
