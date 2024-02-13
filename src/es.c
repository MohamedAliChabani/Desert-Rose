#include "es.h"
#include "movement.h"

extern SDL_Surface *screen;

extern Entity player;
extern Entity player2;

void init_ennemy(Entity *ennemy, int n)
{
    ennemy->num = n;

    ennemy->pos.y = 520;
    ennemy->vie = 30;

    ennemy->velocity_x = 0;
    ennemy->acceleration = 0.1;

    ennemy->movement = RUNNING;


    switch (ennemy->num) {
        case 1:
            ennemy->pos.x = 500;
            init_spritesheet(&ennemy->spritesheets[RUNNING], "../assets/gfx/ennemy/walk.png", 6, 5);
            init_spritesheet(&ennemy->spritesheets[RUNNING_BACK], "../assets/gfx/ennemy/walk_back.png", 6, 5);
            break;
        case 2:
            ennemy->pos.x = 600;
            init_spritesheet(&ennemy->spritesheets[RUNNING], "../assets/gfx/ennemy/walk2.png", 6, 5);
            init_spritesheet(&ennemy->spritesheets[RUNNING_BACK], "../assets/gfx/ennemy/walk_back2.png", 6, 5);
            break;
        default: {}
    }
}

void get_ennemy_movement(Entity *ennemy)
{
    if (ennemy->velocity_x > 0) {
        ennemy->movement = RUNNING;
    }

    else if (ennemy->velocity_x < 0) {
        ennemy->movement = RUNNING_BACK;
    }
}

void move_ennemy(Entity *ennemy)
{
    ennemy->acceleration = 0;

    switch (ennemy->num) {
        case 1:
            if (ennemy->pos.x < player.pos.x) {
                ennemy->acceleration = -0.1;
            }
            else if (ennemy->pos.x > player.pos.x) {
                ennemy->acceleration = 0.05;
            }
            break;
        case 2:
            if (ennemy->pos.x < player2.pos.x)
                ennemy->acceleration = -0.1;
            if (ennemy->pos.x > player2.pos.x)
                ennemy->acceleration = 0.05;
        default: {}
    }

    ennemy->velocity_x += ennemy->acceleration;
    ennemy->pos.x -= ennemy->velocity_x;
}

void update_ennemy(Entity *ennemy)
{
    if (ennemy->pos.x <= 0) {
        ennemy->pos.x = 0;
    }

    if (ennemy->pos.x + ennemy->spritesheets[ennemy->movement].sprite_width > screen->w)
        ennemy->velocity_x = 0;

    move_ennemy(ennemy);
    get_ennemy_movement(ennemy);
}

void check_collision(Entity *ennemy, Entity player)
{
    if (player.pos.x < ennemy->pos.x + ennemy->spritesheets[ennemy->movement].sprite_width - 70 &&
            player.pos.x + player.spritesheets[player.movement].sprite_width - 70 > ennemy->pos.x &&
            player.pos.y < ennemy->pos.y + ennemy->spritesheets[ennemy->movement].sprite_height
            ) {
        if (player.movement == RUNNING || player.movement == RUNNING_BACK) {
            ennemy->vie--;
        }
    }
}

void draw_ennemy(Entity *ennemy)
{
    draw_spritesheet(screen, &ennemy->spritesheets[ennemy->movement], ennemy->pos.x, ennemy->pos.y);
}
