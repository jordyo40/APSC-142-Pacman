// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "ghost.h"
#include "stdlib.h" //added myself
#include <time.h>

// I added these extern myself
extern char *map, *dot_map;
extern int width, height;

char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {

    // check to see if in same row
    if(pacman_y == ghost_y){

        int increment;
        int index = 1;

        // check to see is ghost is right or left of pacman
        if(pacman_x > ghost_x){
            increment = 1;
        }
        if(pacman_x < ghost_x){
            increment = -1;
        }

        // run loop is the spot on the map is not out of bounds
        while(ghost_x + increment*index >= 0 && ghost_x + increment*index <= 8){

            // check to see if the spot is a wall
            if(map[ghost_y*width + ghost_x+increment*index] == WALL){
                return SEES_NOTHING;
            }

                // check to see if the spot is pacman
            else if(map[ghost_y*width + ghost_x+increment*index] == PACMAN){
                if(pacman_x < ghost_x)
                    return LEFT;
                if(pacman_x > ghost_x)
                    return RIGHT;
            }

            index++;

        }

    }

    // Check to see if in same column
    if(pacman_x == ghost_x){

        int increment;
        int index = 1;

        // check to see is ghost is above or below pacman
        if(pacman_y > ghost_y){
            increment = 1;
        }
        if(pacman_y < ghost_y){
            increment = -1;
        }

        // run loop is the spot on the map is not out of bounds
        while(ghost_y + increment*index >= 0 && ghost_y + increment*index <= 8){

            // check to see if the spot is a wall
            if(map[ghost_y*width + width*increment*index] == WALL){
                return SEES_NOTHING;
            }

                // check to see if the spot is pacman
            else if(map[ghost_y*width + width*increment*index + ghost_x] == PACMAN){
                if(pacman_y < ghost_y)
                    return UP;
                if(pacman_y > ghost_y)
                    return DOWN;
            }

            index++;

        }

    }

    return SEES_NOTHING;
}

