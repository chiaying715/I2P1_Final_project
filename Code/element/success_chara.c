#include "success_chara.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/
Elements *New_Success_Character(int label)
{
    
    Success_Character *pDerivedObj = (Success_Character *)malloc(sizeof(Success_Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[5][10] = {"dancing", "dancing", "dancing", "dancing", "dancing"};
    
    for (int i = 0; i < 5; i++)
    {
        char buffer[60];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    
    //initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = HEIGHT - pDerivedObj->height ;//- 60;
    //printf("h:%d objecth:%d\n", HEIGHT, pDerivedObj->height);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);


    pObj->pDerivedObj = pDerivedObj;
    
    // setting derived object function
    pObj->Draw = Success_Character_draw;
    pObj->Update = Success_Character_update;
    pObj->Interact = Success_Character_interact;
    pObj->Destroy = Success_Character_destory;
    return pObj;
}
void Success_Character_update(Elements *self){}
void Success_Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Success_Character *chara = ((Success_Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[0], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, 0);
    }
    
}
void Success_Character_destory(Elements *self)
{
    Success_Character *Obj = ((Success_Character *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
    
}

void _Success_Character_update_position(Elements *self, int dx, int dy){}

void Success_Character_interact(Elements *self, Elements *tar) {}