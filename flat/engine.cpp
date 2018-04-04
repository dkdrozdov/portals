#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

#define PLATFORM_WIDTH 10.0	//Terrain
#define PLATFORM_LENGTH 10.0
#define OBJECT_WALLS_MAX 100
#define OBJECT_PLATFORMS_MAX 100

#define OBJECT_WALL_GEN_WIDTH 1.0

typedef struct segment{
	double x1;
	double y1;
	double x2;
	double y2;
}SEGMENT;

typedef struct wall_obstacle{
	double x[2];
	double y[2];
}WALL_OBSTACLE;

typedef struct platform_square{
	double x[2];
	double y[2];
}PLATFORM_SQUARE;

#define WALL_HEIGHT 5.0
WALL_OBSTACLE object_walls[OBJECT_WALLS_MAX];
PLATFORM_SQUARE object_platforms[OBJECT_PLATFORMS_MAX];
int wallCount=0, platformCount=0;

#define CHAR_SPEED 0.10		//Character&Camera
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
GLdouble xPos=5.0, yPos=5.0;
double xCharRelative=0.0, yCharRelative=0.0;
int charDirection=0;


unsigned char pressedKey;	//Keyboard
bool keyPressed[4]={0, 0, 0, 0};
#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3

//	//	//	//	//	//	//	//	//	//	// 	//

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

void init(void){					//Initialization
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	object_platforms[0].x[0]=0.0;
	object_platforms[0].y[0]=0.0;
	object_platforms[0].x[1]=PLATFORM_WIDTH;
	object_platforms[0].y[1]=PLATFORM_LENGTH;
	
	object_platforms[1].x[0]=0.0;
	object_platforms[1].y[0]=0.0;
	object_platforms[1].x[1]=PLATFORM_WIDTH;
	object_platforms[1].y[1]=PLATFORM_LENGTH*2;

	platformCount=2;				//ÏÅÍÒÓÐÀ//

	initWalls();
}

//				DRAWING FUNCTIONS			

int drawPlatform(){					//Draw the ground
	int count;
	for(count=0; count<platformCount; count++){
		glPushMatrix();
			glTranslatef(-xPos, -yPos, -0.1);
			glColor3f(0.6, 0.6, 0.6);
			glRectf(object_platforms[count].x[0], object_platforms[count].y[0],
				object_platforms[count].x[1], object_platforms[count].y[1]);
		glPopMatrix();
	}

	return 0;
}

int drawAxisHelper(){					//Draw x and y axis
	glPushMatrix();
		glTranslatef(-xPos+0.1, -yPos, 0.0);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(100.0, 0.0, 0.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 100.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 100.0);
		glEnd();
	glPopMatrix();

	return 0;
}

int drawChar(){						//Draw a character
	glPushMatrix();
		glRotatef(45.0*(charDirection), 0.0, 0.0, 1.0);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, CHAR_HITBOX);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glBegin(GL_LINES);
			glColor3f(0.2, 0.2, 1.0);
			glVertex2f(-CHAR_HITBOX, CHAR_HITBOX);
			glVertex2f(CHAR_HITBOX, CHAR_HITBOX);

			glVertex2f(-CHAR_HITBOX, -CHAR_HITBOX);
			glVertex2f(-CHAR_HITBOX, CHAR_HITBOX);

			glVertex2f(-CHAR_HITBOX, -CHAR_HITBOX);
			glVertex2f(CHAR_HITBOX, -CHAR_HITBOX);
			
			glVertex2f(CHAR_HITBOX, -CHAR_HITBOX);
			glVertex2f(CHAR_HITBOX, CHAR_HITBOX);
		glEnd();
	glPopMatrix();

	return 0;
}

int drawWalls(){					//ÏÅÍÒÓÐÀ//
	int count;
	for(count=0; count<wallCount; count++){
		glPushMatrix();
			glTranslatef(-xPos, -yPos, 0.1);
			glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_POLYGON);
				glVertex2f(object_walls[count].x[0],object_walls[count].y[0]);
				glVertex2f(object_walls[count].x[0],object_walls[count].y[1]);
				glVertex2f(object_walls[count].x[1],object_walls[count].y[1]);
				glVertex2f(object_walls[count].x[1],object_walls[count].y[0]);
			glEnd();
		glPopMatrix();}

	return 0;
}

