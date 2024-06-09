#ifndef Seeds_s_H_INCLUDED
#define Seeds_s_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
/*
   [Seeds_s object]
*/
typedef struct _Seeds_s
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    // 添加計時相關變量
    double plant_time;
    bool is_harvestable;
    int score; // 添加積分值變量
    // 新增成員變數
    ALLEGRO_FONT *font;
    ALLEGRO_TIMER *timer; // 計時器
    int countdown; // 倒數時間
    ALLEGRO_EVENT_QUEUE *event_queue; // 新增事件佇列成員
} Seeds_s;
Elements *New_Seeds_s(int label, int x, int y);
void Seeds_s_update(Elements *self);
void Seeds_s_interact(Elements *self, Elements *tar);
void Seeds_s_draw(Elements *self);
void Seeds_s_destory(Elements *self);
void _Seeds_s_update_position(Elements *self, int dx, int dy);
#endif