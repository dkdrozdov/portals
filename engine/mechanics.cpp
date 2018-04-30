#include "mechanics.h"
#include "geometry.h"
#include "storemagic.h"

bool collision_object_walls(double x, double y, double r){
	int i, g=0;
	SEGMENT wall_segment[4];


	while(g<n_wall){
		wall_segment[0].x[0]=level_walls[g].x[0];
		wall_segment[0].y[0]=level_walls[g].y[0];
		wall_segment[0].x[1]=level_walls[g].x[0];
		wall_segment[0].y[1]=level_walls[g].y[1];

		wall_segment[1].x[0]=level_walls[g].x[0];
		wall_segment[1].y[0]=level_walls[g].y[1];
		wall_segment[1].x[1]=level_walls[g].x[1];
		wall_segment[1].y[1]=level_walls[g].y[1];

		wall_segment[2].x[0]=level_walls[g].x[1];
		wall_segment[2].y[0]=level_walls[g].y[1];
		wall_segment[2].x[1]=level_walls[g].x[1];
		wall_segment[2].y[1]=level_walls[g].y[0];

		wall_segment[3].x[0]=level_walls[g].x[1];
		wall_segment[3].y[0]=level_walls[g].y[0];
		wall_segment[3].x[1]=level_walls[g].x[0];
		wall_segment[3].y[1]=level_walls[g].y[0];

		for(i=0; i<4; i++){			//for each side of wall
			if(circle_segment_collision(wall_segment[i], x, y, r)){
				return true;}
		}
		g++;
	}

	return false;
}

bool collision_segment_walls(SEGMENT segment){
	int i, g=0;
	double crosspoint[2];
	SEGMENT wall_segment[4];


	while(g<n_wall){
		wall_segment[0].x[0]=level_walls[g].x[0];
		wall_segment[0].y[0]=level_walls[g].y[0];
		wall_segment[0].x[1]=level_walls[g].x[0];
		wall_segment[0].y[1]=level_walls[g].y[1];

		wall_segment[1].x[0]=level_walls[g].x[0];
		wall_segment[1].y[0]=level_walls[g].y[1];
		wall_segment[1].x[1]=level_walls[g].x[1];
		wall_segment[1].y[1]=level_walls[g].y[1];

		wall_segment[2].x[0]=level_walls[g].x[1];
		wall_segment[2].y[0]=level_walls[g].y[1];
		wall_segment[2].x[1]=level_walls[g].x[1];
		wall_segment[2].y[1]=level_walls[g].y[0];

		wall_segment[3].x[0]=level_walls[g].x[1];
		wall_segment[3].y[0]=level_walls[g].y[0];
		wall_segment[3].x[1]=level_walls[g].x[0];
		wall_segment[3].y[1]=level_walls[g].y[0];

		for(i=0; i<4; i++){			//for each side of wall
			if(segments_collision(wall_segment[i], segment, 
						crosspoint)){
				return true;}
		}
		g++;
	}

	return false;
}

bool collision_object_units(double x, double y, double r){
	int i;

	for(i=0; i<n_npc; i++){
		if(circles_collision(unit_npc[i].x, unit_npc[i].y, 
		   unit_npc[i].hitbox, x, y, r)){
			return true;}
	}

	return false;
}

bool collision_segment_units(SEGMENT segment){
	int i;

	for(i=0; i<n_npc; i++){
		if(circle_segment_collision(segment, unit_npc[i].x, unit_npc[i].y,
					    unit_npc[i].hitbox)){
			return true;}
	}

	return false;
}

int char_move(UNIT *unit, double target_x, double target_y){ //Movement animation

	SEGMENT motion_vector;
	motion_vector.x[0]=unit->x;
	motion_vector.y[0]=unit->y;
	motion_vector.x[1]=target_x;
	motion_vector.y[1]=target_y;

	motion_vector=change_vector_length(motion_vector, unit->speed*FRAME_TIME);

	if(!(collision_object_walls(motion_vector.x[1], motion_vector.y[1], 
				  unit->hitbox)
	||collision_object_units(motion_vector.x[1], motion_vector.y[1], 
				 unit->hitbox))
	||collision_segment_units(motion_vector)
	||collision_segment_walls(motion_vector)){
		unit->x=motion_vector.x[1];
		unit->y=motion_vector.y[1];
	}

	return 0;
}

int bury_spell(int index){
	printf("number %d is dead!\n", index+1);
	if(index+1==n_magic){
		n_magic--;
	}
	else{
		int i;
		for(i=index+1; i<n_magic; i++){
			magic_object[i-1]=magic_object[i];
		}
		n_magic--;
	}
}