//				CALLBACK FUNCTIONS

void display(void){					//Render the frame
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -20.0);
		drawPlatform();
		drawWalls();
		drawChar();
		drawAxisHelper();
	glPopMatrix();


	glutSwapBuffers();	
}

void reshape(int w, int h){				//Window size changing
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-14.0, 14.0, 
		-10.0, 10.0,
		1.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int swapDouble(double *a, double *b){
	double swap=*a;
	
	*a=*b;
	*b=swap;

	return 0;
}

bool checkCrossing(SEGMENT s1, SEGMENT s2, double *crosspoint){
	float s1_x, s1_y, s2_x, s2_y;
	s1_x=s1.x2-s1.x1;
	s1_y=s1.y2-s1.y1;
	s2_x=s2.x2-s2.x1;
	s2_y=s2.y2-s2.y1;

	float s, t;
	s=(-s1_y*(s1.x1-s2.x1)+s1_x*(s1.y1-s2.y1))/(-s2_x*s1_y+s1_x*s2_y);
	t=(s2_x*(s1.y1-s2.y1)-s2_y*(s1.x1-s2.x1))/(-s2_x*s1_y+s1_x*s2_y);

	if(s>=0 && s<=1 && t>=0 && t<=1)
	{
		//Collision detected
		crosspoint[0]=s1.x1+(t*s1_x);
		crosspoint[1]=s1.y1+(t*s1_y);
		return true;
	}

	return false; //No collision
}

bool checkObstacles(double newPosX, double newPosY){
	int count=0, i;
	double intersection[2]={0.0, 0.0};

	SEGMENT hitboxLeft, hitboxRight, hitboxBack, hitboxFront, wallSegment[4];

	hitboxLeft.x1=newPosX-CHAR_HITBOX;
	hitboxLeft.y1=newPosY-CHAR_HITBOX;
	hitboxLeft.x2=newPosX-CHAR_HITBOX;
	hitboxLeft.y2=newPosY+CHAR_HITBOX;

	hitboxRight.x1=newPosX+CHAR_HITBOX;
	hitboxRight.y1=newPosY-CHAR_HITBOX;
	hitboxRight.x2=newPosX+CHAR_HITBOX;
	hitboxRight.y2=newPosY+CHAR_HITBOX;

	hitboxBack.x1=newPosX-CHAR_HITBOX;
	hitboxBack.y1=newPosY-CHAR_HITBOX;
	hitboxBack.x2=newPosX-CHAR_HITBOX;
	hitboxBack.y2=newPosY+CHAR_HITBOX;

	hitboxFront.x1=newPosX-CHAR_HITBOX;
	hitboxFront.y1=newPosY+CHAR_HITBOX;
	hitboxFront.x2=newPosX+CHAR_HITBOX;
	hitboxFront.y2=newPosY+CHAR_HITBOX;

	while(count<wallCount){
		wallSegment[0].x1=object_walls[count].x[0];
		wallSegment[0].y1=object_walls[count].y[0];
		wallSegment[0].x2=object_walls[count].x[0];
		wallSegment[0].y2=object_walls[count].y[1];

		wallSegment[1].x1=object_walls[count].x[0];
		wallSegment[1].y1=object_walls[count].y[1];
		wallSegment[1].x2=object_walls[count].x[1];
		wallSegment[1].y2=object_walls[count].y[1];

		wallSegment[2].x1=object_walls[count].x[1];
		wallSegment[2].y1=object_walls[count].y[1];
		wallSegment[2].x2=object_walls[count].x[1];
		wallSegment[2].y2=object_walls[count].y[0];

		wallSegment[3].x1=object_walls[count].x[1];
		wallSegment[3].y1=object_walls[count].y[0];
		wallSegment[3].x2=object_walls[count].x[0];
		wallSegment[3].y2=object_walls[count].y[0];

		for(i=0; i<4; i++){			//for each side of wall
			if(checkCrossing(hitboxFront, wallSegment[i], intersection)){
				return false;
			}
	
			if(checkCrossing(hitboxBack, wallSegment[i], intersection)){
				return false;
			}
	
			if(checkCrossing(hitboxRight, wallSegment[i], intersection)){
				return false;
			}
	
			if(checkCrossing(hitboxLeft, wallSegment[i], intersection)){
				return false;
			}
		}

		count++;
	}

	return true;
}

int changePosition(){					//Changes the position of the character
	switch(charDirection){			//The displacement of the direction is
						//related to the specific camera position
		case DIRECTION_UP_RIGHT:{
			if(checkObstacles(xPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR), 
					  yPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR))){
			xPos=xPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);
			yPos=yPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);}
			break;}

		case DIRECTION_UP:{
			if(checkObstacles(xPos, yPos+CHAR_SPEED)){
			yPos=yPos+CHAR_SPEED;}
			break;}

		case DIRECTION_RIGHT:{
			if(checkObstacles(xPos+CHAR_SPEED, yPos)){
			xPos=xPos+CHAR_SPEED;}
			break;}

		case DIRECTION_DOWN_LEFT:{
			if(checkObstacles(xPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR), 
					  yPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR))){
			xPos=xPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);
			yPos=yPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);}
			break;}

		case DIRECTION_LEFT:{
			if(checkObstacles(xPos-CHAR_SPEED, yPos)){
			xPos=xPos-CHAR_SPEED;}
			break;}

		case DIRECTION_DOWN:{
			if(checkObstacles(xPos, yPos-CHAR_SPEED)){
			yPos=yPos-CHAR_SPEED;}
			break;}

		case DIRECTION_UP_LEFT:{
			if(checkObstacles(xPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR), 
					  yPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR))){
			xPos=xPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);
			yPos=yPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);}
			
			break;}

		case DIRECTION_DOWN_RIGHT:{
			if(checkObstacles(xPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR), 
					  yPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR))){
			xPos=xPos+(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);
			yPos=yPos-(CHAR_SPEED*DIAGONAL_MOTION_FACTOR);}
			break;}

		default:{break;}
	}
}

