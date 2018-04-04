#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

//Level
#define PLATFORM_WIDTH 10.0	
#define PLATFORM_LENGTH 10.0
#define OBJECT_WALLS_MAX 100
#define OBJECT_PLATFORMS_MAX 100
#define OBJECT_WALL_GEN_WIDTH 1.0
#define WALL_HEIGHT 5.0

//Character
#define CHAR_SPEED 0.10		
#define CHAR_HITBOX 1.0
#define DIAGONAL_MOTION_FACTOR 0.75
#define DIRECTION_UP 0
#define DIRECTION_UP_LEFT 1
#define DIRECTION_LEFT 2
#define DIRECTION_DOWN_LEFT 3
#define DIRECTION_DOWN 4
#define DIRECTION_DOWN_RIGHT 5
#define DIRECTION_RIGHT 6
#define DIRECTION_UP_RIGHT 7

//Keyboard
#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3

typedef struct wall_obstacle{
	double x[2];
	double y[2];
}WALL_OBSTACLE;

typedef struct platform_square{
	double x[2];
	double y[2];
}PLATFORM_SQUARE;

//Engine.cpp:
extern WALL_OBSTACLE object_walls[OBJECT_WALLS_MAX];
extern PLATFORM_SQUARE object_platforms[OBJECT_PLATFORMS_MAX];
extern int wallCount, platformCount;
extern bool keyPressed[4];
extern GLdouble xPos, yPos;
extern int charDirection;

//Drawing.cpp:
int drawPlatform();
int drawWalls();
int drawChar();
int drawAxisHelper();

//Callback.cpp:
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);
void init(void);

//Level.cpp:
int initPlatforms();
int initWalls();

//Keyboard.cpp:
int determineKeyState(unsigned char usedKey, bool newState);

//Character.cpp:
void charMove(void);

//Collision.cpp:
bool checkObstacles(double newPosX, double newPosY);

