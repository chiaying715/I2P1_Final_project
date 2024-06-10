#ifndef ABOUT_H_INCLUDED
#define ABOUT_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _About
{
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
} About;
Scene *New_About(int label);
void About_update(Scene *self);
void About_draw(Scene *self);
void About_destroy(Scene *self);

#endif