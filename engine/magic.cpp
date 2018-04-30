#include "magic.h"
#include "geometry.h"

//		RUNES				//

/*Sort of rune are base and end of word:	*
* End-runes depend on base and clarify the 	*
* meaning of word.				*
* Base-runes have the role of the main meaning	*
* and type of the word.				*
* 						*
* 						*
* Word are as follows:				*
*	spell type is WHAT should spell do;	*
*	spell form is WHERE should spell go;	*
*	spell size is HOW MUCH should spell do;	*
*	spell extra effect can give special	*
* 	unusual effect to the spell.		*/

const int N_RUNES=14;

//Sorting of runes by parts of word:
const int RUNE_BASE=0;
const int RUNE_END=1;

//Sorting of runes by parts of spell:
const int RUNE_SPELL_NONE=0;	//End-runes don't determine the type of the word.
const int RUNE_SPELL_TYPE=1;
const int RUNE_SPELL_FORM=2;
const int RUNE_SPELL_SIZE=3;
const int RUNE_SPELL_PERFORMANCE=4;
const int RUNE_SPELL_TRAP=5;
const int RUNE_SPELL_WHIRLWIND=6;
const int RUNE_SPELL_EXCLUSION=7;

const int RUNE_END_OFFSET=6;

//Reverse:
const char RUNE_REVERSE[N_RUNES][5]={"AN", "AS", "US", "IL", "ON", "IR",/*End-runes*/
	"TER", "RU", "KAN", "RAN", "DUR", "AMA", "KOL", "RO"};

typedef struct rune_struct{
	int part;
	int spell;
}RUNE_STRUCT;

const RUNE_STRUCT DEFINITION_RUNES[N_RUNES]= 
       {{RUNE_END, RUNE_SPELL_NONE}, 		/* 0 RUNEID_AN  END*/
	{RUNE_END, RUNE_SPELL_NONE},		/* 1 RUNEID_AS  END*/
	{RUNE_END, RUNE_SPELL_NONE},		/* 2 RUNEID_US  END*/
	{RUNE_END, RUNE_SPELL_NONE},		/* 3 RUNEID_IL  END*/
	{RUNE_END, RUNE_SPELL_NONE},		/* 4 RUNEID_ON  END*/
	{RUNE_END, RUNE_SPELL_NONE},		/* 5 RUNEID_IR  END*/
    	{RUNE_BASE, RUNE_SPELL_FORM},		/* 6 RUNEID_TER	*/
	{RUNE_BASE, RUNE_SPELL_SIZE},		/* 7 RUNEID_RU	*/
	{RUNE_BASE, RUNE_SPELL_TYPE},		/* 8 RUNEID_KAN	*/
	{RUNE_BASE, RUNE_SPELL_WHIRLWIND},	/* 9 RUNEID_RAN	*/
	{RUNE_BASE, RUNE_SPELL_PERFORMANCE},	/*10 RUNEID_DUR	*/
	{RUNE_BASE, RUNE_SPELL_TYPE},		/*11 RUNEID_AMA	*/
	{RUNE_BASE, RUNE_SPELL_TRAP},		/*12 RUNEID_KOL	*/
	{RUNE_BASE, RUNE_SPELL_EXCLUSION}};	/*13 RUNEID_RO	*/

const int RUNE_BASE_COMPLICATED[N_RUNES-RUNE_END_OFFSET]={
	/*0 TER*/2, /*1 RU*/2, /*2 KAN*/3, /*3 RAN*/1, /*4 DUR*/2,
       	/*5 AMA*/2, /*6 KOL*/1, /*7 RO*/1};
//Spells
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>MAGIC<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

int find_property(int property){
	int i;

	for(i=0; i<n_word; i++){
		if(DEFINITION_RUNES[state_spell[i][0]].spell==property){
			return i;
		}
	}

	return n_word;
}

bool spell_create_condition(){
	
	if((find_property(RUNE_SPELL_TYPE)==n_word)||
	(find_property(RUNE_SPELL_FORM)==n_word)||
	(find_property(RUNE_SPELL_PERFORMANCE)==n_word)||
	(find_property(RUNE_SPELL_SIZE)==n_word)){
		return false;
	}

	return true;
}

