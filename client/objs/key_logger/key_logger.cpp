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
        my_lvl->key_buff[cnt] = VK_RIGHT;
        cnt++;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        my_lvl->key_buff[cnt] = VK_LEFT;

    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {

        my_lvl->key_buff[cnt] = VK_UP;
        cnt++;
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {

        my_lvl->key_buff[cnt] = VK_DOWN;
        cnt++;
    }

    if (GetAsyncKeyState(D_KEY) & 0x8000)
    {

        my_lvl->key_buff[cnt] = D_KEY;
        cnt++;

    }
    if (GetAsyncKeyState(W_KEY) & 0x8000)
    {

        my_lvl->key_buff[cnt] = W_KEY;
        cnt++;

    }
    if (GetAsyncKeyState(A_KEY) & 0x8000)
    {

        my_lvl->key_buff[cnt] = A_KEY;
        cnt++;

    }
    if (GetAsyncKeyState(S_KEY) & 0x8000)
    {

        my_lvl->key_buff[cnt] = S_KEY;
        cnt++;
    }


    if (GetAsyncKeyState(KEY_1) & 0x8000)
    {

        my_lvl->key_buff[cnt] = KEY_1;
        cnt++;
    }
    if (GetAsyncKeyState(KEY_2) & 0x8000)
    {

        my_lvl->key_buff[cnt] = KEY_2;
        cnt++;
    }
    if (GetAsyncKeyState(KEY_3) & 0x8000)
    {

        my_lvl->key_buff[cnt] = KEY_3;
        cnt++;
    }
    if (GetAsyncKeyState(KEY_4) & 0x8000)
    {

        my_lvl->key_buff[cnt] = KEY_4;
        cnt++;
    }
}

