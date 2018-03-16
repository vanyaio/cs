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
    int new_x0 = x1 - _this->x_img;
    int new_y0 = y1 - _this->y_img;
    int new_x1 = new_x0 + _this->skin->x;
    int new_y1 = new_y0 + _this->skin->y;
    scan_space(new_x0, new_y0, new_x1, new_y1, objs, _this->my_lvl);
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

void network_step(lvl* _this)
{
    SOCKET slave = accept((_this->master), 0, 0);
    if (slave != -1)
    {
        obj* new_hero = new hero(3, 3, _this);
        _this->add_list.push_back(new_hero);

        user* new_user = new user(new_hero, slave);
        _this->connections.insert(new_user);

        (static_cast<hero*>(new_hero))->my_user = new_user;
    }
    for (auto _user : _this->connections)
    {
        int gotten = recv((_user->my_sock), (char*)(_user->key_buff), key_buff_sz * sizeof(int), 0);
        if (gotten != -1)
        {
            for (int i = 0 ; i < key_buff_sz; ++i)
                _user->key_buff[i] = ntohl(_user->key_buff[i]);
        }
        /*
        int objs_sz = (_this->my_objs).size();
        int send_sz[1] = {objs_sz};
        send_sz[0] = htonl(send_sz[0]);
        int send1 = send((_user->my_sock), (char*)send_sz, sizeof(int), 0);

        int objs_ind[objs_sz];
        int i = 0;
        for (auto obj_sending: (_this->my_objs))
        {
            objs_ind[i] = obj_sending->ind;
            ++i;
        }
        for (int j = 0 ; j < objs_sz; ++j)
            objs_ind[j] = htonl(objs_ind[j]);
        int send2 = send((_user->my_sock), (char*)objs_ind, sizeof(int) * objs_sz, 0);


        int objs_x[objs_sz];
        i = 0;
        for (auto obj_sending: (_this->my_objs))
        {
            objs_x[i] = obj_sending->x_room;
            ++i;
        }
        for (int j = 0 ; j < objs_sz; ++j)
            objs_x[j] = htonl(objs_x[j]);
        int send3 = send((_user->my_sock), (char*)objs_x, sizeof(int) * objs_sz, 0);

        int objs_y[objs_sz];
        i = 0;
        for (auto obj_sending: (_this->my_objs))
        {
            objs_y[i] = obj_sending->y_room;
            ++i;
        }
        for (int j = 0 ; j < objs_sz; ++j)
            objs_y[j] = htonl(objs_y[j]);
        int send4 = send((_user->my_sock), (char*)objs_y, sizeof(int) * objs_sz, 0);

        /*if ((send1 == -1) || (send2 == -1) || (send3 == -1) || (send4 == -1))
        {
            cout << 4 << endl;
            _this->connections.erase(_user);
            closesocket(_user->my_sock);
            _user->my_hero->erase_called = true;
            delete _user;
            continue;
        }*/

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
        send((_user->my_sock), (char*)signs, sizeof(int) * game_screen_x * game_screen_y, 0);
        send((_user->my_sock), (char*)colors, sizeof(int) * game_screen_x * game_screen_y, 0);
    }
}

bool out_of_border(int x, int y, lvl* _this)
{
    if (x < 0 || x >= _this->x)
        return true;
    if (y < 0 || y >= _this->y)
        return true;
    return false;
}

