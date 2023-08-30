#include "my_facility.h"


SDL_Renderer* mainRender;

SDL_TimerID actorLeftTimer,actorJumpTimer,backgroundLeftTimer;

window pWin;

//actor dstrect x point in window
int xPoint = 0;
//

Image background;

ImageFirst actor;

ImageFirst enemy;

// speed of box
const int speed = 300;

const int jumpHigh = 150;

//picture to background rect
SDL_Rect ImageRect;

Uint32 actorLeft(Uint32 interval, void * param){
    actor.moveCount++;

    actor.dstrect.x += speed / 30;

    mainRender = background.setRenderBitmap(mainRender,ImageRect, background.dstrect);

    actor.actorChooseBitmap(actor.moveCount,actor.direct);
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);

    if(enemy.onMove){
        enemy.dstrect.x -=speed/60;

        if(enemy.style == 1)
            enemy.getLoadBitmap("res//enemy//2.bmp");
        else if(enemy.style == 0)
            enemy.getLoadBitmap("res//enemy//1.bmp");

        mainRender = enemy.setRenderBitmap(mainRender,enemy.dstrect);

        enemy.style++;

        enemy.style %=2;
    
    }
        
    SDL_RenderPresent(mainRender);
    xPoint +=actor.dstrect.x;
    return interval;
}
        
Uint32 backgroundLeft(Uint32 interval, void * param){
    background.moveCount++;

    ImageRect.x += speed / 30;
    background.dstrect.w -= speed / 30;

    mainRender = background.setRenderBitmap(mainRender,ImageRect,background.dstrect);

    actor.actorChooseBitmap(background.moveCount,2);
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
        
    SDL_RenderPresent(mainRender);
    xPoint += ImageRect.x;
    return interval;
}

Uint32 actorRight(Uint32 interval, void * param){
    actor.moveCount++;

    actor.dstrect.x -= speed / 30;

    mainRender = background.setRenderBitmap(mainRender,ImageRect, background.dstrect);

    actor.actorChooseBitmap(actor.moveCount,actor.direct);
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
        
    SDL_RenderPresent(mainRender);

    return interval;
}

Uint32 actorUp(Uint32 interval, void * param){
    
    if(actor.upOrDown == 1){
        actor.dstrect.y -= speed / 15;
        actor.moveCount = 5;
    }
    else if(actor.upOrDown == 0){
        actor.dstrect.y += speed / 15;
        actor.moveCount = 6;
    }

    mainRender = background.setRenderBitmap(mainRender,ImageRect, background.dstrect);


    actor.actorChooseBitmap(actor.moveCount,actor.direct);
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
        
    SDL_RenderPresent(mainRender);

    return interval;

}

Uint32 enemyMove(Uint32 interval, void * param){
    
    enemy.dstrect.x -=speed/60;
    
    if(!actor.onMove){
        mainRender = background.setRenderBitmap(mainRender,ImageRect, background.dstrect);
        mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
    }

    if(enemy.style == 1)
        enemy.getLoadBitmap("res//enemy//2.bmp");
    else if(enemy.style == 0)
        enemy.getLoadBitmap("res//enemy//1.bmp");

    mainRender = enemy.setRenderBitmap(mainRender,enemy.dstrect);
        
    SDL_RenderPresent(mainRender);

    enemy.style++;

    enemy.style %=2;

    return interval;

}

