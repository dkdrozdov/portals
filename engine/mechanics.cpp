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

bool collision_object_units(double x, double y, double r, int exception){
	int i;
	exception--;

	for(i=0; i<n_unit; i++){
		if(i!=exception){
			if(circles_collision(unit_list[i].x, unit_list[i].y, 
			   unit_list[i].hitbox, x, y, r)){
				return true;}
		}
	}

	return false;
}

bool collision_segment_units(SEGMENT segment, int exception){
	int i;
	exception--;

	for(i=0; i<n_unit; i++){
		if(i!=exception){
			if(circle_segment_collision(segment, unit_list[i].x, unit_list[i].y,
			    unit_list[i].hitbox)){
				return true;}
		}
	}

	return false;
}

int find_effect(int unit, int effect_id){
	int i;

	for(i=0; i<unit_list[unit].n_state; i++){
		if(unit_list[unit].state[i].id==effect_id){
			return i;}
	}
	
	return unit_list[unit].n_state;
}

int impose_magic_effect(int magic, int unit){

	/*exclusion*/
	if(magic_object[magic].exclusion==true&&magic_object[magic].owner==unit){
		printf("Excluse %d!\n", unit);
		return 0;
	}

	int i;
	int effect_index;
	EFFECT imposing_effect;
	SEGMENT segment;
	segment.x[0]=magic_object[magic].x;
	segment.y[0]=magic_object[magic].y;
	segment.x[1]=unit_list[unit].x;
	segment.y[1]=unit_list[unit].y;

	for(i=0; i<magic_object[magic].n_effect; i++){
		imposing_effect=magic_object[magic].effect[i];
	
		if(magic_object[magic].form==MAGIC_FORM_POINTED||
		magic_object[magic].form==MAGIC_FORM_SQUARE){
			imposing_effect.value=magic_object[magic].time*imposing_effect.value
			/magic_object[magic].begin_time;
		}
		else if(magic_object[magic].form==MAGIC_FORM_RADIAL){
			imposing_effect.value=
			((-magic_object[magic].effect[i].value/
			magic_object[magic].max_size)*segment_length(segment)+
			magic_object[magic].effect[i].value);
		}

		effect_index=find_effect(unit, magic_object[magic].effect[i].id);
		unit_list[unit].state[effect_index]=imposing_effect;

		if(effect_index==unit_list[unit].n_state){
			unit_list[unit].n_state++;
			effect_buffer[magic_object[magic].id]++;
		}
	}
	
	return 0;
}

bool impose_collision_object_units(int index, double x, double y, double r){
	int i;

	for(i=0; i<n_unit; i++){
		if(circles_collision(unit_list[i].x, unit_list[i].y, 
		   unit_list[i].hitbox, x, y, r)){
			impose_magic_effect(index, i);
		}
	}

	return false;
}

bool impose_collision_segment_units(int index, SEGMENT segment){
	int i;

	for(i=0; i<n_unit; i++){
		if(circle_segment_collision(segment, unit_list[i].x, unit_list[i].y,
		    unit_list[i].hitbox)){
			impose_magic_effect(index, i);
		}
	}

	return false;
}

int unit_move(UNIT *unit, int index, double target_x, double target_y){

	SEGMENT target_vector;
	target_vector.x[0]=unit->x;
	target_vector.y[0]=unit->y;
	target_vector.x[1]=target_x;
	target_vector.y[1]=target_y;

	SEGMENT motion_vector;

	motion_vector=change_vector_length(target_vector, unit->speed*FRAME_TIME);

	if(!(collision_object_walls(motion_vector.x[1], motion_vector.y[1], 
				  unit->hitbox)
	||collision_object_units(motion_vector.x[1], motion_vector.y[1], 
				 unit->hitbox, index+1)
	||collision_segment_units(motion_vector, index+1)
	||collision_segment_walls(motion_vector))){
		if((unit->hitbox)<segment_length(target_vector)){
			unit->x=motion_vector.x[1];
			unit->y=motion_vector.y[1];}
	}

	return 0;
}

