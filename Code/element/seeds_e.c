#include "seeds_e.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdbool.h>
#include "../scene/sceneManager.h"

/*
   [seeds_e function]
*/
Elements *New_seeds_e(int label, int x, int y)
{
    seeds_e *pDerivedObj = (seeds_e *)malloc(sizeof(seeds_e));
    if (!pDerivedObj) {
        //printf("Error: Failed to allocate memory for seeds_e object\n");
        return NULL;
    }
    Elements *pObj = New_Elements(label);
    if (!pObj) {
        free(pDerivedObj); // 释放 seeds_e 对象的内存
        //printf("Error: Failed to allocate memory for Elements object\n");
        return NULL;
    }
    
    // 初始化种子对象的成员变量
    pDerivedObj->img = al_load_bitmap("assets/image/seeds_e.webp");
    if (!pDerivedObj->img) {
        //printf("Error: Failed to load bitmap\n");
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
        //printf("Error: Failed to create circle\n");
        al_destroy_bitmap(pDerivedObj->img);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->plant_time = al_get_time();
    pDerivedObj->is_harvestable = false;
    pDerivedObj->is_dying = false;
    pDerivedObj->score = 10;
    pDerivedObj->dele = 0;
    pDerivedObj->font = al_create_builtin_font();
    if (!pDerivedObj->font) {
        //printf("Error: Failed to create font\n");
        al_destroy_bitmap(pDerivedObj->img);
        free(pDerivedObj->hitbox);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->timer = al_create_timer(1.0);
    if (!pDerivedObj->timer) {
        //printf("Error: Failed to create timer\n");
        al_destroy_bitmap(pDerivedObj->img);
        free(pDerivedObj->hitbox);
        al_destroy_font(pDerivedObj->font);
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pDerivedObj->countdown = 90;
    pDerivedObj->minus = 0;
    //pDerivedObj->dele = 0;
    pDerivedObj->last_watered_time = al_get_time();
    pDerivedObj->event_queue = al_create_event_queue();
    if (!pDerivedObj->event_queue) {
        //printf("Error: Failed to create event queue\n");
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
    //pDerivedObj->dele = 0;
    pObj->dele = 0;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = seeds_e_update;
    pObj->Interact = Seeds_e_interact;
    pObj->Draw = seeds_e_draw;
    pObj->Destroy = seeds_e_destroy;

    return pObj;
}

void seeds_e_update(Elements *self)
{
    seeds_e *Obj = ((seeds_e *)(self->pDerivedObj));
    ALLEGRO_EVENT ev;
    while (al_get_next_event(Obj->event_queue, &ev)) { // 获取下一个事件
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            double current_time = al_get_time();
            double elapsed_time = current_time - Obj->plant_time;
            double time_since_last_watered = current_time - Obj->last_watered_time;
            
            if(Obj->dele){
                printf("seeds_e_delete_ntd:%d\n", self->id);
                self->dele=1;
                Obj->dele=0;
            }
            if (time_since_last_watered >= 25.0) {
                //printf("Seeds_c object has not been watered for 60 seconds and will be destroyed\n");
                Obj->is_dying= true; // 标记为删除
            }
            else{
                Obj->is_dying= false;
            }
            if (time_since_last_watered >= 30.0) {
                //printf("seeds_e object has not been watered for 60 seconds and will be destroyed\n");
                self->dele = true; // 标记为删除
                printf("seeds_e_delete_nowater:%d\n", self->id);
                //printf("seeds_e_delete_nowater:%d\n", self->id);
                Obj->last_watered_time = current_time;
                return;
            }
            //else{
                //add
                //self->dele = false;
                //add
            //}

            if (elapsed_time >= 90.0) {
                Obj->is_harvestable = true;
            }
            if (Obj->countdown > 0) {
                Obj->countdown = 90 - (int)elapsed_time - Obj->minus;
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

void Seeds_e_interact(Elements *self, Elements *tar)
{
    seeds_e *Obj = ((seeds_e *)(self->pDerivedObj));
    /*Sif (tar->label == Character_L && Obj->is_harvestable) {
        Obj->score += 5; // 收获后增加积分
        Obj->is_harvestable = false; // 重置为不可收获状态
        Obj->plant_time = al_get_time(); // 重置种植时间
        Obj->countdown = 50; // 重置倒计时
        Obj->minus = 0; 
        al_start_timer(Obj->timer); // 重启计时器
    }
    */
    Scene *currentScene = scene;
    ElementVec allSeeds = _Get_label_elements(currentScene, Seeds_e_L);
    if((thief % 100) / 10 != 0) {
        for (int i = 0; i < allSeeds.len; i++) {
            seeds_e *seed = (seeds_e *)(allSeeds.arr[i]->pDerivedObj);
            seed->dele = true;
            printf("seeds_e_delete_thief:%d\n", self->id);
            }
        thief -= 10;
    }
    else if (tar->label == Character_L&&Obj->is_harvestable&&key_state[ALLEGRO_KEY_H]) {
        seeds_e *Obj = (seeds_e *)(self->pDerivedObj);
        Character *chara = (Character *)(tar->pDerivedObj);
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            self->dele = true;
            printf("seeds_e_delete_harvest:%d\n", self->id);
            tot_score += Obj->score;
            //printf("-10s\n"); // 打印 -10s
        }
        // 检查是否碰撞
        else {
             //add
            //self->dele = false;
            //add
            //printf("No collision detected\n"); // 没有检测到碰撞
        }
    }
}
void reduce_seeds_e_countdown() {
    Scene *currentScene = scene;
    if (currentScene != NULL) {
        ElementVec allSeeds = _Get_label_elements(currentScene, Seeds_e_L);
        for (int i = 0; i < allSeeds.len; i++) {
            seeds_e *seed = (seeds_e *)(allSeeds.arr[i]->pDerivedObj);
            seed->minus += 10;
            seed->last_watered_time = 0;
            //printf("seeds_e countdown reduced by 10\n");
        }
    }
}

void water_seeds_e(seeds_e *self) {
    Scene *currentScene = scene;
    if (currentScene != NULL) {
       // ElementVec allSeeds = _Get_label_elements(currentScene, Seeds_e_L);
       // for (int i = 0; i < allSeeds.len; i++) {
            //seeds_e *seed = (seeds_e *)(allSeeds.arr[i]->pDerivedObj);
            self->last_watered_time = al_get_time();
            printf("seeds_e watered\n");
       // }
    }
}
// 修改 seeds_e 的繪製函數
void seeds_e_draw(Elements *self) 
{
    seeds_e *Obj = ((seeds_e *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y-30, 0);
    } 
    else if(Obj->is_dying){
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(0, 0, 0), Obj->x, Obj->y-30, 0);
    }
    else {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y-30, 0);
    }
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y + Obj->height-30, ALLEGRO_ALIGN_CENTER, "Score: %d", Obj->score);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 40, ALLEGRO_ALIGN_CENTER, "Time: %d", Obj->countdown);
}

void seeds_e_destroy(Elements *self) 
{
    if (!self) return;

    seeds_e *obj = (seeds_e *)(self->pDerivedObj);
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