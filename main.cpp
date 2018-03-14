#include"objs.h"
#include"lvls.h"
#include"img.h"
#include"stl.h"
#include"vars.h"
#include"scripts.h"

int main()
{
    loca _loca(30, 30);
    while (true)
    {
        _loca.step();
    }
    return 0;
}
