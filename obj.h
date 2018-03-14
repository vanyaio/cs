#ifndef obj_h
#define obj_h

class obj;
#include "lvl.h"
#include "img.h"
#include "stl.h"
class obj
{
public:
    string name;

    lvl* my_lvl;
    img* skin;

    int x_room;
    int y_room;
    int x_img;
    int y_img;

    int depth;

    bool erase_called;
    bool spawned;

    virtual void step() = 0;
    virtual void init() = 0;
};
#endif // obj_h
