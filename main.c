// Writer: Mustafa Sadiqi
// Application: It is a classic game called Tetris. I wrote my own Tetris game in C language using SDL2 library
// The game contains five unique blocks which are Terminos
// The purpose of the game is to create full line of colorized rectangles, each time, you create lines of termino rectangles,
// the lines will be removed. And based on the number of rectangles which were removed, you will get your score.
// You will lost the game, if the termino is stuck at the begining of the screen.
// Your score will be shown after the game is finished

/*
    The keys for interacting with the game:
        1- Up arrow key: used for right rotation of the termino.
        2- Down arrow key: used for left rotation of the termino.
        3- Right arrow key: used for right shifting of the termino.
        4- Left arrow key: used for left shifting of the termino.
        5- Space key: used for moving the termino down.
        6- Escape key: used for exiting the game.
*/

//Header Files
#include <SDL2/SDL.h> // The main graphics library for making the game.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"  // The user-defined header file containing the macros and structs.
#include "function.h"   // The user-defined header file containing the functions used for making the game.

// The functionality of each function is expressed in the function.h header file.

int main(int argc, char *argv[]) {


    bool running;                       // The flag used in the infinite loop of the game.
    SDL_Window* window = NULL;          // The window of the game.
    SDL_Renderer* renderer = NULL;      // The main renderer of the game.
    SDL_Event event;                    // The main event variable used for handling the event occurrences.
    Rectangle rectangles[12][16];       // The 2-D array containing the 192 rectangles which covers the whole window.
    Termino terminos[5];                // The array containing the five pre-defined terminos.
    Termino currentTermino;             // The currentTermino which is selected by random.


    int rowRect, colRect, wRect, hRect; // Used for storing the row, column, width and height of a rectangle. 
    char* flag = "start";               // Flag used for specifying Whether the current termino movement is finished or not.
    int FPS = 2.5;                      // Frame per Second.
    int frameDelay = 1000/FPS;          // The delay for each frame.
    int userInput = 0;                  // Used for storing the number of times the user presses a key.
    int terminoIndex;                   // Used for storing the random number which then be used as index for the array of terminos to select
                                        // a termino randomly.
    int score = 0;                      // Used for storing score of game. After the game is finished, it is printed.
    Movement movement;                  // Used for storing the next movement of the current termino: right, left or rotations
    Uint32 frameStart = 0;              // Used for storing the start frame of the game.
    

    if(init(&window, &renderer, rectangles, terminos)){  
        running = true;
    }
    else {
        running = false;
        printf("The game did not start!");
    }
    
    

    while(running) {

        userInput += 1;
        movement = noMove;

        if(strcmp(flag, "start") == 0) {
            terminoIndex = randomNumber(0, 4);      // generating a random number for selecting a termino randomly from the array of terminos.
            currentTermino = terminos[terminoIndex];
            flag = "running";
        }
        else if (strcmp(flag, "new") == 0){
            for(int i = 0 ;i < 4; i++) {
                // Used for storing the termino colors which has stopped, in the 2-D array.  
                    colRect = currentTermino.terminoRectangles[i].x/terminoRectPosX;
                    rowRect = currentTermino.terminoRectangles[i].y/terminoRectPosY;
                    wRect = currentTermino.terminoRectangles[i].w;
                    hRect = currentTermino.terminoRectangles[i].h;
                    SDL_Rect rect = {currentTermino.terminoRectangles[i].x, currentTermino.terminoRectangles[i].y, wRect, hRect};
                    rectangles[colRect][rowRect].rect = rect;
                    rectangles[colRect][rowRect].r = cyanR;
                    rectangles[colRect][rowRect].g = cyanG;
                    rectangles[colRect][rowRect].b = cyanB;
                
            }
                
            terminoIndex = randomNumber(0, 4); //generating a random number for selecting a termino randomly.
            currentTermino = terminos[terminoIndex];
            flag = "running";
        }
        else  if(strcmp(flag, "stop") == 0){
            // when the flag is "stop", it means the user lost the game and the 'running' boolean become false.
            running = false;
            break;
        }

        if(userInput){
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT) {
                    running = false;
                }
                if(event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:       // The Up arrow key is used for right rotation of the termino.
                        movement = rightRotation;
                        break;
                    case SDLK_DOWN:     // The down arrow key is used for left rotation of the termino.
                        movement = leftRotation;
                        break;
                    case SDLK_RIGHT:    // The right arrow key is used for right movement of the termino.
                        movement = moveRight;
                        break;
                    case SDLK_LEFT:     // The left arrow key is used for left movement of the termino.
                        movement = moveLeft;
                        break;
                    case SDLK_SPACE:    //  The space key is used down movement of the termino.
                        movement = moveDown;
                        break;
                    case SDLK_ESCAPE:   // The escape key is used for exiting the game.
                        running = false;
                        break;
                    default:
                        break;
                    }
                }
            }
            if(userInput == 3) {    // After three user key pressing, one moveDown movement is applied to the termino.
                userInput = -1;
            }
            
        }

                flag = update(&currentTermino, frameDelay, frameStart, movement, rectangles);
                SDL_RenderRectangles(&renderer, rectangles);
                SDL_RenderTermino(&renderer, currentTermino);
                SDL_RenderLines(&renderer);
                if(destroyRow(rectangles, &score)) {
                    SDL_RenderRectangles(&renderer, rectangles);
                    SDL_RenderTermino(&renderer, currentTermino);
                }
                

                SDL_RenderPresent(renderer);
                
    }
    close(window, renderer, &score);
    return 0;
}