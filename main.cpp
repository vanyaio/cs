#include"objs.h"
#include"lvls.h"
#include"img.h"
#include"stl.h"
#include"vars.h"
#include"scripts.h"
#include"user.h"
#include<fstream>
int main()
{
    srand(time(0));
    char buff[1024];
    if (WSAStartup(0x0202,(WSADATA *) &buff[0]))
    {
        printf("Error WSAStartup %d\n",
               WSAGetLastError());
        return -1;
    }
    //
    ofstream fout;
    fout.open("logs.txt");
    int last = 0;
    //
    loca _loca(300, 300);
    while (true)
    {
        _loca.step();
        //
        if (last != _loca.cnt)
        {
            fout << _loca.cnt << endl;
            last = _loca.cnt;
        }
    }
    return 0;
}