int magic_move(MAGIC *magic, int index){ //Movement animation
	SEGMENT target_vector;
	target_vector.x[0]=magic->x;
	target_vector.y[0]=magic->y;
	target_vector.x[1]=magic->target_x;
	target_vector.y[1]=magic->target_y;

	target_vector=change_vector_length(target_vector, magic->speed*10);
	magic->target_x=target_vector.x[1];
	magic->target_y=target_vector.y[1];

	SEGMENT motion_vector;
	motion_vector.x[0]=magic->x;
	motion_vector.y[0]=magic->y;
	motion_vector.x[1]=magic->target_x;
	motion_vector.y[1]=magic->target_y;

	motion_vector=change_vector_length(motion_vector, magic->speed*FRAME_TIME);

	switch(magic->form){
		case WORD_FORM_POINTED:
		{
			//If conserns unit/player, impose effect and be destroyed
			if(collision_object_units
			(motion_vector.x[1], motion_vector.y[1], magic->size)||
			circles_collision
			(unit_player.x, unit_player.y, unit_player.hitbox,
			motion_vector.x[1], motion_vector.y[1], magic->size)||
			collision_segment_units(motion_vector)){
				bury_spell(index);
				break;
			}

			//Else if conserns wall, be destroyed
			else if(collision_object_walls
			(motion_vector.x[1], motion_vector.y[1], magic->size)||
			collision_segment_walls(motion_vector)){
				bury_spell(index);
			}

			//No collision - move
			else{
				magic->x=motion_vector.x[1];
				magic->y=motion_vector.y[1];}
			
			//Decrease time and size
			magic->time-=FRAME_TIME;
			magic->size-=magic->begin_size/(magic->begin_time/FRAME_TIME);

			//Time is over - bury
			if(magic->time<=0){
				bury_spell(index);
			}
			break;
		}

		case WORD_FORM_SQUARE:
		{
			//Don't consern any wall
			if(!(collision_object_walls
			(motion_vector.x[1], motion_vector.y[1], magic->size)||
			collision_segment_walls(motion_vector))){
	
				//If conserns unit/player, impose effect and move
				if(collision_object_units
				(motion_vector.x[1], motion_vector.y[1], magic->size)||
				circles_collision
				(unit_player.x, unit_player.y, unit_player.hitbox,
				motion_vector.x[1], motion_vector.y[1], magic->size)||
				collision_segment_units(motion_vector)){
					/*here must be effect imposing*/
				}

				//Don't consern walls - move
				magic->x=motion_vector.x[1];
				magic->y=motion_vector.y[1];
			}
			
			//If conserns wall, be reduced by its speed and move
			else{
				magic->size=magic->size-magic->speed*FRAME_TIME;
				magic->x=motion_vector.x[1];
				magic->y=motion_vector.y[1];
			}

			//Decrease time and size
			magic->time-=FRAME_TIME;
			magic->size-=magic->begin_size/(magic->begin_time/FRAME_TIME);
			
			//Too small square or time is over - bury
			if((magic->size<=0)||(magic->time<=0)){
				bury_spell(index);
			}

			break;
		}

		case WORD_FORM_RADIAL:
		{
			//Move to player
			magic->x=unit_player.x;
			magic->y=unit_player.y;

			//If conserns unit/player, impose effect and grow
			if(collision_object_units
			(magic->x, magic->y, magic->size+magic->speed)||
			circles_collision
			(unit_player.x, unit_player.y, unit_player.hitbox,
			magic->x, magic->y, magic->size+magic->speed)){
				/*here must be effect imposing*/
			}

			//Don't consern any wall - grow by its speed
			if(!(collision_object_walls
			(magic->x, magic->y, magic->size))&&(magic->size<magic->max_size)){
				magic->size+=magic->speed*FRAME_TIME;
			}
			//Consern wall - decrease in size until it do
			else
			{
				do{
					magic->size-=magic->speed*FRAME_TIME;
				}while(collision_object_walls
				(magic->x, magic->y, magic->size));
			}
			
			//Decrease time
			magic->time-=FRAME_TIME;
			
			//Time is over - bury
			if(magic->time<=0){
				bury_spell(index);
			}

			break;
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

int bury_npc_effect(int unit, int index){
	printf("number %d is dead!\n", index+1);
	if(index+1==unit_npc[unit].n_state){
		unit_npc[unit].n_state--;
	}
	else{
		int i;
		for(i=index+1; i<unit_npc[unit].n_state; i++){
			unit_npc[unit].state[i-1]=unit_npc[unit].state[i];
		}
		unit_npc[unit].n_state--;
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

int refresh_player_angle(){
	SEGMENT direction_vector;

	direction_vector.x[0]=unit_player.x;
	direction_vector.y[0]=unit_player.y;
	direction_vector.x[1]=mouse_x-unit_player.x;
	direction_vector.y[1]=mouse_y-unit_player.y;

	double arc=atan2(direction_vector.y[1], direction_vector.x[1])*180/3.1415;

//	printf("\n%f\n", arc);

	unit_player.direction=arc;

	return 0;
}

int state_process(){			//Processing of units state
	int i;

	check_graveyard();

	return 0;
}

int magic_process(){
	int i;

	for(i=0; i<n_magic; i++){
		magic_move(&magic_object[i], i);
	}

	return 0;
}
