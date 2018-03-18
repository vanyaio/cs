#include"loca.h"
#include".\..\..\vars.h"
#include".\..\..\scripts.h"

#include<fstream>
using namespace std;

loca::loca()
{
}

loca::loca(int _x, int _y)
{
    x = _x;
    y = _y;
    first_enter = true;

    room = new list<obj*>*[x];
    for (int i = 0; i < x; i++)
        room[i] = new list<obj*>[y];

    cd_spawn_b = false;
    cd_spawn = 2.0;

    add_list.push_back(new wall(40, 20, this));

    buffer = new pixel*[x];
    for (int i = 0; i < x; i++)
        buffer[i] = new pixel[y];
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            buffer[i][j] = pixel(' ', 15);
    terminal = new pixel*[x];
    for (int i = 0; i < x; i++)
        terminal[i] = new pixel[y];
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            terminal[i][j] = pixel(' ', 15);


    /*master = new socket(AF_INET,
                    SOCK_STREAM,
                    IPPROTO_TCP);*/
    master = socket(AF_INET,
                    SOCK_STREAM,
                    IPPROTO_TCP);

    set_nonblock(master);
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(12345);
    sock_addr.sin_addr.s_addr = 0;

    bind(master, (struct sockaddr*)(&sock_addr), sizeof(sock_addr));
    listen(master, 0x100);
    //
    cnt = 0;
}
void loca::update_terminal_lvl()
{
    std::cout.flush();

    if (first_enter)
    {
        for (auto my_obj : my_objs)
            update_terminal(my_obj);
        for (int i = 0; i < x; i++)
            for (int j = 0; j < y; j++)
                print(i, j, terminal[i][j]);
        first_enter = false;
        return;
    }

    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            terminal[i][j] = pixel(' ', 15);

    for (auto my_obj : my_objs)
        if (my_obj->spawned)
            update_terminal(my_obj);
    //
    bool flag = false;
    //
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
        {
            if (buffer[i][j].color == terminal[i][j].color && buffer[i][j].sign == terminal[i][j].sign)
                continue;
            print(i, j, terminal[i][j]);
            //
            if (!flag)
            {
                cnt++;
                flag = true;
            }
        }
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            buffer[i][j] = terminal[i][j];
    std::cout.flush();
}

void smart_delete(obj* _obj)
{
    obj* new_obj;
    if (_obj->name == "hero")
        new_obj = static_cast<hero*>(_obj);
    if (_obj->name == "wall")
        new_obj = static_cast<wall*>(_obj);
    if (_obj->name == "bullet")
        new_obj = static_cast<bullet*>(_obj);
    delete new_obj;
}
void loca::step()
{
    //
    string path = "kek";
    //
    if (first_enter)
        load_map(path);

    update_terminal_lvl();

    for (auto my_obj : my_objs)
        my_obj->step();

    set<obj*> my_objs_erase_called;
    for (auto my_obj : my_objs)
        if (my_obj->erase_called)
            my_objs_erase_called.insert(my_obj);

    for (auto my_obj : my_objs_erase_called)
    {
        if (my_obj->name == "hero")
            delete static_cast<hero*>(my_obj);
        if (my_obj->name == "wall")
            delete static_cast<wall*>(my_obj);
        if (my_obj->name == "bullet")
            delete static_cast<bullet*>(my_obj);
        if (my_obj->name == "bonus")
            delete static_cast<bonus*>(my_obj);
        my_objs.erase(my_obj);
    }
    if (!cd_spawn_b || (time_passed(cd_spawn_t, clock()) > cd_spawn)){
        spawn_bonus();
        cd_spawn_b = true;
        cd_spawn_t = clock();
    }

    for (auto new_obj : add_list)
        new_obj->init();
    add_list.clear();

    network_step(this);
}

void loca::load_map(string path)
{
    spawns_sz = 2;
    spawns_x = new int[2];
    spawns_y = new int[2];
    spawns_x[0] = 3;
    spawns_x[1] = 25;
    spawns_y[0] = 10;
    spawns_y[1] = 10;
}
void loca::spawn_bonus()
{
    int _x, _y;
    set_spawn(_x, _y, this);
    add_list.push_back(new bonus(_x, _y, this, ARF));
}
