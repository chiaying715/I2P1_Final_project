#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "seeds_s.h"
#include "seeds_c.h"
#include "seeds_e.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // load effective sound for plt. by lintzoe
    ALLEGRO_SAMPLE *sample2 = al_load_sample("assets/sound/plt_sound.mp3");
    pDerivedObj->plt_Sound = al_create_sample_instance(sample2);
    al_set_sample_instance_playmode(pDerivedObj->plt_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->plt_Sound, al_get_default_mixer());

    // load effective sound for walk. by lintzoe
    ALLEGRO_SAMPLE *sample3 = al_load_sample("assets/sound/wlk_sound.mp3");
    pDerivedObj->wlk_Sound = al_create_sample_instance(sample3);
    al_set_sample_instance_playmode(pDerivedObj->wlk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->wlk_Sound, al_get_default_mixer());

    // load effective sound for walk. by lintzoe
    ALLEGRO_SAMPLE *sample4 = al_load_sample("assets/sound/up_sound.mp3");
    pDerivedObj->up_Sound = al_create_sample_instance(sample4);
    al_set_sample_instance_playmode(pDerivedObj->up_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->up_Sound, al_get_default_mixer());

    ALLEGRO_SAMPLE *sample5 = al_load_sample("assets/sound/hvst_sound.mp3");
    pDerivedObj->hvst_Sound = al_create_sample_instance(sample5);
    al_set_sample_instance_playmode(pDerivedObj->hvst_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->hvst_Sound, al_get_default_mixer());

    ALLEGRO_SAMPLE *sample6 = al_load_sample("assets/sound/watering_sound.mp3");
    pDerivedObj->watering_Sound = al_create_sample_instance(sample6);
    al_set_sample_instance_playmode(pDerivedObj->watering_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->watering_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(self->pDerivedObj));
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        //press z to plant a seed(using a tree pic for now). by lintzoe
        else if (key_state[ALLEGRO_KEY_1])
        {
            Elements *pro;
            pro = New_Seeds_s(Seeds_s_L, chara->x, chara->y);
            _Register_elements(scene, pro);
            //chara->new_proj = true;
            //chara->state = STOP;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_2])
        {
            Elements *pro;
            pro = New_Seeds_c(Seeds_c_L, chara->x, chara->y);
            _Register_elements(scene, pro);
            //chara->new_proj = true;
            //chara->state = STOP;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_3])
        {
            Elements *pro;
            pro = New_Seeds_e(Seeds_e_L, chara->x, chara->y);
            _Register_elements(scene, pro);
            //chara->new_proj = true;
            //chara->state = STOP;
            chara->state = MOVE;
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Character_update_position(self, -5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Character_update_position(self, 5, 0);
            chara->state = MOVE;
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
    else if (chara->state == ATK)
    {
        printf("new_pro: %d\n", chara->new_proj);
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
            if (chara->dir)
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y + 10,
                                     5);
            }
            else
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x - 50,
                                     chara->y + 10,
                                     -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
    //added this status to plant. by lintzoe
    /*else if(chara->state == PLANT)
    {   
        //printf("plant new_pro: %d\n", chara->new_proj);
        Elements *pro;
    //try to put a seed on (50,50). by lintzoe
            //pro = New_Seeds_s(Seeds_s_L, 50, 50);
            //try to put a seed on where the character is. by lintzoe
            pro = New_Seeds_s(Seeds_s_L, chara->x, chara->y);
            _Register_elements(scene, pro);
            //chara->new_proj = true;
            if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }*/
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
    if(key_state[ALLEGRO_KEY_1]||key_state[ALLEGRO_KEY_2]||key_state[ALLEGRO_KEY_3])
    {
        al_play_sample_instance(chara->plt_Sound);
    }
    if(key_state[ALLEGRO_KEY_A]||key_state[ALLEGRO_KEY_D])
    {
        al_play_sample_instance(chara->wlk_Sound);
    }
    if(key_state[ALLEGRO_KEY_H])
    {
        al_play_sample_instance(chara->hvst_Sound);
    }
    if(key_state[ALLEGRO_KEY_F])
    {
        al_play_sample_instance(chara->watering_Sound);
    }
    if(key_state[ALLEGRO_KEY_S])
    {
        al_play_sample_instance(chara->up_Sound);
    }
}
void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *self, Elements *tar) {}
