#include"user.h"

user::user(){}
user::user(obj* _my_hero, SOCKET _my_sock)
{
    my_hero = _my_hero;
    my_sock = _my_sock;
    key_buff = new int[key_buff_sz];
}
user::~user()
{
}
