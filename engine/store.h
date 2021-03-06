/*				�.�.�.�.�.�.�					*/
#pragma once
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Render
const double FRAME_TIME=0.01;

//Level
const double PLATFORM_WIDTH=20.0;
const double PLATFORM_LENGTH=20.0;
const int UNIT_MAX=10;
const int WALL_MAX=10;
const int PLATFORM_MAX=10;
const int MAGIC_MAX=10;
const double WALL_GEN_WIDTH=1.0;
const double WALL_HEIGHT=5.0;

//Character
const double PLAYER_SPEED=5.0;
const double PLAYER_HITBOX=1.0;

//Effects
const int EFFECT_LIFE=0;
const int EFFECT_HP=1;

//Keyboard
const int KEY_W=0;
const int KEY_A=1;
const int KEY_S=2;
const int KEY_D=3;

//Mouse
extern double mouse_x, mouse_y;
extern double window_mouse_x, window_mouse_y;
extern int mouse_left;

typedef struct obstacle_wall_struct{
	double x[2];
	double y[2];
}OBSTACLE_WALL;

typedef struct platform_struct{
	double x[2];
	double y[2];
}PLATFORM;

typedef struct effect_struct{
	double time;
	double value;
	int type;
	int role;
	int id;
}EFFECT;

typedef struct unit_struct{
	double x, y;
	double speed;
	double hitbox;
	double direction;
	int voice;
	int max_hp;
	EFFECT state[10];
	int n_state;
}UNIT;

typedef struct object_magic_struct{
	double x, y;
	double target_x, target_y;
	double speed;
	
	double begin_size;
	double size;
	double max_size;

	double begin_time;
	double time;

	int type, form, performance;
	bool exclusion;

	int owner;
	int id;

	int cost;

	bool is_form, is_performance;
	EFFECT effect[10];
	int n_effect;
}MAGIC;

typedef struct object_struct{
	double x;
	double y;
}OBJECT;

//Global data:
//level
extern OBSTACLE_WALL level_walls[WALL_MAX];
extern PLATFORM level_platforms[PLATFORM_MAX];
extern UNIT unit_list[UNIT_MAX];
extern int n_wall, n_platform, n_unit;
//camera
extern bool key_motion[4];
extern int turn_ratio;
extern bool camera_fixed;
//magic
const int N_WORDS_MAX=7, N_RUNES_MAX=3;
extern int state_spell[N_WORDS_MAX][N_RUNES_MAX];
extern int spell_sentence[N_WORDS_MAX];
extern int n_word, n_rune[N_WORDS_MAX];
extern MAGIC magic_object[MAGIC_MAX];
extern int n_magic;
//effects
extern int effect_buffer[MAGIC_MAX];
