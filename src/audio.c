#include "game.h"
#include "audio.h"

extern SDL_Surface *screen;

void handle_sound(game_t *game) 
{
    if (game->volume < MIN_VOL)
        game->volume = MIN_VOL;
    else if (game->volume > MAX_VOL)
        game->volume = MAX_VOL;

    Mix_VolumeMusic(game->volume);
}

void toggle_sound(game_t *game)
{
    game->volume = (game->volume == 0 ) ? MAX_VOL :  MIN_VOL;
}
