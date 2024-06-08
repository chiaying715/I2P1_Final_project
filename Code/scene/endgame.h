#ifndef ENDGAME_H_INCLUDED
#define ENDGAME_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
/*
   [game scene object]
*/
/*
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Character_L,
    Projectile_L,
    Trap_L
} EleType;*/
typedef struct _EndGame
{
    ALLEGRO_BITMAP *background;

} EndGame;
Scene *New_EndGame(int label);
void end_game_update(Scene *self);
void end_game_draw(Scene *self);
void end_game_destroy(Scene *self);

#endif
