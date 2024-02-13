#include "init.h"

void initialize(const char *window_title)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
        fprintf(stderr, "Could not initialize subsystems > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create Window
    Uint32 flags = SDL_HWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF;
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, flags);
    if (screen == NULL) {
        fprintf(stderr, "Couldn't create window > %s\n",
                        SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Set the audio rate to 48000, 16 bit, stereo, 2 channels and a 4096 byte buffer
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        fprintf(stderr, "Could not open audio > %s\n", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialize ttf library
    TTF_Init();

    // Add a title to the window
    SDL_WM_SetCaption(window_title, NULL);
}

void shutdown()
{
    printf("Arret SDL...\n");
    TTF_Quit();
    Mix_CloseAudio();
}
