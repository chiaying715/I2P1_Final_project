#ifndef TRAP_H_INCLUDED
#define TRAP_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene.h" // for element label
/*
   [Trap object]
*/
typedef struct _Trap
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int map_data[6][6];
    bool activate;
} Trap;

Elements *New_Trap(int label);
void _Trap_load_map(Trap *Trap);
void Trap_update(Elements *self);
void Trap_interact(Elements *self, Elements *tar);
void Trap_draw(Elements *self);
void Trap_destory(Elements *self);

#endif
