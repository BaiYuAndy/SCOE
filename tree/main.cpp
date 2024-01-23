#include "my_facility.h"
#include "tree.h"

window pWin;

SDL_Renderer* mainRender;

Image & chooseBlock(int data){
	assert(data>0 && data<=10);

	Image *nodeBlock;

	switch(data){
	case 10:
		nodeBlock->getLoadBitmap("res//score//0.bmp");
		break;

	case 1:
		nodeBlock->getLoadBitmap("res//score//1.bmp");
		break;
		
	case 2:
		nodeBlock->getLoadBitmap("res//score//2.bmp");
		break;

	case 3:
		nodeBlock->getLoadBitmap("res//score//3.bmp");
		break;
		
	case 4:
		nodeBlock->getLoadBitmap("res//score//4.bmp");
		break;
	
	case 5:
		nodeBlock->getLoadBitmap("res//score//5.bmp");
		break;
		
	case 6:
		nodeBlock->getLoadBitmap("res//score//6.bmp");
		break;

	case 7:
		nodeBlock->getLoadBitmap("res//score//7.bmp");
		break;
		
	case 8:
		nodeBlock->getLoadBitmap("res//score//8.bmp");
		break;
	
	case 9:
		nodeBlock->getLoadBitmap("res//score//9.bmp");
		break;
		
	}

	return *nodeBlock;
}

int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    
    Image background;

    //Image();
    background.getLoadBitmap("res//background.bmp");

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

    HD *root;

	root = NULL;
	int i=0;
	while(i<10){
		root = creatHeap(data[i],root);
		i++;
	}

	/*Image *block =new Image();

    block = &chooseBlock(1);

    block->dstrect.x = background.width/3;
    block->dstrect.y = 0;
    block->dstrect.w = (block->width);
    block->dstrect.h = (block->high);*/
    int initPositionX = background.width/3;
    int initPositionY = 0;

	vector<vector<int> >* q;
	q=levelOrder(root);
	
	i=0;
	
	typedef struct treeNodeInfo{
		int info;
		int xposition;
	}NI;

	vector<queue<NI*> > vRes;
	queue<NI*> res;

	queue<NI*> * hitP;

	NI *p;
	while(i<q->size()){
		int j=0;

		while(j< (q->at(i)).size() ){
			
			int choose = (q->at(i)).at(j);
			
			if(i>0 && !(hitP->empty()) ){
				
				if(choose <(hitP->front())->info ){
					initPositionX = (hitP->front())->xposition-60;
					//cout<<choose<<"\t"<<(hitP->front())->info<<endl;
					Image *block =new Image();
					block = &chooseBlock(choose);
					block->dstrect.x = initPositionX;
    				block->dstrect.y = initPositionY;
    				block->dstrect.w = (block->width);
    				block->dstrect.h = (block->high);
					mainRender =block->setRenderBitmap(mainRender,block->dstrect);
					delete(block);
					j++;
		
					p = new NI();
		
					p->info = choose;
					p->xposition = initPositionX;
					res.push(p);
					
					hitP->pop();

					initPositionY+=60;
				}
			}
			else{
				//cout<<"choose"<<choose<<"\t"<<i<<endl;	
				if(i==0){
					Image *block =new Image();
					block = &chooseBlock(choose);
					
					block->dstrect.x = initPositionX;
    				block->dstrect.y = initPositionY;
    				block->dstrect.w = (block->width);
    				block->dstrect.h = (block->high);
					mainRender =block->setRenderBitmap(mainRender,block->dstrect);
					delete(block);

					initPositionY+=60;
				}

				else{
					Image *block =new Image();
					block = &chooseBlock(choose);
					
					block->dstrect.x = initPositionX+60;
    				block->dstrect.y = initPositionY;
    				block->dstrect.w = (block->width);
    				block->dstrect.h = (block->high);
					mainRender =block->setRenderBitmap(mainRender,block->dstrect);
					delete(block);

					initPositionY+=60;
				}

				j++;
	
				p = new NI();
	
				p->info = choose;
				p->xposition = initPositionX;
				res.push(p);
			}
			
		}

		vRes.push_back(res);
		//hitP =(vRes.at(i)).front();
		hitP=&(vRes.at(i));
		int size=res.size();
		while(size--)
			res.pop();
		i++;
	}

    //mainRender =block->setRenderBitmap(mainRender,block->dstrect);

	//
    SDL_RenderPresent(mainRender);

    int close = 0; 
    //

    while (!close) {

    	//
        SDL_Event event;
 
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

                default:
                    break;
            }
        }
    }

    pWin.~window();
    delete q;
    //delete res;
    //delete block;
	return 0;
}

