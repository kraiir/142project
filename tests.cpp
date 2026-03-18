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

/* Tests for map.c */

TEST_CASE("Testing for loss") {
    CHECK(check_loss(3,3,3,3) == YOU_LOSE);
    // Lost because same position
    CHECK(check_loss(3,3,1,1) == KEEP_GOING);
    // Keeps going because not same position
}

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

TEST_SUITE_BEGIN("Map tests");

// Tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");

// tests for move_character

// tests for locate_character

// tests for charge_minotaur

// tests for sees_player

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win

// test for check_loss

TEST_SUITE_END();
