#include "my_facility.h"
#include "word.h"

SDL_Renderer* mainRender;

Image* block = new Image();
Image* backMap = new Image(); 

int moveCount = 0 , wordNum = 0;

int width,high;

struct node
{
	int x;
	int y;

	int mapNum;
};

vector<node> list;

void setBlock(){

}

Uint32 blockDown(Uint32 interval, void * param){
	
	block->dstrect.y += block->high/4;

	mainRender = backMap->setRenderBitmap(mainRender,backMap->dstrect);

	for(int i = 0;i< list.size();i++){

    	Image *end = new Image();

    	end->dstrect.x = (list.at(i)).x;
    	end->dstrect.y = (list.at(i)).y;
    	end->dstrect.w = width;
    	end->dstrect.h = high;

    	end->getLoadBitmap(getWordByNUM((list.at(i)).mapNum));

    	mainRender =end->setRenderBitmap(mainRender,end->dstrect);
    	
    	delete(end);
  	}

	mainRender = block->setRenderBitmap(mainRender,block->dstrect);

	SDL_RenderPresent(mainRender);
	
	return interval;
}

Uint32 blockMove(Uint32 interval, void * param){

	if(block->direct == 2)
		block->dstrect.x += block->width/4;
	else if(block->direct == 1)
		block->dstrect.x -= block->width/4;

	mainRender = backMap->setRenderBitmap(mainRender,backMap->dstrect);

	/*for(int i = 0;i< list.size();i++){
    	int x = (list.at(i)).x;
    	int y = (list.at(i)).y;
    	int Num = (list.at(i)).mapNum;

    	Image *end = new Image();

    	end->dstrect.x = x;
    	end->dstrect.y = y;
    	end->dstrect.w = width;
    	end->dstrect.h = high;

    	end->getLoadBitmap(getWordByNUM(Num));

    	mainRender =end->setRenderBitmap(mainRender,end->dstrect);
    	
    	delete(end);
  	}
	*/
	mainRender = block->setRenderBitmap(mainRender,block->dstrect);

	SDL_RenderPresent(mainRender);

	moveCount++;

	return interval;
}

int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    Image background;

    Image();
    background.getLoadBitmap("res//background.bmp");

    background.width =(background.width/10)*10;
    background.high = (background.high/10)*10;
    
    //set window size width is background 1/4
    window pWin;

    pWin.winRect.w = background.width;
    pWin.winRect.h = background.high;


    background.bmpRect.x = background.dstrect.x = 0;
    background.bmpRect.y = background.dstrect.y = 0;
    background.bmpRect.w = background.dstrect.w = background.width;
    background.bmpRect.h = background.dstrect.h = background.high;
 
    // creates a renderer to render our images
    mainRender = pWin.getWindow();

    mainRender = background.setRenderBitmap(mainRender,background.dstrect);
    
    //

    //block->getLoadBitmap("res//word//yi.bmp");
    block->getLoadBitmap(getWordByNUM(wordNum));
    width = block->width = (block->width/10)*10;
    high  = block->high = (block->high/10)*10;
    
    // block X position when Y is 0
    const int blockPointX = block->width * 3;

    block->dstrect.x = blockPointX;
    block->dstrect.y = 0;
    block->dstrect.w = block->width;
    block->dstrect.h = block->high;

    mainRender =block->setRenderBitmap(mainRender,block->dstrect);

    // controls animation loop
    int close = 0; 
    //

	SDL_RenderPresent(mainRender);

	SDL_TimerID blockDownTimer,blockMoveTimer;

	backMap = &background;

	blockDownTimer = SDL_AddTimer(100,blockDown,NULL);

    // animation loop
    while (!close) {
		//block on bottom line
    	if(block->dstrect.y+block->high >= pWin.winRect.h){
    		//add to vector list
        	struct node point;
        	
        	point.x = block->dstrect.x;
        	point.y = block->dstrect.y;
        	point.mapNum = wordNum;

        	list.push_back(point);

    		//	
    		SDL_RemoveTimer(blockDownTimer);
    		block->dstrect.x = blockPointX;
    		block->dstrect.y = 0;

    		// calculates to 60 fps
        	SDL_Delay(1000 / 60);
        	wordNum = random(0,10);
        	block->getLoadBitmap(getWordByNUM(wordNum));
        	blockDownTimer = SDL_AddTimer(100,blockDown,NULL);

        	//free(point);
    	}
    	
    	//
    	else if(moveCount >3){
    		blockDownTimer = SDL_AddTimer(100,blockDown,NULL);
    		moveCount = 0;
    		SDL_RemoveTimer(blockMoveTimer);
    	}
    	
    	//
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
                   
                    break;

                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    block->direct = 1;
                	SDL_RemoveTimer(blockDownTimer);
                	blockMoveTimer = SDL_AddTimer(100,blockMove,NULL);
                    break;

                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                 	
                    break;

                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                	block->direct = 2;
                	SDL_RemoveTimer(blockDownTimer);
                	blockMoveTimer = SDL_AddTimer(100,blockMove,NULL);
                	break;

                default:
                    break;
                }
            }
        }
	}

	// destroy renderer
    SDL_DestroyRenderer(mainRender);
 
    pWin.~window();
    //actor.~ImageFirst();
    background.~Image();

    delete(block);
     
    // close SDL
    SDL_Quit();

	return 0;
}