int magic_get_spell(){
	MAGIC spell;
	spell.x=0; 		spell.y=0;
	spell.target_x=0; 	spell.target_x=0;
	spell.size=0;		spell.speed=0;
	spell.time=0;		spell.type=0;
	spell.form=0;		spell.owner=0;
	spell.cost=0;		spell.performance=0;
	spell.effect.time=0;	spell.effect.value=0;
	spell.effect.type=0;

	int index;


	if(!spell_create_condition()){
		return 0;
	}

		//Type
	index=find_property(RUNE_SPELL_TYPE);
	spell.type=spell_sentence[index];

		//Form
	index=find_property(RUNE_SPELL_FORM);
	spell.form=spell_sentence[index];

	switch(spell.form){
		case WORD_FORM_POINTED:{
			spell.speed=15.0;
			spell.target_x=mouse_x;
			spell.target_y=mouse_y;
			spell.begin_size=0.3;
			spell.size=0.3;
			break;}

		case WORD_FORM_SQUARE:{
			spell.speed=10.0;
			spell.target_x=mouse_x;
			spell.target_y=mouse_y;
			spell.begin_size=3;
			spell.size=3;
			break;}

		case WORD_FORM_RADIAL:{
			spell.speed=7.0;
			spell.begin_size=0;
			spell.size=0;
			spell.max_size=7;
			break;}

		case WORD_FORM_ONESELF:{break;}
		case WORD_FORM_AVOID:{break;}
		case WORD_FORM_CLOAK:{break;}
	}

		//Performance
	index=find_property(RUNE_SPELL_PERFORMANCE);
	spell.performance=spell_sentence[index];

	switch(spell.performance){
		case WORD_PERFORMANCE_BLAST:{
			SEGMENT spell_path;
			spell_path.x[0]=unit_player.x;
			spell_path.y[0]=unit_player.y;
			spell_path.x[1]=mouse_x;
			spell_path.y[1]=mouse_y;
		
			switch(spell.form){
				case WORD_FORM_POINTED:
				{
					//Avoid target oneself
					if(segment_length(spell_path)<
					unit_player.hitbox+spell.size+0.1){
					spell_path=change_vector_length
					(spell_path, (unit_player.hitbox+spell.size+0.1)*2);
						spell.target_x=spell_path.x[1];
						spell.target_y=spell_path.y[1];
					}

					//Time
					spell.begin_time=2.0;
					spell.time=2.0;
		
					//Starting position: in front of the player,
					//no touch with player
					spell_path=change_vector_length
					(spell_path, unit_player.hitbox+spell.size+0.1);

					spell.x=spell_path.x[1];
					spell.y=spell_path.y[1];

					break;}

				case WORD_FORM_SQUARE:
				{
					//Time
					spell.begin_time=1.5;
					spell.time=1.5;

					//Starting position: in front of the player,
					//touch him
					spell_path=change_vector_length
					(spell_path, unit_player.hitbox);
	
					spell.x=spell_path.x[1];
					spell.y=spell_path.y[1];

					break;}
				
				case WORD_FORM_RADIAL:
				{
					//Time
					spell.begin_time=1.0;
					spell.time=1.0;

					//Starting position: right in player position
					spell.x=unit_player.x;
					spell.y=unit_player.y;

					break;}

			}
	
			break;}
		case WORD_PERFORMANCE_INSTANT:{break;}
		case WORD_PERFORMANCE_MAINTAIN:{break;}
		case WORD_PERFORMANCE_STUFF:{break;}
		case WORD_PERFORMANCE_SKY:{break;}
		case WORD_PERFORMANCE_GROUND:{break;}
	}

		//Size
	index=find_property(RUNE_SPELL_SIZE);

	magic_object[n_magic]=spell;

	n_magic++;

	return 0;
}

int magic_translate_sentence(){	
	int i, g, k;
	for(i=0; i<n_word; i++){
		spell_sentence[i]=0;

		for(g=0, k=100; g<n_rune[i]; g++, k=(int)k/10){

			if(g==0){
				spell_sentence[i]+=(state_spell[i][g]-RUNE_END_OFFSET)*k;}
			else{
				spell_sentence[i]+=(state_spell[i][g])*k;}
		}
	}

	return 0;
}

int print_runes(int index){
	int g;
	for(g=0; g<n_rune[index]; g++){
		printf("%s", RUNE_REVERSE[state_spell[index][g]]);
	}
	
	printf(" ");
}

