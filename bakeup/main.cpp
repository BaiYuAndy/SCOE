#include "my_facility.h"

#include "my_thread.h"

//#include <windows.h> 
#define sleep(n) Sleep(1000 * (n))

window win;

SDL_Rect loadPictureRect;

SDL_Renderer *mainRenderer;

Image background;

ImageFirst actor;

ImageSecond enemy;

int oneWidth,oneHigh;

SDL_TimerID backgroundRightTimer,actorRightTimer,updateBackgroundTimer;

const int backgroundMoveCap = 10;

//
pthread_t thActor;
void *threadBackgroundMove(void *argvpm){
	
	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	free(argvpm);
	
	return NULL;
}
//
Uint32 backgroundRight(Uint32 interval, void * param){
	
	background.moveCount++;
	
	loadPictureRect.x += backgroundMoveCap;
	
	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	actor.actorChooseBitmap(background.moveCount,actor.direct);
	actor.drawBitmap(mainRenderer,actor.dstrect);
	
	if(background.moveCount > 4){
		background.moveCount = 0;

		actor.actorChooseBitmap(background.moveCount+1,actor.direct);
		actor.drawBitmap(mainRenderer,actor.dstrect);
	
		SDL_RemoveTimer(backgroundRightTimer);
		
	}
	
	static int i = 0;
	
	if(!blockList.empty()){
		
		blockList.at(0).xPoint -= (i+1)*backgroundMoveCap;
		
		ImageSecond enemyLast;
		enemyLast.dstrect.x = blockList.at(0).xPoint;
		enemyLast.dstrect.y = blockList.at(0).yPoint;
		enemyLast.style = blockList.at(0).style;
		
		enemyLast.styleCount = 3;
		enemyLast.actorChooseBitmap();
		
		enemyLast.dstrect.w = enemyLast.width;
		enemyLast.dstrect.h = enemyLast.high;
		
		enemyLast.drawBitmap(mainRenderer,enemyLast.dstrect);
		
		enemyLast.~ImageSecond();
		
		if(enemyLast.dstrect.x + oneWidth <=0){
			i = 0;
			
			blockList.erase (blockList.begin());
		}
		else
			i++;
	}
	
	return interval;
}

void *threadActorMove(void *argvpm){
	
	int chooseCount = *(int *)argvpm;
	
	//actor.actorChooseBitmap(actor.moveCount,actor.direct);
	actor.actorChooseBitmap(chooseCount,actor.direct);
	
	actor.drawBitmap(mainRenderer,actor.dstrect);
	
	return NULL;
}



Uint32 actorRight(Uint32 interval, void * param){
	actor.moveCount++;

	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	actor.dstrect.x += 10;
	
	actor.actorChooseBitmap(actor.moveCount,actor.direct);
	actor.drawBitmap(mainRenderer,actor.dstrect);
	
	if(actor.moveCount > 5){

		actor.moveCount = 0;
		SDL_RemoveTimer(actorRightTimer);
	}
	
	return interval;
}

SDL_TimerID actorLeftTimer,actorJumpTimer;

Uint32 actorLeft(Uint32 interval, void * param){
	actor.moveCount++;

	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	actor.dstrect.x -= 10;
	
	actor.actorChooseBitmap(actor.moveCount,actor.direct);
	actor.drawBitmap(mainRenderer,actor.dstrect);
	
	if(!blockList.empty()){
			ImageSecond enemyLast;
			enemyLast.dstrect.x = blockList.at(0).xPoint;
			enemyLast.dstrect.y = blockList.at(0).yPoint;
			enemyLast.style = blockList.at(0).style;
			
			enemyLast.styleCount = 3;
			enemyLast.actorChooseBitmap();
			
			enemyLast.dstrect.w = enemyLast.width;
			enemyLast.dstrect.h = enemyLast.high;
			enemyLast.drawBitmap(mainRenderer,enemyLast.dstrect);
			
			enemyLast.~ImageSecond();
		}
	
	if(actor.moveCount > 5){

		actor.moveCount = 0;
		SDL_RemoveTimer(actorLeftTimer);
	}
	
	return interval;
}

SDL_TimerID enemyMoveTimer;

enemyMartix *blockOne;

