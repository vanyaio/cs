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

    clock_t cd_set_t;
    bool cd_set;
    hero();
    hero(int _x, int _y);
    hero(int _x, int _y, lvl* _my_lvl);

    void step();
    void init();
    bool key_pressed(int key);
};
#endif
