#include"bonus.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"
#include<string>
bonus::bonus()
{
}

bonus::bonus(int _x, int _y, lvl* _my_lvl, int skill)
{
    depth = 1000;
    name = "bonus";
    ind = skill;

    std::string s;
    if (skill == AWP)
        s = ".\\imgs\\awp.txt";
    if (skill == SGN)
        s = ".\\imgs\\sgn.txt";
    if (skill == PST)
        s = ".\\imgs\\pst.txt";
    if (skill == ARF)
        s = ".\\imgs\\arf.txt";

    skin = new img(s);
    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;

    erase_called = false;
    spawned = false;

    solid = false;
    invis = false;

    living_time = 1.0;

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

bonus::~bonus()
{
    clear_position(this);
    delete skin;
}

void bonus::init()
{
    spawned = true;
    living_begin = clock();
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

}

void bonus::step()
{
    clock_t t_now = clock();
    if (time_passed(living_begin, t_now) > living_time)
        erase_called = true;
}
