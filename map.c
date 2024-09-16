// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

extern char *map, *dot_map;
extern int width, height;

int move_actor(int * y, int * x, char direction, int eat_dots) {
    int temp_y = *y;
    int temp_x = *x;
//    printf("\n %d, %d\n",(int) *x,(int)(*y));
//move temp location variables
    if(direction == LEFT){
        temp_x--;
    } else if(direction == RIGHT){
        temp_x++;
    } else if(direction == UP){
        temp_y--;
    } else if(direction == DOWN){
        temp_y++;
    } else{
        return MOVED_INVALID_DIRECTION;
    }

    if(is_wall(temp_y, temp_x)){
        return MOVED_WALL;
    }

    if(eat_dots){
        dot_map[(*y*width) + *x] = EMPTY;
    }

    // set the character to the moved position
    map[(temp_y*width)+temp_x] = map[(*y * width) + *x];
    map[(*y * width) + *x] = dot_map[(*y * width) + *x];

    if(!eat_dots){
        map[(temp_y * width) + temp_x] = GHOST;
    }
    //set location with the moved temp variables
    *y = temp_y;
    *x = temp_x;

    return MOVED_OKAY;
}

int is_wall(int y, int x) {

    //check if wall
    if(map[y*width + x] == 'W') {
        return YES_WALL;
    }

    // check if out of bounds wall
    else if(y > width -1 || y < 0 || x > height -1 || x < 0) {
        return YES_WALL;
    }

    return NOT_WALL;
}

// loads the map
char  *load_map(char * filename, int* map_height, int* map_width) {

    FILE *pFile = NULL; //initialize the file pointer

    pFile = fopen(filename, "r");//set pointer to file
    if (pFile == NULL) {
        printf("The file was not found\n");
        return NULL; //Non-zero return to show error has occurred
    }
    char temp;
    int index = 0, count = 2, currentWidth = 0, tempHeight = 1, tempWidth = 0;
    //loop through until end of file and increase width as you go across
    while ((temp = getc(pFile)) != EOF) {
        if (temp != '\n' && count == 2) {
            currentWidth++;
            count = 0;
        }
        //find how wide with whenever a new line is added, reset temporary width and increase map height
        if (temp == '\n') {
            tempWidth = currentWidth;
            tempHeight++;
            count = 2;
            currentWidth = 0;
            //if empty space is present add to the count to only take 1 of 3 characters
        } else if (temp == ' ') {
            count++;
        }
    }
    //same as top part but with a different temporary variable
    char other;
    count = 2;
    char *fake_map = malloc(tempWidth * tempHeight * sizeof(char));
    fclose(pFile);
    pFile = NULL;
    pFile = fopen(filename, "r");//set pointer to file
    if (pFile == NULL) {
        printf("The file was not found\n");
        return NULL; //Non-zero return to show error has occurred
    }
    //same while condition as earlier but this loop places the characters in the map array
    while ((other = getc(pFile)) != EOF) {
        if (other != '\n' && count == 2) {
            count = 0;
            fake_map[index] = other;
            index++;
        }
        if (other == '\n') {
            count = 2;
        } else if (other == ' ') {
            count++;
        }
    }
    *map_height = tempHeight;
    *map_width = tempWidth;

    //close file, return the map
    fclose(pFile);
    pFile = NULL;
    return fake_map;

}

// prints the map
void printMap(){

    // get the bottom walls
    int counter = 0;
    for(int j = 0; j < width + 2; j++ ){
        printf("W ");
    }
    printf("\n");
    printf("W ");

    // print the map with outer walls
    for(int i = 0; i < (width * height); i++) {

        printf("%c ", map[i]);hub

        counter++;
        if (counter == width) {
            printf("W ");
            printf("\n");
            printf("W ");
            counter = 0;
        }
    }

    // print the bottom walls of the map
    for(int k = 0; k < width + 1; k++ ){
        printf("W ");
    }
    printf("\n");
    printf("\n");

}

// loads dot map
char * load_dot_map(char * filename, int *map_height, int *map_width) {
    char * fake_dot_map = malloc(width * height * sizeof(char));

    // save only the dots
    for (int i = 0; i < width * height; i++) {
        if (map[i] == DOT || map[i] == GHOST) {
            fake_dot_map[i] = DOT;
            continue;
        } else
            fake_dot_map[i] = EMPTY;
    }

    return fake_dot_map;
}
// gives random direction
char random_move(){


    int random;
    char move;

    //randomly pick a direction with the rand function
    //will return a number from 0-3 and use that to pick direction
    random  = rand() % 4;
    switch(random) {
        case 0:
            move = UP;
            break;
        case 1:
            move = RIGHT;
            break;
        case 2:
            move = DOWN;
            break;
        case 3:
            move = LEFT;

            break;
        default:
            return '0';

    }
    return move;

}

// find the pacmans position
void find_pacman_position(char *map, int map_width, int map_height, char character, int *x, int *y) {
    *x = -1;
    *y = -1;

    // find the point where the character P is found
    for (int row = 0; row < map_height; row++) {
        for (int col = 0; col < map_width; col++) {
            if (map[row * map_width + col] == character) {
                // set to x and y
                *x = col;
                *y = row;
                return; // exit once character is found
            }
        }
    }
}

// find the ghosts position and updates the position variables
void find_ghost_positions(char *map, int map_width, int map_height, char ghost_char, int xGhost[], int yGhost[]) {
    int ghost_count = 0;

    // find the point where the character G is found
    for (int row = 0; row < map_height; row++) {
        for (int col = 0; col < map_width; col++) {
            if (map[row * map_width + col] == ghost_char && ghost_count < NUM_GHOSTS) {
                // set to xGhost yGhost values for NUM_GHOST index
                xGhost[ghost_count] = col;
                yGhost[ghost_count] = row;
                ghost_count++;
            }
        }
    }
}