#ifndef wall_h
#define wall_h

#include".\..\..\obj.h"
class wall;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class wall : public obj
{
public:


    clock_t cd_set_t;
    bool cd_set;
    wall();
    wall(int _x, int _y);
    wall(int _x, int _y, lvl* _my_lvl);

    void step();
    void init();
};
#endif