int bury_spell(int index){
	printf("spell #%d is disappear!\n", index+1);
	effect_buffer[magic_object[index].id]--;

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

int magic_move(MAGIC *magic, int index){
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
		case MAGIC_FORM_POINTED:
		{
			//If conserns unit/player, impose effect and be destroyed
			if(collision_object_units
			(motion_vector.x[1], motion_vector.y[1], magic->size, 0)||
			collision_segment_units(motion_vector, 0)){
				impose_collision_object_units(index, motion_vector.x[1],
				motion_vector.y[1], magic->size);
				impose_collision_segment_units(index, motion_vector);
				bury_spell(index);
				break;
			}

			//Else if conserns wall, be destroyed
			if(collision_object_walls
			(motion_vector.x[1], motion_vector.y[1], magic->size)||
			collision_segment_walls(motion_vector)){
				bury_spell(index);
				break;
			}

			//No collision - move
			magic->x=motion_vector.x[1];
			magic->y=motion_vector.y[1];
			
			//Decrease time and size
			magic->time-=FRAME_TIME;
			magic->size-=magic->begin_size/(magic->begin_time/FRAME_TIME);

			//Time is over - bury
			if(magic->time<=0){
				bury_spell(index);
			}
			break;
		}

		case MAGIC_FORM_SQUARE:
		{
			//Don't consern any wall
			if(!(collision_object_walls
			(motion_vector.x[1], motion_vector.y[1], magic->size)||
			collision_segment_walls(motion_vector))){
	
				//If conserns unit/player, impose effect and move
				if(collision_object_units
				(motion_vector.x[1], motion_vector.y[1], magic->size, 0)||
				collision_segment_units(motion_vector, 0)){
					impose_collision_object_units(index, motion_vector.x[1],
					motion_vector.y[1], magic->size);
					impose_collision_segment_units(index, motion_vector);
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

		case MAGIC_FORM_RADIAL:
		{
			//Move to player
			magic->x=unit_list[magic->owner].x;
			magic->y=unit_list[magic->owner].y;

			//If conserns unit/player, impose effect and grow
			if(collision_object_units
			(magic->x, magic->y, magic->size+magic->speed*FRAME_TIME, 0)){
				impose_collision_object_units(index, magic->x,
				magic->y, magic->size+magic->speed*FRAME_TIME);
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

int bury_unit(int index){
	printf("unit #%d is dead!\n", index+1);
	if(index+1==n_unit){
		n_unit--;
	}
	else{
		int i;
		for(i=index+1; i<n_unit; i++){
			unit_list[i-1]=unit_list[i];
		}
		n_unit--;
	}
}

int bury_unit_effect(int unit, int index){
	printf("effect #%d is defused!\n", index+1);
	effect_buffer[unit_list[unit].state[index].id/10]--;

	if(index+1==unit_list[unit].n_state){
		unit_list[unit].n_state--;
	}
	else{
		int i;
		for(i=index+1; i<unit_list[unit].n_state; i++){
			unit_list[unit].state[i-1]=unit_list[unit].state[i];
		}
		unit_list[unit].n_state--;
	}
}

int end_game(){
	printf("You are dead!\n");
	exit(0);
}

int check_graveyard(){
	int i=0;

	while(i<n_unit){
		if(unit_list[i].state[EFFECT_LIFE].value<0.0001){
			if(i==0){
				end_game();
			}
			bury_unit(i);
		}
		else{
			i++;
		}
	}
}

int refresh_player_angle(){
	SEGMENT direction_vector;

	direction_vector.x[0]=unit_list[0].x;
	direction_vector.y[0]=unit_list[0].y;
	direction_vector.x[1]=mouse_x-unit_list[0].x;
	direction_vector.y[1]=mouse_y-unit_list[0].y;

	double arc=atan2(direction_vector.y[1], direction_vector.x[1])*180/3.1415;

	unit_list[0].direction=arc;

	return 0;
}

int state_process(){			//Processing of units state
	int i, g;

	check_graveyard();

	for(i=0; i<n_unit; i++){
		for(g=1; g<unit_list[i].n_state; g++){
			if(unit_list[i].state[g].time<=0.0){
				bury_unit_effect(i, g);}
			else{

			if(unit_list[i].state[g].role==EFFECT_HP){
				printf("dmg %5.3f time %5.3f, eff %d\n",
				unit_list[i].state[g].value*FRAME_TIME,
				unit_list[i].state[g].time, g);

				unit_list[i].state[EFFECT_LIFE].value+=
				unit_list[i].state[g].value*FRAME_TIME;}

			unit_list[i].state[g].time-=FRAME_TIME;
			}

		}

		if(unit_list[i].max_hp<unit_list[i].state[EFFECT_LIFE].value){
			unit_list[i].state[EFFECT_LIFE].value=unit_list[i].max_hp;
		}
	}

	return 0;
}

int magic_process(){
	int i;

	for(i=0; i<n_magic; i++){
		magic_move(&magic_object[i], i);
	}

	return 0;
}
