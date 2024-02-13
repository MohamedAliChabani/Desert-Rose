#ifndef UTILS_H_
#define UTILS_H_

#include "defs.h"
#include "structs.h"

void die();
void draw_image(SDL_Surface *screen, SDL_Surface *image, int x, int y);
void render_text(SDL_Surface *surface, TTF_Font *font,  const char *text, SDL_Color color, int x, int y);
void delay(uint32_t frame_limit);
void init_spritesheet(spritesheet_t *sprt, const char *filename, int num_frames, int frame_multiplier);
void draw_spritesheet(SDL_Surface *screen, spritesheet_t *sprt, int x, int y);

#endif // !UTILS_H_
