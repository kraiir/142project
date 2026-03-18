// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

/** Functions required to be implemented **/

#define KEEP_GOING 0
#define YOU_WIN 1
/**
 * Returns if the game has been won or not.
 * Checks the position of the player to see if they are outside of the map or not.
 * The function can assume that the global map and width/height are valid.
 *
 * @param player_y The Y coordinate of player
 * @param player_x The X coordinate of player
 * @return YOU_WIN if the player is outside of the map, otherwise KEEP_GOING
 */
int check_win(int player_y, int player_x);

#define YOU_LOSE 1
/**
 * Returns if the game has been lost or not.
 * Compares the positions of the Minotaur with the position of
 * player to see if player has been caught.  If so, the function
 * should return YOU_LOSE.  If not, it should return KEEP_GOING.
 *
 * @param player_y The Y coordinate of player
 * @param player_x The X coordinate of player
 * @param minotaur_y The Y coordinate of the minotaur
 * @param minotaur_x The x coordinate of the minotaur
 * @return
 */
int check_loss(int player_y, int player_x, int minotaur_y, int minotaur_x);

/** Other function prototypes can go below here **/


#endif //PROJECT_GAME_H
