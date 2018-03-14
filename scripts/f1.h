#ifndef f1_h
#define f1_h

#include".\..\objs.h"
#include".\..\lvls.h"
#include".\..\img.h"
#include".\..\stl.h"
void print(int x, int y, img& _img);
void print(int x, int y, pixel& _img);

void clear_position(obj* _this);
void moving(int new_x_room, int new_y_room, obj* _this);
void update_terminal(obj* _this);
void scan_space(obj* _this, int x1, int y1, set<obj*>& objs);
void scan_space(int x0, int y0, int x1, int y1, set<obj*>& objs, lvl* _lvl);

#endif
