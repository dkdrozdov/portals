#include "engine.h"


int determineKeyState(unsigned char usedKey, bool newState){ //Sets the state for used key
	switch(usedKey){
		case 'w':{
			keyPressed[KEY_W]=newState;
			break;}

		case 'a':{
			keyPressed[KEY_A]=newState;
			break;}

		case 's':{
			keyPressed[KEY_S]=newState;
			break;}

		case 'd':{
			keyPressed[KEY_D]=newState;
			break;}

		default:{
			break;}
	}
	return 0;
}
