#ifndef seeds_e_H_INCLUDED
#define seeds_e_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
/*
   [seeds_e object]
*/
typedef struct _seeds_e
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    // 添加計時相關變量
    double last_watered_time;
    double plant_time;
    bool is_harvestable;
    int score; // 添加積分值變量
    // 新增成員變數
    ALLEGRO_FONT *font;
    ALLEGRO_TIMER *timer; // 計時器
    int countdown; // 倒數時間
    ALLEGRO_EVENT_QUEUE *event_queue; // 新增事件佇列成員
    double minus; //踩到肥料
} seeds_e;
Elements *New_seeds_e(int label, int x, int y);
void reduce_seeds_e_countdown() ;
void water_seeds_e(Elements *self);
void seeds_e_update(Elements *self);
void Seeds_e_interact(Elements *self, Elements *tar);
void seeds_e_draw(Elements *self);
void seeds_e_destroy(Elements *self);
void _seeds_e_update_position(Elements *self, int dx, int dy);
#endif