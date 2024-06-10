
#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/trap.h"
#include "../element/projectile.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Character_L,
    Projectile_L,
    Seeds_s_L,
    Seeds_c_L,
    Seeds_e_L,
    Trap_L, 
    Butcher_L
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *day_background;
    ALLEGRO_BITMAP *dusk1_background;
    ALLEGRO_BITMAP *dusk2_background;
    ALLEGRO_BITMAP *night_background;
    ALLEGRO_FONT *font;
    double lastTreeTime;
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
