// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "ghost.h"

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int width, height;



/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PACMAN when no pacman is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */

int main(void) {
    setbuf(stdout, NULL);

    // read the contents of the file into map
    map = load_map(MAP_NAME, &width, &height);
    dot_map = load_dot_map(MAP_NAME, &width, &height);


    printMap();

    char userInput;

    // variables for pacman
    int *x = malloc(sizeof(int));
    int *y = malloc(sizeof(int));

    // find position of pacman in the map
    find_pacman_position(map,width, height, PACMAN, x, y);

    // variables for ghosts
    int xGhost[NUM_GHOSTS];
    int yGhost[NUM_GHOSTS];

    // find positions of ghosts in the map
    find_ghost_positions((char *)map, width, height, GHOST, xGhost, yGhost);

    // while loop that breaks when game ends
    while (1) {

        // check if loss
        if (check_loss(*y, *x, yGhost, xGhost)){
            printf("Sorry, you lose.");

            // free variables
            free(map);
            free(dot_map);
            free(x);
            free(y);
            return NO_ERROR;
        }
        if (check_win(*y, *x, yGhost, xGhost)){
            printf("Congratulation! You Win!");

            // free variables
            free(map);
            free(dot_map);
            free(x);
            free(y);
            return NO_ERROR;
        }

        // check if win ( to me made later )

        // get user input
        userInput = getch();


//            printf("\n Player position: %d, %d\n", *x, *y);

        // Code to move ghost
        for(int i = 0; i < 2; i ++) {

            // check if ghost sees pacman
            char direction = sees_pacman((int) *y, (int) *x, (int) yGhost[i], (int) xGhost[i]);
//                printf("\nSees pacman number %d: %c\n", i, direction);

            // if does not see pacman, move randomly
            if(direction == SEES_NOTHING){
                char a = random_move();
//                    printf("DIRECTION random by pacman %d: %c",i, a);
                int moveGhost = move_actor(&yGhost[i],&xGhost[i], a, REPLACE_DOTS);

            }
                // if ghost sees pacman move in direction of pacman
            else{
                int moveGhost = move_actor(&yGhost[i],&xGhost[i], direction, REPLACE_DOTS );
//                    printf("\n Ghost position: %d, %d\n", yGhost[i], xGhost[i]);

            }
        }
        // end of code to move ghost

        // move pacman
        int move = move_actor(y, x, userInput, 1);

        // if pacman moves out of bounds
        if(move == MOVED_INVALID_DIRECTION){
            printMap();
            continue;
        }

        // print out the map
        printMap();

    }

}

