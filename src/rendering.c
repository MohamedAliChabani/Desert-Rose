/**
* @file rendering.c
* @brief fonctions affichage jeu
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for background scrollilng
*
*/

#include "rendering.h"

extern SDL_Surface *screen;

extern Entity player;
extern Entity player2;

extern Entity ennemy;
extern Entity ennemy2;

extern Background background;
extern Minimap minimap;

void render_game()
{
    SDL_FillRect(screen, NULL, 0);
    draw_background();

    draw_player(&player);
    draw_player(&player2);

    if (ennemy.vie > 0)
        draw_ennemy(&ennemy);
    if (ennemy2.vie > 0)
        draw_ennemy(&ennemy2);

    draw_minimap(screen, minimap);

    SDL_Flip(screen);
}
