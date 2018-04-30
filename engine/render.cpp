#include "store.h"
#include "mechanics.h"
#include "input.h"

//Level
OBSTACLE_WALL level_walls[WALL_MAX];
PLATFORM level_platforms[PLATFORM_MAX];
UNIT unit_npc[UNIT_MAX];
int n_wall=0, n_platform=0, n_npc=1;

//Character
UNIT unit_player={5.0, 5.0, PLAYER_SPEED, PLAYER_HITBOX, 0, 1};

//

//Keyboard
int turn_ratio=0;
unsigned char pressedKey;
bool key_motion[4]={0, 0, 0, 0};

//Mouse
double mouse_x, mouse_y;
double window_mouse_x, window_mouse_y;
int mouse_left=GLUT_UP;

//Render
double camera_x=PLATFORM_WIDTH/*unit_player.x*/, camera_y=PLATFORM_LENGTH/*unit_player.y*/;
bool camera_fixed=true;

//Magic
MAGIC magic_object[MAGIC_MAX];
int n_magic;
int state_spell[N_WORDS_MAX][N_RUNES_MAX];
int spell_sentence[N_WORDS_MAX];
int n_word=0, n_rune[N_WORDS_MAX];


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

int draw_circle(GLint edges, GLdouble size){
	int i;
	glPushMatrix();
	glScalef(size, size, 1.0);
	glBegin(GL_LINE_LOOP);
		for(i=0; i<edges; i++){
			glVertex2f(cos((2*3.14*i)/edges), sin((2*3.14*i)/edges));}
	glEnd();
	glPopMatrix();
	return 0;
}

int draw_unit(UNIT unit){

	//Direction arrow
	glPushMatrix();
		glTranslatef(-camera_x+unit.x, 
			     -camera_y+unit.y, 0.0);
		glRotatef(unit.direction, 0.0, 0.0, 1.0);
		glBegin(GL_LINES);		
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(0.0, 0.0);
			glVertex2f(unit.hitbox, 0.0);
		glEnd();
	glPopMatrix();

	//Hitbox circle
	glPushMatrix();
		glTranslatef(-camera_x+unit.x,
			     -camera_y+unit.y, 0.1);
		glColor3f(0.2, 0.2, 1.0);
		draw_circle(30, (GLdouble)unit.hitbox);
	glPopMatrix();

	//Hit bar
	glPushMatrix();
		glTranslatef(-camera_x+unit.x,
			     -camera_y+unit.y, 1.0);
		glRotatef(45.0*turn_ratio, 0.0, 0.0, 1.0);
		glTranslatef(-unit.hitbox, 1.0, 0.0);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(0.0, 0.1);
			glVertex2f(0.0, 0.2);
			glVertex2f((unit.state[0].value*unit.hitbox*2)/unit.max_hp, 0.2);
			glVertex2f((unit.state[0].value*unit.hitbox*2)/unit.max_hp, 0.1);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(0.0, 0.1);
			glVertex2f(0.0, 0.2);
			glVertex2f(unit.hitbox*2, 0.2);
			glVertex2f(unit.hitbox*2, 0.1);
		glEnd();
	glPopMatrix();

	return 0;
}

int draw_magic(MAGIC magic){
	glPushMatrix();
		glTranslatef(-camera_x+magic.x,
			     -camera_y+magic.y, 0.1);
		glColor3f(1.0, 1.0, 1.0);
		draw_circle(30, (GLdouble)magic.size);
	glPopMatrix();
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
	glEnable(GL_DEPTH_TEST);
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

int draw_magic_objects(){
	int i;
	for(i=0; i<n_magic; i++){
		draw_magic(magic_object[i]);}
	return 0;
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -20.0);
		glRotatef(-45.0*turn_ratio, 0.0, 0.0, 1.0);
		draw_platforms();
		draw_walls();
		draw_unit(unit_player);
		draw_npcs();
		draw_axis();
		draw_magic_objects();
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

int mouse_unproject(int x, int y, GLdouble *wx, GLdouble *wy, GLdouble *wz){
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realY;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	realY=viewport[3]-(GLint)y;
	gluUnProject((GLdouble)x, (GLdouble)realY, 0.0, 
		      mvmatrix, projmatrix, viewport,
		      wx, wy, wz);
}

void mouse_motion(int x, int y){
	double real_x, real_y, real_z;

	window_mouse_x=x;
	window_mouse_y=y;
	glPushMatrix();	
		glRotatef(-45.0*turn_ratio, 0.0, 0.0, 1.0);
		mouse_unproject(x, y, &real_x, &real_y, &real_z);
	glPopMatrix();
	mouse_x=real_x+camera_x;
	mouse_y=real_y+camera_y;

	refresh_player_angle();

	glutPostRedisplay();
//	printf("%f, %f\n", mouse_x, mouse_y);
}

void keyboard(unsigned char key, int x, int y){
	determineKeyState(key, 1);
}

void keyboard_up(unsigned char key, int x, int y){
	determineKeyState(key, 0);
	keystroke(key);
}

void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT:
			{
				mouse_left=state;
				mouse_motion(x, y);
				break;}
	}
}

void idle_frames(void){
	Sleep(FRAME_TIME*1000);

	int i;
	magic_process();
	state_process();

	if(unit_player.state[0].value<=0){
		printf("You are dead!\n");
		exit(0);
	}

	if(mouse_left==GLUT_DOWN&&(!(unit_player.x==mouse_x&&unit_player.y==mouse_y))){
		mouse_motion(window_mouse_x, window_mouse_y);
		char_move(&unit_player, mouse_x, mouse_y);}

	if(!camera_fixed){
		camera_x=unit_player.x;
		camera_y=unit_player.y;}


	
	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(690, 450);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Engine");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
//	glutPassiveMotionFunc(mouse_motion);
	glutMotionFunc(mouse_motion);
	glutMouseFunc(mouse);
	glutIdleFunc(idle_frames);
	glutKeyboardUpFunc(keyboard_up);
	glutMainLoop();

	return 0;
}
