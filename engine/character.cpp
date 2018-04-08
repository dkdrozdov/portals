#include "engine.h"


int changePosition(){		
	switch((charDirection+turnRatio)%8){
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

int determineCharDirection(){				//Set the direction of char,
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
