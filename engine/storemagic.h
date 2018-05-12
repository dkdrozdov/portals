
//List of runes:
	/*End-runes*/
const int RUNE_AN=0;		
const int RUNE_AS=1;
const int RUNE_US=2;
const int RUNE_IL=3;
const int RUNE_ON=4;
const int RUNE_IR=5;
	/*Base-runes*/
const int RUNE_TER=6; 	//Form rune
const int RUNE_RU=7;	//Power rune
const int RUNE_KAN=8;	//Element 3-part combination rune
const int RUNE_RAN=9; 	//Single KAN-IL (air) extension: whirlwind
const int RUNE_DUR=10;	//Performance rune
const int RUNE_AMA=11;	//Energy rune
const int RUNE_KOL=12;	//Single trap rune
const int RUNE_RO=13;	//Single exclusion of oneself rune

//List of words:
const int MAGIC_FORM_POINTED= 		0;	//TER+AN
const int MAGIC_FORM_SQUARE= 		10;	//TER+AS
const int MAGIC_FORM_RADIAL= 		20;	//TER+US
const int MAGIC_FORM_ONESELF= 		30;	//TER+IL
const int MAGIC_FORM_AVOID= 		40;	//TER+ON
const int MAGIC_FORM_CLOAK= 		50;	//TER+IR


const int MAGIC_POWER_LOW=   		100;	//RU+AN
const int MAGIC_POWER_MEDIUM=  		101;	//RU+AS
const int MAGIC_POWER_GREATER= 		102;	//RU+US
const int MAGIC_POWER_MAXIMUM=		103;	//RU+IL
const int MAGIC_POWER_OVERLOAD=		104;	//RU+ON
const int MAGIC_POWER_SAFE=		105;	//RU+ON


const int EFFECT_ELEMENT_HEAT=		200;	//KAN+AN+AN
//					201	  KAN+AN+AS don't exist
const int EFFECT_ELEMENT_STEAM=		202;	//KAN+AN+US
const int EFFECT_ELEMENT_FIRE=		203;	//KAN+AN+IL
const int EFFECT_ELEMENT_MAGMA=		204;	//KAN+AN+ON
const int EFFECT_ELEMENT_FLAMELIGHT=	205;	//KAN+AN+IR


//					210	  KAN+AS+AN don't exist
const int EFFECT_ELEMENT_COLD= 		211;	//KAN+AS+AS
const int EFFECT_ELEMENT_ICE= 		212;	//KAN+AS+US
const int EFFECT_ELEMENT_FREEZEWIND=	213;	//KAN+AS+IL
const int EFFECT_ELEMENT_COLDSTONE=	214;	//KAN+AS+ON
const int EFFECT_ELEMENT_COLDLIGHT=	215;	//KAN+AS+IR


// 					220=202	  KAN+US+AN =KAN+AN+US
//			 		221=212	  KAN+US+AS =KAN+AS+US
const int EFFECT_ELEMENT_WATER= 		222;	//KAN+US+US
const int EFFECT_ELEMENT_WETWIND=		223;	//KAN+US+IL
const int EFFECT_ELEMENT_MUG= 		224;	//KAN+US+ON
const int EFFECT_ELEMENT_WATERLIGHT=	225;	//KAN+US+IR

//					230=203	  KAN+IL+AN =KAN+AN+IL
//					231=213	  KAN+IL+AS =KAN+AS+IL
//					232=223	  KAN+IL+US =KAN+US+IL
const int EFFECT_ELEMENT_WIND= 		233;	//KAN+IL+IL
const int EFFECT_ELEMENT_SANDWIND=	234;	//KAN+IL+ON
const int EFFECT_ELEMENT_WINDLIGHT=	235;	//KAN+IL+IR

//					240=204	  KAN+ON+AN =KAN+AN+ON
//					241=214	  KAN+ON+AS =KAN+AS+ON
//					242=224	  KAN+ON+US =KAN+US+ON
//					243=234	  KAN+ON+IL =KAN+IL+ON
const int EFFECT_ELEMENT_STONE=		244;	//KAN+ON+ON
const int EFFECT_ELEMENT_STONELIGHT=	245;	//KAN+ON+IR

//					250=205	  KAN+IR+AN =KAN+AN+IR
//					251=215	  KAN+IR+AS =KAN+AS+IR
//					252=225	  KAN+IR+US =KAN+US+IR
//					253=235	  KAN+IR+IL =KAN+IL+IR
//					254=245	  KAN+IR+ON =KAN+ON+IR
const int EFFECT_ELEMENT_LIGHT=		255;	//KAN+IR+IR

const int MAGIC_WHIRLWIND=		300;	//RAN

const int MAGIC_PERFORMANCE_BLAST=	400;	//DUR+AN
const int MAGIC_PERFORMANCE_INSTANT=	410;	//DUR+AS
const int MAGIC_PERFORMANCE_MAINTAIN=	420;	//DUR+US
const int MAGIC_PERFORMANCE_STUFF=	430;	//DUR+IL
const int MAGIC_PERFORMANCE_SKY=		440;	//DUR+ON
const int MAGIC_PERFORMANCE_GROUND=	450;	//DUR+IR

const int MAGIC_ENERGY_GET=		500;	//AMA+AN
const int MAGIC_ENERGY_RELEASE=		510;	//AMA+AS
const int MAGIC_ENERGY_CONCENTRATE=	520;	//AMA+US
const int MAGIC_ENERGY_EXPEL=		530;	//AMA+IL
const int MAGIC_ENERGY_RESURGE=		540;	//AMA+ON
const int MAGIC_ENERGY_DESTROY=		550;	//AMA+IR

const int MAGIC_TRAP=			600;	//KOL

const int MAGIC_EXCLUSION=		700;	//RO


