// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#ifndef PROJECT_CHARACTER_H
#define PROJECT_CHARACTER_H

/** Functions required to be implemented **/

#define SEES_NOTHING 0
#define CAUGHT_PLAYER 1
/**
 * Checks if the Minotaur can see the player, and in what direction it must
 * look to see them.
 * This function should use the passed coordinates of player and the
 * Minotaur to see if the Minotaur can see the player by looking in a straight
 * line without looking through a wall.  The function can assume that
 * the global map / height / width are valid.
 *
 * If the Minotaur can the see player without looking through a wall, the
 * function should return the direction that the Minotaur must look to see
 * them (LEFT, RIGHT, UP, DOWN) as defined in defines.h.  If the Minotaur has
 * caught the player, the function should return CAUGHT_PLAYER.  If
 * the Minotaur cannot see the player, the function should return SEES_NOTHING.
 * @param player_y Player's Y coordinate
 * @param player_x Player's X coordinate
 * @param minotaur_y The Minotaur's Y coordinate
 * @param minotaur_x The Minotaur's X coordinate
 * @return The direction the Minotaur must look to see player, if possible.
 *         Otherwise, a status code.
 */
char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x);

#define MOVED_OKAY 0
#define MOVED_WALL 1
#define MOVED_INVALID_DIRECTION 2

/**
 * Try to move the character at the given coordinates, respecting walls.
 * This function is passed the coordinates of the character.  The function
 * also takes a direction that the character should move (UP, DOWN, LEFT,
 * RIGHT) defined in defines.h.
 * The coordinates are passed by reference so that they can be updated
 * by the function, while the return of the function is a status code.
 *
 * If the move is valid, the function must update map to move the character.
 * The old location of the character must be replaced by EMPTY and the new
 * location must be updated to hold the symbol (either PLAYER or MINOTAUR)
 * given in the character parameter.
 *
 * If the character cannot move because it would run into a wall, the
 * function should return MOVED_WALL and not update the map or the
 * coordinate pointers.  If the direction that was passed was not a
 * valid direction, the function should return MOVED_INVALID_DIRECTION.
 * If the function successfully moves the character, it should return
 * MOVED_OKAY.
 *
 * Preconditions: y and x must not be NULL
 * Postconditions: If the move is valid, y and x will be updated with
 *   the new coordinates, map will be updated at the old location with EMPTY,
 *   and the the new location will be filled with the symbol in character. Returns MOVED_OKAY.
 *   If the move is invalid, none of those updates will occur and the
 *   function will return the appropriate status code: MOVED_WALL or
 *   MOVED_INVALID_DIRECTION.
 *
 * @param y A pointer to the Y position of the character to move
 * @param x A pointer to the X position of the character to move
 * @param direction The direction to try to move
 * @param character The character to move (either PLAYER or MINOTAUR)
 * @return A status code depending on the result of the function
 */
int move_character(int *y, int *x, char direction, char character);

/**
 *
 * Move the Minotaur 2 spaces at a time in the direction given by
 * the direction parameter. The function should update the passed by reference
 * coordinate pointers and map to reflect the movement. When the Minotaur
 * encounters a wall, it will need to destroy it by replacing it with the MINOTAUR
 * symbol. The function should return the MOVED_WALL status code when this occurs.
 *
 * If an invalid movement direction is passed in the direction parameter,
 * the function should return MOVED_INVALID_DIRECTION. When no wall is
 * encountered, the function should return MOVED_OK.
 *
 * @param y The y coordinate of the minotaur
 * @param x The x coordinate of the minotaur
 * @param direction The direction to move the minotaur
 * @return A status code depending on the result of the function
 */
int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction);

/** Other function prototypes can go below here **/


#endif //PROJECT_CHARACTER_H
