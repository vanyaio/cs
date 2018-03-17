#ifndef hero_h
#define hero_h

#include".\..\..\obj.h"
class hero;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class hero : public obj
{
public:
    user* my_user;

    clock_t cd_moving_t;
    bool cd_moving_b;
    double cd_moving;

    int hp;

    hero();
    hero(int _x, int _y);
    hero(int _x, int _y, lvl* _my_lvl);

    void step();
    void init();
    bool key_pressed(int key);
    void hero_moving(int new_x_room, int new_y_room);
};
#endif
