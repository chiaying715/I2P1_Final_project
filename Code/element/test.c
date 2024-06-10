#include "Test.h"
#include <stdio.h>
/*
   [Test function]
*/
Elements *New_Test(int label)
{
    Test *pDerivedObj = (Test *)malloc(sizeof(Test));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/success_farmer.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = WIDTH - pDerivedObj->width;
    pDerivedObj->y = HEIGHT + 20 - pDerivedObj->height;
    pDerivedObj->activate = false;
    // setting the interact object
    //pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Test_draw;
    pObj->Update = Test_update;
    pObj->Interact = Test_interact;
    pObj->Destroy = Test_destory;
    return pObj;
}

void Test_update(Elements *self) 
{
    Test *Obj = ((Test *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_INSERT])
    {
        Obj->activate = true;
        printf("activate\n");
    }
    else
    {
        Obj->activate = false;
    }
}
void Test_interact(Elements *self, Elements *tar)
{
    /*if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Test *Obj = (Test *)(self->pDerivedObj);
        if (chara->x >= Obj->x &&
            chara->x <= Obj->x + Obj->width &&
            Obj->activate)
        {
            Endgamescene_switch_trigger = 1;
            printf("!!\n");
        }
        
    }*/
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
void Test_draw(Elements *self)
{
    Test *Obj = ((Test *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Test_destory(Elements *self)
{
    Test *Obj = ((Test *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}