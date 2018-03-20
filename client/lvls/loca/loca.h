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
int* skills_buff;
int* kdh_buff;

loca();
loca(int _x, int _y);
void step(int* signs, int* colors, int* skills, int* kdh, bool recv_flag);
void update_terminal_lvl(int* signs, int* colors, int* skills, int* kdh, bool recv_flag);
};
#endif
