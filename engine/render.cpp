#include "store.h"
#include "mechanics.h"
#include "input.h"

//Level
OBSTACLE_WALL level_walls[WALL_MAX];
PLATFORM level_platforms[PLATFORM_MAX];
UNIT unit_npc[UNIT_MAX];
int n_wall=0, n_platform=0, n_npc=1;

//Character
UNIT unit_player={5.0, 5.0, PLAYER_SPEED, PLAYER_HITBOX, 0};

//Keyboard
int turn_ratio=7;
unsigned char pressedKey;
bool key_motion[4]={0, 0, 0, 0};

//Render
double camera_x=unit_player.x, camera_y=unit_player.y;
bool camera_fixed=false;

int draw_platforms(){
	int count;
	for(count=0; count<n_platform; count++){
		glPushMatrix();
			glTranslatef(-camera_x, -camera_y, -0.1);
			glColor3f(0.6, 0.6, 0.6);
			glRectf(level_platforms[count].x[0], level_platforms[count].y[0],
				level_platforms[count].x[1], level_platforms[count].y[1]);
		glPopMatrix();
	}

	return 0;
}

int draw_axis(){
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

int draw_unit(UNIT unit){
	glPushMatrix();
		glTranslatef(-camera_x+unit.x, 
			     -camera_y+unit.y, 0.0);
		glRotatef(45.0*unit.direction, 0.0, 0.0, 1.0);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, unit.hitbox);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-camera_x+unit.x,
			     -camera_y+unit.y, 0.0);
		glBegin(GL_LINES);
			glColor3f(0.2, 0.2, 1.0);
			glVertex2f(-unit.hitbox, unit.hitbox);
			glVertex2f(unit.hitbox, unit.hitbox);

			glVertex2f(-unit.hitbox, -unit.hitbox);
			glVertex2f(-unit.hitbox, unit.hitbox);

			glVertex2f(-unit.hitbox, -unit.hitbox);
			glVertex2f(unit.hitbox, -unit.hitbox);
			
			glVertex2f(unit.hitbox, -unit.hitbox);
			glVertex2f(unit.hitbox, unit.hitbox);
		glEnd();
	glPopMatrix();

	return 0;
}

int draw_walls(){					//ÏÅÍÒÓÐÀ//
	int count;
	for(count=0; count<n_wall; count++){
		glPushMatrix();
			glTranslatef(-camera_x, -camera_y, 0.1);
			glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_POLYGON);
				glVertex2f(level_walls[count].x[0],level_walls[count].y[0]);
				glVertex2f(level_walls[count].x[0],level_walls[count].y[1]);
				glVertex2f(level_walls[count].x[1],level_walls[count].y[1]);
				glVertex2f(level_walls[count].x[1],level_walls[count].y[0]);
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
	
	loadLevel();
}

int draw_npcs(){
	int i;
	for(i=0; i<n_npc; i++){
		draw_unit(unit_npc[i]);}
	return 0;
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -20.0);
		glRotatef(-45.0, 1.0, 0.0, 0.0);
		glRotatef(-45.0*turn_ratio, 0.0, 0.0, 1.0);
		draw_platforms();
		draw_walls();
		draw_unit(unit_player);
		draw_npcs();
		draw_axis();
	glPopMatrix();


	glutSwapBuffers();	
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-23.0, 23.0, 
		-15.0, 15.0,
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

	int i;
	state_process();

	if(unit_player.state[0].value<=0){
		printf("You are dead!\n");
		exit(0);
	}

	char_move(&unit_player);

	if(!camera_fixed){
		camera_x=unit_player.x;
		camera_y=unit_player.y;}
	
	glutPostRedisplay();
}


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(690, 450);
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
