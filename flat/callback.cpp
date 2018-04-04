#include "engine.h"

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	
	initPlatforms();
	initWalls();
}


void display(void){
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
	glutIdleFunc(charMove);
}

void keyboard_up(unsigned char key, int x, int y){
	determineKeyState(key, 0);
}

