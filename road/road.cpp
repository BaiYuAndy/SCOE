/*project//Setting//Link//modules add SDL2main.lib SDL2.lib*/
#include <iostream>
#include <fstream>      // std::ifstream
#include <sstream>
#include <vector>
#include <math.h>       /* sqrt */

#include "lib//SparseGraph.h"
#include "lib//SearchPath.h"

#include "lib//my_facility.h"

Image *block = new Image();

Image *actorStar = new Image();
Image *actorStarCover = new Image();

Image background;

//set window project 
window pWin;

vector<int> getData(){
	vector<int> res;

	ifstream inputFile("res//data.txt"); // Open the file

    if (inputFile.is_open()) { // Check if the file was opened successfully
        string line;

        while (std::getline(inputFile, line)) { // Read each line from the file
        	char *p;
        	int size = line.length();
        	p = (char *)malloc(size);
        	strcpy(p,line.c_str());

        	for(int i = 0;i<size;i++){
        		if(*(p+i) =='1' ||*(p+i) =='0'){
        			if((*(p+i)) =='1')
        				res.push_back(1);
        			else if(*(p+i) =='0')
        				res.push_back(0);
        		}
        	}
        }
        inputFile.close(); // Close the file
        
    } 
    else {
        std::cerr << "Unable to open the file." << std::endl;
    }

    return res;
}

DenseGraph transferMatrix(vector<int> dataMatrix){
	
	DenseGraph graph;
	
	graph.initDenseGraph(dataMatrix.size(),1);
	
	int nodeLine = 0;
	nodeLine = (int )sqrt(dataMatrix.size());
	
	for(int v = 0 ; v < dataMatrix.size() ; v ++ ){
		for(int i = 0 ; i < dataMatrix.size() ; i ++ ){
			
			if(v == i )
				graph.g.push_back(false);
			else if(v%nodeLine == 0){
				if(i == v+1|| i == v+nodeLine || i == v-nodeLine){
					if(dataMatrix.at(i) == 1)// || dataMatrix.at(v) == 1)
						graph.g.push_back(true);
					else
						graph.g.push_back(false);
				}
				else 
					graph.g.push_back(false);
			}
			else if(v%nodeLine == (nodeLine -1) ){
				if(i == v-1|| i == v+nodeLine || i == v-nodeLine){
					if(dataMatrix.at(i) == 1)// || dataMatrix.at(v) == 1)
						graph.g.push_back(true);
					else
						graph.g.push_back(false);
				}
				else 
					graph.g.push_back(false);
			}
			else if(i == v+1 || i == v-1 || i == v+nodeLine || i == v-nodeLine){	
				if(dataMatrix.at(i) == 0 || dataMatrix.at(v) == 0)
					graph.g.push_back(false);
				else
					graph.g.push_back(true);
			}
			else
				graph.g.push_back(false);
		
		}
		
		graph.g2.push_back(graph.g);
		graph.g.clear();
	}
  
	return graph;
}

vector<int> road;

SDL_Renderer *mainRender;

static int sequence = 0;

int lineNumber;

static bool inRoad = false;

int width,high;

static int seq = 1;

bool endGame = false;

int totalNode;

vector<int> dataMatrix;

void initMap(vector<int> dataMatrix,int totalNode){

    mainRender = background.setRenderBitmap(mainRender,background.dstrect);

	lineNumber = (int)sqrt(totalNode);

	for(int i = 0;i<dataMatrix.size();i++){
		if( dataMatrix.at(i) == 0){
			
			(block->dstrect).x = (i%lineNumber)*(block->width);

			(block->dstrect).y = (i/lineNumber)*(block->high);

			mainRender = block->setRenderBitmap(mainRender,block->dstrect);
		}
	}
}

