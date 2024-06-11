#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"

#include "endgame.h"
#include "success.h"
#include "about.h"

#include <stdio.h>
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        //printf("into gamescene\n");
        scene = New_GameScene(GameScene_L);
        break;
    case EndGame_L:
        scene = New_EndGame(EndGame_L);
        break;
    case Success_L:
        scene = New_Success(Success_L);
        break;
    case About_L:
        scene = New_About(About_L);
        break;
    default:
        break;
    }
}