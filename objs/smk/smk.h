#ifndef smk_h
#define smk_h

#include".\..\..\obj.h"
class smk;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class smk : public obj
{
public:
    clock_t cd_moving_t;
    bool cd_moving_b;
    double cd_moving;

    clock_t become_smk_t;
    double living_time;

    bool is_flying;

    int direction;

    hero* my_hero;

    smk();
    smk(int _x, int _y, lvl* _my_lvl, int _direction, hero* _my_hero);
    ~smk();

    void become_smk();
    void step();
    void init();
};
#endif
