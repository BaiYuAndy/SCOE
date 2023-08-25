#ifndef _IMAGE_H_
#define _IMAGE_H_


#include "SDL/SDL.h"

class Image{
	
private:

	SDL_Surface *imageSurface;

	SDL_Texture* BlueShapes;

public:

	SDL_Rect dstrect;

	int width,high;

	int loadbitmap(const char *image_path){
		imageSurface = SDL_LoadBMP(image_path);
		
		return imageSurface->w;
	}

	int loadbitmapH(const char *image_path){
		imageSurface = SDL_LoadBMP(image_path);
		
		return imageSurface->h;
	}

	void drawBitmap(SDL_Renderer* pRender){

		BlueShapes = SDL_CreateTextureFromSurface(pRender, imageSurface);
		//SDL_FreeSurface(imageSurface);

		SDL_RenderCopy(pRender,BlueShapes, NULL, NULL);
		SDL_RenderPresent(pRender);

	}
	
	void drawBitmap(SDL_Renderer* pRender,SDL_Rect bitmapRect){
		

		BlueShapes = SDL_CreateTextureFromSurface(pRender, imageSurface);
		//SDL_FreeSurface(imageSurface);
		SDL_Rect ImageRect;
		ImageRect.x=0;
		ImageRect.y=0;
		ImageRect.w = imageSurface->w;
		ImageRect.h = imageSurface->h;

		SDL_RenderCopy(pRender,BlueShapes, &ImageRect, &bitmapRect);
		SDL_RenderPresent(pRender);

	}	
	
	void drawBitmap(SDL_Renderer* pRender,SDL_Rect bitmapRect,SDL_Rect drstect){
		BlueShapes = SDL_CreateTextureFromSurface(pRender, imageSurface);
		
		SDL_RenderCopy(pRender,BlueShapes, &bitmapRect, &drstect);
		SDL_RenderPresent(pRender);
	}

};



#endif 