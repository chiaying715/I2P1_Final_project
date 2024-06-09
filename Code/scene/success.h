#ifndef SUCCESS_H_INCLUDED
#define SUCCESS_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/success_chara.h"
#include "../element/test.h"
/*
   [game scene object]
*/

typedef enum _EleType_SuccessScene
{
    Success_chara_L
} EleType_SuccessScene;
typedef struct _Success
{
    ALLEGRO_BITMAP *background;

} Success;
Scene *New_Success(int label);
void Success_update(Scene *self);
void Success_draw(Scene *self);
void Success_destroy(Scene *self);

#endif
