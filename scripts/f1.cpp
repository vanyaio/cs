#include"f1.h"
#include".\..\vars.h"
#include".\..\scripts.h"
void print(int x, int y, img& _img)
{
    COORD c1;
    c1.X = x; c1.Y = y;

    SetConsoleCursorPosition(hConsole, c1);
    SetConsoleTextAttribute(hConsole, _img.arr[0][0].color);
    std::cout << _img.arr[0][0].sign;
}
void print(int x, int y, pixel& _img)
{
    COORD c1;
    c1.X = x; c1.Y = y;

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
