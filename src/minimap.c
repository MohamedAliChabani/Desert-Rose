/**
* @file minimap.c
* @brief minimap du programme
* @author Chaabani Mohamed Ali
* @version 0.1
* @date May 05, 2023
*
* Testing program for background scrollilng
*
*/

#include "minimap.h"

extern TTF_Font *font;
extern tempo_t t;
TTF_Font *fr;

extern Entity player;
extern Entity player2;

void init_map(Minimap *m)
{
    m->map = IMG_Load("../assets/gfx/minimap/minimap.png");

    //m->masque= IMG_Load("");
    m->miniplayer.img = IMG_Load("../assets/gfx/minimap/miniplayer.png");
    m->miniplayer2.img = IMG_Load("../assets/gfx/minimap/miniplayer2.png");

    m->positionmap.x = 650;
    m->positionmap.y = 0;

    fr = TTF_OpenFont("../assets/fonts/font.ttf", 35);
}


void init_time(tempo_t *t)
{
    strcpy(t->str, "");
    t->sec_e = 0;
    time(&(t->t1));
}

void update_time(tempo_t *t)
{
    t->t2 = time(&(t->t2));
    t->sec_e = (t->t2 - t->t1);
    t->min =((t->sec_e/60) % 60);
    t->sec = (t->sec_e % 60);

    sprintf(t->str,"%02d : %02d",t->min,t->sec);
}

void draw_time(SDL_Surface *screen, tempo_t *t)
{
    SDL_Color color = {.r = 76, .g = 50, .b = 3};
    render_text(screen, fr, t->str, color, 310, 0);
}

void update_map(Minimap *m)
{
    float x = 352.0f / 800.0f;
    float y = 84.0f / 600.0f;

    if (player.pos.x < 400)
        m->miniplayer.pos.x = 580 + player.pos.x * x;
    else
        m->miniplayer.pos.x = 750;


    if (player2.pos.x < 400)
        m->miniplayer2.pos.x = 600 + player2.pos.x * x;
    else
        m->miniplayer2.pos.x = 750;

    m->miniplayer.pos.y = (int) ((player.pos.y) * y) + 10 - (m->miniplayer.img->h / 2);
    m->miniplayer2.pos.y = (int) ((player2.pos.y) * y) + 10 - (m->miniplayer2.img->h / 2);
}

void draw_minimap(SDL_Surface *screen, Minimap m)
{
    draw_image(screen, m.map, 600, 0);
    update_map(&m);
    draw_image(screen, m.miniplayer.img, m.miniplayer.pos.x, m.miniplayer.pos.y);
    draw_image(screen, m.miniplayer2.img, m.miniplayer2.pos.x, m.miniplayer2.pos.y);

    update_time(&t);
    draw_time(screen, &t);

    SDL_Flip(screen);
}

void save_score(Entity player, const char *filename)
{
    FILE *f = fopen(filename, "a");
    if (f == NULL) {
        fprintf(stderr, "Could not open score board\n");
        return;
    }

    fprintf(f, "%d\n", player.score);

    fclose(f);
}
