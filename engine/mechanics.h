#include "store.h"
//
bool moving_condition();
int determine_player_direction();
int unit_move(UNIT *unit, int index, double target_x, double target_y);
bool check_obstacles(double newPosX, double newPosY);
int state_process();
int refresh_player_angle();
int magic_process();
