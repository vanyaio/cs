#ifndef key_logger_h
#define key_logger_h

#include".\..\..\obj.h"
class key_logger;
#include".\..\..\objs.h"
#include".\..\..\lvls.h"
#include".\..\..\img.h"
#include".\..\..\stl.h"
class key_logger : public obj
{
public:
    clock_t cd_set_t;
    bool cd_set;
    key_logger();
    key_logger(int _x, int _y);
    key_logger(int _x, int _y, lvl* _my_lvl);

    void step();
    void init();
};
#endif
