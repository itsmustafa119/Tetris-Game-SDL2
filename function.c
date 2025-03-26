#include "function.h"
#include "macro.h"
#include <time.h>
bool init(SDL_Window** window, SDL_Renderer** renderer, Rectangle rectangles[12][16], Termino terminos[]) {
    bool success;
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
        *window = SDL_CreateWindow(" Tetris ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        *renderer = SDL_CreateRenderer(*window, -1, 0);
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 16; j++) {
                rectangles[i][j] = (Rectangle ) {(SDL_Rect){terminoRectPosX*i, terminoRectPosY*j, terminoRectWidth, terminoRectHeight}, blackR, blackG, blackB};
                
            }
        }
        terminos[0] = (Termino) {  {(SDL_Rect) {5*terminoRectPosX, 0*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 1*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 2*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 3*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight}},
                                    blueR, blueG, blueB,
                                    3, 6, I, Up};
        terminos[1] = (Termino) {  {(SDL_Rect) {5*terminoRectPosX, 0*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {4*terminoRectPosX, 1*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 1*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {6*terminoRectPosX, 1*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight}},
                                    redR, redG, redB,
                                    3, 6, T, Up};
        terminos[2] = (Termino) {  {(SDL_Rect) {5*terminoRectPosX, 0*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 1*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 2*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {6*terminoRectPosX, 2*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight}},
                                    greenR, greenG, greenB,
                                    3, 6, L, Up};
        terminos[3] = (Termino) {  {(SDL_Rect) {5*terminoRectPosX, 0*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {6*terminoRectPosX, 0*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {4*terminoRectPosX, 1*terminoRectPosY - terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 1*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight}},
                                    yellowR, yellowG, yellowB,
                                    3, 6, Z, Up};
        terminos[4] = (Termino) {  {(SDL_Rect) {5*terminoRectPosX, 0*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {6*terminoRectPosX, 0*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {5*terminoRectPosX, 1*terminoRectPosY- terminoRectPosY , terminoRectWidth, terminoRectHeight},
                                    (SDL_Rect) {6*terminoRectPosX, 1*terminoRectPosY- terminoRectPosY, terminoRectWidth, terminoRectHeight}},
                                    purpleR, purpleG, purpleB,
                                    3, 6, O, Up};
        SDL_SetRenderDrawColor( *renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( *renderer);
        success = true;
    }
    return success;
}

void close (SDL_Window* window,  SDL_Renderer* renderer, int * score) {

    printf("You lost! try again buddy!\n");
    printf("The score: %d ", *score);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int randomNumber(int minNum, int maxNum)
    {
        int result = 0, lowNum = 0, highNum = 0;

        if (minNum < maxNum)
        {
            lowNum = minNum;
            highNum = maxNum + 1; 
        } else {
            lowNum = maxNum + 1; 
            highNum = minNum;
        }

        srand(time(NULL));
        result = (rand() % (highNum - lowNum)) + lowNum;
        return result;
    }

void SDL_RenderTermino(SDL_Renderer** renderer, Termino termino) {
    
    SDL_SetRenderDrawColor(*renderer, termino.r, termino.g, termino.b, SDL_ALPHA_OPAQUE);
    for(int i = 0; i < 4; i++) {
        SDL_RenderFillRect(*renderer, &termino.terminoRectangles[i]);
    }
    
}
void SDL_RenderRectangles(SDL_Renderer** renderer, Rectangle rectangles[12][16]) {
    
    for(int i = 0; i < 12; i ++) {
        for( int j = 0; j < 16; j++) {
            SDL_SetRenderDrawColor(*renderer, rectangles[i][j].r, rectangles[i][j].g, rectangles[i][j].b, 255);
            SDL_RenderFillRect(*renderer, &rectangles[i][j].rect);
            
        }
    }
}
void SDL_RenderLines(SDL_Renderer** renderer) {
    SDL_SetRenderDrawColor(*renderer, whiteR, whiteG, whiteB, SDL_ALPHA_OPAQUE);
    for( int i = 0 ; i < 12; i++) {
        SDL_RenderDrawLine(*renderer, i*terminoRectPosX, 0, i*terminoRectPosX, windowHeight);
    }
    for( int i = 0 ; i < 16; i++) {
        SDL_RenderDrawLine(*renderer, 0, i*terminoRectPosY, windowWidth, i*terminoRectPosY);
    }
}
char* update(Termino *termino, int frameDelay, int frameStart, Movement movement, Rectangle rectangles[12][16]) {

    Termino currentTermino = *termino;
    Termino newTermino = *termino;
    Status status ;
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), 1000/60));

    frameStart = SDL_GetTicks();
    if(frameDelay > SDL_GetTicks() - frameStart) {
        SDL_Delay(frameDelay - (SDL_GetTicks() - frameStart));
    }

    
        
    switch (termino->shape)
    {
        case I:
            status = updateI(&newTermino, movement, rectangles);
            break;
        case T:
            status = updateT(&newTermino, movement, rectangles);
            break;
        case L:
            status = updateL(&newTermino, movement, rectangles);
            break;
        case Z:
            status = updateZ(&newTermino, movement, rectangles);
            break;
        case O:
            status = updateO(&newTermino, movement, rectangles);
            break;
        default:
            status = MOVING;
            break;
    }

    if( status == STOP){
        if(currentTermino.terminoRectangles[0].y + terminoRectPosY == 0) {
            return "stop";
        }
        *termino = currentTermino;
        return "new";
    }
    else if(status == MOVING) {
        
        *termino = newTermino;
        return "running";
    }
    else if(status == COLLIDED) {
        
        return "running";
    }
        frameStart = SDL_GetTicks();
    return "running";
}
bool destroyRow(Rectangle rectangles[12][16], int* score) {
bool flag = false;
int i , j;
int counter;
        for( i = 15; i >= 0; i--) {
            counter = 0;
            for(  j = 0; j < 12; j++) {
                if((rectangles[j][i].r == cyanR) && (rectangles[j][i].g == cyanG) && (rectangles[j][i].b == cyanB)) {
                    counter++;
                } 

            }
            if(counter == 12) {
                *score += 12;
                flag = true;
                for(j = 0; j < 12; j++) {
                    rectangles[j][i].r = blackR;
                    rectangles[j][i].g = blackG;
                    rectangles[j][i].b = blackB;
                }
                for(int p = i - 1 ; p >= 0 ; p--) {
                    for(j = 0; j < 12; j++) {
                            rectangles[j][p + 1].r = rectangles[j][p].r;
                            rectangles[j][p + 1].g = rectangles[j][p].g;
                            rectangles[j][p + 1].b = rectangles[j][p].b;
                            
                    }
                }
            }
        }
    return flag;
}



Status updateI (Termino *termino, Movement movement, Rectangle rectangles[12][16]) {
    Termino currentTermino = *termino;
    char shape = currentTermino.shape;
    Status status;
    switch(currentTermino.direction){ 
            case Up:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                            
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                            
                        }
                        break;
                    case rightRotation:
                        currentTermino.terminoRectangles[0].x += terminoRectPosX*2;
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[1].x += terminoRectPosX;
                        currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[3].y -= terminoRectPosY * 2;
                        currentTermino.direction = Right;
                        break;
                    case leftRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[2].x += terminoRectPosX;
                        currentTermino.terminoRectangles[3].y -= terminoRectPosY * 2;
                        currentTermino.terminoRectangles[3].x += terminoRectPosX * 2;
                        currentTermino.direction = Left;
                        break;
                    default:
                        break;
                    }
                break;
            case Down:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                        }
                        break;

                    case rightRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[0].y -= terminoRectPosY * 2;
                        currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[2].x += terminoRectPosX;
                        currentTermino.terminoRectangles[3].x += terminoRectPosX * 2;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    
                    case leftRotation:
                        currentTermino.terminoRectangles[0].x += terminoRectPosX * 2;
                        currentTermino.terminoRectangles[0].y -= terminoRectPosY * 2;
                        currentTermino.terminoRectangles[1].x += terminoRectPosX;
                        currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.direction = Right;
                        break;
                    default:
                        break;
                    }
                break;
            case Right:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].x -= terminoRectPosX * 2;
                    currentTermino.terminoRectangles[0].y += terminoRectPosY * 2;
                    currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[1].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.direction = Down;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x -= terminoRectPosX * 2; 
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[2].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.terminoRectangles[3].y += terminoRectPosY * 2;
                    currentTermino.direction = Up;
                    break;
                default:
                    break;
                }
                    break;
            case Left:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX; 
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[2].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[2].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x -= terminoRectPosX * 2;
                    currentTermino.terminoRectangles[3].y += terminoRectPosY * 2;
                    currentTermino.direction = Up;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX;
                    currentTermino.terminoRectangles[0].y += terminoRectPosY * 2;
                    currentTermino.terminoRectangles[1].y += terminoRectPosY;
                    currentTermino.terminoRectangles[2].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[3].x -= terminoRectPosX * 2;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.direction = Down;
                    break;
                default:
                    break;
                }
                        
                break;
            default:
                break;

    }
    status = checkCollision(currentTermino, movement, rectangles);
    currentTermino.shape = shape;
    *termino = currentTermino;
    return status;
}

