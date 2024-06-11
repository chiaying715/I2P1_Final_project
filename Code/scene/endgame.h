#ifndef ENDGAME_H_INCLUDED
#define ENDGAME_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/butcher.h"
/*
   [game scene object]
*/

// typedef enum _EleType_EndGame
// {
//     Floor_L,
//     Teleport_L,
//     Tree_L,
//     Character_L,
//     Projectile_L,
//     Trap_L,
//     Butcher_L
// } EleType_EndGame;
typedef struct _EndGame
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
} EndGame;
Scene *New_EndGame(int label);
void end_game_update(Scene *self);
void end_game_draw(Scene *self);
void end_game_destroy(Scene *self);

#endif