int determineCharDirection(){				//Sets the direction of char,
	if(keyPressed[KEY_A]){				//considering pressed keys
		charDirection=DIRECTION_LEFT;}

	if(keyPressed[KEY_D]){
		charDirection=DIRECTION_RIGHT;}

	if(keyPressed[KEY_S]){
		charDirection=DIRECTION_DOWN;
		if(keyPressed[KEY_A]){
			charDirection=DIRECTION_DOWN_LEFT;}
		if(keyPressed[KEY_D]){
			charDirection=DIRECTION_DOWN_RIGHT;}
	}

	if(keyPressed[KEY_W]){
		charDirection=DIRECTION_UP;
		if(keyPressed[KEY_A]){
			charDirection=DIRECTION_UP_LEFT;}
		if(keyPressed[KEY_D]){
			charDirection=DIRECTION_UP_RIGHT;}}
	return 0;
}

bool movingCondition(){					//Check for moving possibility
	if(!(keyPressed[KEY_W]|keyPressed[KEY_A]|keyPressed[KEY_S]|keyPressed[KEY_D])){
		glutIdleFunc(NULL);
		return false;}

	if((keyPressed[KEY_W]&&keyPressed[KEY_S])|
	(keyPressed[KEY_A]&&keyPressed[KEY_D])){
		return false;}

	return true;
}

void charMove(void){					//Movement animation
	determineCharDirection();
	if(movingCondition()){
		changePosition();
		glutPostRedisplay();
	}
}

int determineKeyState(unsigned char usedKey, bool newState){ //Sets the state for used key
	switch(usedKey){
		case 'w':{
			keyPressed[KEY_W]=newState;
			break;}

		case 'a':{
			keyPressed[KEY_A]=newState;
			break;}

		case 's':{
			keyPressed[KEY_S]=newState;
			break;}

		case 'd':{
			keyPressed[KEY_D]=newState;
			break;}

		default:{
			break;}
	}
	return 0;
}

void keyboard(unsigned char key, int x, int y){		//Reaction to keystrokes
	determineKeyState(key, 1);
	glutIdleFunc(charMove);
}

void keyboard_up(unsigned char key, int x, int y){	//Reaction to releasing the keys
	determineKeyState(key, 0);
}

//				MAIN
int main(int argc, char **argv){			//Entering the main loop
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Engine");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutMainLoop();

	return 0;
}
