#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "endgame.h"
#include "game_menu.h"
#include "success.h"
#include "about.h"
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
        printf("Menu_L\n");
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        printf("GameScene_L\n");
        break;
        //need to add one more .c and .h to generate end game scene file
    case EndGame_L: 
        scene = New_EndGame(EndGame_L);
        printf("EndGame_L\n");
        break;
    case Success_L:
        scene = New_Success(Success_L);
        printf("Success_L\n");
        break;
    case About_L:
        scene = New_About(About_L);
        printf("About_L\n");
        break;
    default:
        break;
    }
}