#include "mechanics.h"


typedef struct segment{
	double x1;
	double y1;
	double x2;
	double y2;
}SEGMENT;

bool check_collision(SEGMENT s1, SEGMENT s2, double *crosspoint){
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

bool check_obstacles(double newPosX, double newPosY, double hitbox){
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

	while(count<n_wall){
		wallSegment[0].x1=level_walls[count].x[0];
		wallSegment[0].y1=level_walls[count].y[0];
		wallSegment[0].x2=level_walls[count].x[0];
		wallSegment[0].y2=level_walls[count].y[1];

		wallSegment[1].x1=level_walls[count].x[0];
		wallSegment[1].y1=level_walls[count].y[1];
		wallSegment[1].x2=level_walls[count].x[1];
		wallSegment[1].y2=level_walls[count].y[1];

		wallSegment[2].x1=level_walls[count].x[1];
		wallSegment[2].y1=level_walls[count].y[1];
		wallSegment[2].x2=level_walls[count].x[1];
		wallSegment[2].y2=level_walls[count].y[0];

		wallSegment[3].x1=level_walls[count].x[1];
		wallSegment[3].y1=level_walls[count].y[0];
		wallSegment[3].x2=level_walls[count].x[0];
		wallSegment[3].y2=level_walls[count].y[0];

		for(i=0; i<4; i++){			//for each side of wall
			if(check_collision(hitboxFront, wallSegment[i], intersection)){
				return false;
			}
	
			if(check_collision(hitboxBack, wallSegment[i], intersection)){
				return false;
			}
	
			if(check_collision(hitboxRight, wallSegment[i], intersection)){
				return false;
			}
	
			if(check_collision(hitboxLeft, wallSegment[i], intersection)){
				return false;
			}
		}

		count++;
	}

	return true;
}

int change_position(int direction, double speed,
		   double *xPos, double *yPos, double hitbox){
	switch(direction){
		case DIRECTION_UP_RIGHT:{
			if(check_obstacles(*xPos+(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos+(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos+(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos+(speed*DIAGONAL_MOTION_FACTOR);}
			break;}

		case DIRECTION_UP:{
			if(check_obstacles(*xPos, *yPos+speed, hitbox)){
			*yPos=*yPos+speed;}
			break;}

		case DIRECTION_RIGHT:{
			if(check_obstacles(*xPos+speed, *yPos, hitbox)){
			*xPos=*xPos+speed;}
			break;}

		case DIRECTION_DOWN_LEFT:{
			if(check_obstacles(*xPos-(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos-(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos-(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos-(speed*DIAGONAL_MOTION_FACTOR);}
			break;}

		case DIRECTION_LEFT:{
			if(check_obstacles(*xPos-speed, *yPos, hitbox)){
			*xPos=*xPos-speed;}
			break;}

		case DIRECTION_DOWN:{
			if(check_obstacles(*xPos, *yPos-speed, hitbox)){
			*yPos=*yPos-speed;}
			break;}

		case DIRECTION_UP_LEFT:{
			if(check_obstacles(*xPos-(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos+(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos-(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos+(speed*DIAGONAL_MOTION_FACTOR);}
			
			break;}

		case DIRECTION_DOWN_RIGHT:{
			if(check_obstacles(*xPos+(speed*DIAGONAL_MOTION_FACTOR), 
					 *yPos-(speed*DIAGONAL_MOTION_FACTOR),hitbox)){
			*xPos=*xPos+(speed*DIAGONAL_MOTION_FACTOR);
			*yPos=*yPos-(speed*DIAGONAL_MOTION_FACTOR);}
			break;}

		default:{break;}
	}
}

int determine_player_direction(){			//Set the direction of char,
	if(key_motion[KEY_A]){				//considering pressed keys
		unit_player.direction=DIRECTION_LEFT;}

	if(key_motion[KEY_D]){
		unit_player.direction=DIRECTION_RIGHT;}

	if(key_motion[KEY_S]){
		unit_player.direction=DIRECTION_DOWN;
		if(key_motion[KEY_A]){
			unit_player.direction=DIRECTION_DOWN_LEFT;}
		if(key_motion[KEY_D]){
			unit_player.direction=DIRECTION_DOWN_RIGHT;}
	}

	if(key_motion[KEY_W]){
		unit_player.direction=DIRECTION_UP;
		if(key_motion[KEY_A]){
			unit_player.direction=DIRECTION_UP_LEFT;}
		if(key_motion[KEY_D]){
			unit_player.direction=DIRECTION_UP_RIGHT;}}

							//offset of camera rotation
	unit_player.direction=(unit_player.direction+turn_ratio)%8;
	return 0;
}

bool determine_player_motion(){				//Check for moving possibility
	if(!(key_motion[KEY_W]|key_motion[KEY_A]|key_motion[KEY_S]|key_motion[KEY_D])){
		return false;}

	if((key_motion[KEY_W]&&key_motion[KEY_S])|
	(key_motion[KEY_A]&&key_motion[KEY_D])){
		return false;}

	return true;
}

int char_move(UNIT *unit){			//Movement animation
	int i;
	if(determine_player_motion()){
		determine_player_direction();

		for(i=0; i<(FRAME_TIME); i++){
			change_position(unit->direction, unit->speed, 
				       &unit->x, &unit->y, 
				       unit->hitbox);
		}
	}

	return 0;
}

int bury_npc(int index){
	printf("number %d is dead!\n", index+1);
	if(index+1==n_npc){
		n_npc--;
	}
	else{
		int i;
		for(i=index+1; i<n_npc; i++){
			unit_npc[i-1]=unit_npc[i];
		}
		n_npc--;
	}
}

int check_graveyard(){
	int i=0;

	while(i<n_npc){
		if(unit_npc[i].state[0].value<=0){
			bury_npc(i);
		}
		else{
			i++;
		}
	}
}


int state_process(){			//Processing of units state
	int i;

	check_graveyard();

	return 0;
}
