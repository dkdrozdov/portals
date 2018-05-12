#include "input.h"

int initPlatforms(){
	level_platforms[0].x[0]=0.0;
	level_platforms[0].y[0]=0.0;
	level_platforms[0].x[1]=PLATFORM_WIDTH*2;
	level_platforms[0].y[1]=PLATFORM_LENGTH*2;

	n_platform=1;

	return 0;
}

int initWalls(){
	int count;
	for(count=0; count<n_platform; count++){
		level_walls[n_wall].x[0]=level_platforms[count].x[0];	//left
		level_walls[n_wall].y[0]=level_platforms[count].y[0];
		level_walls[n_wall].x[1]=level_platforms[count].x[0]+WALL_GEN_WIDTH;
		level_walls[n_wall].y[1]=level_platforms[count].y[1];
		n_wall++;

		level_walls[n_wall].x[0]=level_platforms[count].x[0];	//up
		level_walls[n_wall].y[0]=level_platforms[count].y[1];
		level_walls[n_wall].x[1]=level_platforms[count].x[1];
		level_walls[n_wall].y[1]=level_platforms[count].y[1]-WALL_GEN_WIDTH;
		n_wall++;

		level_walls[n_wall].x[0]=level_platforms[count].x[1];	//right
		level_walls[n_wall].y[0]=level_platforms[count].y[1];
		level_walls[n_wall].x[1]=level_platforms[count].x[1]-WALL_GEN_WIDTH;
		level_walls[n_wall].y[1]=level_platforms[count].y[0];
		n_wall++;
		
		level_walls[n_wall].x[0]=level_platforms[count].x[1];	//down
		level_walls[n_wall].y[0]=level_platforms[count].y[0];
		level_walls[n_wall].x[1]=level_platforms[count].x[0];
		level_walls[n_wall].y[1]=level_platforms[count].y[0]+WALL_GEN_WIDTH;
		n_wall++;}
	return 0;
}

int loadLevel(){
	initPlatforms();
	initWalls();
	unit_list[0].x=5;
	unit_list[0].y=5;
	unit_list[0].speed=PLAYER_SPEED;
	unit_list[0].hitbox=PLAYER_HITBOX;
	unit_list[0].direction=0;
	unit_list[0].state[0].time=0;
	unit_list[0].state[0].value=10;
	unit_list[0].state[0].role=EFFECT_LIFE;
	unit_list[0].state[0].type=EFFECT_LIFE;
	unit_list[0].max_hp=10;
	unit_list[0].n_state=1;

	unit_list[1].x=level_platforms[0].x[1]/1.5;
	unit_list[1].y=level_platforms[0].y[1]/2+WALL_GEN_WIDTH/2;
	unit_list[1].speed=PLAYER_SPEED;
	unit_list[1].hitbox=PLAYER_HITBOX;
	unit_list[1].direction=0;
	unit_list[1].state[0].time=0;
	unit_list[1].state[0].value=5;
	unit_list[1].state[0].role=EFFECT_LIFE;
	unit_list[1].state[0].type=EFFECT_LIFE;
	unit_list[1].max_hp=10;
	unit_list[1].n_state=1;

//	level_walls[n_wall].x[0]=level_platforms[0].x[0];
//	level_walls[n_wall].y[0]=level_platforms[0].y[1]/2-WALL_GEN_WIDTH/2;
//	level_walls[n_wall].x[1]=level_platforms[0].x[1]/1.5;
//	level_walls[n_wall].y[1]=level_platforms[0].y[1]/2+WALL_GEN_WIDTH/2;
//	n_wall++;

	level_walls[n_wall].x[0]=level_platforms[0].x[1]/3-WALL_GEN_WIDTH/2;
	level_walls[n_wall].y[0]=level_platforms[0].y[1]/1.5;
	level_walls[n_wall].x[1]=level_platforms[0].x[1]/3+WALL_GEN_WIDTH/2;
	level_walls[n_wall].y[1]=level_platforms[0].y[1];
	n_wall++;
}
