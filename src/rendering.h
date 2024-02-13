#ifndef RENDERING_H_
#define RENDERING_H_

#include "defs.h"
#include "structs.h"
#include "player.h"
#include "background.h"
#include "minimap.h"
#include "utils.h"
#include "es.h"

void delay(uint32_t frame_limit);
void init_background();
void render_game();

#endif //RENDERING_H_