Status updateT (Termino *termino, Movement movement, Rectangle rectangles[12][16]) {
    Termino currentTermino = *termino;
    char shape = currentTermino.shape;
    Status status;
    switch(currentTermino.direction){ 
            case Up:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                        }
                        break;
                    case rightRotation:
                        currentTermino.terminoRectangles[0].x += terminoRectPosX;
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[1].x += terminoRectPosX;
                        currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.direction = Right;
                        break;
                    case leftRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[1].x += terminoRectPosX;
                        currentTermino.terminoRectangles[1].y += terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    default:
                        break;
                    }
                break;
            case Down:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                        }
                        break;

                    case rightRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[1].y += terminoRectPosY;
                        currentTermino.terminoRectangles[3].x += terminoRectPosX;
                        currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    
                    case leftRotation:
                        currentTermino.terminoRectangles[0].x += terminoRectPosX;
                        currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[3].x += terminoRectPosX;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.direction = Right;
                        break;
                    default:
                        break;
                    }
                break;
            case Right:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[0].y += terminoRectPosY;
                    currentTermino.terminoRectangles[1].x += terminoRectPosX;
                    currentTermino.terminoRectangles[1].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.direction = Down;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[1].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.direction = Up;
                    break;
                default:
                    break;
                }
                    break;
            case Left:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX;
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.terminoRectangles[3].y += terminoRectPosY;
                    currentTermino.direction = Up;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX;
                    currentTermino.terminoRectangles[0].y += terminoRectPosY;
                    currentTermino.terminoRectangles[1].x += terminoRectPosX;
                    currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[3].y += terminoRectPosY;
                    currentTermino.direction = Down;
                    break;
                default:
                    break;
                }
                        
                break;
            default:
                break;

    }
    status = checkCollision(currentTermino, movement, rectangles);
    currentTermino.shape = shape;
    *termino = currentTermino;
    return status;
}


