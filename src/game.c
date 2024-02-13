#include "game.h"
#include "es.h"

extern Entity player;
extern Entity player2;

extern Entity ennemy;
extern Entity ennemy2;

void init_game(game_t *game)
{
    game->is_fullscreen = false;
    game->prev_state = MENU_STATE;
    game->state = MENU_STATE;
    game->volume = MAX_VOL;
}

void play()
{
    update_player(&player);
    update_player(&player2);

    if (ennemy.vie > 0) {
        update_ennemy(&ennemy);
        check_collision(&ennemy, player);
    }

    if (ennemy2.vie > 0) {
        update_ennemy(&ennemy2);
        check_collision(&ennemy2, player2);
    }

    render_game();
}

void handle_game_state(game_t *game)
{
    switch (game->state) {
        case MENU_STATE:
            main_menu(game);
            break;
        case OPTIONS_STATE:
            options_menu(game);
            break;
        case GAME_STATE:
            play();
            break;
        default: {}
    }
}
