#include "main.h"
#include "es.h"

SDL_Surface *screen = NULL;
Background background;

Entity player;
Entity player2;

Minimap minimap;

Entity ennemy;
Entity ennemy2;

tempo_t t;

int main()
{
    atexit(clean_menu);
    atexit(shutdown);

    initialize("Espada Calavera");

    game_t game;
    init_game(&game);

    load_menu_resources();

    init_player(&player, 1);
    init_player(&player2, 2);

    init_ennemy(&ennemy, 1);
    init_ennemy(&ennemy2, 2);

    init_background();

    init_map(&minimap);
    init_time(&t);

    // Set the frame rate to 60 fps
    const int FPS = 60;

    // Calculate the time for each frame
    const int FRAME_TIME = 1000 / FPS;

    while (game.state != EXIT_STATE) {
        int ticks = SDL_GetTicks();

        get_input(&game);
        handle_sound(&game);
        handle_game_state(&game);

        int elapsed_ticks = SDL_GetTicks() - ticks;
        if (elapsed_ticks < FRAME_TIME) {
            SDL_Delay(FRAME_TIME - elapsed_ticks);
        }
    }

    return EXIT_SUCCESS;
}
