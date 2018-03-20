#define _WINSOCKAPI_
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<winsock2.h>
#include<windows.h>
#include<set>
#include <string.h>
#include<time.h>

#define SERVERADDR "127.0.0.1"

using namespace std;
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
    if (WSAStartup(0x202,(WSADATA *)&buff[0]))
    {
        printf("WSAStart error %d\n",WSAGetLastError());
        return -1;
    }

    SOCKET sock = socket(AF_INET,
                         SOCK_STREAM,
                         0);

    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(12345);
    sock_addr.sin_addr.s_addr = inet_addr(SERVERADDR);

    //set_nonblock(sock);
    cout << "connecting..." << endl;
    while (connect(sock,(sockaddr *)&sock_addr, sizeof(sock_addr)) == -1){}
    system("cls");


    loca _loca;
    //
    ofstream fout;
    fout.open("logs.txt");
    int last = -1;
    //
    while (true)
    {
        for (int i = 0 ; i < key_buff_sz; ++i)
            _loca.key_buff[i] = htonl(_loca.key_buff[i]);
        send(sock, (char*)_loca.key_buff, key_buff_sz * sizeof(int), 0);

        int sz = game_screen_x * game_screen_y;
        int signs[sz];
        int recv1 = recv(sock, (char*)signs, sz * sizeof(int), 0);

        int colors[sz];
        int recv2 = recv(sock, (char*)colors, sz * sizeof(int), 0);

        for (int i = 0; i < sz; i++)
        {
            signs[i] = ntohl(signs[i]);
            colors[i] = ntohl(colors[i]);
        }

        int skills[skills_sz];
        int recv3 = recv(sock, (char*)skills, skills_sz * sizeof(int), 0);
        for (int i = 0; i < skills_sz; i++)
            skills[i] = ntohl(skills[i]);

        int kdh[3];
        int recv4 = recv(sock, (char*)kdh, 3 * sizeof(int), 0);
        for (int i = 0; i < 3; i++)
            kdh[i] = ntohl(kdh[i]);

        if (recv1 == (sz*4) && recv2 == (sz*4) && recv3 == (skills_sz * sizeof(int)) && recv4 == (3 * sizeof(int)))
            _loca.step(signs, colors, skills, kdh, true);
        else
            _loca.step(signs, colors, skills, kdh, false);
        //_loca.step(signs, colors, true);
        if (last != _loca.cnt)
            fout << _loca.cnt << endl;
        last = _loca.cnt;
    }
}
