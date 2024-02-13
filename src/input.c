#include "input.h"
#include "game.h"
#include "structs.h"
#include "player.h"
#include <SDL/SDL_keyboard.h>
#include <stdint.h>


extern SDL_Surface *screen;

extern Entity player;
extern Entity player2;

extern Background background;

int x_click_pos;
int y_click_pos;

int selected_button = 0;

void toggle_fullscreen(game_t *game)
{
    // Toggle Fullscreen Mode
    game->is_fullscreen = !(game->is_fullscreen);
    if (game->is_fullscreen == true)
        SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    else
        SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF);
}

void handle_selection(game_t *game)
{
    switch(selected_button) {
        case 1:
            game->state = GAME_STATE;
            break;
        case 2:
            game->state = OPTIONS_STATE;
            break;
        case 3:
            game->state = EXIT_STATE;
            break;
        default: {}
    }
    selected_button = 0;
}

void handle_keyboard_event_menu(game_t *game, SDLKey sym)
{
    switch (sym) {
        case SDLK_0:
        case SDLK_ESCAPE:
            game->state = EXIT_STATE;
            break;

        case SDLK_j:
            game->prev_state = game->state;
            game->state = GAME_STATE;
            break;

        case SDLK_o:
            game->prev_state = game->state;
            game->state = OPTIONS_STATE;
            break;

        case SDLK_i:
            game->prev_state = game->state;
            game->state = MENU_STATE;
            break;

        case SDLK_EQUALS:
            game->volume += 10;
            break;

        case SDLK_6:
            game->volume -= 10;
            break;

        case SDLK_BACKSPACE:
            game->state = game->prev_state;
            break;

        case SDLK_m:
            toggle_sound(game);
            break;

        case SDLK_f:
            toggle_fullscreen(game);
            break;

        case SDLK_UP:
            if (selected_button > 0)
                selected_button--;
            break;

        case SDLK_DOWN:
            if (selected_button < 3)
                selected_button++;
            break;

        case SDLK_RETURN:
            handle_selection(game);
            break;

        default: {}
    }
}

void handle_events_menu(SDL_Event event, game_t *game)
{
    switch (event.type) {
        case SDL_KEYDOWN:
            handle_keyboard_event_menu(game, event.key.keysym.sym);
            break;

        case SDL_MOUSEBUTTONDOWN:
            x_click_pos = event.button.x;
            y_click_pos = event.button.y;

            break;
        default: {}
    }
}

void handle_keyup_game(SDL_Event event)
{
    switch(event.key.keysym.sym) {
        case SDLK_RIGHT:
            player.velocity_x = 0;
            if (player.acceleration > 0) {
                player.acceleration = 0;
            }
            break;
        case SDLK_LEFT:
            player.velocity_x = 0;
            if (player.acceleration < 0) {
                player.acceleration = 0;
            }
            break;
        case SDLK_UP:
        case SDLK_SPACE:
            player.velocity_y = player.gravity;
            break;

        case SDLK_d:
            player2.velocity_x = 0;
            if (player2.acceleration > 0) {
                player2.acceleration = 0;
            }
            break;
        case SDLK_q:
            player2.velocity_x = 0;
            if (player2.acceleration < 0) {
                player2.acceleration = 0;
            }
            break;
        case SDLK_z:
            player2.velocity_y = player.gravity;
            break;

        default: {}
    }
}

void handle_held_key_game()
{
    const uint8_t *keys = SDL_GetKeyState(NULL);
    //Running
    if (keys[SDLK_RIGHT] && keys[SDLK_LSHIFT]) {
        player.acceleration = 0.2;

        if (background.srect.x + background.srect.w + background.offset_val <= background.img->w)
            background.offset_x += background.offset_val;
    }

    if (keys[SDLK_RIGHT]) {
        player.acceleration = 0.1;

        if (background.srect.x + background.srect.w + background.offset_val <= background.img->w)
            background.offset_x += background.offset_val;
    }

    if (keys[SDLK_LEFT]) {
        if (player.velocity_x > 0)
            player.velocity_x = 0;
        player.acceleration = -0.1;

        if (background.srect.x - background.offset_val >= 5)
            background.offset_x -= background.offset_val;
    }

    if (keys[SDLK_SPACE] || keys[SDLK_UP]) {
        if (!player.is_jumping) {
            jump(&player);
            player.pos_init = player.pos.y;
        }
    }

    if (keys[SDLK_DOWN]) {
        if (player.is_jumping == true)
            player.velocity_y = player.gravity + 4;
    }

    //Running
    if (keys[SDLK_d] && keys[SDLK_LSHIFT]) {
        player2.acceleration = 0.2;

        if (background.srect.x + background.srect.w + background.offset_val <= background.img->w)
            background.offset_x += background.offset_val;
    }

    if (keys[SDLK_d]) {
        player2.acceleration = 0.1;

        if (background.srect.x + background.srect.w + background.offset_val <= background.img->w)
            background.offset_x += background.offset_val;
    }

    if (keys[SDLK_q]) {
        player2.acceleration = -0.1;

        if (player2.velocity_x > 0)
            player2.velocity_x = 0;

        if (background.srect.x - background.offset_val >= 5)
            background.offset_x -= background.offset_val;
    }

    if (keys[SDLK_z]) {
        if (!player2.is_jumping) {
            jump(&player2);
            player2.pos_init = player.pos.y;
        }

    }
}

void handle_events_game(SDL_Event event, game_t *game)
{
    switch (event.type) {
        case SDL_KEYUP:
            handle_keyup_game(event);
            break;
        case SDL_KEYDOWN:
            handle_keyboard_event_menu(game, event.key.keysym.sym);
            break;
        default: {}
    }
}

void handle_events(SDL_Event event, game_t *game)
{
    if (event.type == SDL_QUIT)
        game->state = EXIT_STATE;

    switch (game->state) {
        case OPTIONS_STATE:
        case MENU_STATE:
            handle_events_menu(event, game);
            break;
        case GAME_STATE:
            handle_events_game(event, game);
            break;
        default: {}
    }
}

void get_input(game_t *game)
{
    if (game->state == GAME_STATE) {
        handle_held_key_game();
    }

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        handle_events(event, game);
    }
}
