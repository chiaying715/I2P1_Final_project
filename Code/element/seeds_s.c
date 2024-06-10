#include "seeds_s.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdbool.h>
#include "../scene/sceneManager.h"

/*
   [seeds_s function]
*/
Elements *New_seeds_s(int label, int x, int y)
{
    seeds_s *pDerivedObj = (seeds_s *)malloc(sizeof(seeds_s));
    if (!pDerivedObj) {
        printf("Error: Failed to allocate memory for seeds_s object\n");
        return NULL;
    }
    Elements *pObj = New_Elements(label);
    if (!pObj) {
        free(pDerivedObj); // 释放 seeds_s 对象的内存
        printf("Error: Failed to allocate memory for Elements object\n");
        return NULL;
    }
    
    // 初始化种子对象的成员变量
    pDerivedObj->img = al_load_bitmap("assets/image/seeds_s.webp");
    if (!pDerivedObj->img) {
        printf("Error: Failed to load bitmap\n");
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    if (!pDerivedObj->hitbox) {
        printf("Error: Failed to create circle\n");
        al_destroy_bitmap(pDerivedObj->img);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->plant_time = al_get_time();
    pDerivedObj->is_harvestable = false;
    pDerivedObj->score = 20;
    pDerivedObj->font = al_create_builtin_font();
    if (!pDerivedObj->font) {
        printf("Error: Failed to create font\n");
        al_destroy_bitmap(pDerivedObj->img);
        free(pDerivedObj->hitbox);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->timer = al_create_timer(1.0);
    if (!pDerivedObj->timer) {
        printf("Error: Failed to create timer\n");
        al_destroy_bitmap(pDerivedObj->img);
        free(pDerivedObj->hitbox);
        al_destroy_font(pDerivedObj->font);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->countdown = 160;
    pDerivedObj->minus = 0;
    //pDerivedObj->last_watered_time = al_get_time();
    pDerivedObj->event_queue = al_create_event_queue();
    if (!pDerivedObj->event_queue) {
        printf("Error: Failed to create event queue\n");
        al_destroy_bitmap(pDerivedObj->img);
        free(pDerivedObj->hitbox);
        al_destroy_font(pDerivedObj->font);
        al_destroy_timer(pDerivedObj->timer);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    al_register_event_source(pDerivedObj->event_queue, al_get_timer_event_source(pDerivedObj->timer));
    al_start_timer(pDerivedObj->timer);

    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = seeds_s_update;
    pObj->Interact = Seeds_s_interact;
    pObj->Draw = seeds_s_draw;
    pObj->Destroy = seeds_s_destroy;

    return pObj;
}

void seeds_s_update(Elements *self)
{
    seeds_s *Obj = ((seeds_s *)(self->pDerivedObj));
    ALLEGRO_EVENT ev;
    while (al_get_next_event(Obj->event_queue, &ev)) { // 获取下一个事件
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            double current_time = al_get_time();
            double elapsed_time = current_time - Obj->plant_time;
            //double time_since_last_watered = current_time - Obj->last_watered_time;

           /*if (time_since_last_watered >= 10.0) {
                printf("seeds_s object has not been watered for 60 seconds and will be destroyed\n");
                self->dele = true; // 标记为删除
                Obj->last_watered_time = current_time;
                return;
            }*/

            if (elapsed_time >= 160.0) {
                Obj->is_harvestable = true;
            }
            if (Obj->countdown > 0) {
                Obj->countdown = 160 - (int)elapsed_time - Obj->minus;
                if (Obj->countdown <= 0) {
                    Obj->countdown = 0;
                    Obj->is_harvestable = true;
                }
            }
        }
    }
    /*if (self->dele) {
        printf("self:%d deleted\n", self->label);
        _Remove_elements(scene, self);
    }*/
}

void Seeds_s_interact(Elements *self, Elements *tar)
{
    seeds_s *Obj = ((seeds_s *)(self->pDerivedObj));
    /*if (tar->label == Character_L && Obj->is_harvestable) {
        Obj->score += 5; // 收获后增加积分
        Obj->is_harvestable = false; // 重置为不可收获状态
        Obj->plant_time = al_get_time(); // 重置种植时间
        Obj->countdown = 50; // 重置倒计时
        Obj->minus = 0; 
        al_start_timer(Obj->timer); // 重启计时器
    }
    */
    if (tar->label == Character_L&&Obj->is_harvestable&&key_state[ALLEGRO_KEY_H]) {
        seeds_s *Obj = (seeds_s *)(self->pDerivedObj);
        Character *chara = (Character *)(tar->pDerivedObj);
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            self->dele = true;
            tot_score += Obj->score;
            //printf("-10s\n"); // 打印 -10s
        }
        // 检查是否碰撞
        else {
            //printf("No collision detected\n"); // 没有检测到碰撞
        }
    }
}

void reduce_seeds_s_countdown() {
    Scene *currentScene = scene;
    if (currentScene != NULL) {
        ElementVec allSeeds = _Get_label_elements(currentScene, Seeds_s_L);
        for (int i = 0; i < allSeeds.len; i++) {
            seeds_s *seed = (seeds_s *)(allSeeds.arr[i]->pDerivedObj);
            seed->minus += 10;
            //seed->last_watered_time = 0;
            printf("seeds_s countdown reduced by 10\n");
        }
    }
}

/*void water_seeds_s(Elements *self) {
    Scene *currentScene = scene;
    if (currentScene != NULL) {
        ElementVec allSeeds = _Get_label_elements(currentScene, seeds_s_L);
        for (int i = 0; i < allSeeds.len; i++) {
            seeds_s *seed = (seeds_s *)(allSeeds.arr[i]->pDerivedObj);
            seed->last_watered_time = al_get_time();
            printf("seeds_s watered\n");
        }
    }
}
*/
// 修改 seeds_s 的繪製函數
void seeds_s_draw(Elements *self) 
{
    seeds_s *Obj = ((seeds_s *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y-15, 0);
    } else {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y-15, 0);
    }
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y + Obj->height-8, ALLEGRO_ALIGN_CENTER, "Score: %d", Obj->score);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 40, ALLEGRO_ALIGN_CENTER, "Time: %d", Obj->countdown);
}

void seeds_s_destroy(Elements *self) 
{
    if (!self) return;

    seeds_s *obj = (seeds_s *)(self->pDerivedObj);
    if (obj) {
        al_destroy_bitmap(obj->img);
        free(obj->hitbox);
        al_destroy_font(obj->font);
        al_destroy_timer(obj->timer);
        al_destroy_event_queue(obj->event_queue);
        free(obj);
    }
    
    free(self);
}