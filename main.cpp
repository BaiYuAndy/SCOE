#include "my_facility.h"

#define WIDTH 600
#define HIGH 600

SDL_Renderer* mainRender;

int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    //get background information
    Image background;
    background.getLoadBitmap("res//background.bmp");

    background.width =(background.width/10)*10;
    background.high = (background.high/10)*10;
    
    //set window size width is background 1/4
    window pWin;

    pWin.winRect.w = background.width/4;
    pWin.winRect.h = background.high;


    background.dstrect.x = 0;
    background.dstrect.y = 0;
    background.dstrect.w = background.width;
    background.dstrect.h = background.high;
 
    // creates a renderer to render our images
    mainRender = pWin.getWindow();

    mainRender = background.setRenderBitmap(mainRender,background.dstrect);
    //
    
    Image actor;

    actor.getLoadBitmap("res//actor//1.bmp");
    actor.dstrect.x = 0;
    actor.dstrect.y = background.dstrect.h - 1.8*actor.high;
    actor.dstrect.w = actor.width;
    actor.dstrect.h = actor.high;

    // set actor and background to window text contend.

    mainRender = background.setRenderBitmap(mainRender,background.dstrect);
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 300;
    //

	SDL_RenderPresent(mainRender);
    //

    // animation loop
    while (!close) {
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
 
            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    actor.dstrect.y -= speed / 30;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    actor.dstrect.x -= speed / 30;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    actor.dstrect.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    actor.dstrect.x += speed / 30;

                    mainRender = background.setRenderBitmap(mainRender,background.dstrect);

                    actor.getLoadBitmap("res//actor//2.bmp");
                    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);

                    //SDL_RenderCopy(mainRender, tex, NULL, &actor.dstrect);
        
                    SDL_RenderPresent(mainRender);

                    break;
                default:
                    break;
                }
            }
        }
 
        // right boundary
        if (actor.dstrect.x + actor.dstrect.w > 1000)
            actor.dstrect.x = 1000 - actor.dstrect.w;
 
        // left boundary
        if (actor.dstrect.x < 0)
            actor.dstrect.x = 0;
 
        // bottom boundary
        if (actor.dstrect.y + actor.dstrect.h > 1000)
            actor.dstrect.y = 1000 - actor.dstrect.h;
 
        // upper boundary
        if (actor.dstrect.y < 0)
            actor.dstrect.y = 0;
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy renderer
    SDL_DestroyRenderer(mainRender);
 
    pWin.~window();
    actor.~Image();
    background.~Image();
     
    // close SDL
    SDL_Quit();
 
    return 0;
}

