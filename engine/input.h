#include "store.h"

//Level.cpp:
int loadLevel();

//Keyboard.cpp:
//Keybindings

	/*bases*/
const char KEY_RUNE_TER='Z';
const char KEY_RUNE_RU='X';
const char KEY_RUNE_KAN='C';
const char KEY_RUNE_RAN='V';

const char KEY_RUNE_DUR='B';
const char KEY_RUNE_AMA='N';
const char KEY_RUNE_KOL='M';
const char KEY_RUNE_RO='L';

	/*ends*/
const char KEY_RUNE_AN='T';
const char KEY_RUNE_AS='Y';
const char KEY_RUNE_US='U';
const char KEY_RUNE_IL='I';
const char KEY_RUNE_ON='O';
const char KEY_RUNE_IR='P';

const char KEY_SPELL_INTERRUPT='Q';

int determineKeyState(unsigned char usedKey, bool newState);
int keystroke(unsigned char usedKey);

