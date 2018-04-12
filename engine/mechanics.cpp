#include "mechanics.h"


typedef struct segment{
	double x1;
	double y1;
	double x2;
	double y2;
}SEGMENT;

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

bool checkObstacles(double newPosX, double newPosY, double hitbox){
	int count=0, i;
	double intersection[2]={0.0, 0.0};

	SEGMENT hitboxLeft, hitboxRight, hitboxBack, hitboxFront, wallSegment[4];

	hitboxLeft.x1=newPosX-hitbox;
	hitboxLeft.y1=newPosY-hitbox;
	hitboxLeft.x2=newPosX-hitbox;
	hitboxLeft.y2=newPosY+hitbox;

	hitboxRight.x1=newPosX+hitbox;
	hitboxRight.y1=newPosY-hitbox;
	hitboxRight.x2=newPosX+hitbox;
	hitboxRight.y2=newPosY+hitbox;

	hitboxBack.x1=newPosX-hitbox;
	hitboxBack.y1=newPosY-hitbox;
	hitboxBack.x2=newPosX-hitbox;
	hitboxBack.y2=newPosY+hitbox;

	hitboxFront.x1=newPosX-hitbox;
	hitboxFront.y1=newPosY+hitbox;
	hitboxFront.x2=newPosX+hitbox;
	hitboxFront.y2=newPosY+hitbox;

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

int changePosition(int direction, double speed,
		   double *xPos, double *yPos, double hitbox){
	switch((direction+turnRatio)%8){
		case DIRECTION_UP_RIGHT:{
			if(checkObstacles(*xPos+(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos+(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos+(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos+(speed*DIAGONAL_MOTION_FACTOR);}
			break;}

		case DIRECTION_UP:{
			if(checkObstacles(*xPos, *yPos+speed, hitbox)){
			*yPos=*yPos+speed;}
			break;}

		case DIRECTION_RIGHT:{
			if(checkObstacles(*xPos+speed, *yPos, hitbox)){
			*xPos=*xPos+speed;}
			break;}

		case DIRECTION_DOWN_LEFT:{
			if(checkObstacles(*xPos-(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos-(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos-(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos-(speed*DIAGONAL_MOTION_FACTOR);}
			break;}

		case DIRECTION_LEFT:{
			if(checkObstacles(*xPos-speed, *yPos, hitbox)){
			*xPos=*xPos-speed;}
			break;}

		case DIRECTION_DOWN:{
			if(checkObstacles(*xPos, *yPos-speed, hitbox)){
			*yPos=*yPos-speed;}
			break;}

		case DIRECTION_UP_LEFT:{
			if(checkObstacles(*xPos-(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos+(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos-(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos+(speed*DIAGONAL_MOTION_FACTOR);}
			
			break;}

		case DIRECTION_DOWN_RIGHT:{
			if(checkObstacles(*xPos+(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos-(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos+(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos-(speed*DIAGONAL_MOTION_FACTOR);}
			break;}

		default:{break;}
	}
}

int determinePlayerDirection(){				//Set the direction of char,
	if(keyPressed[KEY_A]){				//considering pressed keys
		character_player.direction=DIRECTION_LEFT;}

	if(keyPressed[KEY_D]){
		character_player.direction=DIRECTION_RIGHT;}

	if(keyPressed[KEY_S]){
		character_player.direction=DIRECTION_DOWN;
		if(keyPressed[KEY_A]){
			character_player.direction=DIRECTION_DOWN_LEFT;}
		if(keyPressed[KEY_D]){
			character_player.direction=DIRECTION_DOWN_RIGHT;}
	}

	if(keyPressed[KEY_W]){
		character_player.direction=DIRECTION_UP;
		if(keyPressed[KEY_A]){
			character_player.direction=DIRECTION_UP_LEFT;}
		if(keyPressed[KEY_D]){
			character_player.direction=DIRECTION_UP_RIGHT;}}
	return 0;
}

bool movingCondition(){					//Check for moving possibility
	if(!(keyPressed[KEY_W]|keyPressed[KEY_A]|keyPressed[KEY_S]|keyPressed[KEY_D])){
		return false;}

	if((keyPressed[KEY_W]&&keyPressed[KEY_S])|
	(keyPressed[KEY_A]&&keyPressed[KEY_D])){
		return false;}

	return true;
}

int charMove(CHARACTER *character){			//Movement animation
	int i;
//	printf("enter %f, %f\n", character->x, character->y);
	for(i=0; i<(FRAME_TIME/10); i++){
		changePosition(character->direction, character->speed, 
			       &character->x, &character->y, 
			       character->hitbox);}
//	printf("exit  %f, %f\n\n", character->x, character->y);

	return 0;
}
