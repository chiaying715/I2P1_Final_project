#include "butcher.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Butcher function]+
*/

Elements *New_Butcher(int label)
{
    printf("before malloc new butcher\n");
    Butcher *pDerivedObj = (Butcher *)malloc(sizeof(Butcher));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load Butcher images
    // char state_string[3][10] = {"1", "2", "3"};
    // for (int i = 0; i < 3; i++)
    // {
    //     char buffer[50];
    //     sprintf(buffer, "assets/image/butcher%s.gif", state_string[i]);
    //     pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    // }
    printf("before load butcher gif\n");
    pDerivedObj->gif_status[0] = algif_new_gif("assets/image/chara_farmer_re.gif", -1);
    // initial the geometric information of Butcher
    printf("before init butcher's geo info\n");
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    printf("before setting butcher's position\n");
    // pDerivedObj->x = 300;
    // pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->x = 335;
    pDerivedObj->y = 255;
    printf("before create new hitbox\n");
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    printf("before draw\n");
    // setting derived object function
    pObj->Draw = Butcher_draw;
    printf("before update\n");
    pObj->Update = Butcher_update;
    printf("before interact\n");
    pObj->Interact = Butcher_interact;
    printf("before destroy\n");
    pObj->Destroy = Butcher_destory;
    printf("before return\n");
    return pObj;
}

void Butcher_update(Elements *self)
{}

void Butcher_draw(Elements *self)
{
    // with the state, draw corresponding image
    Butcher *chara = ((Butcher *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }

}
void Butcher_destory(Elements *self)
{
    Butcher *Obj = ((Butcher *)(self->pDerivedObj));
    // for (int i = 0; i < 3; i++)
    //     algif_destroy_animation(Obj->gif_status[i]);
    algif_destroy_animation(Obj->gif_status[0]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Butcher_update_position(Elements *self, int dx, int dy)
{
    Butcher *chara = ((Butcher *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Butcher_interact(Elements *self, Elements *tar) {}