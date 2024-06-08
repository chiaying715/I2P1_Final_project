#ifndef SUCCESS_H_INCLUDED
#define SUCCESS_H_INCLUDED
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
typedef struct _Success
{
    ALLEGRO_BITMAP *background;

} Success;
Scene *New_Success(int label);
void success_update(Scene *self);
void success_draw(Scene *self);
void success_destroy(Scene *self);

#endif
