#ifndef SUCCESS_CHARA_H_INCLUDED
#define SUCCESS_CHARA_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [character object]
*/

typedef struct _Success_Character
{
    int x, y;
    int width, height;              // the width and height of image
    ALGIF_ANIMATION *gif_status[5]; // gif for each state. 0: stop, 1: move, 2:attack  
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    Shape *hitbox; // the hitbox of object
    ALLEGRO_BITMAP *img;
} Success_Character;
Elements *New_Success_Character(int label);
void _Success_Character_update_position(Elements *self, int dx, int dy);
void Success_Character_update(Elements *self);
void Success_Character_interact(Elements *self, Elements *target);
void Success_Character_draw(Elements *self);
void Success_Character_destory(Elements *self);

#endif