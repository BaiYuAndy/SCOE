#include <iostream>

#include <string.h>

using namespace std;

const char* getWordByNUM(int num){
	
	const char *name = "res//word//yi.bmp";
	
	if(num>=200)
		num -=100;
	
	switch(num){
		case 0:
			name = "res//word//shu.bmp";
		break;
		
		case 1:
			name = "res//word//yi.bmp";
		break;
		
		case 2:
			name = "res//word//er.bmp";
		break;
		
		case 3:
			name = "res//word//san.bmp";
		break;
		
		case 4:
			name = "res//word//tu.bmp";
		break;
		
		case 5:
			name = "res//word//shui.bmp";
		break;
		
		case 6:
			name = "res//word//mu.bmp";
		break;
		
		case 7:
			name = "res//word//ren.bmp";
		break;
		
		case 8:
			name = "res//word//ri.bmp";
		break;
		
		case 9:
			name = "res//word//kou.bmp";
		break;
		
		case 10:
			name = "res//word//shi.bmp";
		break;
		//can choose input max number chinese word is  shi
		case 11:
			name = "res//word//wang.bmp";
			break;
			
		case 12:
			name = "res//word//da.bmp";
			break;
		
		case 13:
			name = "res//word//gui.bmp";
			break;
		
		case 14:
			name = "res//word//quan.bmp";
			break;
		
		case 15:
			name = "res//word//tian.bmp";
		break;
		
		case 100:
			name = "res//word//bian.bmp";
		break;
			
		case 101:
			name = "res//word//pin.bmp";
			break;		
		
		case 102:
			name = "res//word//jing.bmp";
		break;
		
		case 103:
			name = "res//word//miao.bmp";
		break;
		
		case 104:
			name = "res//word//sen.bmp";
		break;
		
		case 105:
			name = "res//word//zhong.bmp";
		break;
		
		default:
			//name = "res//word//yi.bmp";
		break;
		
	}
	
	return name;
}

bool setBlockMap(int (*map)[9],int x,int y){
	//cout<<*(*(map+x)+y);
	if( *(*(map+x)+y) != -1)
		return true;
	else
		return false;
	
}

int setNewBlockMap(int (*map)[9],int x,int y){
	int addDown;
	int block = *(*(map+x)+y);
	
	int blockDown = *(*(map+x+1)+y);
	
	if( blockDown == 1 && block == 0)
		addDown = 10;
	else if(blockDown == 0 && block == 1)
		addDown = 10;
	else if(blockDown == 1 && block == 1)
		addDown = 2;
	else if(blockDown ==2  && block == 1)
		addDown = 3;
	else if(blockDown ==2  && block == 0)
		addDown = 4;
	else if(blockDown == 3 && block == 0)
		addDown = 11;
	else if(blockDown == 4 && block == 1)
		addDown = 11;
	else if(blockDown == 7 && block == 1)
		addDown = 12;
	else if(blockDown ==  11 && block == 7)
		addDown = 14;
	else if(blockDown ==  12 && block == 1)
		addDown = 15;
	else if(blockDown ==  7 && block == 2)
		addDown = 15;
	else if(blockDown ==  4 && block == 4)
		addDown = 13;
	
	else if(blockDown == 10 && block == 10){
		if(*(*(map+x)+y+1) == 10)
			addDown = 100;
		else if(*(*(map+x)+y-1) == 10)
			addDown = 200;
		else 
			addDown = 0;
	}
	else if(blockDown == 9 && block == 9){
		if(*(*(map+x)+y+1) == 9)
			addDown = 101;
		else if(*(*(map+x)+y-1) == 9)
			addDown = 201;
		else 
			addDown = 0;
	}
	else if(blockDown == 8 && block == 8){
		if(*(*(map+x)+y+1) == 8)
			addDown = 102;
		else if(*(*(map+x)+y-1) == 8)
			addDown = 202;
		else 
			addDown = 0;
	}
	else if(blockDown == 5 && block == 5){
		if(*(*(map+x)+y+1) == 5)
			addDown = 103;
		else if(*(*(map+x)+y-1) == 5)
			addDown = 203;
		else 
			addDown = 0;
	}
	else if(blockDown == 6 && block == 6){
		if(*(*(map+x)+y+1) == 6)
			addDown = 104;
		else if(*(*(map+x)+y-1) == 6)
			addDown = 204;
		else 
			addDown = 0;
	}
	else if(blockDown == 7 && block == 7){
		if(*(*(map+x)+y+1) == 7)
			addDown = 105;
		else if(*(*(map+x)+y-1) == 7)
			addDown = 205;
		else 
			addDown = 0;
	}
	//
	
	else
		addDown = 0;
	
	return addDown;
}

const char* getScoreByNUM(int num){
	const char *name;
	switch(num){
		case 0:
			name = "res\\score\\0.bmp";
		break;
		
		case 1:
			name  = "res\\score\\1.bmp";
		break;                     
		case 2:                    
			name  = "res\\score\\2.bmp";
		break;                     
		case 3:                   
			name  = "res\\score\\3.bmp";
		break;                     
		case 4:                    
			name  = "res\\score\\4.bmp";
		break;                     
		case 5:                    
			name  = "res\\score\\5.bmp";
		break;                     
		case 6:                    
			name  = "res\\score\\6.bmp";
		break;                     
		case 7:                    
			name  = "res\\score\\7.bmp";
		break;                    
		case 8:                    
			name  = "res\\score\\8.bmp";
		break;                     
		case 9:                   
			name  = "res\\score\\9.bmp";
		break;
	}
	
	return name;
}