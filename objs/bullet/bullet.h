#ifndef bullet_h
#define bullet_h

#include".\..\..\obj.h"
class bullet;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class bullet : public obj
{
public:


    clock_t cd_moving_t;
    bool cd_moving_b;
    double cd_moving;

    int direction;
    int dmg;
    //DON'T FORGET ABOUT MY HERO

    bullet();
    bullet(int _x, int _y);
    bullet(int _x, int _y, lvl* _my_lvl, int _direction, int _dmg, double _cd_moving);
    bullet(int _x, int _y, lvl* _my_lvl, int _direction, int skill);
    ~bullet();
    void step();
    void init();
};
#endif
