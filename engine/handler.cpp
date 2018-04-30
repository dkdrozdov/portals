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

			 if(index==0){
			 	unit_player.state[0].value=0;}
			 else{
				unit_npc[index-1].state[0].value=0;}

			 break;}
		case 'n':{
			 if(n_npc<=UNIT_MAX-1){
				unit_npc[n_npc].speed=PLAYER_SPEED;
				unit_npc[n_npc].hitbox=PLAYER_HITBOX;
				unit_npc[n_npc].direction=0;
				unit_npc[n_npc].x=unit_player.x+unit_player.hitbox
				 		+unit_npc[n_npc].hitbox;
				unit_npc[n_npc].y=unit_player.y;
				unit_npc[n_npc].max_hp=10;
				unit_npc[n_npc].state[0].time=0;
				unit_npc[n_npc].state[0].value=10;
				unit_npc[n_npc].state[0].type=LIFE;
				unit_npc[n_npc].n_state=1;
				n_npc++;
				printf("n_npc=%d\n", n_npc);}
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
