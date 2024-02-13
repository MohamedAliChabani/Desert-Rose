#ifndef MENU_H_
#define MENU_H_

#include "defs.h"
#include "utils.h"
#include "audio.h"
#include "input.h"
#include "structs.h"

#define FONTSIZE 40

#define TITLE_X_POS 100
#define TITLE_Y_POS 10

#define DELAY_TIME 200

void load_menu_resources();

void help();

void main_menu(game_t *game);
void options_menu(game_t *game);

void clean_menu();

#endif // MENU_H_
