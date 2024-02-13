/**
* @file structs.h
* @brief les structures
* @author Chaabani Mohamed ali
* @version 0.1
* @date May 05, 2023
*
* structures du programme
*
*/

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include "defs.h"

/**
* @struct tempo_t
* @brief sturcture du temps (pour la minimap)
*/

typedef struct {
    char str[100]; /*!< chaine où on va storer le temps*/
    int sec_e; /*!< secondes écoulées*/
    time_t t1, t2; /*!< intervalle du temps entre t1 et t2*/
    int min, sec; /*!< temps en secondes et en minutes*/
}tempo_t;

/**
* @struct spritesheet_t
* @brief structure spritesheet pour l'animation des perso
*/

typedef struct {
    SDL_Surface *spritesheet; /*!< image de la spritesheet*/
    int sprite_width; /*!< largeur de l'image*/
    int sprite_height; /*!< hauteur de l'image*/
    int num_frames; /*!< numero d'images*/
    int frame_index; /*!< numero d'images*/
    int frame_multiplier; /*!< numero d'images multipliées*/
}spritesheet_t;

/**
* @struct vector_t
* @brief sturcture vecteur
*/

typedef struct {
    int x; /*!< valeur x du vecteur*/
    int y; /*!< valeur y du vecteur*/
}vector_t;

/**
* @struct Player
* @brief structure du Joueur
*/

typedef struct {
    int num; /*!< numero du joueur*/
    vector_t pos; /*!< position du joueur*/
    unsigned int vie; /*!< vie du joueur*/
    int score; /*!< score du joueur*/
    float velocity_x; /*!< velocité du joueur (acceleration et direction)*/
    float velocity_y; /*!< velocité du joueur sur l'axe y*/
    float max_velocity; /*!< velocité maximale du joueur*/
    float acceleration; /*!< acceleration du joueur*/
    float gravity; /*!< gravité du joueur*/
    float jump_height; /*!< puissance du joueur*/
    bool is_jumping; /*!< etat: saut = true, sinon faux*/
    unsigned int pos_init; /*!< position initiale avant le saut*/
    int prev_movement; /*!< etat du mouvement precedent*/
    int movement; /*!< etat du mouvement actuel*/
    spritesheet_t spritesheets[7]; /*!< tableau de spritesheets pour l'animation*/
}Entity;

/**
* @struct Background
* @brief structure du background
*/

typedef struct {
    int offset_x; /*!< entier: Valeur avec laquelle on va couper l'image du background sur l'axe x*/
    int offset_y; /*!< entier: Valeur avec laquelle on va couper l'image du background sur l'axe y*/
    int offset_val; /*!< entier: Valeur avec laquelle on va couper l'image du background*/
    SDL_Rect srect; /*!< Rectangle source pour couper l'image. */;
    SDL_Rect dsrect; /*!< Rectagle destination */
    SDL_Surface *img; /*!< Surface. */
}Background;

/**
* @struct miniplayer
* @brief structure du minijoueur qui va être affiché sur la minimap
*/

typedef struct {
    vector_t pos; /*!< position du minijoueur. */
    SDL_Surface *img; /*!< image du minijoueur. */
}miniplayer_t;

/**
* @struct Minimap
* @brief structure de la minimap
*/

typedef struct {
    SDL_Surface *map; /*!< tableau d'images pour l'animation. */
    miniplayer_t miniplayer; /*!< minijoueur 1 */
    miniplayer_t miniplayer2; /*!< minijoueur 2 */
    SDL_Rect positionmap; /*!< position de la map */
}Minimap;

// Enumerate all possible states of the game
enum {
    GAME_STATE,
    OPTIONS_STATE,
    MENU_STATE,
    PAUSE_STATE,
    EXIT_STATE,
};

typedef struct {
    bool is_fullscreen;
    int prev_state;
    int state;
    int volume;
}game_t;

#endif //STRUCTS_H_
