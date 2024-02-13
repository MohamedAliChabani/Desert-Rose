#ifndef MINIMAP_H_
#define MINIMAP_H_

#include "defs.h"
#include "structs.h"
#include "utils.h"

void init_map(Minimap *m);
void init_time(tempo_t *t);
void update_map(Minimap *m);
void draw_minimap(SDL_Surface *screen, Minimap m);
void update_time(tempo_t *t);
void save_score(Entity player, const char *filename);

#endif //MINIMAP_H_
