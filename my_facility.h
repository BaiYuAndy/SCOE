#ifndef _FACILITY_H_
#define _FACILITY_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<fstream>
#include<sys/uio.h>
#include <ctime>
#include <cmath>
#include <assert.h>

#undef main

#define random(a,b) (rand()%(b-a+1)+a)

using namespace std;

class window{

	private:
		SDL_Window *pWindow;
		SDL_Renderer *renderer;

	public:
		const char *str;
		
		SDL_Rect winRect;
		
		SDL_Renderer* drawWindow(){
			
			//SDL_Window *pWindow = NULL;
			pWindow = SDL_CreateWindow(str,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,winRect.w,winRect.h,SDL_WINDOW_SHOWN);

			//SDL_Renderer *renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

			SDL_SetRenderDrawColor(renderer, 0, 0xaa, 0xaa, 0xaa);

			SDL_RenderPresent(renderer);

			return renderer;
		
		}
		
		SDL_Renderer* drawWindow(int x,int y, int width,int high){
			
			//SDL_Window *pWindow = NULL;
			pWindow = SDL_CreateWindow(str,x,y,width,high,SDL_WINDOW_SHOWN);

			//SDL_Renderer *renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
			renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

			SDL_SetRenderDrawColor(renderer, 0, 0xaa, 0xaa, 0xaa);

			SDL_RenderPresent(renderer);

			return renderer;
		
		}

		SDL_Renderer* getWindow(){
			pWindow = SDL_CreateWindow(str,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,winRect.w,winRect.h,0);

			renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

			return renderer;
		}
		
		window(){
			
			winRect.x = 0;
			winRect.y = 0;
			winRect.w = 0;
			winRect.h = 0;
			
			pWindow = NULL;
			renderer = NULL;
		}
		
		~window(){
			SDL_DestroyWindow(pWindow);
			SDL_DestroyRenderer(renderer);
		}
		
};

class Image{
	
private:

	SDL_Surface *imageSurface;

	SDL_Texture* BlueShapes;

public:
	Image(){
		imageSurface = NULL;
		BlueShapes = NULL;
		
		direct = 2;//default direct is right
	
		moveCount = 0;
		downCount = 0;
	}
	SDL_Rect dstrect;

	int width,high;
	
	int direct; //1-left,2-right

	int moveCount;
	int downCount;

	SDL_Surface * getLoadBitmap(const char *image_path){
		imageSurface = SDL_LoadBMP(image_path);
		
		this->width = imageSurface->w;
		this->high = imageSurface->h;

		return imageSurface;
	}
	
	int loadJpg(const char *image_path){
		imageSurface = IMG_Load(image_path);
		return imageSurface->w;
	}
	
	int loadJpgH(const char *image_path){
		imageSurface = IMG_Load(image_path);
		
		return imageSurface->h;
	}

	void drawBitmap(SDL_Renderer* pRender){

		BlueShapes = SDL_CreateTextureFromSurface(pRender, imageSurface);
		//SDL_FreeSurface(imageSurface);

		SDL_RenderCopy(pRender,BlueShapes, NULL, NULL);
		SDL_RenderPresent(pRender);

	}
	
	SDL_Renderer* setRenderBitmap(SDL_Renderer* pRender,SDL_Rect bitmapRect){	
	
		assert(pRender !=NULL);
		
		assert(this->imageSurface !=NULL);
	
		BlueShapes = SDL_CreateTextureFromSurface(pRender, this->imageSurface);
		
		assert(BlueShapes !=NULL);
		
		//SDL_FreeSurface(imageSurface);
		SDL_Rect ImageRect;
		ImageRect.x=0;
		ImageRect.y=0;
		ImageRect.w = imageSurface->w;//this part is control for background in window.
		ImageRect.h = imageSurface->h;

		SDL_RenderCopy(pRender,BlueShapes, &ImageRect, &bitmapRect);

		//SDL_QueryTexture(BlueShapes, NULL, NULL, &ImageRect.w, &ImageRect.h);
		//SDL_RenderPresent(pRender);
		return pRender;
	}	
	
	SDL_Renderer* setRenderBitmap(SDL_Renderer* pRender,SDL_Rect bitmapRect,SDL_Rect drstect){
		assert(pRender !=NULL);
		
		assert(imageSurface !=NULL);
		
		BlueShapes = SDL_CreateTextureFromSurface(pRender, imageSurface);
		
		//assert(BlueShapes !=NULL);
		
		if (BlueShapes == NULL) {
			
			cout<<"CreateTextureFromSurface failed: "<<SDL_GetError()<<endl;
			
			exit(1);
		}
		
		assert(bitmapRect.w >= drstect.w);
		
		SDL_RenderCopy(pRender,BlueShapes, &bitmapRect, &drstect);
		//SDL_RenderPresent(pRender);

		return pRender;
	}
	
