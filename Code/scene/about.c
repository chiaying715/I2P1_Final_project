#include <allegro5/allegro_primitives.h>
#include "about.h"
#include <stdbool.h>
/*
   [About function]
*/
Scene *New_About(int label)
{
    About *pDerivedObj = (About *)malloc(sizeof(About));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/About.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());

    ///////////
    al_play_sample_instance(pDerivedObj->sample_instance);
    if (al_get_sample_instance_playing(pDerivedObj->sample_instance )) {
    //printf("The sample instance is playing.\n");
} else {
    //printf("The sample instance is not playing.\n");
}
    ///////////
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;

    // setting derived object function
    pDerivedObj->background = al_load_bitmap("assets/image/about.png");
    ///////////////////////
    // setting derived object function
    pObj->Update = About_update;
    pObj->Draw = About_draw;
    pObj->Destroy = About_destroy;
    return pObj;
}
void About_update(Scene *self)
{
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    if (key_state[ALLEGRO_KEY_BACKSPACE])
    {
        self->scene_end = true;
        window = 0; //MENU
    }
    else if (key_state[ALLEGRO_KEY_ESCAPE])
    {
        self->scene_end = true;
        window = -1; //exit
        About_destroy(self);
        exit(0);
    }
    //return;
}
void About_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    About *gs = ((About *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void About_destroy(Scene *self)
{
    About *Obj = ((About *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}