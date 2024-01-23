#include "my_facility.h"

window pWin;

SDL_Renderer *mainRender;

Image block;

Image background;

vector<Image *> snake;

int xLast=0,yLast = 0;

int blockWidth = 0;

Uint32 blockMove(Uint32 interval, void * param){

	if(block.moveCount==0){
		xLast = (snake.at(0))->dstrect.x;
		yLast = (snake.at(0))->dstrect.y;
	}

	if(block.direct == 4)
		(snake.at(0))->dstrect.y+=10;
	else if(block.direct == 3)
		(snake.at(0))->dstrect.y-=10;
	else if(block.direct == 2)
		(snake.at(0))->dstrect.x-=10;
	else if(block.direct == 1)
		(snake.at(0))->dstrect.x+=10;

	
	block.moveCount++;
	int xTemp = 0;
	int yTemp = 0;
	
	if(block.moveCount == 6){

		for(int i=1;i<snake.size();i++){
			
				xTemp = (snake.at(i))->dstrect.x;
				yTemp = (snake.at(i))->dstrect.y;

				(snake.at(i))->dstrect.y = yLast;//-(block.dstrect.h);
				(snake.at(i))->dstrect.x = xLast;
				
				yLast = yTemp;
				xLast = xTemp;

		}

		mainRender = background.setRenderBitmap(mainRender,background.dstrect);

		for(int i=0;i<snake.size();i++){
			mainRender = (snake.at(i))->setRenderBitmap(mainRender,(snake.at(i))->dstrect);
		}


		SDL_RenderPresent(mainRender);
	}

    return interval;
}

void addSnake(int count){
	assert(count>0 && count<10);
	Image *pN = new Image();

	switch(count){
	case 1:
		pN->getLoadBitmap("res//score//1.bmp");
		break;
	case 2:
		pN->getLoadBitmap("res//score//2.bmp");
		break;
	case 3:
		pN->getLoadBitmap("res//score//3.bmp");
		break;
	case 4:
		pN->getLoadBitmap("res//score//4.bmp");
		break;
	case 5:
		pN->getLoadBitmap("res//score//5.bmp");
		break;
	case 6:
		pN->getLoadBitmap("res//score//6.bmp");
		break;
	case 7:
		pN->getLoadBitmap("res//score//7.bmp");
		break;
	case 8:
		pN->getLoadBitmap("res//score//8.bmp");
		break;
	case 9:
		pN->getLoadBitmap("res//score//9.bmp");
		break;

	}

	snake.back();
	pN->dstrect.x = snake.back()->dstrect.x;
    pN->dstrect.y = snake.back()->dstrect.y - blockWidth;
    pN->dstrect.w = blockWidth;
    pN->dstrect.h = blockWidth;

    snake.push_back(pN);
}

int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    block.getLoadBitmap("res//score//6.bmp");
    
    block.moveCount = 0;

    blockWidth = ((block.width/10)*10);
    block.dstrect.w = blockWidth;
    block.dstrect.h = blockWidth;

    block.dstrect.x = blockWidth*4;
    block.dstrect.y = blockWidth*3;

    block.direct = 4;

    Image *sHead = &block;
    
    Image *sNext = new Image;

    sNext->getLoadBitmap("res//score//7.bmp");
    sNext->dstrect.x = sHead->dstrect.x;
    sNext->dstrect.y = sHead->dstrect.y - blockWidth;
    sNext->dstrect.w = blockWidth;
    sNext->dstrect.h = blockWidth;

    Image *sThird = new Image;

    sThird->getLoadBitmap("res//score//8.bmp");
    sThird->dstrect.x = sHead->dstrect.x;
    sThird->dstrect.y = sNext->dstrect.y - blockWidth;
    sThird->dstrect.w = blockWidth;
    sThird->dstrect.h = blockWidth;

    snake.push_back(sHead);
    snake.push_back(sNext);
    snake.push_back(sThird);
    
    //set background width and high
    //Image background;

    int backgroundWidth = blockWidth*20;
    int backgroundHigh = blockWidth*10;

    //Image();
    background.getLoadBitmap("res//background.bmp");

    pWin.winRect.w = backgroundWidth;//background.width;
    pWin.winRect.h = backgroundHigh;//background.high;

    
    background.bmpRect.x = background.dstrect.x = 0;
    background.bmpRect.y = background.dstrect.y = 0;
    background.bmpRect.w = background.dstrect.w = backgroundWidth;//background.width;
    background.bmpRect.h = background.dstrect.h = backgroundHigh;//background.high;
 
    // creates a renderer to render our images
    mainRender = pWin.getWindow();

    //
    mainRender = background.setRenderBitmap(mainRender,background.dstrect);

    mainRender = block.setRenderBitmap(mainRender,block.dstrect);

    //
    SDL_RenderPresent(mainRender);

    //

    SDL_TimerID blockMoveTimer;

    blockMoveTimer =  SDL_AddTimer(50,blockMove,NULL);
    //

    int coutSelect =1;
    //
    int close = 0; 
    //

    while (!close) {

    	if(block.dstrect.y >=backgroundHigh
    		|| block.dstrect.x >=backgroundWidth
    		|| block.dstrect.y <0
    		|| block.dstrect.x <0)
    		SDL_RemoveTimer(blockMoveTimer);

    	if(block.moveCount >=6)
    		block.moveCount=0;
    	//
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            // keyword condition
            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    block.direct = 3;
                    break;

                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    
                    block.direct = 4;
                    break;

                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    
                    block.direct = 2;
                    break;

                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    
                    block.direct = 1;
                    break;

                case SDL_SCANCODE_SPACE:

                	addSnake(coutSelect);
                	coutSelect++;

                	if(coutSelect ==10)
                		coutSelect = 1;

                	break;

                default:
                	break;

             	}
                default:
                    break;
            }
        }
    }

    SDL_RemoveTimer(blockMoveTimer);
    pWin.~window();
    block.~Image();
    background.~Image();

    // destroy renderer
    SDL_DestroyRenderer(mainRender);

    // close SDL
    SDL_Quit();
	return 0;
}

