#include "my_facility.h"
#include "word.h"

#define fix 66 //this is block high number

#define DOWNSPEED 150

SDL_Renderer* mainRender;

 //set window project 
 window pWin;

Image* block = new Image();
Image* backMap = new Image(); 

int moveCount = 0 , wordNum = 0;

int width,high;

int blockPointX;

struct node
{
	int x;
	int y;

	int mapNum;
};

vector<node> list;

void setBlock(){
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
}

int onBlock(int x,int y){

	int onSite = 0;
	//cout<<"Ypoint is"<<y<<endl;
	for(int i = 0;i< list.size();i++){
	//	cout<<"list is "<<list.at(i).x<<"\t"<<list.at(i).y<<endl;
		if(x == (list.at(i)).x){
			if(y + high == (list.at(i)).y){
				onSite = (list.at(i)).y;
				break;
			}
		}
  	}
  	//cout<<"----------"<<endl;
  	return onSite;

}

int onBlockXpositionLeft(int x,int y){

	int onSite = 0;
	
	for(int i = 0;i< list.size();i++){

		if(y == (list.at(i)).y){
			
			if(x - width == (list.at(i)).x){
				onSite = (list.at(i)).x;
				break;
			}
		}
		
  	}
  	
  	return onSite;

}

int onBlockXpositionRight(int x,int y){

	int onSite = 0;
	
	for(int i = 0;i< list.size();i++){

		if(y == (list.at(i)).y){
			
			if(x + width == (list.at(i)).x){
				onSite = (list.at(i)).x;
				break;
			}
		}
		
  	}
  	
  	return onSite;

}

int onBlockNum(int x, int y){
	int onSite = 0;

	for(int i = 0;i< list.size();i++){

		if(x == (list.at(i)).x){
			if(y == (list.at(i)).y){
				onSite = (list.at(i)).mapNum;
				break;
			}
		}
  	}
  	return onSite;
}

void setList(int x,int y,int wordNum){
	for(int i = 0;i< list.size();i++){

		if(x == (list.at(i)).x){
			if(y == (list.at(i)).y){
				(list.at(i)).mapNum = wordNum;
				//cout<<"bai";
				break;
			}
		}
  	}
}

void earseList(int x ,int y){
	for(int i = 0;i< list.size();i++){

		if(x == (list.at(i)).x){
			if(y == (list.at(i)).y){
				list.erase(list.begin()+i);
				//cout<< i<<endl;
				break;
			}
		}
  	}
}

bool inList(int x,int y){

	bool inList = false;

	for(int i = 0;i< list.size();i++){

		if(x == (list.at(i)).x){
			if(y == (list.at(i)).y){
				inList = true;
				break;
			}
		}
  	}
  	return inList;
}

int setMapBlock(Image *block){
	bool panduan = false;
	int onBottom = 0;

	struct node point;
        	
    point.x = block->dstrect.x;

    if(onBlock(block->dstrect.x,block->dstrect.y)){
        int tempWord;
        int tempY = onBlock(block->dstrect.x,block->dstrect.y);
        int tempNum = onBlockNum(block->dstrect.x,tempY);
        	
        if(onBlockXpositionLeft(block->dstrect.x,block->dstrect.y) > 0){
        	int tempX = onBlockXpositionLeft(block->dstrect.x,block->dstrect.y);
        			
        	if(onBlockNum(tempX,block->dstrect.y) > -1){
        				
        		int tempNumRight = onBlockNum(tempX,block->dstrect.y);
        				
        		if(setTripBlockMap(wordNum,tempNum,tempNumRight)){
        			tempWord = setTripBlockMap(wordNum,tempNum,tempNumRight);
        			setList(block->dstrect.x,tempY,tempWord);
        			
        			earseList(tempX,block->dstrect.y);
        			earseList(block->dstrect.x,block->dstrect.y);
        			
        			onBottom = tempWord;

        		}
        		else{
        			if(upDownBlock(wordNum,tempNum)> -1){
        				tempWord = upDownBlock(wordNum,tempNum);
        				setList(block->dstrect.x,tempY,tempWord);
        				onBottom = tempWord;
        			}
        			else {
        				point.y =  onBlock(block->dstrect.x,block->dstrect.y) - high;
        				point.mapNum = wordNum;
        				list.push_back(point);
        				
        				onBottom = 0;
        			}
        		}
        	}
        }
        else if(onBlockXpositionRight(block->dstrect.x,block->dstrect.y) > 0){
        	int tempX = onBlockXpositionRight(block->dstrect.x,block->dstrect.y);
        	
        	if(onBlockNum(tempX,block->dstrect.y) > -1){
        		
        		int tempNumRight = onBlockNum(tempX,block->dstrect.y);
        		
        		if(setTripBlockMap(wordNum,tempNum,tempNumRight)){
        			tempWord = setTripBlockMap(wordNum,tempNum,tempNumRight);
        			setList(block->dstrect.x,tempY,tempWord);
        			
        			earseList(tempX,block->dstrect.y);
        			earseList(block->dstrect.x,block->dstrect.y);
        			//cout<<tempX<<"\t"<<block->dstrect.y<<endl;
        			onBottom = tempWord;
        			
        		}
        		else{
        			if(upDownBlock(wordNum,tempNum)> -1){
        				tempWord = upDownBlock(wordNum,tempNum);
        				setList(block->dstrect.x,tempY,tempWord);

        				onBottom = tempWord;
        			}
        			else{
        				point.y =  onBlock(block->dstrect.x,block->dstrect.y) - high;
        				point.mapNum = wordNum;
        				list.push_back(point);
        				
        				onBottom = 0;
        			}
        		}
        	}
        }
        else if(upDownBlock(wordNum,tempNum)> -1){
        	tempWord = upDownBlock(wordNum,tempNum);
        	
        	setList(block->dstrect.x,tempY,tempWord);
        	
        	onBottom = tempWord;
        }
       	else{
       		if(!inList(block->dstrect.x,block->dstrect.y)){
       			point.y =  onBlock(block->dstrect.x,block->dstrect.y) - high;
       			point.mapNum = wordNum;
       			list.push_back(point);
       		}
       			
    		onBottom = 0;
       	}
       	
    }
    else{

        point.y = pWin.winRect.h-high;
        point.mapNum = wordNum;
        list.push_back(point);
    	
    	onBottom = 0;		
    }

	return onBottom;
}// onBottom 0 means true on bottom

