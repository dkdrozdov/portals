#include "store.h"
#include "mechanics.h"
#include "input.h"

//Level
WALL_OBSTACLE object_walls[OBJECT_WALLS_MAX];
PLATFORM_SQUARE object_platforms[OBJECT_PLATFORMS_MAX];
int wallCount=0, platformCount=0;

//Character
CHARACTER character_player={5.0, 5.0, PLAYER_SPEED, PLAYER_HITBOX, 0};

//Keyboard
int turnRatio=1;
unsigned char pressedKey;
bool keyPressed[4]={0, 0, 0, 0};

//Render
double camera_x=character_player.x, camera_y=character_player.y;
bool camera_fixed=false;

int drawPlatform(){
	int count;
	for(count=0; count<platformCount; count++){
		glPushMatrix();
			glTranslatef(-camera_x, -camera_y, -0.1);
			glColor3f(0.6, 0.6, 0.6);
			glRectf(object_platforms[count].x[0], object_platforms[count].y[0],
				object_platforms[count].x[1], object_platforms[count].y[1]);
		glPopMatrix();
	}

	return 0;
}

int drawAxisHelper(){
	glPushMatrix();
		glTranslatef(-camera_x, -camera_y, 0.0);
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

int drawCharacter(){
	glPushMatrix();
		glTranslatef(-camera_x+character_player.x, 
			     -camera_y+character_player.y, 0.0);
		glRotatef(45.0*(character_player.direction+turnRatio), 0.0, 0.0, 1.0);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, character_player.hitbox);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-camera_x+character_player.x,
			     -camera_y+character_player.y, 0.0);
		glBegin(GL_LINES);
			glColor3f(0.2, 0.2, 1.0);
			glVertex2f(-character_player.hitbox, character_player.hitbox);
			glVertex2f(character_player.hitbox, character_player.hitbox);

			glVertex2f(-character_player.hitbox, -character_player.hitbox);
			glVertex2f(-character_player.hitbox, character_player.hitbox);

			glVertex2f(-character_player.hitbox, -character_player.hitbox);
			glVertex2f(character_player.hitbox, -character_player.hitbox);
			
			glVertex2f(character_player.hitbox, -character_player.hitbox);
			glVertex2f(character_player.hitbox, character_player.hitbox);
		glEnd();
	glPopMatrix();

	return 0;
}

int drawWalls(){					//ÏÅÍÒÓÐÀ//
	int count;
	for(count=0; count<wallCount; count++){
		glPushMatrix();
			glTranslatef(-camera_x, -camera_y, 0.1);
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


void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	
	initPlatforms();
	initWalls();
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -20.0);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		glRotatef(-45.0*turnRatio, 0.0, 0.0, 1.0);
		drawPlatform();
		drawWalls();
		drawCharacter();
		drawAxisHelper();
	glPopMatrix();


	glutSwapBuffers();	
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-14.0, 14.0, 
		-10.0, 10.0,
		1.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
	determineKeyState(key, 1);
}

void keyboard_up(unsigned char key, int x, int y){
	determineKeyState(key, 0);
	keystroke(key);
}

void idle_frames(void){
	Sleep(FRAME_TIME);

	if(movingCondition()){
		determinePlayerDirection();
		charMove(&character_player);}

	if(!camera_fixed){
		camera_x=character_player.x;
		camera_y=character_player.y;}
	
	glutPostRedisplay();
}


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Engine");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle_frames);
	glutKeyboardUpFunc(keyboard_up);
	glutMainLoop();

	return 0;
}
