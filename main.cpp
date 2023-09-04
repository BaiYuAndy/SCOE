#include "my_facility.h"

#define WIDTH 600
#define HIGH 600

SDL_Renderer* mainRender;

SDL_TimerID actorLeftTimer, backgroundLeftTimer;

// speed of box
int speed = 300;

int xPoint  = 0;

int onGround = 0;

ImageFirst actor;

Image background;

ImageSecond* enemy = new ImageSecond;

Uint32 actorLeft(Uint32 interval, void * param){
    actor.dstrect.x += speed / 30;

    mainRender = background.setRenderBitmap(mainRender,background.bmpRect,background.dstrect);

    if(actor.upOrDown == 1 && actor.dstrect.y < (background.dstrect.h - 2*actor.high))
        actor.actorChooseBitmap(2,2);
    else
        actor.actorChooseBitmap(actor.moveCount,2);
        
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);

    if(enemy->inMove)
        mainRender = enemy->setRenderBitmap(mainRender,enemy->dstrect);

    SDL_RenderPresent(mainRender);

    actor.moveCount++;

    xPoint += speed / 30;;

    return interval;
}

Uint32 actorRight(Uint32 interval, void * param){
    actor.dstrect.x -= speed / 30;

    mainRender = background.setRenderBitmap(mainRender,background.bmpRect,background.dstrect);

    if(actor.upOrDown == 1 && actor.dstrect.y < (background.dstrect.h - 2*actor.high))
        actor.actorChooseBitmap(2,2);
    else
        actor.actorChooseBitmap(actor.moveCount,1);
    
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);

    if(enemy->inMove)
        mainRender = enemy->setRenderBitmap(mainRender,enemy->dstrect);

    SDL_RenderPresent(mainRender);

    actor.moveCount++;

    return interval;
}

Uint32 backgroundLeft(Uint32 interval, void * param){

    background.bmpRect.x += speed /30;
    background.dstrect.w -= speed /30;

    mainRender = background.setRenderBitmap(mainRender,background.bmpRect, background.dstrect);

    if(actor.upOrDown == 1 && actor.dstrect.y < (background.dstrect.h - 2*actor.high))
        actor.actorChooseBitmap(2,2);
    else
        actor.actorChooseBitmap(actor.moveCount,2);
    
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);

    if(enemy->inMove)
        mainRender = enemy->setRenderBitmap(mainRender,enemy->dstrect);

    SDL_RenderPresent(mainRender);

    actor.moveCount++;

    if(actor.moveCount>6)
        actor.moveCount = 1;

    background.moveCount++;

    xPoint += speed /30;

    return interval;
}

SDL_TimerID actorJumpTimer;
Uint32 actorJump(Uint32 interval, void * param){
    
    if(actor.upOrDown == 1){
        actor.dstrect.y -= speed / 20;
        actor.actorChooseBitmap(2,actor.direct);
    }
    else if(actor.upOrDown == 0){
        actor.dstrect.y += speed / 20;
        actor.actorChooseBitmap(1,actor.direct);
    }

    mainRender = background.setRenderBitmap(mainRender,background.bmpRect,background.dstrect);

    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);

    if(enemy->inMove)
       mainRender = enemy->setRenderBitmap(mainRender,enemy->dstrect);

    SDL_RenderPresent(mainRender);

    //actor.moveCount++;

    return interval;
}

SDL_TimerID enemyMoveTimer;
Uint32 enemyMove(Uint32 interval, void * param){

    enemy->dstrect.x -= speed / 60;

    enemy->actorChooseBitmap(enemy->style,enemy->styleCount);
//
    (enemy->styleCount)++;
    //
    if(enemy->styleCount >2)
        enemy->styleCount = 1;

    if(!actor.onMove){
        mainRender = background.setRenderBitmap(mainRender,background.bmpRect,background.dstrect);
        mainRender = enemy->setRenderBitmap(mainRender,enemy->dstrect);

        mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
    
       SDL_RenderPresent(mainRender);

    }

    return interval;
}

