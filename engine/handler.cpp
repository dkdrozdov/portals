#include "input.h"
#include "magic.h"


int determineKeyState(unsigned char usedKey, bool newState){ //Sets the state for used key
	switch(usedKey){
		case 'w':{
			key_motion[KEY_W]=newState;
			break;}

		case 'a':{
			key_motion[KEY_A]=newState;
			break;}

		case 's':{
			key_motion[KEY_S]=newState;
			break;}

		case 'd':{
			key_motion[KEY_D]=newState;
			break;}

		default:{
			break;}
	}
	return 0;
}

int command_handler(){
	char command_string[10];

	printf("command\n");
	scanf("%s", &command_string);
	if(command_string){}

	return 0;
}

int keystroke(unsigned char usedKey){
	switch(usedKey){
		case 'r':{				//r - rotate
			turn_ratio=(turn_ratio+1)%8;
			break;}
		case 'f':{				//f - fix camera
			camera_fixed=!camera_fixed;
			break;}
/*		case '/':{
			command_handler();
			break;}*/
		case 'k':{				//k - kill
			int index;
			printf("Index: ");
			scanf("%d", &index);

			unit_list[index].state[0].value=0;

			 break;}
		case 'n':{
			 if(n_unit<=UNIT_MAX-1){
				unit_list[n_unit].speed=PLAYER_SPEED;
				unit_list[n_unit].hitbox=PLAYER_HITBOX;
				unit_list[n_unit].direction=0;
				unit_list[n_unit].x=mouse_x;
				unit_list[n_unit].y=mouse_y;
				unit_list[n_unit].max_hp=10;
				unit_list[n_unit].state[0].time=0;
				unit_list[n_unit].state[0].value=10;
				unit_list[n_unit].state[0].role=EFFECT_LIFE;
				unit_list[n_unit].state[0].type=EFFECT_LIFE;
				unit_list[n_unit].n_state=1;
				n_unit++;
				printf("n_unit=%d\n", n_unit);}
			 break;}
		case KEY_RUNE_KAN:{
			magic_get_base(RUNE_KAN);
		     	break;}
		case KEY_RUNE_RU:{
			magic_get_base(RUNE_RU);
		     	break;}
		case KEY_RUNE_TER:{
			magic_get_base(RUNE_TER);
		     	break;}
		case KEY_RUNE_RAN:{
			magic_get_base(RUNE_RAN);
		     	break;}
		case KEY_RUNE_DUR:{
			magic_get_base(RUNE_DUR);
		     	break;}
		case KEY_RUNE_AMA:{
			magic_get_base(RUNE_AMA);
		     	break;}
		case KEY_RUNE_KOL:{
			magic_get_base(RUNE_KOL);
		     	break;}
		case KEY_RUNE_RO:{
			magic_get_base(RUNE_RO);
		     	break;}
		case KEY_RUNE_AN:{
			magic_get_end(RUNE_AN);
		     	break;}
		case KEY_RUNE_AS:{
			magic_get_end(RUNE_AS);
		     	break;}
		case KEY_RUNE_US:{
			magic_get_end(RUNE_US);
		     	break;}
		case KEY_RUNE_IL:{
			magic_get_end(RUNE_IL);
		     	break;}
		case KEY_RUNE_ON:{
			magic_get_end(RUNE_ON);
		     	break;}
		case KEY_RUNE_IR:{
			magic_get_end(RUNE_IR);
		     	break;}
		case KEY_SPELL_INTERRUPT:{
			int i;
			for(i=0; i<n_word; i++){
				n_rune[i]=0;
			}
			n_word=0;
			printf("\n");
			break;}
		default:{
			break;}
	}
	return 0;
}
