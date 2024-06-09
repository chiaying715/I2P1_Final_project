#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "endgame.h"
#include "game_menu.h"
#include "success.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    /*case Game_Menu_L:
        scene = New_Game_Menu(Game_Menu_L);
        break;*/
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
        //need to add one more .c and .h to generate end game scene file
    case EndGame_L: 
        scene = New_EndGame(EndGame_L);
        break;
    case Success_L:
        scene = New_Success(Success_L);
        break;
    default:
        break;
    }
}