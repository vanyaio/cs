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


    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = VK_RIGHT;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = VK_LEFT;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = VK_UP;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = VK_DOWN;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }

    if (GetAsyncKeyState(D_KEY) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = D_KEY;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
    if (GetAsyncKeyState(W_KEY) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = W_KEY;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
    if (GetAsyncKeyState(A_KEY) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = A_KEY;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
    if (GetAsyncKeyState(S_KEY) & 0x8000)
    {
        clock_t t1;
        t1 = clock();
        double diff = t1 - cd_set_t;
        double secs = diff / CLOCKS_PER_SEC;

        if (!cd_set || (secs > 0.1))
        {
            my_lvl->key_buff[cnt] = S_KEY;
            cnt++;

            cd_set = true;
            cd_set_t = clock();
        }
    }
}

