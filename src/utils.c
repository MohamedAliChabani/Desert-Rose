/**
* @file utils.c
* @brief utilité du programme
* @author C Team
* @version 0.1
* @date May 05, 2023
*
* Testing program for background scrollilng
*
*/

#include "utils.h"

void die()
{
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(-1);
}

void draw_image(SDL_Surface *screen, SDL_Surface *image, int x, int y)
{
    SDL_Rect dsrect = {.h=image->h, .w=image->w, .x=x, .y=y};
    SDL_BlitSurface(image, NULL, screen, &dsrect);
}

void render_text(SDL_Surface *surface, TTF_Font *font,  const char *text, SDL_Color color, int x, int y)
{
	SDL_Rect titlepos;
	titlepos.x=x;
	titlepos.y=y;
	//title

	SDL_Surface *blended_text = TTF_RenderText_Blended(font, text, color);

    SDL_BlitSurface(blended_text, NULL, surface, &titlepos);
}

void delay(uint32_t frame_limit)
{
    uint32_t ticks = SDL_GetTicks();

    if (frame_limit < ticks)
        return;
    if (frame_limit > ticks + 16)
        SDL_Delay(16);
    else
        SDL_Delay(frame_limit - ticks);
}

void init_spritesheet(spritesheet_t *sprt, const char *filename, int num_frames, int frame_multiplier)
{
    sprt->spritesheet = IMG_Load(filename);
    sprt->num_frames = num_frames;
    sprt->sprite_width = sprt->spritesheet->w / sprt->num_frames;
    sprt->sprite_height = sprt->spritesheet->h;
    sprt->frame_index = 0;
    sprt->frame_multiplier = frame_multiplier;
}

void draw_spritesheet(SDL_Surface *screen, spritesheet_t *sprt, int x, int y) {
    SDL_Rect srcRect;
    SDL_Rect destRect;

    // Set the source rectangle
    srcRect.x = (sprt->frame_index / sprt->frame_multiplier) * sprt->sprite_width;
    srcRect.y = 0;
    srcRect.w = sprt->sprite_width;
    srcRect.h = sprt->sprite_height;;

    // Set the destination rectangle
    destRect.x = x;
    destRect.y = y;
    destRect.w = sprt->sprite_width;
    destRect.h = sprt->sprite_height;

    // Copy the sprite from the sprite sheet to the screen
    SDL_BlitSurface(sprt->spritesheet, &srcRect, screen, &destRect);

    if (sprt->frame_index / sprt->frame_multiplier >= sprt->num_frames - 1)
        sprt->frame_index = 0;
    else
        sprt->frame_index++;
}
