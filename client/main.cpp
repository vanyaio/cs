#define _WINSOCKAPI_
#include<iostream>
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

    //
    clock_t cd_set_t = clock();
    bool cd_set = false;
    //

    loca _loca;
    while (true)
    {
        for (int i = 0 ; i < key_buff_sz; ++i)
            _loca.key_buff[i] = htonl(_loca.key_buff[i]);
        send(sock, (char*)_loca.key_buff, key_buff_sz * sizeof(int), 0);

        /*
        int send_sz[1];
        recv(sock, (char*)send_sz, sizeof(int), 0);
        int objs_sz = ntohl(send_sz[0]);

        int objs_ind[objs_sz];
        recv(sock, (char*)objs_ind, objs_sz * sizeof(int), 0);

        int objs_x[objs_sz];
        recv(sock, (char*)objs_x, objs_sz * sizeof(int), 0);

        int objs_y[objs_sz];
        recv(sock, (char*)objs_y, objs_sz * sizeof(int), 0);
        */

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

        if (recv1 == (sz*4) && recv2 == (sz*4))
            _loca.step(signs, colors, true);
        else
            _loca.step(signs, colors, false);
        //_loca.step(signs, colors, true);
    }
}
