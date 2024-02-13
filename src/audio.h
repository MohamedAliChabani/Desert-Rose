#ifndef AUDIO_H_
#define AUDIO_H_

#include "defs.h"
#include "structs.h"

#define MAX_VOL 128
#define MIN_VOL 0

void handle_sound(game_t *game);
void toggle_sound(game_t *game);

#endif // AUDIO_H_
