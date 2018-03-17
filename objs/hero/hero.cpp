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
    cd_moving_b = false;
    cd_moving_t = clock();
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

    cd_moving_b = false;
    cd_moving_t = clock();
    cd_moving = 0.1;

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

    //if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    if (key_pressed(VK_RIGHT))
        hero_moving(x_room + 1, y_room);
    if (key_pressed(VK_LEFT))
        hero_moving(x_room - 1, y_room);
    if (key_pressed(VK_DOWN))
        hero_moving(x_room, y_room + 1);
    if (key_pressed(VK_UP))
        hero_moving(x_room, y_room - 1);

    if (key_pressed(D_KEY))
        my_lvl->add_list.push_back(new bullet(x_room + 1, y_room, my_lvl, RIGHT, 1, 0.05));
    if (key_pressed(W_KEY))
        my_lvl->add_list.push_back(new bullet(x_room, y_room - 1, my_lvl, UP, 1, 0.05));
    if (key_pressed(S_KEY))
        my_lvl->add_list.push_back(new bullet(x_room, y_room + 1, my_lvl, DOWN, 1, 0.05));
    if (key_pressed(A_KEY))
        my_lvl->add_list.push_back(new bullet(x_room - 1, y_room, my_lvl, LEFT, 1, 0.05));
}

void hero::hero_moving(int new_x_room, int new_y_room)
{
    clock_t t_now;
    t_now = clock();

    double diff = t_now - cd_moving_t;
    double secs = diff / CLOCKS_PER_SEC;

    if (!cd_moving_b || (secs > cd_moving))
    {
        set<obj*> bord;
        scan_space(this, new_x_room, new_y_room, bord);
        bool solid_found = false;
        for (auto bord_obj : bord)
            if (bord_obj->solid)
                solid_found = true;
        if (!solid_found)
        {
            clear_position(this);
            moving(new_x_room, new_y_room, this);

            cd_moving_b = true;
            cd_moving_t = clock();
        }
    }
}

bool hero::key_pressed(int key)
{
    for (int i = 0; i < key_buff_sz; i++)
        if (key == my_user->key_buff[i])
            return true;
    return false;
}
