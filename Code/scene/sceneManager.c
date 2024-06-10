#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        printf("into gamescene\n");
        scene = New_GameScene(GameScene_L);
        break;
    default:
        break;
    }
}