#include "my_facility.h"

int main(){
	
	SDL_Rect loadPictureRect;

	SDL_Renderer *mainRenderer;

	Image background;

	window win;

	win.str = "my win";
	
	background.getLoadBitmap("res//background.bmp");
	
	background.width =(background.width/10)*10;
	background.high = (background.high/10)*10;
	
	win.winRect.w = background.width/4;
	win.winRect.h = background.high;
	mainRenderer = win.drawWindow();
	
	loadPictureRect.x = 0;
	loadPictureRect.y = 0;
	
	loadPictureRect.w = win.winRect.w;
	loadPictureRect.h = win.winRect.h;
	
	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);

	//
	bool quit = false;
	SDL_Event event;
	//

	while(!quit){
		while (SDL_PollEvent(&event)) {
		
				switch (event.type) {
				
				case SDL_QUIT:
					quit = true;
					
					//SDL_RemoveTimer(updateBackgroundTimer);
					
				break;
			}
		}
	}
	
	background.~Image();
	//enemy.~ImageSecond();
	//actor.~ImageFirst();
	win.~window();

	return 0;
}

