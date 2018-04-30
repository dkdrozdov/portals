#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

#define PLATFORM_WIDTH 10.0				//Terrain
#define PLATFORM_LENGTH 10.0
#define OBJECT_WALLS_MAX 100
#define OBJECT_PLATFORMS_MAX 100
#define LEVEL_WIDTH 5
#define LEVEL_LENGTH 10

#define OBJECT_WALL_GEN_WIDTH 1.0

typedef struct wall_obstacle{
	double x[2];
	double y[2];
	bool downWall;
}WALL_OBSTACLE;

typedef struct platform_square{
	double x[2];
	double y[2];
}PLATFORM_SQUARE;

PLATFORM_SQUARE object_platforms[OBJECT_PLATFORMS_MAX];
WALL_OBSTACLE object_walls[OBJECT_WALLS_MAX];
int platformCount;
int wallCount;

							//Cursor&Camera
GLdouble xPos=7, yPos=5;
GLdouble zoomFactor=0.5;
GLdouble rotateFactor=1.0;

//cursor
#define CURSOR_HAND 0
int cursorMode=CURSOR_HAND;
bool pressed_LMB=0;
GLdouble mouse_positionX, mouse_positionY;
GLdouble mouse_oldX=xPos, mouse_oldY=yPos;


//	//	//	//	//	//	//	//	//	//	//	//


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


/*	if(FILE *levelf=fopen("testlevel.txt", "r")!=NULL){
		int i=0;
		char object_name;
		char object_value_type;
		int object_number;
		int object_value[5];
		
		if(fscanf(levelf, "%d", &object_name)!=EOF){
			
			i++;
		};

		fclose(levelf);
	}
	else{
		printf("File you have can not be opened.");}*/

	object_platforms[0].x[0]=0.0;
	object_platforms[0].y[0]=0.0;
	object_platforms[0].x[1]=PLATFORM_WIDTH;
	object_platforms[0].y[1]=PLATFORM_LENGTH;
	
	object_platforms[1].x[0]=0.0;
	object_platforms[1].y[0]=0.0;
	object_platforms[1].x[1]=PLATFORM_WIDTH;
	object_platforms[1].y[1]=PLATFORM_LENGTH*2;

	platformCount=2;				

	
	initWalls();
}

int drawWalls(){					//ÏÅÍÒÓÐÀ//
	int count;
	for(count=0; count<wallCount; count++){
		glPushMatrix();
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

int drawPlatform(){					//Draw the ground
	int count;
	for(count=0; count<platformCount; count++){
		glPushMatrix();
			glTranslatef(0.0, 0.0, -0.1);
			glColor3f(0.6, 0.6, 0.6);
			glRectf(object_platforms[count].x[0], object_platforms[count].y[0],
				object_platforms[count].x[1], object_platforms[count].y[1]);
		glPopMatrix();
	}

	return 0;
}

int drawAxisHelper(){					//Draw x and y axis
	glPushMatrix();
		glTranslatef(-0.1, -0.1, 0.0);
		glLineWidth(2.5);
		glBegin(GL_LINES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(LEVEL_WIDTH*PLATFORM_WIDTH+6.0, 0.0, 0.0);
			glColor3f(0.0, 0.0, 1.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, LEVEL_LENGTH*PLATFORM_LENGTH+6.0, 0.0);
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(0.0, 0.0, ((LEVEL_WIDTH*PLATFORM_WIDTH)+
						(LEVEL_LENGTH*PLATFORM_LENGTH))/2+6.0);
		glEnd();
		glLineWidth(1.0);
	glPopMatrix();

	return 0;
}

int drawGrid(){						//Draw grid
	int count;
	glPushMatrix();	
		glTranslatef(0.0, 0.0, 0.1);
		glBegin(GL_LINES);
			glColor3f(0.0, 1.0, 0.0);
			for(count=0; count<=LEVEL_WIDTH; count++){
				glVertex3f(count*PLATFORM_WIDTH, -3.0, 0.0);
				glVertex3f(count*PLATFORM_WIDTH,
						 PLATFORM_LENGTH*LEVEL_LENGTH+3.0, 0.0);
			}

			for(count=0; count<=LEVEL_LENGTH; count++){
				glVertex3f(-3.0, count*PLATFORM_LENGTH, 0.0);
				glVertex3f(PLATFORM_WIDTH*LEVEL_WIDTH+3.0,
						count*PLATFORM_LENGTH, 0.0);
			}
		glEnd();
	glPopMatrix();
}


void display(void){			//DISPLAY//
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glPushMatrix();	
		glTranslatef(-xPos, -yPos, -60.0);
		glRotatef(-45.0*(rotateFactor-1.0), 0.0, 0.0, 1.0);
		glScalef(1.0*zoomFactor, 1.0*zoomFactor, 1.0);
		drawAxisHelper();
		drawGrid();
		drawPlatform();
		drawWalls();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-14.0, 14.0,
		-10.0, 10.0,
		30.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int mouse_unproject(int x, int y, GLdouble *wx, GLdouble *wy){
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realY;
	GLdouble wz;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	realY=viewport[3]-(GLint)y-1;
	gluUnProject((GLdouble)x, (GLdouble)realY, 0.0, 
		      mvmatrix, projmatrix, viewport,
		      wx, wy, &wz);
}

void motion(int x, int y){
	if(pressed_LMB){
		GLdouble realX, realY;
		mouse_unproject(x, y, &realX, &realY);

		xPos=mouse_oldX-realX;
		yPos=mouse_oldY-realY;

		glutPostRedisplay();
	}
}

void mouse(int button, int state, int x, int y){
	if(state==GLUT_DOWN){
		switch(button){
			case(GLUT_LEFT_BUTTON):{
				GLdouble realX, realY;
				mouse_unproject(x, y, &realX, &realY);

				pressed_LMB=true;
	
				mouse_oldX=xPos+realX;
				mouse_oldY=yPos+realY;
				glutPostRedisplay();
				break;}

			case(3):{
				if(zoomFactor+0.1<1.0){
				zoomFactor+=0.1;}
				
				glutPostRedisplay();
				break;}

			case(4):{
				if(zoomFactor-0.1>0.1){
				zoomFactor-=0.1;}
				glutPostRedisplay();
				break;}
		}
	}
	else{
		switch(button){
			case(GLUT_MIDDLE_BUTTON):{
				break;
			}

			case(GLUT_LEFT_BUTTON):{
				pressed_LMB=false;
				break;
			}

			case(GLUT_RIGHT_BUTTON):{
				break;
			}
		}
	}
}

void passive(int x, int y){
	mouse_positionX;
	mouse_positionY;
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Level Editor");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutMainLoop();

	return 0;
}
