#include "engine.h"


typedef struct segment{
	double x1;
	double y1;
	double x2;
	double y2;
}SEGMENT;

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

