#include "engine.h"

//Level
WALL_OBSTACLE object_walls[OBJECT_WALLS_MAX];
PLATFORM_SQUARE object_platforms[OBJECT_PLATFORMS_MAX];
int wallCount=0, platformCount=0;

//Character
GLdouble xPos=5.0, yPos=5.0;
double xCharRelative=0.0, yCharRelative=0.0;
int charDirection=0;

//Keyboard
int turnRatio=1;
unsigned char pressedKey;
bool keyPressed[4]={0, 0, 0, 0};

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
	glutKeyboardUpFunc(keyboard_up);
	glutMainLoop();

	return 0;
}
