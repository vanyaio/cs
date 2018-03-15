#ifndef  user_h
#define user_h

class user;
#include "lvl.h"
#include "obj.h"
#include "img.h"
#include "stl.h"
class user
{
public:
    obj* my_hero;
    SOCKET my_sock;
    int* key_buff;

    user();
    user(obj* _my_hero, SOCKET _my_sock);
    ~user();
};
#endif
