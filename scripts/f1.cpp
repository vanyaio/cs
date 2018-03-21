#include"f1.h"
#include".\..\vars.h"
#include".\..\scripts.h"
void print(int x, int y, img& _img)
{
    COORD c1;
    c1.X = x;
    c1.Y = y;

    SetConsoleCursorPosition(hConsole, c1);
    SetConsoleTextAttribute(hConsole, _img.arr[0][0].color);
    std::cout << _img.arr[0][0].sign;
}
void print(int x, int y, pixel& _img)
{
    COORD c1;
    c1.X = x;
    c1.Y = y;

    SetConsoleCursorPosition(hConsole, c1);
    SetConsoleTextAttribute(hConsole, _img.color);
    std::cout << _img.sign;
}

void clear_position(obj* _this)
{
    int x0 = _this->x_room - _this->x_img;
    int y0 = _this->y_room - _this->y_img;
    for (int i = 0; i < _this->skin->x; i++)
        for (int j = 0; j < _this->skin->y; j++)
        {
            pixel pixel_ij = _this->skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;

            list<obj*>::iterator it = _this->my_lvl->room[i + x0][j + y0].begin();
            while (*it != _this)
                it++;

            _this->my_lvl->room[i + x0][j + y0].erase(it);
        }
}

void moving(int new_x_room, int new_y_room, obj* _this)
{
    int new_x0 = new_x_room - _this->x_img;
    int new_y0 = new_y_room - _this->y_img;
    for (int i = 0; i < _this->skin->x; i++)
        for (int j = 0; j < _this->skin->y; j++)
        {
            pixel pixel_ij = _this->skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;

            _this->my_lvl->room[i + new_x0][j + new_y0].push_back(_this);
        }
    _this->x_room = new_x_room;
    _this->y_room = new_y_room;
}

void update_terminal(obj* _this)
{
    int x0 = _this->x_room - _this->x_img;
    int y0 = _this->y_room - _this->y_img;
    for (int i = 0; i < _this->skin->x; i++)
        for (int j = 0; j < _this->skin->y; j++)
        {
            pixel pixel_ij = _this->skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;

            bool draw_flag = true;
            for (auto obj_on_cell : _this->my_lvl->room[i + x0][j + y0])
                if (obj_on_cell->depth < _this->depth)
                    draw_flag = false;

            if (draw_flag)
                _this->my_lvl->terminal[i + x0][j + y0] = pixel(pixel_ij.sign, pixel_ij.color);
        }
}

void scan_space(int x0, int y0, int x1, int y1, set<obj*>& objs, lvl* _lvl)
{
    for (int i = x0; i <= x1; i++)
        for (int j = y0; j <= y1; j++)
            for (auto obj_in_cell : _lvl->room[i][j])
                objs.insert(obj_in_cell);
}

void scan_space(obj* _this, int x1, int y1, set<obj*>& objs)
{
    int x0 = x1 - _this->x_img;
    int y0 = y1 - _this->y_img;
    for (int i = 0; i < _this->skin->x; i++)
        for (int j = 0; j < _this->skin->y; j++)
        {
            pixel pixel_ij = _this->skin->arr[i][j];
            if ((pixel_ij.sign == ' ') && (pixel_ij.color == 15))
                continue;

            for (auto obj_in_cell : _this->my_lvl->room[i + x0][j + y0])
                objs.insert(obj_in_cell);
        }
}

int set_nonblock(SOCKET fd)
{
    u_long flags;
#if defined(O_NONBLOCK)
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctlsocket(fd, FIONBIO, &flags);
#endif
}

int rand_num(int mx)
{
    return (rand() % mx);
}
void set_spawn(int& _x, int& _y, lvl* _this)
{
    set<int> free_spawns;
    int cnt = 0;
    for (int i = 0; i < _this->spawns_sz; i++)
        if (_this->room[_this->spawns_x[i]][_this->spawns_y[i]].empty())
        {
            free_spawns.insert(i);
            cnt++;
        }

    int ret = rand_num(cnt);
    cnt = 0;
    for (auto it : free_spawns)
    {
        if (cnt == ret)
        {
            _x = _this->spawns_x[it];
            _y = _this->spawns_y[it];
            return;
        }
        cnt++;
    }

    if (cnt == 0)
    {
        _x = -1;
        _y = -1;
    }
}