Status updateL (Termino *termino, Movement movement, Rectangle rectangles[12][16]) {
    Termino currentTermino = *termino;
    char shape = currentTermino.shape;
    Status status;
    switch(currentTermino.direction){ 
            case Up:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                            
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                            
                        }
                        break;
                    case rightRotation:
                        currentTermino.terminoRectangles[0].x += terminoRectPosX*2;
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[1].x += terminoRectPosX;
                        currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.direction = Right;
                        break;
                    case leftRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[0].y += terminoRectPosY*2;
                        currentTermino.terminoRectangles[1].y += terminoRectPosY;
                        currentTermino.terminoRectangles[2].x += terminoRectPosX;
                        currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    default:
                        break;
                    }
                break;
            case Down:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosY;
                        }
                        break;

                    case rightRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX * 2;
                        currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[1].y += terminoRectPosY;
                        currentTermino.terminoRectangles[2].y += terminoRectPosY*2;
                        currentTermino.terminoRectangles[3].x += terminoRectPosX;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    
                    case leftRotation:
                        currentTermino.terminoRectangles[0].x += terminoRectPosX;
                        currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[2].x -= terminoRectPosX; 
                        currentTermino.terminoRectangles[2].y += terminoRectPosY;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY * 2;
                        currentTermino.direction = Right;
                        break;
                    default:
                        break;
                    }
                break;
            case Right:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[0].y += terminoRectPosY;
                    currentTermino.terminoRectangles[2].x += terminoRectPosX;
                    currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY * 2;
                    currentTermino.direction = Down;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x -= terminoRectPosX * 2; 
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[2].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.direction = Up;
                    break;
                default:
                    break;
                }
                    break;
            case Left:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX ; 
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY * 2;
                    currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[2].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[3].y += terminoRectPosY;
                    currentTermino.direction = Up;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX * 2;
                    currentTermino.terminoRectangles[1].x += terminoRectPosX;
                    currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[2].y -= terminoRectPosY * 2;
                    currentTermino.terminoRectangles[3].x -= terminoRectPosX ;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.direction = Down;
                    break;
                default:
                    break;
                }
                        
                break;
            default:
                break;

    }
    status = checkCollision(currentTermino, movement, rectangles);
    currentTermino.shape = shape;
    *termino = currentTermino;
    return status;
}