Uint32 starMove(Uint32 interval, void *param)
{
	static int xPoint,yPoint;

	if(!inRoad && sequence != (lineNumber*lineNumber -1 ) ){

		inRoad = true;
		sequence = road.at(seq);
		seq++;
	
		//cout<<sequence<<"\t";
	
		if(sequence < lineNumber )
			xPoint = 0;
		else
			xPoint = sequence%lineNumber;
		
		yPoint = sequence/lineNumber;

		//cout<<xPoint<<"\t"<<yPoint;
		
		xPoint = xPoint*(actorStar->dstrect).w;
		yPoint = yPoint*(actorStar->dstrect).h;

	}

		if(xPoint == (actorStar->dstrect).x){

			if(yPoint > (actorStar->dstrect).y ){
				initMap(dataMatrix,totalNode);
				int yOrign = (actorStar->dstrect).y;
				
				(actorStar->dstrect).y += ((actorStar->dstrect).h/4);
				
				mainRender = actorStar->setRenderBitmap(mainRender,actorStar->dstrect);
			
				(actorStarCover->dstrect.y) = yOrign;
				(actorStarCover->dstrect.x) = (actorStar->dstrect).x;
				
				(actorStarCover->dstrect.w) = width;
				(actorStarCover->dstrect.h) = high/4;
				
			//	cout<<actorStarCover.dstrect.w<<"\t"<<actorStarCover.dstrect.h<<endl;

				mainRender = actorStarCover->setRenderBitmap(mainRender,actorStarCover->dstrect);

				SDL_RenderPresent(mainRender);
			}
			else if(yPoint < (actorStar->dstrect).y ){
				initMap(dataMatrix,totalNode);
				(actorStar->dstrect).y -= ((actorStar->dstrect).h/4);
				
				mainRender = actorStar->setRenderBitmap(mainRender,actorStar->dstrect);
		
				(actorStarCover->dstrect).y = (actorStar->dstrect).y + high;
				(actorStarCover->dstrect).x = (actorStar->dstrect).x;
				
				(actorStarCover->dstrect).w = width;
				(actorStarCover->dstrect).h = high/4;	
				
				mainRender = actorStarCover->setRenderBitmap(mainRender,actorStarCover->dstrect);

				SDL_RenderPresent(mainRender);
			}
			else if(yPoint ==(actorStar->dstrect).y )
				inRoad =false;
		}
		else if(yPoint == (actorStar->dstrect).y){
			if(xPoint > (actorStar->dstrect).x ){
				initMap(dataMatrix,totalNode);
				int xOrign = (actorStar->dstrect).x;
				
				(actorStar->dstrect).x += ((actorStar->dstrect).w/4);
				
				mainRender = actorStar->setRenderBitmap(mainRender,actorStar->dstrect);
		
				(actorStarCover->dstrect).x = xOrign;
				(actorStarCover->dstrect).y = (actorStar->dstrect).y;
				
				(actorStarCover->dstrect).w = width/4;
				(actorStarCover->dstrect).h = high;
				
				mainRender = actorStarCover->setRenderBitmap(mainRender,actorStarCover->dstrect);

				SDL_RenderPresent(mainRender);
			}
			else if(xPoint < (actorStar->dstrect).x ){
				initMap(dataMatrix,totalNode);
				(actorStar->dstrect).x -= ((actorStar->dstrect).w/4);
				
				mainRender = actorStar->setRenderBitmap(mainRender,actorStar->dstrect);
		
				(actorStarCover->dstrect).x = (actorStar->dstrect).x +width; 
				(actorStarCover->dstrect).y = (actorStar->dstrect).y;
				
				(actorStarCover->dstrect).w = width/4;
				(actorStarCover->dstrect).h = high;
				
				mainRender = actorStarCover->setRenderBitmap(mainRender,actorStarCover->dstrect);

				SDL_RenderPresent(mainRender);
			}
			else if(xPoint ==(actorStar->dstrect).x )
				inRoad =false;
		}
		
		if(seq == (road.size()-1) 
			&& (actorStar->dstrect).x == (lineNumber-1)*width
			&& (actorStar->dstrect).y == (lineNumber-1)*high
			&& !inRoad)
			endGame = true;
	
	return interval;
}

