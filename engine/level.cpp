#include "engine.h"


int initPlatforms(){
	object_platforms[0].x[0]=0.0;
	object_platforms[0].y[0]=0.0;
	object_platforms[0].x[1]=PLATFORM_WIDTH;
	object_platforms[0].y[1]=PLATFORM_LENGTH;
	
	object_platforms[1].x[0]=0.0;
	object_platforms[1].y[0]=PLATFORM_LENGTH-OBJECT_WALL_GEN_WIDTH;
	object_platforms[1].x[1]=PLATFORM_WIDTH;
	object_platforms[1].y[1]=PLATFORM_LENGTH*2;

	platformCount=2;

	return 0;
}

int initWalls(){
	int count;
	for(count=0; count<platformCount; count++){
		object_walls[wallCount].x[0]=object_platforms[count].x[0];	//left
		object_walls[wallCount].y[0]=object_platforms[count].y[0];
		object_walls[wallCount].x[1]=object_platforms[count].x[0]+OBJECT_WALL_GEN_WIDTH;
		object_walls[wallCount].y[1]=object_platforms[count].y[1];
		wallCount++;

		object_walls[wallCount].x[0]=object_platforms[count].x[0];	//up
		object_walls[wallCount].y[0]=object_platforms[count].y[1];
		object_walls[wallCount].x[1]=object_platforms[count].x[1];
		object_walls[wallCount].y[1]=object_platforms[count].y[1]-OBJECT_WALL_GEN_WIDTH;
		wallCount++;

		object_walls[wallCount].x[0]=object_platforms[count].x[1];	//right
		object_walls[wallCount].y[0]=object_platforms[count].y[1];
		object_walls[wallCount].x[1]=object_platforms[count].x[1]-OBJECT_WALL_GEN_WIDTH;
		object_walls[wallCount].y[1]=object_platforms[count].y[0];
		wallCount++;
		
		object_walls[wallCount].x[0]=object_platforms[count].x[1];	//down
		object_walls[wallCount].y[0]=object_platforms[count].y[0];
		object_walls[wallCount].x[1]=object_platforms[count].x[0];
		object_walls[wallCount].y[1]=object_platforms[count].y[0]+OBJECT_WALL_GEN_WIDTH;
		wallCount++;}
	return 0;
}

