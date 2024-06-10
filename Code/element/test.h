#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#include "element.h"
//#include "charater.h" 是因為trap原本有要跟charater互動
#include "../scene/success.h" // for element label
/*
   [Test object]
*/
typedef struct _Test
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    bool activate;
} Test;

Elements *New_Test(int label);
void _Test_load_map(Test *Test);
void Test_update(Elements *self);
void Test_interact(Elements *self, Elements *tar);
void Test_draw(Elements *self);
void Test_destory(Elements *self);

#endif