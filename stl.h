#define _WINSOCKAPI_
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include<time.h>
#include <conio.h>
#include<string>
#include<stdio.h>
#include<list>
#include<set>
#include<cstdlib>
#include<map>

#define SERVERADDR "127.0.0.1"
#define key_buff_sz 5

#define game_screen_x 21
#define game_screen_y 11

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#define W_KEY 0x57
#define A_KEY 0x41
#define S_KEY 0x53
#define D_KEY 0x44

#define KEY_1 0x31
#define KEY_2 0x32
#define KEY_3 0x33
#define KEY_4 0x34
#define KEY_5 0x35
#define KEY_6 0x36
#define KEY_7 0x37
#define KEY_8 0x38

#define skills_sz 9

#define AWP 1
#define AWP_DMG 5
#define AWP_CD 4.0
#define AWP_CD_MOVING 0.02
#define AWP_AMMO 5

#define SGN 2
#define SGN_DMG 10
#define SGN_CD 0.8
#define SGN_CD_MOVING 0.3
#define SGN_AMMO 8

#define ARF 3
#define ARF_DMG 10
#define ARF_CD 0.3
#define ARF_CD_MOVING 0.1
#define ARF_AMMO 15

#define PST 4
#define PST_DMG 10
#define PST_CD 0.5
#define PST_CD_MOVING 0.1
#define PST_AMMO 15

#define GRN 5
#define GRN_CD 2.0
#define GRN_AMMO 13

#define SMK 6
#define SMK_AMMO 15

#define HPU 7
#define HPU_CD 0.3
#define HPU_AMMO 15
#define HP_UP 10

#define SPD 8
#define SPD_AMMO 15
#define SPD_CD 0.3
#define SPD_UP 0.01
#define SPD_DURATION 7.0
