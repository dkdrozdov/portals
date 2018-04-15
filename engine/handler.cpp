#include "input.h"


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

			 if(index==0){
			 	unit_player.state[0].value=0;}
			 else{
				unit_npc[index-1].state[0].value=0;}

			 break;}
		case 'n':{
			 if(n_npc<=UNIT_MAX-1){
				 unit_npc[n_npc].state[0].value=1;
				 unit_npc[n_npc].x=unit_player.x;
				 unit_npc[n_npc].y=unit_player.y;
				 unit_npc[n_npc].hitbox=PLAYER_HITBOX;
				 n_npc++;
				 printf("n_npc=%d\n", n_npc);}
			 break;}
		default:{
			break;}
	}
	return 0;
}
