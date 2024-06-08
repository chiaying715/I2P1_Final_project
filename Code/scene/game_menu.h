#ifndef GAME_MENU_H_INCLUDED
#define GAME_MENU_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _Game_Menu
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
    ALLEGRO_BITMAP *background;
} Game_Menu;
Scene *New_Game_Menu(int label);
void Game_Menu_update(Scene *self);
void Game_Menu_draw(Scene *self);
void Game_Menu_destroy(Scene *self);

#endif
