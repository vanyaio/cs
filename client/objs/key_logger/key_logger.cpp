#include"key_logger.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"
#include<string>
key_logger::key_logger()
{
}
key_logger::key_logger(int _x, int _y)
{
}
key_logger::key_logger(int _x, int _y, lvl* _my_lvl)
{
    name = "key_logger";
    ind = 1;
    x_room = _x;
    y_room = _y;
    my_lvl = _my_lvl;

    erase_called = false;
    spawned = true;

    cd_set = false;
    cd_set_t = clock();
}

void key_logger::init()
{
    my_lvl->my_objs.insert(this);
}

void key_logger::step()
{
    fill(my_lvl->key_buff, my_lvl->key_buff + key_buff_sz, 0);
    int cnt = 0;

    clock_t t1;
    t1 = clock();

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.2))
        {
            my_lvl->key_buff[cnt] = VK_RIGHT;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
    /*
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.9))
        {
            my_lvl->add_list.push_back(new hero(4, 4, my_lvl));
            cd_set = true;
            cd_set_t = clock();
        }
    }
    */
}

