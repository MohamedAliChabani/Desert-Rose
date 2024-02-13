#ifndef PLAYER_H_
#define PLAYER_H_

#include "defs.h"
#include "structs.h"
#include "utils.h"
#include "movement.h"

#define PLAYER_DEFAULT_X 100
#define PLAYER_DEFAULT_Y 600
#define PLAYER_DEFAULT_ACCELERATION 0
#define PLAYER_DEFAULT_VELOCITY 0
#define PLAYER_MAX_VELOCITY 10
#define PLAYER_JUMP_HEIGHT 4
#define PLAYER_GRAVITY 7

void init_player(Entity *player, int n);
void load_player_resources();
void jump(Entity *player);
void update_player(Entity *player);
void draw_player(Entity *player);

#endif //PLAYER_H_