int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    //get background information
    //Image background;
    Image();
    background.getLoadBitmap("res//background.bmp");

    background.width =(background.width/10)*10;
    background.high = (background.high/10)*10;
    
    //set window size width is background 1/4
    window pWin;

    pWin.winRect.w = background.width/4;
    pWin.winRect.h = background.high;


    background.bmpRect.x = background.dstrect.x = 0;
    background.bmpRect.y = background.dstrect.y = 0;
    background.bmpRect.w = background.dstrect.w = background.width;
    background.bmpRect.h = background.dstrect.h = background.high;
 
    // creates a renderer to render our images
    mainRender = pWin.getWindow();

    mainRender = background.setRenderBitmap(mainRender,background.dstrect);
    //
    
    //Image actor;

    actor.getLoadBitmap("res//actor//1.bmp");
    actor.dstrect.x = 0;
    actor.dstrect.y = background.dstrect.h - 1.8*actor.high;
    actor.dstrect.w = actor.width;
    actor.dstrect.h = actor.high;

    actor.upOrDown = 1;
    // set actor and background to window text contend.

    mainRender = background.setRenderBitmap(mainRender,background.bmpRect,background.dstrect);
    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
    
    //enemy init
    //ImageSecond* enemy = new ImageSecond;
    enemy->actorChooseBitmap(enemy->style,enemy->styleCount);
    enemy->dstrect.x = pWin.winRect.w - enemy->width;
    enemy->dstrect.y = background.dstrect.h - 1.8*actor.high;
    enemy->dstrect.w = enemy->width;
    enemy->dstrect.h = enemy->high;

    enemy->inMove = true;
    
    mainRender = enemy->setRenderBitmap(mainRender,enemy->dstrect);

    enemyMoveTimer = SDL_AddTimer(100,enemyMove,NULL);

    // set enemy other
    short enemCount = 2;

    // controls animation loop
    int close = 0; 
    //

	SDL_RenderPresent(mainRender);

    // animation loop
    while (!close) {

        if(actor.upOrDown == 1 && actor.dstrect.y < (pWin.winRect.h - 4.5*actor.dstrect.h)){
            actor.upOrDown = 0;
        }
        else if(actor.upOrDown == 0 && actor.dstrect.y >= (background.dstrect.h - 2*actor.high)){
            actor.upOrDown = 1;
            SDL_RemoveTimer(actorJumpTimer);
            actor.dstrect.y = (background.dstrect.h - 1.8*actor.high);
            actor.onMove = false;
            if(enemCount >= 0 && enemy->start) {
                if(actor.dstrect.x+actor.dstrect.w> enemy->dstrect.x
                    && actor.dstrect.x< enemy->dstrect.x+enemy->dstrect.w){
                    SDL_RemoveTimer(enemyMoveTimer);//
                    enemy->inMove = false;
                    enemy->start = false;
                    //this is a demo
                    enemy->styleCount = 3;
                    enemy->actorChooseBitmap(enemy->style,enemy->styleCount);
                    enemy->dstrect.x = actor.dstrect.x +actor.dstrect.w;
                    enemy->dstrect.y = actor.dstrect.y;

                    mainRender = background.setRenderBitmap(mainRender,background.bmpRect,background.dstrect);
                    mainRender = enemy->setRenderBitmap(mainRender,enemy->dstrect);

                    mainRender = actor.setRenderBitmap(mainRender,actor.dstrect);
                    
                    SDL_RenderPresent(mainRender);
                    if(enemCount > 1)
                        enemCount--;
                    //
                }
            }
        }

        //cout<<xPoint<<"\t"<<background.width/2<<enemCount<<"\t"<<endl;
        if(enemCount == 1 && xPoint >= background.width/2){
            enemCount--;
            enemy->dstrect.x = pWin.winRect.w;
            
            enemy->style =3;

            enemy->styleCount = 1;

            enemy->inMove = true;

            enemy->start = true;
    
            enemyMoveTimer = SDL_AddTimer(100,enemyMove,NULL);
            
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
                    actorJumpTimer = SDL_AddTimer(100,actorJump,NULL);
                    actor.onMove = true;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    //actor.dstrect.x -= speed / 30;
                    actorLeftTimer = SDL_AddTimer(100,actorRight,NULL); 
                    actor.direct = 1;
                    actor.onMove = true;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    actor.dstrect.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    actor.direct = 2;
                    if(!actor.end && actor.upOrDown == 1){

                        if(actor.dstrect.x <= pWin.winRect.w*0.55)
                            actorLeftTimer = SDL_AddTimer(100,actorLeft,NULL); 
                        else
                            backgroundLeftTimer = SDL_AddTimer(100,backgroundLeft,NULL);
    
                        actor.onMove = true;

                    }
                    else if(actor.upOrDown == 1){
                        actorLeftTimer = SDL_AddTimer(100,actorLeft,NULL); 
                    }

                    break;
                default:
                    break;
                }
            }
        }
 
        // right boundary
        if (!actor.end && background.dstrect.w < 1.1*pWin.winRect.w)
            actor.end = true;
        else if(actor.end && background.dstrect.w < 1.1*pWin.winRect.w
                && actor.dstrect.x > pWin.winRect.w){
            SDL_RemoveTimer(actorLeftTimer);
        }

        if(enemy->dstrect.x +enemy->width <0 && (enemy->inMove == true) ){
            SDL_RemoveTimer(enemyMoveTimer);
            enemy->inMove = false;
            enemCount--;
        }
 
        // left boundary
        if (actor.dstrect.x < 0)
            actor.dstrect.x = 0;
 
        // bottom boundary
        if (actor.dstrect.y + actor.dstrect.h > 1000)
            actor.dstrect.y = 1000 - actor.dstrect.h;
 
        // upper boundary
        if (actor.dstrect.y < 0)
            actor.dstrect.y = 0;
 
        if(actor.moveCount > 6){
            actor.moveCount = 1;
            SDL_RemoveTimer(actorLeftTimer);

            actor.onMove = false;
        }

        if(background.moveCount >6){
            SDL_RemoveTimer(backgroundLeftTimer);
            background.moveCount = 1;

            actor.onMove = false;
        }

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
 
    // destroy renderer
    SDL_DestroyRenderer(mainRender);
 
    pWin.~window();
    actor.~ImageFirst();
    background.~Image();

    delete(enemy);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}