Status updateZ (Termino *termino, Movement movement, Rectangle rectangles[12][16]) {
    Termino currentTermino = *termino;
    char shape = currentTermino.shape;
    Status status;
    switch(currentTermino.direction){ 
            case Up:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                            
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                            
                        }
                        break;
                    case rightRotation:
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[1].y += terminoRectPosY * 2;
                        currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.direction = Right;
                        break;
                    case leftRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[1].x -= terminoRectPosX *2;
                        currentTermino.terminoRectangles[2].x += terminoRectPosX;
                        currentTermino.terminoRectangles[2].y += terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    default:
                        break;
                    }
                break;
            case Down:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                        }
                        break;

                    case rightRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX ;
                        currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[2].y += terminoRectPosY*2;
                        currentTermino.terminoRectangles[2].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    
                    case leftRotation:
                        currentTermino.terminoRectangles[1].x += terminoRectPosX;
                        currentTermino.terminoRectangles[1].y += terminoRectPosY;
                        currentTermino.terminoRectangles[2].x -= terminoRectPosX * 2;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.direction = Right;
                        break;
                    default:
                        break;
                    }
                break;
            case Right:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[2].x += terminoRectPosX * 2;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.direction = Down;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[1].x += terminoRectPosX;
                    currentTermino.terminoRectangles[1].y -= terminoRectPosY * 2;
                    currentTermino.terminoRectangles[2].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.direction = Up;
                    break;
                default:
                    break;
                }
                    break;
            case Left:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX ; 
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY ;
                    currentTermino.terminoRectangles[1].x += terminoRectPosY * 2;
                    currentTermino.terminoRectangles[2].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                    currentTermino.direction = Up;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX ;
                    currentTermino.terminoRectangles[1].y += terminoRectPosY;
                    currentTermino.terminoRectangles[2].x += terminoRectPosX;
                    currentTermino.terminoRectangles[2].y -= terminoRectPosY * 2;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.direction = Down;
                    break;
                default:
                    break;
                }
                        
                break;
            default:
                break;

    }
    status = checkCollision(currentTermino, movement, rectangles);
    currentTermino.shape = shape;
    *termino = currentTermino;
    return status;
}
Status updateO (Termino *termino, Movement movement, Rectangle rectangles[12][16]) {
    Termino currentTermino = *termino;
    char shape = currentTermino.shape;
    Status status;
    switch(currentTermino.direction){ 
            case Up:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x += terminoRectPosX;
                            
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                            
                        }
                        break;
                    case rightRotation:
                        currentTermino.terminoRectangles[0].x += terminoRectPosX;
                        currentTermino.terminoRectangles[1].y += terminoRectPosY;
                        currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                        currentTermino.direction = Right;
                        break;
                    case leftRotation:
                        currentTermino.terminoRectangles[0].y += terminoRectPosY;
                        currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[2].x += terminoRectPosX;
                        currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                        currentTermino.direction = Left;
                        break;
                    default:
                        break;
                    }
                break;
            case Down:
                    switch (movement)
                    {
                    case noMove:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                            
                        } 
                        break;
                    case moveDown:
                        for(int i = 0; i < 4; i++) {
                            currentTermino.terminoRectangles[i].y += terminoRectPosY;
                        }
                        break;
                    case moveRight:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x +=terminoRectPosX;
                        }
                        break;
                    case moveLeft:
                        for(int i = 0 ; i < 4; i ++) {
                            currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                        }
                        break;

                    case rightRotation:
                        currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[2].y += terminoRectPosY;
                        currentTermino.terminoRectangles[3].x += terminoRectPosX;
                        currentTermino.direction = Left;
                        break;
                    
                    case leftRotation:
                        currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                        currentTermino.terminoRectangles[1].x += terminoRectPosX;
                        currentTermino.terminoRectangles[2].x -= terminoRectPosX;
                        currentTermino.terminoRectangles[3].y += terminoRectPosY;
                        currentTermino.direction = Right;
                        break;
                    default:
                        break;
                    }
                break;
            case Right:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].y += terminoRectPosY;
                    currentTermino.terminoRectangles[1].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[2].x += terminoRectPosX;
                    currentTermino.terminoRectangles[3].y -= terminoRectPosY;
                    currentTermino.direction = Down;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[1].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[2].y += terminoRectPosY;
                    currentTermino.terminoRectangles[3].x += terminoRectPosX;
                    currentTermino.direction = Up;
                    break;
                default:
                    break;
                }
                    break;
            case Left:
                switch (movement)
                {
                case noMove:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY;
                    } 
                    break;
                case moveDown:
                    for(int i = 0; i < 4; i++) {
                        currentTermino.terminoRectangles[i].y += terminoRectPosY * 2;
                    }
                    break;
                case moveRight:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x += terminoRectPosX;
                    }
                    break;
                case moveLeft:
                    for(int i = 0 ; i < 4; i ++) {
                        currentTermino.terminoRectangles[i].x -= terminoRectPosX;
                    }
                    break;

                case rightRotation:
                    currentTermino.terminoRectangles[0].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[1].x += terminoRectPosX;
                    currentTermino.terminoRectangles[2].x -= terminoRectPosX;
                    currentTermino.terminoRectangles[3].y += terminoRectPosY;
                    currentTermino.direction = Up;
                    break;
            
                case leftRotation:
                    currentTermino.terminoRectangles[0].x += terminoRectPosX;
                    currentTermino.terminoRectangles[1].y += terminoRectPosY;
                    currentTermino.terminoRectangles[2].y -= terminoRectPosY;
                    currentTermino.terminoRectangles[3].x -= terminoRectPosX;
                    currentTermino.direction = Down;
                    break;
                default:
                    break;
                }
                        
                break;
            default:
                break;

    }
    status = checkCollision(currentTermino, movement, rectangles);
    currentTermino.shape = shape;
    *termino = currentTermino;
    return status;
}
bool checkRectanglesColor (Rectangle rectangles[12][16], int col, int row, int r, int g, int b) {
    if (rectangles[col][row].r == r && rectangles[col][row].g == g && rectangles[col][row].b == b) {
        return true;
    }
    return false;
}

