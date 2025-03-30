#ifndef FUNCTION_H
#define FUNCTION_H


#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include <time.h>




// The init function is used to initialize the SDL2 modules like video, audio. It creates window and renderer. It creates a 
// 2-D array of rectangles. It creates an array of size 5 for 5 different terminos.
bool init(SDL_Window** window, SDL_Renderer** renderer, Rectangle rectangles[12][16], Termino terminos[]);


// Thc close function is used after the game is finished, it destroys the window and renderer.
// It also prints the score of the game.
void close (SDL_Window* window,  SDL_Renderer* renderer, int * score);


// the randomNumber function is used for generating a random number between minNum and maxNum.
int randomNumber(int minNum, int maxNum);


// The SDL_RenderLines function is used for rendering the white lines of the game.
void SDL_RenderLines(SDL_Renderer** renderer);


// The update function is used for updating the coordinates of the current termino based on the movement.
char* update(Termino *termino, int frameDelay, int frameStart, Movement movement, Rectangle rectangles[12][16]);


// The destroyRow function is used for destroying rows of the rectangles that has a full line of termino rectangles.
bool destroyRow(Rectangle rectangles[12][16], int * score);


// The update function is calling this function to check if the new position will not collide with other terminos or the game borders. 
static Status checkCollision(Termino termino, Movement movement, Rectangle rectangles[12][16]);


// The checkRectanglesColor function is used by checkCollision function for checking if a specific rectangle has a specific
// RGB color or not.
static bool checkRectanglesColor (Rectangle rectangles[12][16], int col, int row, int r, int g, int b);


// The SDL_RenderRectangles is used for rendering the 2-D array of rectangles.
void SDL_RenderRectangles(SDL_Renderer** renderer, Rectangle rectangles[12][16]);


// The SDL_RenderTermino is used for rendering the rectangles of the current termino.
void SDL_RenderTermino(SDL_Renderer** renderer, Termino termino);

/* These functions are used to update the position of the termino based on the movement
    updateI: updates the position of the I termino
    updateT: updates the position of the T termino
    updateL: updates the position of the L termino
    updateZ: updates the position of the Z termino
    updateO: updates the position of the O termino
*/

static Status updateI (Termino *termino, Movement movement, Rectangle rectangles[12][16]);
static Status updateT (Termino *termino, Movement movement, Rectangle rectangles[12][16]);
static Status updateL (Termino *termino, Movement movement, Rectangle rectangles[12][16]);
static Status updateZ (Termino *termino, Movement movement, Rectangle rectangles[12][16]);
static Status updateO (Termino *termino, Movement movement, Rectangle rectangles[12][16]);



#endif