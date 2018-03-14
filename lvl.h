#ifndef lvl_h
#define lvl_h

class lvl;
#include "obj.h"
#include "img.h"
#include "stl.h"
using namespace std;

class lvl
{
public:
    int x;
    int y;

    list<obj*>** room;

    pixel** terminal;
    pixel** buffer;

    list<obj*> add_list;
    list<obj*> erase_list;

    set<obj*> my_objs;

    bool first_enter;

    virtual void update_terminal_lvl() = 0;
    virtual void step() = 0;
};
#endif // obj_h
