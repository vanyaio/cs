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

    /*cout << connect(sock,(sockaddr *)&sock_addr,
                    sizeof(sock_addr)) << endl;*/

    while (connect(sock,(sockaddr *)&sock_addr, sizeof(sock_addr)) == -1){};
    //
    clock_t cd_set_t = clock();
    bool cd_set = false;
    //

    while (true)
    {

        int key_buff[5] = {0, 0, 0, 0, 0};

        clock_t t1;
        t1 = clock();

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            double diff = t1 - cd_set_t;
            double secs = diff / CLOCKS_PER_SEC;
            if (!cd_set || (secs > 0.1))
            {
                key_buff[0] = VK_RIGHT;

                cd_set = true;
                cd_set_t = clock();
            }
        }
        //

        //
        for (int i = 0 ; i < 5; ++i)
            key_buff[i] = htonl(key_buff[i]);
        send(sock, (char*)key_buff, 5 * sizeof(int), 0);

        int send_sz[1];
        recv(sock, (char*)buff, 2 * sizeof(int), 0);
        int objs_sz = ntohl(send_sz[0]);

        int objs_ind[objs_sz];
        recv(sock, (char*)objs_ind, objs_sz * sizeof(int), 0);

        int objs_x[objs_sz];
        recv(sock, (char*)objs_x, objs_sz * sizeof(int), 0);

        int objs_y[objs_sz];
        recv(sock, (char*)objs_y, objs_sz * sizeof(int), 0);


        for (int i = 0; i < objs_sz; i++)
        {
            int a, b, c;
            a = objs_ind[i] = ntohl(objs_ind[i]);
            b = objs_x[i] = ntohl(objs_x[i]);
            c = objs_y[i] = ntohl(objs_y[i]);
            cout << a << " " << b << " " << c << endl;
        }
        cout << endl << endl << endl;
    }
}
