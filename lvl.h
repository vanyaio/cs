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
    map<user*, clock_t> breaking_time;
    double response_time;

    int* spawns_x;
    int* spawns_y;
    int spawns_sz;
    //
    int cnt;
    //
    virtual void update_terminal_lvl() = 0;
    virtual void step() = 0;
    virtual void load_map(std::string) = 0;
};
#endif // obj_h