	void drawBitmapCover(SDL_Renderer* pRender,SDL_Rect drstect,bool later){
		BlueShapes = SDL_CreateTextureFromSurface(pRender, imageSurface);
		
		SDL_Rect ImageRect;
		ImageRect.x = 0;
		ImageRect.y = 0;
		if(later){
			ImageRect.w = (imageSurface->w)/4;
			ImageRect.h = imageSurface->h;
		}
		else{
			ImageRect.w = imageSurface->w;
			ImageRect.h = (imageSurface->h)/4;
		}
		
		SDL_RenderCopy(pRender,BlueShapes, &ImageRect, &drstect);
		SDL_RenderPresent(pRender);
	}
	//countPart should be 0-3
	void drawBitmapCoverInMove(SDL_Renderer* pRender,SDL_Rect drstect,bool later){
		BlueShapes = SDL_CreateTextureFromSurface(pRender, imageSurface);
		
		SDL_Rect ImageRect;
		//ImageRect.x=0;
		//ImageRect.y=0;
		if(later){
			ImageRect.w = (imageSurface->w)/4;
			ImageRect.h = imageSurface->h;
			
			if(this->direct == 1)
				ImageRect.x = (imageSurface->w)/4 *(3- this->moveCount);
			else
				ImageRect.x = (imageSurface->w)/4 *(this->moveCount);
			
			ImageRect.y = 0;
		}
		else{
			ImageRect.w = imageSurface->w;
			ImageRect.h = (imageSurface->h)/4;
			
			ImageRect.x = 0;
			ImageRect.y = (imageSurface->h)/4 *downCount;
	
		}
		
		SDL_RenderCopy(pRender,BlueShapes, &ImageRect, &drstect);
		SDL_RenderPresent(pRender);
	}
	
	void releaseImage(){
		SDL_FreeSurface(imageSurface);
	}
	
	virtual SDL_Surface *  actorChooseBitmap(int choose,int direct){

		return imageSurface;
	};
	
	virtual ~Image(){
		SDL_FreeSurface(imageSurface);
		SDL_DestroyTexture(BlueShapes);
	}
};

class ImageFirst: public Image{
	private:
		SDL_Surface *imageSurface;

	public:
	
	int upOrDown;
	
	ImageFirst(){
		width =30;
		high =40;
		
		upOrDown = 1;//mean jump up
		
		end = false;
	}
	
	bool end;
	
	SDL_Surface * actorChooseBitmap(int choose,int direct){
	
		assert(choose>0 && choose<7);
		
		assert(direct ==1 || direct == 2);
		
		switch(choose){
			
			case 1:
				if(direct == 2)
					imageSurface = getLoadBitmap("res//actor//1.bmp");
				else
					imageSurface = getLoadBitmap("res//actorL//1.bmp");
			break;
			
			case 2:
				if(direct == 2)
					imageSurface = getLoadBitmap("res//actor//2.bmp");
				else
					imageSurface = getLoadBitmap("res//actorL//2.bmp");
			break;
			
			case 3:
				if(direct == 2)
					imageSurface = getLoadBitmap("res//actor//3.bmp");
				else
					imageSurface = getLoadBitmap("res//actorL//3.bmp");
			break;
			
			case 4:
				if(direct == 2)
					imageSurface = getLoadBitmap("res//actor//4.bmp");
				else
					imageSurface = getLoadBitmap("res//actorL//4.bmp");
			break;
			
			case 5:
				if(direct == 2)
					imageSurface = getLoadBitmap("res//actor//5.bmp");
				else
					imageSurface = getLoadBitmap("res//actorL//5.bmp");
			break;
			
			case 6:
				if(direct == 2)
					imageSurface = getLoadBitmap("res//actor//1.bmp");
				else
					imageSurface = getLoadBitmap("res//actorL//1.bmp");
			break;
			
		}

		return imageSurface;
	
	}

	~ImageFirst(){
		SDL_FreeSurface(imageSurface);
		
	}
};

struct enemyMartix{
	int xPoint;
	int yPoint;
	int style;
	
	int status;
	//int width;
};

queue<enemyMartix> enemyList;

vector<enemyMartix> blockList;

class ImageSecond: public Image{
	public:
	
	bool start;
	bool inMove;
	int style;
	int styleCount;
	void actorChooseBitmap(){
		
		assert(styleCount>0 && styleCount<4);
		
		switch(styleCount){
			
			case 1:
				if( style == 2)
					getLoadBitmap("res//enemy//11.bmp");
				else if( style == 3)
					getLoadBitmap("res//enemy//21.bmp");
				else
					getLoadBitmap("res//enemy//1.bmp");
			break;
			
			case 2:
				if(style == 2)
					getLoadBitmap("res//enemy//12.bmp");
				else if( style == 3)
					getLoadBitmap("res//enemy//22.bmp");
				else
					getLoadBitmap("res//enemy//2.bmp");
			break;
			
			case 3:
				if(style == 2)
					getLoadBitmap("res//enemy//13.bmp");
				else if( style == 3)
					getLoadBitmap("res//enemy//23.bmp");
				else
					getLoadBitmap("res//enemy//3.bmp");
			break;
			
		}
	}
		
	ImageSecond(){
		width =30;
		high =40;
		
		start = false;
		style = 1;
		inMove = false;
		
		styleCount = 1;
	}
		
};


#endif