int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    //get background information
    
    Image();//this is make sure init Image 
    ImageFirst();
    
    background.getLoadBitmap("res//background.bmp");

    background.width =(background.width/10)*10;
    background.high = (background.high/10)*10;
    
    //set window size width is background 1/4

    pWin.str = "my win";

    pWin.winRect.w = background.width/4;
    pWin.winRect.h = background.high;


    background.dstrect.x = 0;
    background.dstrect.y = 0;
    background.dstrect.w = background.width;
    background.dstrect.h = background.high;
 

    ImageRect.x=0;
    ImageRect.y=0;
    ImageRect.w = background.dstrect.w;//this part is control for background in window.
    ImageRect.h = pWin.winRect.h;


    // creates a renderer to render our images
    mainRender = pWin.getWindow();

    //mainRender = background.setRenderBitmap(mainRender,background.dstrect);
    //
    actor.direct = 2;
    actor.actorChooseBitmap(1,actor.direct );
    actor.dstrect.x = 0;
    const int actorOnGround = actor.dstrect.y = background.dstrect.h - 1.8*actor.high;
    actor.dstrect.w = actor.width;
    actor.dstrect.h = actor.high;

    // set actor and background to window text contend.

    mainRender = background.setRenderBitmap(mainRender,ImageRect, background.dstrect);
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
 
    // controls animation loop
    int close = 0;
 
    //
    background.moveCount = 1;
    actor.moveCount = 1;

    //
    enemy.getLoadBitmap("res//enemy//1.bmp");
    
    enemy.dstrect.x = pWin.winRect.w - enemy.width;
    enemy.dstrect.y = actor.dstrect.y;

    enemy.dstrect.w = enemy.width;
    enemy.dstrect.h = enemy.high;
    
    mainRender = enemy.setRenderBitmap(mainRender,enemy.dstrect);
    SDL_TimerID enemyMoveTimer;

    enemyMoveTimer = SDL_AddTimer(100,enemyMove,NULL);

    //
	SDL_RenderPresent(mainRender);
    //

    // animation loop
    while (!close) {

        if(actor.moveCount >=6){
            SDL_RemoveTimer(actorLeftTimer);
            actor.onMove = false;
        }

        if(background.moveCount >=6){
            SDL_RemoveTimer(backgroundLeftTimer);
            background.moveCount = 1;
            actor.moveCount = 1;
            //cout<<xPoint<<endl;
        }

        if(enemy.dstrect.x + enemy.width < 0 || actor.onMove){
            SDL_RemoveTimer(enemyMoveTimer);
            enemy.onMove = true;
        }

        if(enemy.dstrect.x > 0 && !actor.onMove && enemy.onMove){
            enemyMoveTimer = SDL_AddTimer(100,enemyMove,NULL);
            enemy.onMove = false;
        }

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
                    //actor.dstrect.y -= speed / 30;
                    actorJumpTimer = SDL_AddTimer(100,actorUp,NULL);
                    actor.upOrDown = 1;
                    break;

                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    //actor.dstrect.x -= speed / 30;
                    
                    if(actor.direct == 2)
                        actor.direct = 1;

                    if(actor.moveCount ==1 || actor.moveCount >= 6){
                        if(actor.dstrect.x > actor.width){
                            if(actor.moveCount >= 6)
                                actor.moveCount = 1;
                        
                            actorLeftTimer = SDL_AddTimer(100,actorRight,NULL);
                        }
                    }

                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    //actor.dstrect.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    
                if(background.dstrect.w > (pWin.winRect.w)*1.2 ){ // right boundary

                    if(actor.direct == 1)
                        actor.direct = 2;

                    if(actor.dstrect.x <= (pWin.winRect.w)*0.7){// in inti actor move 
                        
                        if(actor.moveCount ==1 || actor.moveCount >= 6){

                            if(actor.moveCount >= 6)
                                actor.moveCount = 1;

                            actor.onMove = true;
                            actorLeftTimer = SDL_AddTimer(100,actorLeft,NULL);
                        }
                    }
                    else if(background.moveCount == 1){
                        backgroundLeftTimer = SDL_AddTimer(100,backgroundLeft,NULL);
                    }

                }
                else if( (actor.dstrect.x + actor.dstrect.w) < 0.8*pWin.winRect.w){

                    if(actor.direct == 1)
                        actor.direct = 2;
                    
                    if(actor.moveCount ==1 || actor.moveCount >= 6){

                        if(actor.moveCount >= 6)
                            actor.moveCount = 1;
                        actorLeftTimer = SDL_AddTimer(100,actorLeft,NULL);

                      }
                    }

                    break;
                default:
                    break;
                }
            }
        }
 
        // right boundary
        if (background.dstrect.w - actor.dstrect.x < actor.dstrect.w){
            //actor.dstrect.x = background.dstrect.w - actor.dstrect.x;
            SDL_RemoveTimer(actorLeftTimer);
        }
 
        // left boundary
        if (actor.dstrect.x < 0)
            actor.dstrect.x = 0;
 
        // bottom boundary
        if (actor.dstrect.y < jumpHigh && actor.upOrDown == 1){
            //actor.dstrect.y = 1000 - actor.dstrect.h;
            //SDL_RemoveTimer(actorJumpTimer);
            actor.upOrDown = 0;
            actor.onFalling = true;
        }
        if(actor.upOrDown ==0 && actor.onFalling && actor.dstrect.y >= actorOnGround){

            SDL_RemoveTimer(actorJumpTimer);
            actor.onFalling = false;
            actor.moveCount = 1;

        }
 
        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // remove timeID
    SDL_RemoveTimer(actorLeftTimer);
    SDL_RemoveTimer(backgroundLeftTimer);
    SDL_RemoveTimer(actorJumpTimer);

    // destroy renderer
    SDL_DestroyRenderer(mainRender);
 
    actor.~ImageFirst();
    background.~Image();
    pWin.~window();

    // close SDL
    SDL_Quit();
 
    return 0;
}

