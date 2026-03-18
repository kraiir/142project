// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

// These definitions help make your code more readable
// first, the symbols that may appear
#define PLAYER 'P'
#define MINOTAUR 'M'
#define WALL 'W'
#define EMPTY ' '
// then, the keys that are valid inputs
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

// some constants that may be useful
#define MAP_NAME "map.txt"
#define PLAYER_VISION_DISTANCE 2
#define MINOTAUR_CHARGE_STEP_SIZE 2

// error codes that you need to use in your program
#define NO_ERROR 0
#define ERR_NO_MAP 1
#define ERR_NO_PLAYER 2
#define ERR_NO_MINOTAUR 3
#define ERR_MEMORY 4

#endif //PROJECT_DEFINES_H
