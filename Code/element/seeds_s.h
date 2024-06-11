#ifndef seeds_s_H_INCLUDED
#define seeds_s_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
/*
   [seeds_s object]
*/
typedef struct _seeds_s
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
    int dele;
    //double last_watered_time;
} seeds_s;
Elements *New_seeds_s(int label, int x, int y);
void reduce_seeds_s_countdown() ;
void water_seeds_s(seeds_s *self);
void seeds_s_update(Elements *self);
void Seeds_s_interact(Elements *self, Elements *tar);
void seeds_s_draw(Elements *self);
void seeds_s_destroy(Elements *self);
void _seeds_s_update_position(Elements *self, int dx, int dy);
#endif