Uint32 actorJump(Uint32 interval, void * param){
	actor.downCount++;

	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	if(actor.upOrDown == 1)
		actor.dstrect.y -= 12;
	else if(actor.upOrDown == 2)
		actor.dstrect.y += 12;
	
	actor.actorChooseBitmap(5,actor.direct);
	actor.drawBitmap(mainRenderer,actor.dstrect);
	//cout<<actor.dstrect.x<<"\t";
	
	if(actor.dstrect.y + oneHigh >= enemy.dstrect.y
		&& actor.dstrect.x <enemy.dstrect.x 
		&& actor.dstrect.x+oneWidth  > enemy.dstrect.x
		&& enemy.inMove){
			SDL_RemoveTimer(enemyMoveTimer);
			
			SDL_RemoveTimer(actorJumpTimer);
			actor.downCount =0;
			actor.actorChooseBitmap(1,actor.direct);
			
			if(enemy.style == 2){
				actor.dstrect.y = enemy.dstrect.y;
				enemy.dstrect.y +=oneHigh;
				
			}
			else if(enemy.style == 1){
				actor.dstrect.y = enemy.dstrect.y;
				enemy.dstrect.x = actor.dstrect.x + oneWidth;
				
				blockOne = new enemyMartix;
				
				/*blockOne->xPoint = loadPictureRect.x;
				blockOne->width = enemy.dstrect.x;*/
				blockOne->xPoint = enemy.dstrect.x;
				
				blockOne->yPoint = enemy.dstrect.y;
				blockOne->style = enemy.style;
				blockOne->status = 3;
				
				blockList.push_back(*blockOne);
				
				delete blockOne;
			}
			else if(enemy.style == 3){
					
				actor.dstrect.x = enemy.dstrect.x -oneWidth;
				actor.dstrect.y = enemy.dstrect.y;//-oneHigh;
				
				blockOne = new enemyMartix;
				
				/*blockOne->xPoint = loadPictureRect.x;
				blockOne->width = enemy.dstrect.x;*/
				blockOne->xPoint = enemy.dstrect.x;
				
				blockOne->yPoint = enemy.dstrect.y;
				blockOne->style = enemy.style;
				
				blockOne->status = 3;
				
				blockList.push_back(*blockOne);
				
				delete blockOne;
					
				actor.drawBitmap(mainRenderer,actor.dstrect);
			}
			enemy.inMove = false;
			enemy.start = false;
			
			enemy.styleCount =3;
			enemy.actorChooseBitmap();
			
			background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
			enemy.drawBitmap(mainRenderer,enemy.dstrect);
			actor.drawBitmap(mainRenderer,actor.dstrect);
		}
	
	if(actor.downCount == 5)
		actor.upOrDown = 2;
	else if(actor.downCount > 9){
		SDL_RemoveTimer(actorJumpTimer);
		actor.downCount =0;
		actor.actorChooseBitmap(1,actor.direct);
		actor.drawBitmap(mainRenderer,actor.dstrect);
	}
	
	return interval;
}

SDL_TimerID cloudHighTimer;
Image cloud;

//void gameInit(int choose);
int winQuene;

Uint32 cloudHigh(Uint32 interval, void * param){
	actor.dstrect.y -=10;
	cloud.dstrect.y = actor.dstrect.y +oneHigh;
	
	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	actor.actorChooseBitmap(1,actor.direct);
	actor.drawBitmap(mainRenderer,actor.dstrect);
	cloud.drawBitmap(mainRenderer,cloud.dstrect);
	//cout<<actor.dstrect.x<<"\t";
	if(cloud.dstrect.y <=0){
		SDL_RemoveTimer(cloudHighTimer);
		winQuene++;
		
		pthread_create(&thGameInit,NULL,threadGameInit,&winQuene);
		pthread_join(thGameInit,NULL);
		//gameInit(winQuene);
		
	}
	
	return interval;
}

Uint32 updateBackground(Uint32 interval, void * param){
	
	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	return interval;
}

