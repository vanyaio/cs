#include"hero.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"
#include<string>
hero::hero()
{
    std::string s = ".\\imgs\\hero.txt";
    skin = new img(s);
    erase_called = false;
    spawned = true;
};
hero::hero(int _x, int _y)
{
    std::string s = ".\\imgs\\hero.txt";
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
hero::hero(int _x, int _y, lvl* _my_lvl)
{
    depth = 10;
    name = "hero";
    std::string s = ".\\imgs\\hero.txt";
    skin = new img(s);
    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;

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

void hero::init()
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

void hero::step()
{
    clock_t t1;
    t1 = clock();

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.2))
        {
            set<obj*> bord;
            scan_space(this, x_room + 1, y_room, bord);
            for (auto bord_obj : bord)
                if (bord_obj->name == "wall")
                    bord_obj->erase_called = true;

            clear_position(this);
            moving(x_room + 1, y_room, this);

            cd_set = true;
            cd_set_t = clock();
        }
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.9))
        {
            my_lvl->add_list.push_back(new hero(4, 4, my_lvl));
            cd_set = true;
            cd_set_t = clock();
        }
    }
}
