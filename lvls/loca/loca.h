#ifndef loca_h
#define loca_h

#include".\..\..\lvl.h"
class loca;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class loca : public lvl
{
public:
clock_t cd_spawn_t;
bool cd_spawn_b;
double cd_spawn;

loca();
loca(int _x, int _y);
void step();
void update_terminal_lvl();
void load_map(std::string path);
void spawn_bonus();
};
#endif
