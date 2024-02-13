/**
* @file player.c
* @brief fichiers du joueur
* @author Chaabani Mohamed Ali
* @version 0.1
* @date May 05, 2023
*
* Testing program for background scrollilng
*
*/

#include "player.h"

extern SDL_Surface *screen;
extern Background background;


TTF_Font *game_font = NULL;

/**
* @brief ouverture de la police font.ttf
* @return Nothing
*/

void load_player_resources()
{
    game_font = TTF_OpenFont("../assets/fonts/font.ttf", 15);
}

/**
* @brief ouverture de la spritesheet selon le numero du joueur
* @param player pointeur sur le joeur
* @return Nothing
*/

void load_spritesheets(Entity *player)
{
    switch (player->num) {
        case 1:
            init_spritesheet(&player->spritesheets[IDLE], "../assets/gfx/player/idle.png", 4, 5);
            init_spritesheet(&player->spritesheets[IDLE_BACK], "../assets/gfx/player/idle_back.png", 4, 5);
            init_spritesheet(&player->spritesheets[RUNNING], "../assets/gfx/player/run.png", 6, 4);
            init_spritesheet(&player->spritesheets[RUNNING_BACK], "../assets/gfx/player/run_back.png", 6, 4);
            init_spritesheet(&player->spritesheets[JUMPING], "../assets/gfx/player/jump.png", 6, 6);
            init_spritesheet(&player->spritesheets[JUMPING_BACK], "../assets/gfx/player/jump_back.png", 6, 6);
            init_spritesheet(&player->spritesheets[FALLING], "../assets/gfx/player/jump.png", 6, 5);
            init_spritesheet(&player->spritesheets[FALLING_BACK], "../assets/gfx/player/jump_back.png", 6, 5);
            break;

        case 2:
            init_spritesheet(&player->spritesheets[IDLE], "../assets/gfx/player/idle2.png", 4, 5);
            init_spritesheet(&player->spritesheets[IDLE_BACK], "../assets/gfx/player/idle_back2.png", 4, 5);
            init_spritesheet(&player->spritesheets[RUNNING], "../assets/gfx/player/run2.png", 6, 4);
            init_spritesheet(&player->spritesheets[RUNNING_BACK], "../assets/gfx/player/run_back2.png", 6, 4);
            init_spritesheet(&player->spritesheets[JUMPING], "../assets/gfx/player/jump2.png", 6, 6);
            init_spritesheet(&player->spritesheets[JUMPING_BACK], "../assets/gfx/player/jump_back2.png", 6, 6);
            init_spritesheet(&player->spritesheets[FALLING], "../assets/gfx/player/jump2.png", 6, 5);
            init_spritesheet(&player->spritesheets[FALLING_BACK], "../assets/gfx/player/jump_back2.png", 6, 5);
            break;

        default: {}
    }
}

/**
* @brief initialisation du joueur et de sa spritesheet selon son numero
* @param player pointeur sur la structure du joueur
* @param n numero du joueur
* @return Nothing
*/

void init_player(Entity *player, int n)
{
    player->pos.x = PLAYER_DEFAULT_X;
    player->pos.y = PLAYER_DEFAULT_Y;
    player->vie = 40;
    player->score = 50;
    player->acceleration = PLAYER_DEFAULT_ACCELERATION;
    player->velocity_x = PLAYER_DEFAULT_VELOCITY;
    player->velocity_y = PLAYER_DEFAULT_VELOCITY;
    player->max_velocity = PLAYER_MAX_VELOCITY;
    player->gravity = PLAYER_GRAVITY;
    player->is_jumping = false;
    player->jump_height = PLAYER_JUMP_HEIGHT;
    player->pos_init = 0;

    player->num = n;

    player->movement = IDLE;
    player->prev_movement = IDLE;

    load_player_resources();
    load_spritesheets(player);
}

/**
* @brief saut du joueur en modifiant sa velocite y
* @param player pointeur sur la structure du joueur
* @return Nothing
*/

void jump(Entity *player)
{
    player->velocity_y -= player->jump_height;
}

