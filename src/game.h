#ifndef GAME_H_
#define GAME_H_

#include "defs.h"
#include "structs.h"
#include "rendering.h"
#include "menu.h"
#include "es.h"

#define MAX_VOL 128
#define MIN_VOL 0

void init_game(game_t *game);
void handle_game_state(game_t *game);
void play();

#endif // GAME_H_