Status checkCollision (Termino termino, Movement movement, Rectangle rectangles[12][16]) {


    int rect0Col = termino.terminoRectangles[0].x/terminoRectPosX;
    int rect0Row = termino.terminoRectangles[0].y/terminoRectPosY;
    int rect1Col = termino.terminoRectangles[1].x/terminoRectPosX;
    int rect1Row = termino.terminoRectangles[1].y/terminoRectPosY;
    int rect2Col = termino.terminoRectangles[2].x/terminoRectPosX;
    int rect2Row = termino.terminoRectangles[2].y/terminoRectPosY;
    int rect3Col = termino.terminoRectangles[3].x/terminoRectPosX;
    int rect3Row = termino.terminoRectangles[3].y/terminoRectPosY;

    for(int i = 0 ; i < 4; i++) {
        if((termino.terminoRectangles[i].x < 0) || (termino.terminoRectangles[i].x > windowWidth - terminoRectPosX)) {
            return COLLIDED;
        }
        else if((termino.terminoRectangles[i].y > windowHeight - terminoRectPosY) && movement != moveDown) {
            return STOP;
        }
        else if((termino.terminoRectangles[i].y > windowHeight - terminoRectPosY) && movement == moveDown) {
            return COLLIDED;
        }
    }
    switch(movement) {
        case noMove:
            switch (termino.shape)
            {
            case I:
                switch(termino.direction) {
                    case Up:
                        if(checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                        break;
                    case Down:
                        if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                        break;
                    case Right:
                        if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB) 
                        || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                        break;
                    case Left:
                        if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB) 
                        || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                        break;
                    default:
                        break;
                }
                break;
            case T:
                switch (termino.direction)
                {
                case Up:
                    if(checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
                
                    break;
                case Down:
                    if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
            
                    break;
                case Right:
                    if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
            
                    break;
                case Left:
                    if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
                    
                    break;
                default:
                    break;
                }
                break;
            case L:
                switch (termino.direction)
                    {
                    case Up:
                        if(checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                    
                        break;
                    case Down:
                        if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                
                        break;
                    case Right:
                        if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                
                        break;
                    case Left:
                        if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                        || checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)) {
                            return STOP;
                        }
                        return MOVING;
                        
                        break;
                    default:
                        break;
                    }
                break;
            case Z:
                switch (termino.direction)
                {
                case Up:
                    if(checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
                
                    break;
                case Down:
                    if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
            
                    break;
                case Right:
                    if(checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
            
                    break;
                case Left:
                    if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
                    
                    break;
                default:
                    break;
                }
                break;
            case O:
                switch (termino.direction)
                {
                case Up:
                    if(checkRectanglesColor(rectangles, rect2Col, rect2Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
                
                    break;
                case Down:
                    if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
            
                    break;
                case Right:
                    if(checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect3Col, rect3Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
            
                    break;
                case Left:
                    if(checkRectanglesColor(rectangles, rect0Col, rect0Row, cyanR, cyanG, cyanB)
                    || checkRectanglesColor(rectangles, rect1Col, rect1Row, cyanR, cyanG, cyanB)) {
                        return STOP;
                    }
                    return MOVING;
                    
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        default:
            for(int i = 0; i < 4; i++) {
                if(checkRectanglesColor(rectangles, termino.terminoRectangles[i].x/terminoRectPosX
                    , termino.terminoRectangles[i].y/terminoRectPosY, cyanR, cyanG, cyanB)) {
                    return COLLIDED;
                    }
            }
                return MOVING;
            break;
    }
    return MOVING;
}