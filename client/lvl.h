#ifndef lvl_h
#define lvl_h

class lvl;
#include "obj.h"
#include "user.h"
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

    SOCKET master;
    set<user*> connections;

    int* key_buff;

    virtual void update_terminal_lvl(int* signs, int* colors, bool recv_flag) = 0;
    virtual void step(int* signs, int* colors, bool recv_flag) = 0;
};
#endif // obj_h
