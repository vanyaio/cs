#include"objs.h"
#include"lvls.h"
#include"img.h"
#include"stl.h"
#include"vars.h"
#include"scripts.h"
#include"user.h"
int main()
{

    char buff[1024];
    if (WSAStartup(0x0202,(WSADATA *) &buff[0]))
    {
        printf("Error WSAStartup %d\n",
               WSAGetLastError());
        return -1;
    }


    loca _loca(30, 30);
    while (true)
    {
        _loca.step();
    }
    return 0;
}
