#ifndef f1_h
#define f1_h

#include".\..\objs.h"
#include".\..\lvls.h"
#include".\..\img.h"
#include".\..\stl.h"
#include".\..\user.h"
void print(int x, int y, img& _img);
void print(int x, int y, pixel& _img);
void print(int x, int y, std::string s);
void print(int x, int y, int s);

void clear_position(obj* _this);
void moving(int new_x_room, int new_y_room, obj* _this);
void update_terminal(obj* _this);
void scan_space(obj* _this, int x1, int y1, set<obj*>& objs);
void scan_space(int x0, int y0, int x1, int y1, set<obj*>& objs, lvl* _lvl);

int set_nonblock(SOCKET fd);

void network_step(lvl* _this);
#endif
