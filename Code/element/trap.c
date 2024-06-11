#include "Trap.h"
#include <stdio.h>
/*
   [Trap function]
*/
Elements *New_Trap(int label)
{
    Trap *pDerivedObj = (Trap *)malloc(sizeof(Trap));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/trap2.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Trap_load_map(pDerivedObj);
    pDerivedObj->x = WIDTH - pDerivedObj->width;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Trap_draw;
    pObj->Update = Trap_update;
    pObj->Interact = Trap_interact;
    pObj->Destroy = Trap_destory;
    return pObj;
}
void _Trap_load_map(Trap *Trap)
{
    FILE *data;
    data = fopen("assets/map/gamescene_trap_map.txt", "r");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fscanf(data, "%d", &Trap->map_data[i][j]);
        }
    }
    fclose(data);
}
void Trap_update(Elements *self) 
{
    Trap *Obj = ((Trap *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_X])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
    //printf("activate: %d\n", Obj->activate);
}
void Trap_interact(Elements *self, Elements *tar)
{
    //added
    
    if (tot_score >= 5)
    {
        //printf("Success!\n");
        Success_switch_trigger = 1;
    }
    
    ////////////////////
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Trap *Obj = (Trap *)(self->pDerivedObj);
        //printf("chara->x=%d, Obj=%d, %d\n", chara->x, 65 + Obj->x - Obj->width, Obj->x + Obj->width);
        // if ((chara->x >= 65 + Obj->x - Obj->width)&&
        //     (chara->x <= Obj->x + Obj->width)&&(chara->y >= HEIGHT - Obj->height - 150))
        if ((chara->x >= -25 + Obj->x - Obj->width)&&
            (chara->x <= Obj->x + Obj->width))
        {
            Endgamescene_switch_trigger = 1;
            //printf("!!\n");
        }
        /*if (chara->x >= Obj->x &&
            chara->x <= Obj->x + Obj->width &&
            Obj->activate)
        {
            Endgamescene_switch_trigger = 1;
            printf("!!\n");
        }*/
        
    }
    /*
    if (tar->label == Character_L)
    {*/
        ////
        
        ////
        /*Character *chara = (Character *)(tar->pDerivedObj);*/
        /*int right_limit = WIDTH - chara->width / 2;
        int left_limit = 0 - chara->width / 2;
        if (chara->x < left_limit)
        {
            _Character_update_position(tar, (left_limit - chara->x), 0);
        }
        else if (chara->x > right_limit)
        {
            _Character_update_position(tar, (right_limit - chara->x), 0);
        }*/
    //}
}
void Trap_draw(Elements *self)
{
    Trap *Obj = ((Trap *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    
    /*Trap *Obj = ((Trap *)(self->pDerivedObj));
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (Obj->map_data[i][j])
            {
                al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
            }
        }
    }*/
}
void Trap_destory(Elements *self)
{
    Trap *Obj = ((Trap *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}