int main () {
	
	DenseGraph graph; 
	
	dataMatrix = getData();
	 
	graph = transferMatrix(dataMatrix);
	
	//graph.showMatrix();
	
	
	SparseGraph graphTable;
	
	graphTable.n = dataMatrix.size();
	graphTable.directed = false;
	
	graphTable.adjMatirxTable(&graph);
	
	//graphTable.showTable();
	
	graphTable.components();
	
	totalNode = dataMatrix.size();
	
	totalNode--;
	
	SearchPath pathRoad;
	
	pathRoad.pathSreach(totalNode,graphTable);
	pathRoad.shortestPath(0,graphTable);
	
	pathRoad.pathNode(totalNode,graphTable);
	for(int i = 0;i<pathRoad.road.size(); i++){
	//	cout<<pathRoad.road.at(i)+1<<"->";
		road.push_back(pathRoad.road.at(i));
	}
	
	
// SDL part

	Image();
	
	background.getLoadBitmap("res//background.bmp");

    block->getLoadBitmap("res//block.bmp");

    block->width = block->width - (block->width)%10;
    block->high = block->high - (block->high)%10;

    (block->dstrect).x = 0;
    (block->dstrect).y = 0;
    (block->dstrect).w = block->width;
    (block->dstrect).h = block->high;

    //
	totalNode++;
	pWin.winRect.w  = block->width * sqrt(totalNode);
	pWin.winRect.h  = block->high * sqrt(totalNode);

	background.width = pWin.winRect.w;
    background.high  = pWin.winRect.h;

    background.bmpRect.x = background.dstrect.x = 0;
    background.bmpRect.y = background.dstrect.y = 0;
    background.bmpRect.w = background.dstrect.w = background.width;
    background.bmpRect.h = background.dstrect.h = background.high;

	width = block->width;
	high  = block->high;
	
	mainRender = pWin.getWindow();

    /*mainRender = background.setRenderBitmap(mainRender,background.dstrect);

	lineNumber = (int)sqrt(totalNode);

	for(int i = 0;i<dataMatrix.size();i++){
		if( dataMatrix.at(i) == 0){
			
			(block->dstrect).x = (i%lineNumber)*(block->width);

			(block->dstrect).y = (i/lineNumber)*(block->high);

			mainRender = block->setRenderBitmap(mainRender,block->dstrect);
		}
	}*/
	initMap(dataMatrix,totalNode);
	
	actorStar->getLoadBitmap("res//star.bmp");
	actorStar->dstrect.x = 0;
	actorStar->dstrect.y = 0;
	actorStar->dstrect.w = block->width;
	actorStar->dstrect.h = block->high;

	mainRender = actorStar->setRenderBitmap(mainRender,actorStar->dstrect);
	
	actorStarCover->getLoadBitmap("res//cover.bmp");
	actorStarCover->dstrect.x = 0;
	actorStarCover->dstrect.y = 0;
	actorStarCover->dstrect.w = block->width;
	actorStarCover->dstrect.h = block->high;

	SDL_RenderPresent(mainRender);
	
	SDL_TimerID actorStarMove;
	
	actorStarMove = SDL_AddTimer(200,starMove,NULL);

	bool quit = false;
	SDL_Event event;
	
	while(!quit){
		
		while (SDL_PollEvent(&event)) {
            switch (event.type) {
            
			case SDL_QUIT:
				SDL_RemoveTimer(actorStarMove);
				SDL_DestroyRenderer(mainRender);
				pWin.~window();
                quit = true;
                break;
				
			}
		}
		
		if(endGame)
			SDL_RemoveTimer(actorStarMove);
	}
	SDL_DestroyRenderer(mainRender);
 
    pWin.~window();
   
    background.~Image();

    delete(block);
    delete(actorStar);
    delete(actorStarCover);
     
    // close SDL
    SDL_Quit();

	return 0;
}

