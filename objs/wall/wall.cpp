#include"wall.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"
#include<string>
wall::wall()
{
    std::string s = ".\\imgs\\wall.txt";
    skin = new img(s);
    erase_called = false;
    spawned = true;
};
wall::wall(int _x, int _y)
{
    std::string s = ".\\imgs\\wall.txt";
    skin = new img(s);
    x_room = _x;
    y_room = _y;
    erase_called = false;
    spawned = true;
    cd_set = false;
    cd_set_t = clock();
    for (int i = 0; i < skin->x; i++)
        for (int j = 0; j < skin->y; j++)
        {
            pixel pixel_ij = skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;
            x_img = i;
            y_img = j;
            return;
        }
}
wall::wall(int _x, int _y, lvl* _my_lvl)
{
    name = "wall";
    depth = 0;
    std::string s = ".\\imgs\\wall.txt";
    skin = new img(s);
    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;

    erase_called = false;
    spawned = true;

    solid = true;
    invis = false;

    cd_set = false;
    cd_set_t = clock();

    for (int i = 0; i < skin->x; i++)
        for (int j = 0; j < skin->y; j++)
        {
            pixel pixel_ij = skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;
            x_img = i;
            y_img = j;
            return;
        }
}

void wall::init()
{
    int x0 = x_room - x_img;
    int y0 = y_room - y_img;
    for (int i = 0; i < skin->x; i++)
        for (int j = 0; j < skin->y; j++)
        {
            pixel pixel_ij = skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;

            my_lvl->room[i + x0][j + y0].push_back(this);
        }

    my_lvl->my_objs.insert(this);

};

void wall::step()
{
}
