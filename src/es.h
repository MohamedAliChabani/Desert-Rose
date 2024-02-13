#ifndef ES_H_
#define ES_H_

#include "defs.h"
#include "structs.h"
#include "utils.h"
#include "movement.h"

void init_ennemy(Entity *ennemy, int n);
void draw_ennemy(Entity *ennemy);
void check_collision(Entity *ennemy, Entity player);
void update_ennemy(Entity *ennemy);

#endif //ES_H_
