#include "menu.h"

SDL_Surface *bg_img = NULL;

SDL_Surface *play_button = NULL;
SDL_Surface *play_button_clicked = NULL;

SDL_Surface *options_button = NULL;
SDL_Surface *options_button_clicked = NULL;

SDL_Surface *exit_button = NULL;
SDL_Surface *exit_button_clicked = NULL;

SDL_Surface *options_menu_background = NULL;

SDL_Surface *back_button = NULL;

SDL_Surface *toggle_fullscreen_button = NULL;
SDL_Surface *toggle_fullscreen_button_clicked = NULL;

SDL_Surface *vol_minus_button = NULL;
SDL_Surface *vol_plus_button = NULL;

SDL_Surface *sound_on_button  = NULL;
SDL_Surface *sound_off_button = NULL;

SDL_Surface *stars[7];

Mix_Music *bg_music = NULL;
Mix_Chunk *switch_sfx = NULL;

extern int x_click_pos;
extern int y_click_pos;

TTF_Font *font = NULL;

extern int selected_button;


void load_menu_resources()
{
    // Load all resources needed for the main menu and the options menu
    bg_img = IMG_Load("../assets/gfx/menu/background_menu.png");
    options_menu_background = IMG_Load("../assets/gfx/menu/options_menu_background.png");

    play_button = IMG_Load("../assets/gfx/menu/play_button.png");
    play_button_clicked = IMG_Load("../assets/gfx/menu/play_button_clicked.png");

    options_button = IMG_Load("../assets/gfx/menu/options_button.png");
    options_button_clicked = IMG_Load("../assets/gfx/menu/options_button_clicked.png");

    exit_button = IMG_Load("../assets/gfx/menu/exit_button.png");
    exit_button_clicked = IMG_Load("../assets/gfx/menu/exit_button_clicked.png");

    back_button = IMG_Load("../assets/gfx/menu/back_button.png");

    toggle_fullscreen_button = IMG_Load("../assets/gfx/menu/toggle_fullscreen_button.png");
    toggle_fullscreen_button_clicked = IMG_Load("../assets/gfx/menu/toggle_fullscreen_button_clicked.png");

    sound_on_button = IMG_Load("../assets/gfx/menu/sound_on_button.png");
    sound_off_button = IMG_Load("../assets/gfx/menu/sound_off_button.png");

    vol_minus_button = IMG_Load("../assets/gfx/menu/vol_minus_button.png");
    vol_plus_button = IMG_Load("../assets/gfx/menu/vol_plus_button.png");

    bg_music = Mix_LoadMUS("../assets/sfx/background_music.wav");
    Mix_PlayMusic(bg_music, -1);

    stars[0] = IMG_Load("../assets/gfx/menu/animation/1.png");
    stars[1] = IMG_Load("../assets/gfx/menu/animation/2.png");
    stars[2] = IMG_Load("../assets/gfx/menu/animation/3.png");
    stars[3] = IMG_Load("../assets/gfx/menu/animation/4.png");
    stars[4] = IMG_Load("../assets/gfx/menu/animation/5.png");
    stars[5] = IMG_Load("../assets/gfx/menu/animation/6.png");
    stars[6] = IMG_Load("../assets/gfx/menu/animation/7.png");

    switch_sfx = Mix_LoadWAV("../assets/sfx/switch.wav");

    font = TTF_OpenFont("../assets/fonts/samurai_font.ttf", FONTSIZE);
}

void draw_options_menu(game_t *game)
{
    draw_image(screen, options_menu_background, 0, 0);
    SDL_Color color = {255, 110, 0};
    render_text(screen, font, "Options", color, 250, 20);
    render_text(screen, font, "Volume", color, 270, 180);

    draw_image(screen, back_button, 10, 10);
    draw_image(screen, vol_minus_button, 130, 160);
    draw_image(screen, vol_plus_button, 540, 160);

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x >= 175 && x <= 580 && y >= 440 && y <= 530)
        draw_image(screen, toggle_fullscreen_button_clicked, 120, 440);
    else
        draw_image(screen, toggle_fullscreen_button, 120, 440);

    if (game->volume != 0)
        draw_image(screen, sound_on_button,  680, 20);
    else
        draw_image(screen, sound_off_button, 680, 20);

    SDL_Flip(screen);
}

