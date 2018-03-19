#ifndef grn_h
#define grn_h

#include".\..\..\obj.h"
class grn;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class grn : public obj
{
public:
    clock_t cd_moving_t;
    bool cd_moving_b;
    double cd_moving;

    clock_t become_burst_t;
    double living_time;

    bool is_flying;

    int direction;

    int dmg;

    hero* my_hero;

    grn();
    grn(int _x, int _y, lvl* _my_lvl, int _direction, hero* _my_hero);
    ~grn();

    void become_burst();
    void step();
    void init();
};
#endif
