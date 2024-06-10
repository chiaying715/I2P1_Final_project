#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/trap.h"
/* 
   [game scene object]
*/
// typedef enum _EleType_GameScene
// {
//     Floor_L,
//     Teleport_L,
//     Tree_L,
//     Character_L,
//     Projectile_L,
//     Trap_L, 
//     // Butcher_L
// } EleType_GameScene;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;

} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