Uint32 blockDown(Uint32 interval, void * param){
	
	block->dstrect.y += high/4;

	mainRender = backMap->setRenderBitmap(mainRender,backMap->dstrect);

	setBlock();

	mainRender = block->setRenderBitmap(mainRender,block->dstrect);

	SDL_RenderPresent(mainRender);
	
	return interval;
}

Uint32 blockMove(Uint32 interval, void * param){

	if(block->direct == 2)
		block->dstrect.x += width/4;
	else if(block->direct == 1)
		block->dstrect.x -= width/4;

	mainRender = backMap->setRenderBitmap(mainRender,backMap->dstrect);

	setBlock();
	
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


    block->getLoadBitmap(getWordByNUM(wordNum));
    width = block->width = (block->width/10)*10;
    high  = block->high  = width;//(block->high/10)*10;

    Image background;

    Image();
    background.getLoadBitmap("res//background.bmp");

    background.width = width*12;
    background.high  = high*10;

    pWin.winRect.w = background.width;
    pWin.winRect.h = background.high;
    //cout<<pWin.winRect.h;

    background.bmpRect.x = background.dstrect.x = 0;
    background.bmpRect.y = background.dstrect.y = 0;
    background.bmpRect.w = background.dstrect.w = background.width;
    background.bmpRect.h = background.dstrect.h = background.high;
 
    // creates a renderer to render our images
    mainRender = pWin.getWindow();

    mainRender = background.setRenderBitmap(mainRender,background.dstrect);
    
    //

    //block->getLoadBitmap("res//word//yi.bmp");
    
    // block X position when Y is 0
    //const int 
    blockPointX = block->width * 4;

    block->dstrect.x = blockPointX;
    block->dstrect.y = 0;
    block->dstrect.w = (block->width);
    block->dstrect.h = (block->high);

    mainRender =block->setRenderBitmap(mainRender,block->dstrect);

    // controls animation loop
    int close = 0; 
    //

	SDL_RenderPresent(mainRender);

	SDL_TimerID blockDownTimer,blockMoveTimer;

	backMap = &background;

	blockDownTimer = SDL_AddTimer(DOWNSPEED,blockDown,NULL);

    // animation loop

    bool blockNext = false;
    while (!close) {
    	//block on bottom line
    	if(block->dstrect.y+ high >= pWin.winRect.h
    		|| onBlock(block->dstrect.x,block->dstrect.y)){
    		/*
    		struct node point;
    		if(block->dstrect.y+ high >= pWin.winRect.h){
    			
    			point.x = block->dstrect.x;
    			point.y = ((block->dstrect.y)/10) * 10;
        		point.mapNum = wordNum;

        		list.push_back(point);
    		}
    		else if(onBlock(block->dstrect.x,block->dstrect.y)){
    			int tempY = onBlock(block->dstrect.x,block->dstrect.y);
    			int tempNum = onBlockNum(block->dstrect.x,tempY);
    			
    			if(upDownBlock(wordNum,tempNum)> -1){
        			int tempWord = upDownBlock(wordNum,tempNum);
        			setList(block->dstrect.x,tempY,tempWord);
        	
        			}
        		else{
	
    				point.x = block->dstrect.x;
    				point.y = onBlock(block->dstrect.x,block->dstrect.y) - high;
        			point.mapNum = wordNum;
	
        			list.push_back(point);
        		}
    		}*/
    		//setMapBlock(block);
    		int start = setMapBlock(block);
    		while( start !=0 ){
    			
    			wordNum = start;
    			block->dstrect.y = onBlock(block->dstrect.x,block->dstrect.y);

    			start = setMapBlock(block);
    		}
        	//cout<<"size"<<list.size()<<endl;	
    			SDL_RemoveTimer(blockDownTimer);

    			block->dstrect.x = blockPointX;

    			block->dstrect.y = 0;

    			// calculates to 60 fps
        		SDL_Delay(1000 / 30);
        	
        		//wordNum = random(0,10);
        		//wordNum = 6;

        		if(wordNum == 0)
        			wordNum = 1;
        		else if(wordNum == 1)
        			wordNum = 0;
        		else
        			wordNum = 1;
				
        		block->getLoadBitmap(getWordByNUM(wordNum));
        		blockDownTimer = SDL_AddTimer(DOWNSPEED,blockDown,NULL);

    		//}
    		
    	}
    	else if(moveCount >3){
    		blockDownTimer = SDL_AddTimer(DOWNSPEED,blockDown,NULL);
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
                	if(block->dstrect.x > width){
                    	block->direct = 1;
                		SDL_RemoveTimer(blockDownTimer);
                		blockMoveTimer = SDL_AddTimer(100,blockMove,NULL);
                	}
                    break;

                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                 	
                    break;

                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                	if(block->dstrect.x +width <pWin.winRect.w - width){
                		block->direct = 2;
                		SDL_RemoveTimer(blockDownTimer);
                		blockMoveTimer = SDL_AddTimer(100,blockMove,NULL);
                	}
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




