#ifndef BUTCHER_H_INCLUDED
#define BUTCHER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [Butcher object]
*/

typedef struct _Butcher
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of Butcher
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
} Butcher;
Elements *New_Butcher(int label);
void _Butcher_update_position(Elements *self, int dx, int dy);
void Butcher_update(Elements *self);
void Butcher_interact(Elements *self, Elements *target);
void Butcher_draw(Elements *self);
void Butcher_destory(Elements *self);

#endif
