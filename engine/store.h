/*				Ï.Å.Í.Ò.Ó.Ð.À					*/
#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

//Render
#define FRAME_TIME 30

//Level
#define PLATFORM_WIDTH 10.0	
#define PLATFORM_LENGTH 10.0
#define UNIT_MAX 10
#define WALL_MAX 10
#define PLATFORM_MAX 10
#define WALL_GEN_WIDTH 1.0
#define WALL_HEIGHT 5.0

//Character
#define PLAYER_SPEED 0.005
#define PLAYER_HITBOX 1.0
#define DIAGONAL_MOTION_FACTOR 0.75
#define DIRECTION_UP 0
#define DIRECTION_UP_LEFT 1
#define DIRECTION_LEFT 2
#define DIRECTION_DOWN_LEFT 3
#define DIRECTION_DOWN 4
#define DIRECTION_DOWN_RIGHT 5
#define DIRECTION_RIGHT 6
#define DIRECTION_UP_RIGHT 7

//Effects
#define LIFE 0

//Keyboard
#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3

typedef struct obstacle_wall_struct{
	double x[2];
	double y[2];
}OBSTACLE_WALL;

typedef struct platform_struct{
	double x[2];
	double y[2];
}PLATFORM;

typedef struct effect_struct{
	int time;
	int value;
	int type;
}EFFECT;

typedef struct unit_struct{
	double x;
	double y;
	double speed;
	double hitbox;
	int direction;
	EFFECT state[10];
	int n_state;
}UNIT;

typedef struct object_struct{
	double x;
	double y;
}OBJECT_INTERACTIVE;

//Global data:
extern OBSTACLE_WALL level_walls[WALL_MAX];
extern PLATFORM level_platforms[PLATFORM_MAX];
extern UNIT unit_player;
extern UNIT unit_npc[UNIT_MAX];
extern int n_wall, n_platform, n_npc;
extern bool key_motion[4];
extern int turn_ratio;
extern bool camera_fixed;
