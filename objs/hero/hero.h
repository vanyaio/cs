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

    clock_t cd_awp_t;
    bool cd_awp_b;

    clock_t cd_sgn_t;
    bool cd_sgn_b;

    clock_t cd_arf_t;
    bool cd_arf_b;

    clock_t cd_pst_t;
    bool cd_pst_b;

    clock_t cd_grn_t;
    bool cd_grn_b;

    clock_t cd_grn_immune_t;
    bool cd_grn_immune_b;
    double cd_grn_immune;

    clock_t cd_hpu_t;
    bool cd_hpu_b;

    clock_t cd_spd_t;
    bool cd_spd_b;
    bool spd_on;

    int hp;

    int curr_skill;
    int* skills;

    hero();
    ~hero();
    hero(int _x, int _y);
    hero(int _x, int _y, lvl* _my_lvl);

    void step();
    void init();
    bool key_pressed(int key);
    void hero_moving(int new_x_room, int new_y_room);
    void skill_cast(int direction);
};
#endif
