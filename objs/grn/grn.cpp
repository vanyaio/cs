#include"grn.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"
#include<string>
grn::grn()
{
}

grn::grn(int _x, int _y, lvl* _my_lvl, int _direction, hero* _my_hero)
{
    depth = 10;
    name = "grn";

    std::string s;
    s = ".\\imgs\\grn.txt";
    skin = new img(s);

    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;
    my_hero = _my_hero;
    direction = _direction;

    erase_called = false;
    spawned = false;

    solid = false;
    invis = false;

    dmg = 10;

    living_time = 1.0;
    cd_moving = 0.3;
    cd_moving_b = false;
    is_flying = true;

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

grn::~grn()
{
    clear_position(this);
    delete skin;
}

void grn::init()
{
    set<obj*> bord;
    scan_space(this, x_room, y_room, bord);
    bool solid_found = false;
    for (auto bord_obj : bord)
        if (bord_obj->solid  && !bord_obj->erase_called)
            solid_found = true;
    if (solid_found)
    {
        my_lvl->my_objs.insert(this);
        become_burst();
        return;
    }

    spawned = true;
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

void grn::become_burst()
{
    if (spawned)
        clear_position(this);
    delete skin;
    std::string s;
    s = ".\\imgs\\burst.txt";
    skin = new img(s);

    for (int i = 0; i < skin->x; i++)
        for (int j = 0; j < skin->y; j++)
        {
            pixel pixel_ij = skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;
            x_img = i;
            y_img = j;
            break;
        }

    solid = false;
    is_flying = false;
    spawned = true;

    become_burst_t = clock();

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
}

void grn::step()
{
    if (erase_called)
        return;

    if (!is_flying)
    {
        if (time_passed(become_burst_t, clock()) > living_time)
            erase_called = true;
        return;
    }

    int new_x_room, new_y_room;
    if (direction == UP)
    {
        new_x_room = x_room;
        new_y_room = y_room - 1;
    }
    if (direction == RIGHT)
    {
        new_x_room = x_room + 1;
        new_y_room = y_room;
    }
    if (direction == DOWN)
    {
        new_x_room = x_room;
        new_y_room = y_room + 1;
    }
    if (direction == LEFT)
    {
        new_x_room = x_room - 1;
        new_y_room = y_room;
    }

    if (my_hero != nullptr && my_hero->key_pressed(VK_SPACE))
    {
        become_burst();
        return;
    }

    if (!cd_moving_b || (time_passed(cd_moving_t, clock()) > cd_moving))
    {
        set<obj*> bord;
        scan_space(this, new_x_room, new_y_room, bord);
        bool solid_found = false;
        for (auto bord_obj : bord)
            if (bord_obj->solid  && !bord_obj->erase_called)
                solid_found = true;

        if (!solid_found)
        {
            clear_position(this);
            moving(new_x_room, new_y_room, this);

            cd_moving_b = true;
            cd_moving_t = clock();
        }
        else
            become_burst();
    }
}