bool replace_repeated_word(int index){
       	if(DEFINITION_RUNES[state_spell[n_word][0]].spell==
	   DEFINITION_RUNES[state_spell[index][0]].spell){
		int i;
		for(i=0; i<n_rune[n_word]; i++){
			state_spell[index][i]=state_spell[n_word][i];
		}
		n_rune[index]=n_rune[n_word];
		n_rune[n_word]=0;
		return true;
	}
	return false;
}

int magic_get_word(){
	print_runes(n_word);

	int i=0;
	while((i<n_word)&&(!replace_repeated_word(i))){	//no similar words can be repeated
		i++;}

		/*Sencence have ended, when the type-word is said*/
	if(DEFINITION_RUNES[state_spell[n_word][0]].spell==RUNE_SPELL_TYPE){
		n_word=n_word+1;

		magic_translate_sentence();	//send sentence to the translator
		printf("\n");
		magic_get_spell();
		/*
		int h;
		printf("\ntranslated: ");
		for(h=0; h<n_word; h++){
			printf("%d ", spell_sentence[h]);	//print coded words
		}*/

		printf("\n");
		for(i=0; i<n_word; i++){ //sentence is ready, cleaning rune-memories
			print_runes(i);
			n_rune[i]=0;
		}
		printf("\n");
		n_word=0;
	}
	else{
	if(i>=n_word){	//this else used to avoid double incrmenting the word counter
		n_word=n_word+1;}
	}


	return 0;
}

int magic_get_base(int RUNE_ID){
	if(n_rune[n_word]==0){	
			//No runes before
		state_spell[n_word][n_rune[n_word]]=RUNE_ID;
		n_rune[n_word]++;}

	else{		
			//Base already here - replace it:
		if(DEFINITION_RUNES[state_spell[n_word][0]].part==RUNE_BASE){
			state_spell[n_word][0]=RUNE_ID;

		}	
			//End aready here
		if(DEFINITION_RUNES[state_spell[n_word][0]].part==RUNE_END){
			
			//If current base is one-part, replace end with it:
			if(RUNE_BASE_COMPLICATED[RUNE_ID-RUNE_END_OFFSET]==1){
				state_spell[n_word][0]=RUNE_ID;}

			//If current base more complex, add base and put it on 1st place
			else{
				int swap=state_spell[n_word][0];
				state_spell[n_word][0]=RUNE_ID;
				state_spell[n_word][1]=swap;
				n_rune[n_word]++;
			}
		}
	}
			//Integrity check
	if(n_rune[n_word]==RUNE_BASE_COMPLICATED[RUNE_ID-RUNE_END_OFFSET]){
		magic_get_word();}

	return 0;
}

int magic_insert_end(int index, int RUNE_ID){
	if(!(index==n_rune[n_word])){
		int i;
		for(i=n_rune[n_word]-1; i>=index; i--){
			state_spell[n_word][i+1]=state_spell[n_word][i];
		}
	}
	state_spell[n_word][index]=RUNE_ID;
}

int magic_get_end(int RUNE_ID){
	switch(n_rune[n_word]){
		case 0:{	
			       	//No runes before
			state_spell[n_word][n_rune[n_word]]=RUNE_ID;
			n_rune[n_word]++;
		        break;}

		case 1:{
				//Here is only base already - add it:
			if(DEFINITION_RUNES[state_spell[n_word][0]].part==RUNE_BASE){
				state_spell[n_word][1]=RUNE_ID;
				n_rune[n_word]++;
			}

		       	       	//Here is only end already - replace it:
			if(DEFINITION_RUNES[state_spell[n_word][0]].part==RUNE_END){
				state_spell[n_word][0]=RUNE_ID;
			}
		        break;}

		//Here is more than one rune already - insert it in a sequential order:
		default:{
			int i=1;
			while((i<n_rune[n_word])&&(RUNE_ID>state_spell[n_word][i])){
				i++;
			}
			magic_insert_end(i, RUNE_ID);
			n_rune[n_word]++;
		       	break;}
	}
			//Integrity check
	if(RUNE_BASE_COMPLICATED[state_spell[n_word][0]-RUNE_END_OFFSET]==n_rune[n_word]){
		magic_get_word();
	}

	return 0;
}
