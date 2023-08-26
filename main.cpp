#include "my_facility.h"

#define WIDTH 600
#define HIGH 600

SDL_Renderer* rend;

int main(int argc, char *argv[])
{
// returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    SDL_Surface* imageSurface;

    Image background;
    imageSurface = background.getLoadBitmap("res//background.bmp");

    background.width =(background.width/10)*10;
    background.high = (background.high/10)*10;

    window pWin;

    pWin.winRect.w = background.width/4;
    pWin.winRect.h = background.high;

    background.dstrect.x = 0;
    background.dstrect.y = 0;
    background.dstrect.w = imageSurface->w;
    background.dstrect.h = imageSurface->h;

 
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = pWin.getWindow();//SDL_CreateRenderer(win, -1, render_flags);

    rend = background.setRenderBitmap(rend,background.dstrect);
//
    
    Image actor;

    // creates a surface to load an image into the main memory
    SDL_Surface* surface = actor.getLoadBitmap("res//actor//1.bmp");
    actor.dstrect.x = 0;
    actor.dstrect.y = background.dstrect.h - 1.8*actor.high;
    actor.dstrect.w = actor.width;
    actor.dstrect.h = actor.high;

    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
 
    rend = background.setRenderBitmap(rend,background.dstrect);

    SDL_RenderCopy(rend, tex, NULL, &actor.dstrect);

    // clears main-memory
    SDL_FreeSurface(surface);
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 300;
    //

	SDL_RenderPresent(rend);
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
                    surface = actor.getLoadBitmap("res//actor//2.bmp");
                    tex = SDL_CreateTextureFromSurface(rend, surface);

                    rend = background.setRenderBitmap(rend,background.dstrect);

                    SDL_RenderCopy(rend, tex, NULL, &actor.dstrect);
        
                    SDL_RenderPresent(rend);

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
 
        // clears the screen
        //SDL_RenderClear(rend);
 
        // triggers the double buffers
        // for multiple rendering

        /*rend = background.setRenderBitmap(rend,background.dstrect);

        SDL_RenderCopy(rend, tex, NULL, &actor.dstrect);
        
		SDL_RenderPresent(rend);*/
        //
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy texture
    SDL_DestroyTexture(tex);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    pWin.~window();
     
    // close SDL
    SDL_Quit();
 
    return 0;
}

