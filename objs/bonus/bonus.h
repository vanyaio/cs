#ifndef bonus_h
#define bonus_h

#include".\..\..\obj.h"
class bullet;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class bonus : public obj
{
public:
    double living_time;
    clock_t living_begin;

    bonus();
    bonus(int _x, int _y, lvl* _my_lvl, int skill);
    ~bonus();

    void step();
    void init();
};
#endif
