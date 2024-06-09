#include <allegro5/allegro_primitives.h>
#include "endgame.h"
//#include "gamescene.h"
#include <stdbool.h>
#include "success.h"
#include "../GameWindow.h"

/*make
   [Test function]
*/
Scene *New_Success(int label)
{
    Success *pDerivedObj = (Success *)malloc(sizeof(Success));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->song = al_load_sample("assets/sound/success_goodnight.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->background = al_load_bitmap("assets/image/success.jpg");
    pObj->pDerivedObj = pDerivedObj;

    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    ///////////
    al_play_sample_instance(pDerivedObj->sample_instance);
    if (al_get_sample_instance_playing(pDerivedObj->sample_instance )) {
    printf("The sample instance is playing.\n");
} else {
    printf("The sample instance is not playing.\n");
}
    ///////////
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;


    // register element
    printf("New_Test1\n");
    _Register_elements(pObj, New_Test(Success_chara_L));
    
    // setting derived object function
    pObj->Update = Success_update;
    printf("New_Test3\n");
    pObj->Draw = Success_draw;
    printf("New_Test4\n");
    pObj->Destroy = Success_destroy;
    printf("New_Test5\n");
    return pObj;
}
void Success_update(Scene *self)
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
    if (key_state[ALLEGRO_KEY_ESCAPE])
    {
        self->scene_end = true;
        end_game_destroy(self);
        exit(0);
        return;
    }
    //Test scene update: to exit
    /*
    BUTTTTTTTTT
    原本計畫是在遊戲進到end game scene 之後，按下tab鍵，可以exit
    但是我發現，我在遊戲進到end game scene 之後，按下tab鍵，會出現Assertion failed: format < ALLEGRO_NUM_PIXEL_FORMATS, file C:/dev/allegro_winpkg/universal/allegro/src/pixels.c, line 421然後就閃退了
    
    
    if (key_state[ALLEGRO_KEY_TAB])//Exit_switch_trigger==1
    {
        self->scene_end = true;
        window = -1;
        printf("window-1\n");
        return; //要嗎?雖然我不知道return 完可以去哪裡QAQ
    }*/

}
void Success_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Success *gs = ((Success *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    //al_flip_display();
}
void Success_destroy(Scene *self)
{
    Success *Obj = ((Success *)(self->pDerivedObj));
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


/*
extern Game *game;
void End_Game()
{
    game_destroy(game);
    exit(0);
}
*/