#include"bullet.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"
#include<string>
bullet::bullet()
{
    /*
    std::string s = ".\\imgs\\wall.txt";
    skin = new img(s);
    erase_called = false;
    spawned = true;
    */
}
bullet::bullet(int _x, int _y)
{
    /*
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
    */
}
bullet::bullet(int _x, int _y, lvl* _my_lvl, int _direction, int _dmg, double _cd_moving)
{
    name = "bullet";
    depth = 10;
    std::string s = ".\\imgs\\bullet.txt";
    skin = new img(s);
    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;

    dmg = _dmg;
    cd_moving = _cd_moving;
    direction = _direction;

    erase_called = false;
    spawned = false;

    solid = true;
    invis = false;

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
bullet::bullet(int _x, int _y, lvl* _my_lvl, int _direction, int skill, hero* _my_hero)
{
    name = "bullet";
    depth = 100;
    std::string s = ".\\imgs\\bullet.txt";
    skin = new img(s);
    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;
    my_hero = _my_hero;

    direction = _direction;

    if (skill == AWP)
    {
        dmg = AWP_DMG;
        cd_moving = AWP_CD_MOVING;
    }
    if (skill == SGN)
    {
        dmg = SGN_DMG;
        cd_moving = SGN_CD_MOVING;
    }
    if (skill == ARF)
    {
        dmg = ARF_DMG;
        cd_moving = ARF_CD_MOVING;
    }
    if (skill == PST)
    {
        dmg = PST_DMG;
        cd_moving = PST_CD_MOVING;
    }

    erase_called = false;
    spawned = false;

    solid = false;
    invis = false;

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
bullet::~bullet()
{
    clear_position(this);
    delete skin;
}
void bullet::init()
{
    set<obj*> bord;
    scan_space(this, x_room, y_room, bord);
    bool solid_found = false;
    for (auto bord_obj : bord)
    {
        if (bord_obj->solid  && !bord_obj->erase_called)
            solid_found = true;
        if (bord_obj->name == "hero")
            static_cast<hero*>(bord_obj)->hp -= dmg;
    }
    if (solid_found)
        return;

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

};

void bullet::step()
{
    if (erase_called)
        return;

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
        {
            if (bord_obj->erase_called)
                continue;
            if (bord_obj->solid  && !bord_obj->erase_called)
                solid_found = true;
            if (bord_obj->name == "hero"){
                int _hp = static_cast<hero*>(bord_obj)->hp;
                static_cast<hero*>(bord_obj)->hp -= dmg;
                if (_hp > 0 && static_cast<hero*>(bord_obj)->hp <= 0)
                    my_hero->kills++;
            }
        }
        if (!solid_found)
        {
            clear_position(this);
            moving(new_x_room, new_y_room, this);

            cd_moving_b = true;
            cd_moving_t = clock();
        }
        else
            erase_called = true;
    }
}
