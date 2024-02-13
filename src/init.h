#ifndef INIT_H_
#define INIT_H_

#include "defs.h"

#define WIDTH  800
#define HEIGHT 600

extern SDL_Surface *screen;
extern SDL_Surface *bg_img;
extern Mix_Music   *bg_music;

void initialize(const char *window_title);
void shutdown();

#endif //INIT_H_
