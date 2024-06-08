#include "endgame.h"
#include "gamescene.h"
/*
   [EndGame function]
*/
Scene *New_EndGame(int label)
{
    EndGame *pDerivedObj = (EndGame *)malloc(sizeof(EndGame));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/endgame.jpg");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    _Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L));
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
    //game scene update: to switch to endgame scene
    if (Endgamescene_switch_trigger==1)
    {
        self->scene_end = true;
        window = 2;
        return; //要嗎?雖然我不知道return 完可以去哪裡QAQ
    }
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
    free(Obj);
    free(self);
}
