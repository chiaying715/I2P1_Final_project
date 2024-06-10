#include "seeds_s.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdbool.h>
#include "../scene/sceneManager.h"
/*
   [Seeds_s function]
*/
//deleted int v. by lintzoe
Elements *New_Seeds_s(int label, int x, int y)
{
    Seeds_s *pDerivedObj = (Seeds_s *)malloc(sizeof(Seeds_s));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    
    pDerivedObj->img = al_load_bitmap("assets/image/seeds_s.webp");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // 初始化計時相關變量
    pDerivedObj->plant_time = al_get_time();
    pDerivedObj->is_harvestable = false;
    pDerivedObj->score = 20;  // 初始化積分值
    pDerivedObj->font = al_create_builtin_font(); // 初始化字型
    pDerivedObj->timer = al_create_timer(1.0);
    pDerivedObj->countdown = 160;
    pDerivedObj->event_queue = al_create_event_queue();
    al_register_event_source(pDerivedObj->event_queue, al_get_timer_event_source(pDerivedObj->timer));
    al_start_timer(pDerivedObj->timer);
    
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Seeds_s_update;
    pObj->Interact = Seeds_s_interact;
    pObj->Draw = Seeds_s_draw;
    pObj->Destroy = Seeds_s_destory;

    return pObj;
}
void Seeds_s_update(Elements *self)
{
   Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    ALLEGRO_EVENT ev;
    while (al_get_next_event(Obj->event_queue, &ev)) { // 獲取下一個事件
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            double current_time = al_get_time();
            double elapsed_time = current_time - Obj->plant_time;

            if(Obj->dele){
                self->dele=1;
                Obj->dele=0;
            }
            if (elapsed_time >= 160.0) {
                Obj->is_harvestable = true;
            }
            if (Obj->countdown > 0) {
                Obj->countdown = 160 - (int)elapsed_time;
                if (Obj->countdown <= 0) {
                    Obj->countdown = 0;
                    Obj->is_harvestable = true;
                }
            }
        }
    }
}
void Seeds_s_interact(Elements *self, Elements *tar)
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    //printf("in seeds_s interact\n");
    Scene *currentScene = scene;
    ElementVec allSeeds = _Get_label_elements(currentScene, Seeds_s_L);
    if(thief / 100 != 0) {
        for (int i = 0; i < allSeeds.len; i++) {
            Seeds_s *seed = (Seeds_s *)(allSeeds.arr[i]->pDerivedObj);
            seed->dele = true;
        }
        thief -= 100;
    }
    else if (tar->label == Character_L&&Obj->is_harvestable&&key_state[ALLEGRO_KEY_H]) {
        Seeds_s *Obj = (Seeds_s *)(self->pDerivedObj);
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
// 修改 Seeds_s 的繪製函數
void Seeds_s_draw(Elements *self) 
{
    Seeds_s *Obj = ((Seeds_s *)(self->pDerivedObj));
    if (Obj->is_harvestable) {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(255, 255, 255), Obj->x, Obj->y-20, 0);
    } else {
        al_draw_tinted_bitmap(Obj->img, al_map_rgb(128, 128, 128), Obj->x, Obj->y-20, 0);
    }
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y + 20 + Obj->height-30, ALLEGRO_ALIGN_CENTER, "Score: %d", Obj->score);
    al_draw_textf(Obj->font, text_color, Obj->x + Obj->width / 2, Obj->y - 40, ALLEGRO_ALIGN_CENTER, "Time: %d", Obj->countdown);
}

void Seeds_s_destory(Elements *self) 
{
    Seeds_s *obj = (Seeds_s *)(self->pDerivedObj);
    al_destroy_bitmap(obj->img);
    free(obj->hitbox);
    al_destroy_font(obj->font);
    al_destroy_timer(obj->timer);
    al_destroy_event_queue(obj->event_queue);
    free(obj);
    free(self);
}