#include "engine.h"


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
		glTranslatef(-xPos, -yPos, 0.0);
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
		glRotatef(45.0*(charDirection+turnRatio), 0.0, 0.0, 1.0);
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

