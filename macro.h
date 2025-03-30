
#ifndef MACRO_H
#define MACRO_H
#include <SDL2/SDL.h>


    #define windowWidth  480
    #define windowHeight  640
    #define terminoRectPosX 40
    #define terminoRectPosY 40
    #define terminoRectWidth 40
    #define terminoRectHeight 40

// The RGB of colors used in the game

    #define blueR 0
    #define blueG 0
    #define blueB 255

    #define greenR 0
    #define greenG 255
    #define greenB 0

    #define redR 255
    #define redG 0
    #define redB 0

    #define yellowR 255
    #define yellowG 255
    #define yellowB 0

    #define purpleR 128
    #define purpleG 0
    #define purpleB 128

    #define blackR 0
    #define blackG 0
    #define blackB 0

    #define cyanR 0
    #define cyanG 255
    #define cyanB 255

    #define whiteR 255
    #define whiteG 255
    #define whiteB 255


// enum for specifying the movement of a termino.
    typedef enum movement {
        noMove,
        moveDown,
        moveRight,
        moveLeft,
        rightRotation,
        leftRotation
    } Movement;
// enum for specifying the shape of a termino.
    typedef enum terminoShape {
        I, 
        T,
        L,
        Z,
        O

    } TerminoShape;
// enum for specifying the direction of a termino.
    typedef enum terminoDirection {
        Up,
        Down,
        Right,
        Left
    } TerminoDirection;
// Termino struct.
    typedef struct Termino {
        SDL_Rect terminoRectangles[4];
        int r, g, b;
        int row, col;
        TerminoShape shape;
        TerminoDirection direction;

    } Termino;
// Rectangle struct.
    typedef struct Rectangle {
        SDL_Rect rect;
        int r, g, b;
    } Rectangle;

// enum for the status of a termino.
    typedef enum Status {
        STOP, 
        MOVING, 
        COLLIDED
    } Status;

#endif