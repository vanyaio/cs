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

    skills_buff = new int[skills_sz];
    fill(skills_buff, skills_buff + skills_sz, -1);
    kdh_buff = new int[3];
    fill(kdh_buff, kdh_buff + 3, -1);
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

    skills_buff = new int[skills_sz];
    fill(skills_buff, skills_buff + skills_sz, 0);
    kdh_buff = new int[3];
    fill(kdh_buff, kdh_buff + 3, 0);
}
void loca::update_terminal_lvl(int* signs, int* colors, int* skills, int* kdh, bool recv_flag)
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

        string s;
        s = "HAS";
        print(game_screen_x, 0, s);
        s = "1.AWP";
        print(game_screen_x, 1, s);
        s = "2.SGN";
        print(game_screen_x, 2, s);
        s = "3.ARF";
        print(game_screen_x, 3, s);
        s = "4.PST";
        print(game_screen_x, 4, s);
        s = "5.GRN";
        print(game_screen_x, 5, s);
        s = "6.SMK";
        print(game_screen_x, 6, s);
        s = "7.HPU";
        print(game_screen_x, 7, s);
        s = "8.SPD";
        print(game_screen_x, 8, s);

        s = "KILLS";
        print(0, game_screen_y, s);
        s = "DEATHS";
        print(0, game_screen_y + 1, s);
        s = "HP";
        print(0, game_screen_y + 2, s);

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
            //
            /*
            if (!check)
            {
                cnt++;
                check = true;
            }
            */
        }
    if (recv_flag){
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            buffer[i][j] = terminal[i][j];
    }
    if (recv_flag)
    {
        for (int i = 0; i < skills_sz; i++)
            if (skills_buff[i] != skills[i])
            {
                string s = "             ";
                print(game_screen_x + 8, i, s);
                print(game_screen_x + 8, i, skills[i]);
                skills_buff[i] = skills[i];
            }
        for (int i = 0; i < 3; i++)
            if (kdh_buff[i] != kdh[i])
            {
                string s = "              ";
                print(7, game_screen_y + i, s);
                print(7, game_screen_y + i, kdh[i]);
                kdh_buff[i] = kdh[i];
            }
    }

    std::cout.flush();
}

void loca::step(int* signs, int* colors, int* skills, int* kdh, bool recv_flag)
{
    update_terminal_lvl(signs, colors, skills, kdh, recv_flag);

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