void my_send(SOCKET sock, int* arr, int sz, lvl* _this)
{
    clock_t came_t = clock();

    int send1 = 0;
    int cnt = 0;
    while (send1 != sz * sizeof(int))
    {
        int _int[1];
        _int[0] = arr[cnt];
        int _send = 0;
        int _cnt = 0;
        while (_send != (sizeof(int)))
        {
            int _send1 = send(sock, (((char*)_int) + _cnt), 1, 0);
            if (_send1 == 1)
            {
                _cnt++;
                _send += _send1;
            }

            if (time_passed(came_t, clock()) > _this->response_time)
                throw true;
        }
        cnt++;
        send1 += _send;
    }
}
void my_recv(SOCKET sock, int* arr, int sz, lvl* _this)
{
    clock_t came_t = clock();

    int recv1 = 0;
    int cnt = 0;
    while (recv1 != sz * sizeof(int))
    {
        int _int[1];
        int _recv = 0;
        int _cnt = 0;
        while (_recv != sizeof(int))
        {
            int _recv1 = recv(sock, (char*)_int + _cnt, 1, 0);
            if (_recv1 == 1)
            {
                _cnt++;
                _recv += _recv1;
            }

            if (time_passed(came_t, clock()) > _this->response_time)
                throw true;
        }
        arr[cnt] = _int[0];
        cnt++;
        recv1 += _recv;

    }
}
void network_step(lvl* _this)
{
    SOCKET slave = accept((_this->master), 0, 0);
    if (slave != -1)
    {
        int x_spawn, y_spawn;
        set_spawn(x_spawn, y_spawn, _this);

        obj* new_hero = new hero(x_spawn, y_spawn, _this);
        _this->add_list.push_back(new_hero);

        user* new_user = new user(new_hero, slave);
        _this->connections.insert(new_user);

        (static_cast<hero*>(new_hero))->my_user = new_user;

        _this->breaking_time[new_user] = 0;
    }
    set<user*> to_erase;
    bool send_happened = false;
    for (auto _user : _this->connections)
    {
        try
        {
            my_recv(_user->my_sock, _user->key_buff, key_buff_sz, _this);
            for (int i = 0 ; i < key_buff_sz; ++i)
                _user->key_buff[i] = ntohl(_user->key_buff[i]);


            send_happened = true;

            int signs[game_screen_x * game_screen_y];
            int colors[game_screen_x * game_screen_y];
            obj* now_obj = _user->my_hero;

            for (int i = now_obj->x_room - (game_screen_x/2), cnt = 0; i <= (now_obj->x_room + (game_screen_x/2)); i++)
                for (int j = now_obj->y_room - (game_screen_y/2); j <= (now_obj->y_room + (game_screen_y/2)); j++, cnt++)
                {
                    if (out_of_border(i, j, _this))
                    {
                        signs[cnt] = htonl((int)' ');
                        colors[cnt] = htonl(15);
                        continue;
                    }
                    signs[cnt] = htonl((int)_this->terminal[i][j].sign);
                    colors[cnt] = htonl((int)_this->terminal[i][j].color);
                }

            my_send(_user->my_sock, signs, game_screen_x * game_screen_y, _this);
            my_send(_user->my_sock, colors, game_screen_x * game_screen_y, _this);

            int _skills[skills_sz];

            _skills[AWP] = static_cast<hero*>(now_obj)->skills[AWP];
            _skills[SGN] = static_cast<hero*>(now_obj)->skills[SGN];
            _skills[ARF] = static_cast<hero*>(now_obj)->skills[ARF];
            _skills[PST] = static_cast<hero*>(now_obj)->skills[PST];

            _skills[SPD] = static_cast<hero*>(now_obj)->skills[SPD];
            _skills[HPU] = static_cast<hero*>(now_obj)->skills[HPU];
            _skills[GRN] = static_cast<hero*>(now_obj)->skills[GRN];
            _skills[SMK] = static_cast<hero*>(now_obj)->skills[SMK];

            _skills[0] = static_cast<hero*>(now_obj)->curr_skill;

            bool flag = false;
            for (int i = 0; i < skills_sz; i++)
                if ((_skills[i] == 32 || _skills[i] == 15) && !flag)
                {
                    flag = true;
                    static_cast<loca*>(_this)->cnt++;
                }

            for (int i = 0; i < skills_sz; i++)
                _skills[i] = htonl(_skills[i]);

            my_send(_user->my_sock, _skills, skills_sz, _this);

            int kdh[3];
            kdh[0] = static_cast<hero*>(now_obj)->kills;
            kdh[1] = static_cast<hero*>(now_obj)->deaths;
            kdh[2] = static_cast<hero*>(now_obj)->hp;
            for (int i = 0; i < 3; i++)
                kdh[i] = htonl(kdh[i]);

            my_send(_user->my_sock, kdh, 3, _this);
        }
        catch (bool no_response)
        {
            if (no_response){
            _user->my_hero->erase_called = true;
            delete _user;
            to_erase.insert(_user);
            }
        }
    }


    for (auto it : to_erase)
        _this->connections.erase(it);

    if (send_happened)
        _this->send_time_t = clock();
}

bool out_of_border(int x, int y, lvl* _this)
{
    if (x < 0 || x >= _this->x)
        return true;
    if (y < 0 || y >= _this->y)
        return true;
    return false;
}

double time_passed(clock_t start, clock_t finish)
{
    double diff = finish - start;
    double secs = diff / CLOCKS_PER_SEC;
    return secs;
}
