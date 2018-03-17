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

    skills = new int[skills_sz];
    fill(skills, skills + skills_sz, 0);
    skills[PST] = INT_MAX;
    curr_skill = PST;

    cd_awp_b = false;
    cd_sgn_b = false;
    cd_arf_b = false;
    cd_pst_b = false;
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

void hero::skill_cast(int direction)
{
    int x_dir = x_room, y_dir = y_room;
    if (direction == UP)
        y_dir--;
    if (direction == DOWN)
        y_dir++;
    if (direction == LEFT)
        x_dir--;
    if (direction == RIGHT)
        x_dir++;

    //DON'T FORGET ABOUT AMMO!!!
    if (curr_skill == AWP && (!cd_awp_b || (time_passed(cd_awp_t, clock()) > AWP_CD)))
    {
        my_lvl->add_list.push_back(new bullet(x_dir, y_dir, my_lvl, direction, curr_skill));
        cd_awp_b = true;
        cd_awp_t = clock();
    }
    if (curr_skill == PST && (!cd_pst_b || (time_passed(cd_pst_t, clock()) > PST_CD))){
        my_lvl->add_list.push_back(new bullet(x_dir, y_dir, my_lvl, direction, curr_skill));
        cd_pst_t = clock();
    }
    if (curr_skill == SGN && (!cd_sgn_b || (time_passed(cd_sgn_t, clock()) > SGN_CD))){
        my_lvl->add_list.push_back(new bullet(x_dir, y_dir, my_lvl, direction, curr_skill));
        cd_sgn_t = clock();
    }
    if (curr_skill == ARF && (!cd_arf_b || (time_passed(cd_arf_t, clock()) > ARF_CD))){
        my_lvl->add_list.push_back(new bullet(x_dir, y_dir, my_lvl, direction, curr_skill));
        cd_arf_t = clock();
    }
}
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
        skill_cast(RIGHT);
    if (key_pressed(W_KEY))
        skill_cast(UP);
    if (key_pressed(S_KEY))
        skill_cast(DOWN);
    if (key_pressed(A_KEY))
        skill_cast(LEFT);

    if (key_pressed(KEY_1))
        curr_skill = AWP;
    if (key_pressed(KEY_2))
        curr_skill = SGN;
    if (key_pressed(KEY_3))
        curr_skill = ARF;
    if (key_pressed(KEY_4))
        curr_skill = PST;

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
