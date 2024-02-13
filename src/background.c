/**
* @file background.c
* @brief fichiers du background
* @author Chaabani Mohamed Ali
* @version 0.1
* @date May, 05, 2023
*
* Testing program for background scrollilng
*
*/

#include "background.h"

extern Background background;
extern SDL_Surface *screen;

/**
* @brief To initialize the background b .
* @param b the background
* @param url the url of the image
* @return Nothing
*/

void init_background()
{
    background.img = IMG_Load("../assets/gfx/background/backgroundtouzer.png");

    background.offset_val = 5;
    background.offset_x = 0;
    background.offset_y = 0;

    background.srect.x = 0;
    background.srect.y = 0;
    background.srect.w = screen->w;
    background.srect.h = screen->h;

    background.dsrect.x = 0;
    background.dsrect.y = 0;
    background.dsrect.w = background.img->w;
    background.dsrect.h = background.img->h;
}

/**
* @brief Drawing Background to screen
* @return Nothing
*/

void draw_background()
{
    background.srect.x = background.offset_x % background.img->w;
    background.srect.y = background.offset_y % background.img->h;
    SDL_BlitSurface(background.img, &background.srect, screen, &background.dsrect);
}
