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
    pDerivedObj->img = al_load_bitmap("assets/image/trap.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Trap_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
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
    data = fopen("assets/map/gamescene_map.txt", "r");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fscanf(data, "%d", &Trap->map_data[i][j]);
        }
    }
    fclose(data);
}
void Trap_update(Elements *ele) {}
void Trap_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        int right_limit = WIDTH - chara->width / 2;
        int left_limit = 0 - chara->width / 2;
        if (chara->x < left_limit)
        {
            _Character_update_position(tar, (left_limit - chara->x), 0);
        }
        else if (chara->x > right_limit)
        {
            _Character_update_position(tar, (right_limit - chara->x), 0);
        }
    }
}
void Trap_draw(Elements *self)
{
    Trap *Obj = ((Trap *)(self->pDerivedObj));
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (Obj->map_data[i][j])
            {
                al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
            }
        }
    }
}
void Trap_destory(Elements *self)
{
    Trap *Obj = ((Trap *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
