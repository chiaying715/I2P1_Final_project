#include "endgame.h"
// #include "element.h"
// #include "gamescene.h"
/*
   [EndGame function]
*/
Scene *New_EndGame(int label)
{
    EndGame *pDerivedObj = (EndGame *)malloc(sizeof(EndGame));
    Scene *pObj = New_Scene(label);
    /////////// added
    pDerivedObj->song = al_load_sample("assets/sound/endgame.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());

    al_play_sample_instance(pDerivedObj->sample_instance);
    if (al_get_sample_instance_playing(pDerivedObj->sample_instance )) 
    {
        printf("The sample instance is playing.\n");
    } 
    else 
    {
        printf("The sample instance is not playing.\n");
    }

    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    ///////////
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/endgame.jpg");
    if (!pDerivedObj->background) {
        printf("Failed to load background image!\n");
        fprintf(stderr, "Failed to load background image!\n");
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    pObj->pDerivedObj = pDerivedObj;
    // register element
    printf("before register butcher\n");
    Elements* tmp = New_Butcher(Butcher_L);
    if (tmp == NULL) printf("Null err\n"); 
    _Register_elements(pObj, tmp/*New_Butcher(Butcher_L)*/);
    // _Register_elements(pObj, New_Character(Character_L));
    // setting derived object function
    pObj->Update = end_game_update;
    pObj->Draw = end_game_draw;
    pObj->Destroy = end_game_destroy;
    return pObj;
}
void end_game_update(Scene *self)
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
    //endgame scene update: to exit
    /*
    BUTTTTTTTTT
    原本計畫是在遊戲進到end game scene 之後，按下tab鍵，可以exit
    但是我發現，我在遊戲進到end game scene 之後，按下tab鍵，會出現Assertion failed: format < ALLEGRO_NUM_PIXEL_FORMATS, file C:/dev/allegro_winpkg/universal/allegro/src/pixels.c, line 421然後就閃退了
    */
    
}
void end_game_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    EndGame *gs = ((EndGame *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void end_game_destroy(Scene *self)
{
    EndGame *Obj = ((EndGame *)(self->pDerivedObj));
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