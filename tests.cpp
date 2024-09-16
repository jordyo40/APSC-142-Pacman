// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "ghost.h"
#include "game.h"
char *map = NULL, *dot_map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

// setup, setup function
void setup(void) {

    map = load_map(MAP_NAME, &height, &width);
    dot_map = load_dot_map(MAP_NAME, &height, &width);

}

// setup teardown function
void teardown(void) {

    free(map);
    free(dot_map);

}

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {
    setup();

    // code from load map
    int map_height = 0;
    int map_width = 0;

    // Assume the file name is "map.txt"
    // Call the load_map function
    char *loaded_map = load_map(MAP_NAME, &map_height, &map_width);

    // Check if the loaded_map pointer is not NULL (indicating successful load)
    CHECK(loaded_map != NULL);

    // Check the dimensions of the loaded map
    // This is assuming that we know the size is 9x9
    CHECK(map_height == 9);
    CHECK(map_width == 9);

    // Check if pacman and ghosts are here
    CHECK(loaded_map[0] == 'G');
    CHECK(loaded_map[map_width * map_height] == 'G');
    CHECK(loaded_map[map_height/2*map_width + map_width/2] == 'P');

    teardown();
}

// tests for is_wall
TEST_CASE("A test for is_wall") {

    // Test known walls
    CHECK(is_wall(1,1) == YES_WALL);
    CHECK(is_wall(7,7) == YES_WALL);

    // Test out of bounds
    CHECK(is_wall(-1,0 == NOT_WALL));
    CHECK(is_wall(10,9 == NOT_WALL));

    // Test non-wall locations
    CHECK(is_wall(0,0) == NOT_WALL);
    CHECK(is_wall(8,8) == NOT_WALL);

}

// tests for move_actor
TEST_CASE("A test for move_actor"){

    // code from load map
    int map_height = 0;
    int map_width = 0;

    // put pacman in a position to move all 4 directions
    int x = width/2-2;
    int y = height/2;

    // if the actor is pacman
    // check horizontal movement and if eats dots
    int move = move_actor(&y, &x, LEFT, EAT_DOTS);
    CHECK(move == MOVED_OKAY);
    CHECK(y == height/2);
    CHECK(x == width/2 - 3);
    CHECK(map[width/2-2 + (height/2)*width] == EMPTY);

    // check vertical movement and if eats dots
    move = move_actor(&y, &x, DOWN, EAT_DOTS);
    CHECK(move == MOVED_OKAY);
    CHECK(y == height/2 + width);
    CHECK(x == width/2);
    CHECK(map[width/2-2 + (height/2)*width] == EMPTY);

    // testing movement into a wall
    move = move_actor(&y, &x, DOWN, EAT_DOTS);
    CHECK(move == MOVED_WALL);
    CHECK(y == height/2);
    CHECK(x == width/2);

    // if the actor is a ghost
    int xG = 0;
    int yG = 0;

    // check if the ghost will replace dots and move down
    move = move_actor(&yG, &xG, DOWN, REPLACE_DOTS);
    CHECK(dot_map[0] == DOT);
    CHECK(move == MOVED_OKAY);
    CHECK(yG == 1);
    CHECK(xG == 0);

}

TEST_SUITE_END();

/* tests for ghost.c */
TEST_SUITE_BEGIN("Ghost tests");

// tests for sees_pacman
TEST_CASE("A test for sees_pacman"){

    // if there is wall inbetween characters
    int pacman_y = 4;
    int pacman_x = 4;
    int ghost1_y = 0;
    int ghost1_x = 0;
    map[pacman_y*width + pacman_x] = PACMAN;
    map[ghost1_y*width + ghost1_x] = GHOST;
    CHECK(sees_pacman(pacman_y, pacman_x, ghost1_y, ghost1_x) == SEES_NOTHING);

    // if pacman is seen vertically by ghost
    pacman_y = 2;
    pacman_x = 2;
    ghost1_y = 4;
    ghost1_x = 2;
    map[pacman_y*width + pacman_x] = PACMAN;
    map[ghost1_y*width + ghost1_x] = GHOST;
    CHECK(sees_pacman(pacman_y, pacman_x, ghost1_y, ghost1_x) == UP);

    // if pacman is seen horizontally by ghost
    pacman_y = 0;
    pacman_x = 0;
    ghost1_y = 0;
    ghost1_x = 3;
    map[pacman_y*width + pacman_x] = PACMAN;
    map[ghost1_y*width + ghost1_x] = GHOST;
    CHECK(sees_pacman(pacman_y, pacman_x, ghost1_y, ghost1_x) == LEFT);

}

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
TEST_CASE("A test for check_win"){

    // arbitrary numbers used for ghosts positions since not used in the function

    // pacman still has dots left
    CHECK(check_win(0,1, 0, 0) == KEEP_GOING);

    // make the dotmap empty
    for(int i = 0; i<width*height; i++){
        if(dot_map[i]==DOT){
            dot_map[i] = EMPTY;
        }
    }

    CHECK(check_win(0,1,0,0) == YOU_WIN);
}

// test for check_loss
TEST_CASE("A test for check_loss"){
    CHECK(check_loss(0,0,0,0) == YOU_LOSE);
    CHECK(check_loss(4,4,0,0) == KEEP_GOING);
}

TEST_SUITE_END();