void *threadGameInit(void *argvpm){

	int choose = *(int *)argvpm;
	
	switch(choose){
		case 1:
			background.getLoadBitmap("res//backgroundFirst.bmp");
		break;
		
		case 2:
			background.getLoadBitmap("res//backgroundSecond.bmp");
		break;
		
		default:
			background.getLoadBitmap("res//background.bmp");
		break;
	}
	
	actor.dstrect.x = 0;
	actor.dstrect.y = (win.winRect.h- 1.8*oneHigh);
	actor.direct = 2;
	actor.moveCount = 0;
	
	actor.end = false;
	
	loadPictureRect.x = 0;
	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	actor.actorChooseBitmap(1,actor.direct);
	actor.drawBitmap(mainRenderer,actor.dstrect);
	
	enemy.start = false;
	
	pthread_exit(NULL);
	
	return NULL;
}

Uint32 enemyMove(Uint32 interval, void * param){
	
	if(actor.moveCount == 0){
		background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
		actor.drawBitmap(mainRenderer,actor.dstrect);
	}
	
	enemy.dstrect.x -=5;
	
	enemy.actorChooseBitmap();
	enemy.drawBitmap(mainRenderer,enemy.dstrect);
	
	if(enemy.styleCount == 1)
		enemy.styleCount = 2;
	else if(enemy.styleCount == 2)
		enemy.styleCount = 1;
	
	if(enemy.dstrect.x<win.winRect.x){
		SDL_RemoveTimer(enemyMoveTimer);
		enemy.start = false;
	}
	
	return interval;
}

void *theadGameLast(void *argvpm){
	
	actor.end = true;
	cloud.getLoadBitmap("res//cloud.bmp");
	cloud.dstrect.x = actor.dstrect.x;
	cloud.dstrect.y = actor.dstrect.y +oneHigh;
	cloud.dstrect.w = cloud.width;
	cloud.dstrect.h = cloud.high;
	
	cloudHighTimer = SDL_AddTimer(100,cloudHigh,NULL);
	
	pthread_exit(NULL);
	return NULL;
}

