#include"smk.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"
#include<string>
smk::smk()
{
}

smk::smk(int _x, int _y, lvl* _my_lvl, int _direction, hero* _my_hero)
{
    depth = 2;
    name = "smk";

    std::string s;
    s = ".\\imgs\\smk_grn.txt";
    skin = new img(s);

    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;
    my_hero = _my_hero;
    direction = _direction;

    erase_called = false;
    spawned = false;

    solid = true;
    invis = false;

    living_time = 6.0;
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

smk::~smk()
{
    clear_position(this);
    delete skin;
}

void smk::init()
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
        become_smk();
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

void smk::become_smk()
{
    if (spawned)
        clear_position(this);
    delete skin;
    std::string s;
    s = ".\\imgs\\smk.txt";
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

    become_smk_t = clock();

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

void smk::step()
{
    if (erase_called)
        return;

    if (!is_flying)
    {
        if (time_passed(become_smk_t, clock()) > living_time)
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
        become_smk();
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
            become_smk();
    }
}
