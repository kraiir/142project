// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "character.h"
#include "game.h"
char *map = NULL;
int width, height;
    int player_x, player_y;
    int minotaur_x, minotaur_y;

}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */




TEST_CASE("Manual movement") {
    width = 3; height = 3;
    char fake_map[] = {'W', 'W', 'W',
                       'W', ' ', 'W',
                       'W', 'W', 'W'};
    map = fake_map;
    int py = 1; int px = 1;
    int result = move_character(&py, &px, 'w', 'P');
    CHECK(result == MOVED_WALL);
    CHECK(py == 1);
    CHECK(px == 1);
}

// Tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");
TEST_CASE("move_character - All outcomes") {
    width = 3; height = 1;
    char test_map[] = {'P', ' ', 'W'};
    map = test_map;
    int py = 0, px = 0;

    // 1. Invalid direction (covers first if)
    CHECK(move_character(&py, &px, 'z', PLAYER) == MOVED_INVALID_DIRECTION);

    // 2. Move OK (covers empty space logic and map update)
    CHECK(move_character(&py, &px, 'd', PLAYER) == MOVED_OKAY);
    CHECK(px == 1);
    CHECK(test_map[0] == ' ');
    CHECK(test_map[1] == PLAYER);

    // 3. Hit Wall (covers wall collision branch)
    CHECK(move_character(&py, &px, 'd', PLAYER) == MOVED_WALL);
}

// tests for move_character
TEST_SUITE_BEGIN("move_character");
TEST_CASE("test for load_map") {

}

TEST_SUITE_END();

// tests for locate_character
TEST_CASE("test for locate_character") {
    width = 2; height = 1;
    char m[] = {MINOTAUR, PLAYER};
    map = m;
    int y, x;
    CHECK(locate_character(PLAYER, &y, &x) == FOUND_CHARACTER);
    CHECK(x == 1); CHECK(y == 0);
    CHECK(locate_character('X', &y, &x) == CHARACTER_NOT_FOUND);
}
TEST_SUITE_END();

// tests for charge_minotaur
TEST_SUITE_BEGIN("charge_minotaur");
TEST_CASE("test for charge_minotaur") {
    int y = 0, x = 0;

    // 1. Invalid direction
    CHECK(charge_minotaur(&y, &x, 0, 3, 'z') == MOVED_INVALID_DIRECTION);

    // 2. Catch player
    char m1[] = {MINOTAUR, EMPTY, PLAYER, EMPTY};
    map = m1; y = 0; x = 0;
    CHECK(charge_minotaur(&y, &x, 0, 2, RIGHT) == CAUGHT_PLAYER);

    // 3. Hit wall (destroys it)
    char m2[] = {MINOTAUR, EMPTY, WALL, EMPTY};
    map = m2; y = 0; x = 0;
    CHECK(charge_minotaur(&y, &x, 0, 5, RIGHT) == MOVED_WALL);
}
TEST_CASE("charge_minotaur - Long charge to wall") {
    width = 5; height = 1;
    // Index: 0 1 2 3 4
    // Map:   M _ _ _ W
    char m_long[] = {MINOTAUR, EMPTY, EMPTY, EMPTY, WALL};
    map = m_long;
    int my = 0, mx = 0;

    CHECK(charge_minotaur(&my, &mx, 0, 10, RIGHT) == MOVED_OKAY);
    CHECK(mx == 1);

    while (charge_minotaur(&my, &mx, 0, 10, RIGHT) == MOVED_OKAY);

    CHECK(mx == 3);
    CHECK(map[3] == MINOTAUR);
}

TEST_SUITE_END();

// tests for sees_player
TEST_SUITE_BEGIN("sees_player");
TEST_CASE("RIGHT") {
    width = 4; height = 1;
    char m[] = {MINOTAUR, EMPTY, EMPTY, PLAYER};
    map = m;
    CHECK(sees_player(0, 3, 0, 0) == RIGHT);
}

TEST_CASE("LEFT") {
    width = 4; height = 1;
    char m[] = {PLAYER, EMPTY, EMPTY, MINOTAUR};
    map = m;
    CHECK(sees_player(0, 0, 0, 3) == LEFT);
}

TEST_CASE("DOWN") {
    width = 1; height = 3;
    char m[] = {MINOTAUR, EMPTY, PLAYER};
    map = m;
    CHECK(sees_player(2, 0, 0, 0) == DOWN);
}

TEST_CASE("UP") {
    width = 1; height = 3;
    char m[] = {PLAYER, EMPTY, MINOTAUR};
    map = m;
    CHECK(sees_player(0, 0, 2, 0) == UP);
}

TEST_CASE("wall horizontal") {
    width = 4; height = 1;
    char m[] = {MINOTAUR, WALL, EMPTY, PLAYER};
    map = m;
    CHECK(sees_player(0, 3, 0, 0) == SEES_NOTHING);
}

TEST_CASE("wall vertical") {
    width = 1; height = 3;
    char m[] = {MINOTAUR, WALL, PLAYER};
    map = m;
    CHECK(sees_player(2, 0, 0, 0) == SEES_NOTHING);
}

TEST_CASE("no line of sight diagonal") {
    width = 2; height = 2;
    char m[] = {MINOTAUR, EMPTY, EMPTY, PLAYER};
    map = m;
    CHECK(sees_player(1, 1, 0, 0) == SEES_NOTHING);
}
TEST_SUITE_END();

// tests for check_win
TEST_CASE("Testing for win") {
    width = 10;
    height = 10;
    // Adds global values so the test has something to test against
    CHECK(check_win(5,5) == KEEP_GOING);
    // Keeps going because not outside the width
    CHECK(check_win(5,10) == YOU_WIN);
    // Won because outside
    CHECK(check_win(-1,5) == YOU_WIN);
    // Won because outside
}

// test for check_loss
TEST_CASE("Testing for loss") {
    CHECK(check_loss(3,3,3,3) == YOU_LOSE);
    // Lost because same position
    CHECK(check_loss(3,3,1,1) == KEEP_GOING);
    // Keeps going because not same position
}

// test for load map
TEST_CASE("load_map - File does not exist") {
    int h, w;
    // Add (char *) before the string to remove the warning
    char* result = load_map((char *)"fakefile.txt", &h, &w);
    CHECK(result == NULL);
}

TEST_CASE("load_map - Successful load") {
    int h = 0, w = 0;
    // Add (char *) here as well
    char* result = load_map((char *)"map.txt", &h, &w);
    if (result != NULL) {
        CHECK(h > 0);
        CHECK(w > 0);
        free(result);
    }
}