int main(){
	
	win.str = "my win";
	
	background.getLoadBitmap("res//background.bmp");
	//cout<<background.width<<"\t"<<background.high;
	
	background.width =(background.width/10)*10;
	background.high = (background.high/10)*10;
	
	win.winRect.w = background.width/4;
	win.winRect.h = background.high;
	mainRenderer = win.drawWindow();
	
	loadPictureRect.x = 0;
	loadPictureRect.y = 0;
	
	loadPictureRect.w = win.winRect.w;
	loadPictureRect.h = win.winRect.h;
	
	//updateBackgroundTimer = SDL_AddTimer(100,updateBackground,NULL);
	background.drawBitmap(mainRenderer,loadPictureRect,win.winRect);
	
	actor.actorChooseBitmap(1,actor.direct);
	
	oneWidth = actor.dstrect.w = actor.width;
	oneHigh = actor.dstrect.h = actor.high;
	
	actor.dstrect.x = 0;
	actor.dstrect.y = win.winRect.h - 1.8*oneHigh;
	//cout<<actor.dstrect.y;
	actor.drawBitmap(mainRenderer,actor.dstrect);
	//
	winQuene = 0;
	//
	enemyMartix *enemyOne;
	int point[3] = {background.width/4,background.width/2,background.width/2+10*oneWidth};
	int i = 0;
	
	while(i<3){
		enemyOne = new enemyMartix;
		enemyOne->xPoint = point[i];
		enemyOne->yPoint = actor.dstrect.y;
		enemyOne->style = i+1;
		enemyList.push(*enemyOne);
		
		i++;
	}
	delete enemyOne;
	/*while(!enemyList.empty()){
		cout<<enemyList.front().xPoint<<endl;
		enemyList.pop();
		
	}*/
	
	//
	bool quit = false;
	SDL_Event event;
	//
	sem_init(&sem,0,1);
	
	//
	while(!quit){
		//
		if(background.moveCount > 4){
			/*actor.actorChooseBitmap(background.moveCount+1,actor.direct);
			actor.drawBitmap(mainRenderer,actor.dstrect);
	
			background.moveCount = 0;
			*/
			SDL_RemoveTimer(backgroundRightTimer);
		
		}
		//
		if(actor.dstrect.x >= (win.winRect.w - 3*oneWidth)
			&& !actor.end){
			/*actor.end = true;
			cloud.getLoadBitmap("res//cloud.bmp");
			cloud.dstrect.x = actor.dstrect.x;
			cloud.dstrect.y = actor.dstrect.y +oneHigh;
			cloud.dstrect.w = cloud.width;
			cloud.dstrect.h = cloud.high;
			
			cloudHighTimer = SDL_AddTimer(100,cloudHigh,NULL);*/
			pthread_create(&thGameNext,NULL,theadGameLast,NULL);
			pthread_join(thGameNext,NULL);
			
		}
		
		if(!enemyList.empty())
			
			if(loadPictureRect.x > enemyList.front().xPoint
				&& !enemy.start ){
	
				enemy.start = true;
				enemy.inMove = true;
				
				enemy.dstrect.x = win.winRect.w;
				enemy.dstrect.y = actor.dstrect.y;
				
				enemy.dstrect.w = enemy.width;
				enemy.dstrect.h = enemy.high;
				
				enemy.styleCount = 1;
				enemy.style = enemyList.front().style;
				enemyMoveTimer = SDL_AddTimer(100,enemyMove,NULL);
				
				enemyList.pop();
			}
		
		while (SDL_PollEvent(&event)) {
		
				switch (event.type) {
				
				case SDL_QUIT:
					quit = true;
					
					//SDL_RemoveTimer(updateBackgroundTimer);
					
				break;
				
				case SDL_KEYDOWN:

				switch(event.key.keysym.sym){
					
					case SDLK_d:
						sleep(0.1);
					/*
					*/if(!actor.end){
		
						if(actor.direct == 1)
							actor.direct = 2;
						
						if(!blockList.empty() && background.moveCount == 0 ){
							if(actor.dstrect.x +oneWidth == blockList.at(0).xPoint
							&& actor.dstrect.y == blockList.at(0).yPoint
							&& blockList.at(0).status == 3){
								actorRightTimer = SDL_AddTimer(100,actorRight,NULL);
							}
							else{		
								if(actor.dstrect.x < (oneWidth*8) && actor.moveCount == 0){
									actorRightTimer = SDL_AddTimer(100,actorRight,NULL);
								}
								else if(loadPictureRect.x + loadPictureRect.w < background.width
										&& background.moveCount == 0){
										//cout<<"bai";
										backgroundRightTimer = SDL_AddTimer(100,backgroundRight,NULL);
										}
								else if(actor.dstrect.x < (win.winRect.w-3*oneWidth) && actor.moveCount == 0 )
									actorRightTimer = SDL_AddTimer(100,actorRight,NULL);
									
								}
							}
						else if(background.moveCount == 0){
							if(actor.dstrect.x < (oneWidth*8) && actor.moveCount == 0)
								actorRightTimer = SDL_AddTimer(100,actorRight,NULL);
							else if(loadPictureRect.x + loadPictureRect.w < background.width
									&& background.moveCount == 0){
									
									backgroundRightTimer = SDL_AddTimer(100,backgroundRight,NULL);
									}
							else if(actor.dstrect.x < (win.winRect.w-3*oneWidth) && actor.moveCount == 0 )
								actorRightTimer = SDL_AddTimer(100,actorRight,NULL);	
						}	
					}
					
						/*pthread_t thActor;
						
						pthread_create(&thActor,NULL,threadBackgroundMove,NULL);
						pthread_join(thActor,NULL);*/
					
					break;
					
					case SDLK_SPACE:
					
					if(!actor.end){
						if(actor.downCount ==0){
							actor.upOrDown = 1;
							actorJumpTimer = SDL_AddTimer(100,actorJump,NULL);
						}
					}
					
					break;
					
					case SDLK_a:
						
					if(!actor.end){
						if(actor.dstrect.x > oneWidth && actor.moveCount == 0){
							if(actor.direct == 2)
								actor.direct = 1;
							actorLeftTimer = SDL_AddTimer(100,actorLeft,NULL);
						}
					}
					break;
				}
			}
		}
	}
	
	//delete blockOne;
	
	background.~Image();
	enemy.~ImageSecond();
	actor.~ImageFirst();
	win.~window();
	
	
	return 0;
}
