// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;

int check_win(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    int dots = 0;
    //go through map and find how many dots are left
    for(int i = 0; i < width*height;i++){
        if(dot_map[i] == DOT){
            dots++;
        }
    }
    //checks win by seeing if there is only the dot underneath pacman left
    if(dots == 1 && dot_map[(pacman_y * width) + pacman_x] == DOT) {
        return YOU_WIN;
    }
    return KEEP_GOING;
}

int check_loss(int pacman_y, int pacman_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    //check loss by seeing is ghost postition and pacman location are the same
    if((pacman_x == ghosts_x[0] && pacman_y == ghosts_y[0]) || (pacman_x == ghosts_x[1] && pacman_y == ghosts_y[1])){
        return YOU_LOSE;
    }

    return KEEP_GOING;
}