/**
* @brief changer l'état du mouvement selon le mouvement du joueur
* @param player pointeur sur la structure du joueur
* @return Nothing
*/

void get_player_movement(Entity *player)
{
    int tmp = player->movement;

    if (player->velocity_x == 0 && player->velocity_y == 0 && player->prev_movement != RUNNING_BACK) {
        player->movement = IDLE;
    }

    if (player->velocity_x == 0 && player->velocity_y == 0 && player->prev_movement == RUNNING_BACK) {
        player->movement = IDLE_BACK;
    }

    if (player->velocity_x > 0) {
        player->movement = RUNNING;
    }
    if (player->velocity_x < 0) {
        player->movement = RUNNING_BACK;
    }
    if (player->velocity_y < 0) {
        if (player->velocity_x >= 0)
            player->movement = JUMPING;
        else
            player->movement = JUMPING_BACK;
    }

    if (player->velocity_y > 0) {
        if (player->movement == JUMPING)
            player->movement = FALLING;
        else if (player->movement == JUMPING_BACK)
            player->movement = FALLING_BACK;
    }

    if (tmp != player->movement && player->movement != IDLE_BACK)
        player->prev_movement = tmp;
}

/**
* @brief mise a jour du joueur, selon le mouvement, et la position
* @param player pointeur sur la structure du joueur
* @return Nothing
*/

void update_player(Entity* player) {
    get_player_movement(player);

    if (player->pos.y < screen->h - player->spritesheets[IDLE].sprite_height)
        player->is_jumping = true;
    else
        player->is_jumping = false;

    if (player->pos.y < 350)
        player->velocity_y = player->gravity;

    player->pos.y += player->velocity_y;

    // Update entity's position based on velocity and acceleration
    if (player->acceleration != 0) {
        player->velocity_x += player->acceleration;
        player->pos.x += player->velocity_x;
    }

    if (player->velocity_x > player->max_velocity) {
        player->velocity_x = player->max_velocity;
        player->acceleration = 0;
    }
    if (player->velocity_x < -(player->max_velocity)) {
        player->velocity_x = -player->max_velocity;
        player->acceleration = 0;
    }

    // Keep character inside the screen rectangle
    if (player->pos.x < 0)
        player->pos.x = 0;
    else if (player->pos.x + player->spritesheets[player->movement].sprite_width > screen->w)
        player->pos.x = screen->w - player->spritesheets[player->movement].sprite_width;

    if (player->pos.y < 0) {
        player->pos.y = 0;
        player->velocity_y = 0;
    }
    else if (player->pos.y + player->spritesheets[player->movement].sprite_height > screen->h) {
        player->pos.y = screen->h - player->spritesheets[player->movement].sprite_height;
        player->velocity_y = 0;
    }
}

/**
* @brief affichage du score, vie et de la velocité ainsi que l'image du joueur
* @param player pointeur sur la structure du joueur
* @return Nothing
*/

void draw_player(Entity *player)
{
    SDL_Color white = {255, 255, 255};
    SDL_Color pink = {.r = 243, .g = 139, .b = 168};

    SDL_Color color = white;

    char buffer[20];

    if (player->num == 1) {
        sprintf(buffer, "Score %d", player->score);
        render_text(screen, game_font, buffer, color, 0, 0);

        sprintf(buffer, "Vie X %d", player->vie);
        render_text(screen, game_font, buffer, color, 0, 25);

        sprintf(buffer, "Vitesse X %d", (int) player->velocity_x);
        render_text(screen, game_font, buffer, color, 0, 45);

        sprintf(buffer, "Vitesse Y %d", (int) player->velocity_y);
        render_text(screen, game_font, buffer, color, 0, 65);

    }
    color = (player->num == 1) ? white : pink;
    sprintf(buffer, "P%d", player->num);
    render_text(screen, game_font,
                buffer, color,
                player->pos.x + player->spritesheets[player->movement].sprite_width / 4 + 2,
                player->pos.y + 5);

    draw_spritesheet(screen, &player->spritesheets[player->movement], player->pos.x, player->pos.y);
}
