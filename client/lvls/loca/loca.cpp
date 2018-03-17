#include"loca.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"

loca::loca()
{
    x = full_screen_x;
    y = full_screen_y;
    first_enter = true;

    room = new list<obj*>*[x];
    for (int i = 0; i < x; i++)
        room[i] = new list<obj*>[y];

    obj* a = new key_logger(-1, -1, this);
    add_list.push_back(a);

    buffer = new pixel*[full_screen_x];
    for (int i = 0; i < full_screen_x; i++)
        buffer[i] = new pixel[y];
    for (int i = 0; i < full_screen_x; i++)
        for (int j = 0; j < full_screen_y; j++)
            buffer[i][j] = pixel(' ', 15);
    terminal = new pixel*[full_screen_x];
    for (int i = 0; i < full_screen_x; i++)
        terminal[i] = new pixel[y];
    for (int i = 0; i < full_screen_x; i++)
        for (int j = 0; j < full_screen_y; j++)
            terminal[i][j] = pixel(' ', 15);

    key_buff = new int[key_buff_sz];
    fill(key_buff, key_buff + key_buff_sz, 0);
    //
    cnt = 0;
}

loca::loca(int _x, int _y)
{
    x = _x;
    y = _y;
    first_enter = true;

    room = new list<obj*>*[x];
    for (int i = 0; i < x; i++)
        room[i] = new list<obj*>[y];

    buffer = new pixel*[full_screen_x];
    for (int i = 0; i < full_screen_x; i++)
        buffer[i] = new pixel[y];
    for (int i = 0; i < full_screen_x; i++)
        for (int j = 0; j < full_screen_y; j++)
            buffer[i][j] = pixel(' ', 15);
    terminal = new pixel*[full_screen_x];
    for (int i = 0; i < full_screen_x; i++)
        terminal[i] = new pixel[y];
    for (int i = 0; i < full_screen_x; i++)
        for (int j = 0; j < full_screen_y; j++)
            terminal[i][j] = pixel(' ', 15);

}
void loca::update_terminal_lvl(int* signs, int* colors, bool recv_flag)
{
    std::cout.flush();
    if (first_enter)
    {
        if (recv_flag)
        {
            for (int i = 0, cnt = 0; i < game_screen_x; i++)
                for (int j = 0; j < game_screen_y; j++, cnt++)
                    terminal[i][j] = pixel((char)signs[cnt], colors[cnt]);
        }
        for (auto my_obj : my_objs)
            update_terminal(my_obj);
        for (int i = 0; i < full_screen_x; i++)
            for (int j = 0; j < full_screen_y; j++)
                print(i, j, terminal[i][j]);
        first_enter = false;
        return;
    }

    if (recv_flag)
    {
        for (int i = 0, cnt = 0; i < game_screen_x; i++)
            for (int j = 0; j < game_screen_y; j++, cnt++)
                terminal[i][j] = pixel((char)signs[cnt], colors[cnt]);
    }

    for (auto my_obj : my_objs)
        if (my_obj->spawned && my_obj->ind != 1)
            update_terminal(my_obj);
    //
    bool check = false;
    //
    for (int i = 0; i < full_screen_x; i++)
        for (int j = 0; j < full_screen_y; j++)
        {
            if (buffer[i][j].color == terminal[i][j].color && buffer[i][j].sign == terminal[i][j].sign)
                continue;
            print(i, j, terminal[i][j]);
            if (!check)
            {
                cnt++;
                check = true;
            }
        }
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            buffer[i][j] = terminal[i][j];
    std::cout.flush();
}
void loca::step(int* signs, int* colors, bool recv_flag)
{
    update_terminal_lvl(signs, colors, recv_flag);

    for (auto my_obj : my_objs)
        my_obj->step();

    set<obj*> my_objs_erase_called;
    for (auto my_obj : my_objs)
        if (my_obj->erase_called)
            my_objs_erase_called.insert(my_obj);

    for (auto my_obj : my_objs_erase_called)
    {
        delete my_obj;
        my_objs.erase(my_obj);
    }

    for (auto new_obj : add_list)
        new_obj->init();
    add_list.clear();
}