void handle_mouse_click_options_menu(game_t *game)
{
    if (x_click_pos >= 13 && x_click_pos <= 85 && y_click_pos >= 14 && y_click_pos <= 80) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        game->state = MENU_STATE;
    }

    else if (x_click_pos >= 130 && x_click_pos <= 245 && y_click_pos >= 160 && y_click_pos <= 275) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        game->volume -= 10;
    }

    else if (x_click_pos >= 540 && x_click_pos <= 655 && y_click_pos >= 160 && y_click_pos <= 275) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        game->volume += 10;
    }

    else if (x_click_pos >= 175 && x_click_pos <= 580 && y_click_pos >= 440 && y_click_pos <= 535) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        toggle_fullscreen(game);
    }

    else if (x_click_pos >= 675 && x_click_pos <= 770 && y_click_pos >= 20 && y_click_pos <= 90) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        toggle_sound(game);
    }

    x_click_pos = y_click_pos = 0;
}

void options_menu(game_t *game)
{
    draw_options_menu(game);
    handle_mouse_click_options_menu(game);

    SDL_Flip(screen);
}

void draw_main_menu()
{
    // Comment this line to enable arrow key selection
    selected_button = 0;

    const char *GAME_TITLE = "Desert Rose";

    draw_image(screen, bg_img, 0, 0);

    SDL_Color color = {245, 238, 82};
    render_text(screen, font, GAME_TITLE, color, TITLE_X_POS, TITLE_Y_POS);

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x >= 27 && x <= 230 && y >= 100 && y <= 145)
        selected_button = 1;

    else if (x >= 27 && x <= 230 && y >= 200 && y <= 245)
        selected_button = 2;

    else if(x >= 27 && x <= 230 && y >= 300 && y <= 345)
        selected_button = 3;

    switch (selected_button) {
        case 1:
            draw_image(screen, play_button_clicked, 0, 100);
            draw_image(screen, options_button, 0, 200);
            draw_image(screen, exit_button, 0, 300);
            break;
        case 2:
            draw_image(screen, play_button, 0, 100);
            draw_image(screen, options_button_clicked, 0, 200);
            draw_image(screen, exit_button, 0, 300);
            break;
        case 3:
            draw_image(screen, play_button, 0, 100);
            draw_image(screen, options_button, 0, 200);
            draw_image(screen, exit_button_clicked, 0, 300);
            break;

        default: {
            draw_image(screen, play_button, 0, 100);
            draw_image(screen, options_button, 0, 200);
            draw_image(screen, exit_button, 0, 300);
        }
    }

    // Screen Animation
    for (int i = 0; i < 7; i++) {
        draw_image(screen, stars[i], 435, 375);
        draw_image(screen, stars[i], 505, 395);
        SDL_Delay(10);
        SDL_Flip(screen);
    }
}

void handle_mouse_click_main_menu(game_t *game)
{
    // Play a sound effect when clicking on a button and change the game state
    // according to what button was clicked

    if (x_click_pos >= 27 && x_click_pos <= 230 && y_click_pos >= 100 && y_click_pos <= 145) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        // SDL_Delay(DELAY_TIME);
        game->state = GAME_STATE;
    }

    else if (x_click_pos >= 27 && x_click_pos <= 230 && y_click_pos >= 200 && y_click_pos <= 245) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        // SDL_Delay(DELAY_TIME);
        game->state = OPTIONS_STATE;
    }

    else if (x_click_pos >= 27 && x_click_pos <= 230 && y_click_pos >= 300 && y_click_pos <= 345) {
        Mix_PlayChannel(-1, switch_sfx, 0);
        // SDL_Delay(DELAY_TIME + 200);
        game->state = EXIT_STATE;
    }

    x_click_pos = y_click_pos = 0;
}

void main_menu(game_t *game)
{
    draw_main_menu();

    handle_mouse_click_main_menu(game);

    SDL_Flip(screen);
}

void help()
{
    printf("--------Menu--------\n");
    printf("\tf: fullscreen\n");
    printf("\tj: Jouer\n");
    printf("\to: menu options\n");
    printf("\tfleches: selection\n");
    printf("\tbackspace: revenir en arriere\n");
    printf("\t-/+: augmenter ou diminuer le volume\n");
    printf("\tm: arreter ou jouer le son\n");
    printf("\tq/esc: quitter le jeu\n");
}

void clean_menu()
{
    printf("Liberation memoire menu...\n");

    SDL_FreeSurface(bg_img);
    SDL_FreeSurface(play_button);
    SDL_FreeSurface(play_button_clicked);
    SDL_FreeSurface(options_button);
    SDL_FreeSurface(options_button_clicked);
    SDL_FreeSurface(exit_button);
    SDL_FreeSurface(exit_button_clicked);
    SDL_FreeSurface(back_button);
    SDL_FreeSurface(toggle_fullscreen_button);
    SDL_FreeSurface(toggle_fullscreen_button_clicked);
    SDL_FreeSurface(sound_on_button);
    SDL_FreeSurface(sound_off_button);

    for (int i = 0; i < 7; i++)
        SDL_FreeSurface(stars[i]);

    Mix_FreeMusic(bg_music);
}
