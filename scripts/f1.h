#ifndef f1_h
#define f1_h

#include".\..\objs.h"
#include".\..\lvls.h"
#include".\..\img.h"
#include".\..\stl.h"
#include".\..\user.h"
void print(int x, int y, img& _img);
void print(int x, int y, pixel& _img);

void clear_position(obj* _this);
void moving(int new_x_room, int new_y_room, obj* _this);
void update_terminal(obj* _this);
void scan_space(obj* _this, int x1, int y1, set<obj*>& objs);
void scan_space(int x0, int y0, int x1, int y1, set<obj*>& objs, lvl* _lvl);

int set_nonblock(SOCKET fd);

void network_step(lvl* _this);
void set_spawn(int& _x, int& _y, lvl* _this);
bool out_of_border(int x, int y, lvl* _this);

double time_passed(clock_t start, clock_t finish);

int rand_num(int mx);

void my_send(SOCKET sock, char* arr, int sz);
void my_recv(SOCKET sock, int* arr, int sz);
#endif
