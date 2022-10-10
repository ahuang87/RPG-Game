#include "graphics.h"

#include "globals.h"

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+11, v+11, BLACK);
}

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++) {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = 0xFFFF00; // Yellow
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = 0xD2691E; // "Dirt"
        else if (img[i] == '5') colors[i] = LGREY; // 50% grey
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_plant(int u, int v)
{
    int plant[121]= {
        0x00000000, 0x00000000, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0xff2d5219, 0xff1515da, 0xff5fd122, 0xff439116, 0xff1515da, 0xff5fd122, 0xff2d5219, 0x00000000, 0x00000000,
        0x00000000, 0xff2d5219, 0xff2d5219, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff5fd122, 0xff2d5219, 0x00000000,
        0xff2d5219, 0xff5fd122, 0xff439116, 0xff439116, 0xff439116, 0xff5fd122, 0xff439116, 0xff439116, 0xff1515da, 0xff439116, 0xff2d5219,
        0xff2d5219, 0xff439116, 0xff439116, 0xff439116, 0xff1515da, 0xff439116, 0xff439116, 0xff5fd122, 0xff439116, 0xff439116, 0xff2d5219,
        0xff2d5219, 0xff439116, 0xff5fd122, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff5fd122, 0xff2d5219,
        0xff2d5219, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff5fd122, 0xff439116, 0xff439116, 0xff439116, 0xff1515da, 0xff2d5219,
        0xff2d5219, 0xff1515da, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff439116, 0xff2d5219,
        0xff2d5219, 0xff439116, 0xff439116, 0xff5fd122, 0xff439116, 0xff1515da, 0xff439116, 0xff439116, 0xff5fd122, 0xff439116, 0xff2d5219,
        0x00000000, 0xff2d5219, 0xff2d5219, 0xff439116, 0xff439116, 0xff439116, 0xff5fd122, 0xff439116, 0xff2d5219, 0xff2d5219, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0xff2d5219, 0x00000000, 0x00000000, 0x00000000
    };
    uLCD.BLIT(u,v,11,11,plant);
}

void draw_wall(int u, int v)
{
    int walls[121]= {
        0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7da4c4, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe,
        0xff7da4c4, 0xff7da4c4, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7da4c4, 0xff7da4c4,
        0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff6f7bbe, 0xff7da4c4, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe,
        0xff7da4c4, 0xff7da4c4, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7da4c4, 0xff7da4c4,
        0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7da4c4, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe,
        0xff7da4c4, 0xff7da4c4, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7da4c4, 0xff7da4c4,
        0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff6f7bbe, 0xff7da4c4, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe,
        0xff7da4c4, 0xff7da4c4, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8,
        0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7da4c4, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe,
        0xff7da4c4, 0xff7da4c4, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8,
        0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff6f7bbe, 0xff7ba2c8, 0xff6f7bbe, 0xff6f7bbe, 0xff6f7bbe
    };
    uLCD.BLIT(u,v,11,11,walls);
}


void draw_team1(int u, int v)
{
    int team1[] = {

        0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xff030303, 0xff030303, 0xff797bd1, 0xFF0000, 0xFF0000, 0xFF0000, 0xff797bd1, 0xff030303, 0xff030303, 0xff030303,
        0xff000000, 0xff030303, 0xff030303, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff030303, 0xff030303, 0xff030303,
        0xff000000, 0xff030303, 0xff030303, 0xff797bd1, 0xFF0000, 0xFF0000, 0xFF0000, 0xff797bd1, 0xff030303, 0xff030303, 0xff030303,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff797bd1, 0xff797bd1, 0xFF0000, 0xFF0000, 0xFF0000, 0xff797bd1, 0xff797bd1, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff797bd1, 0xff797bd1, 0xFF0000, 0xFF0000, 0xFF0000, 0xff797bd1, 0xff797bd1, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff797bd1, 0xff797bd1, 0xFF0000, 0xFF0000, 0xFF0000, 0xff797bd1, 0xff797bd1, 0xFF0000, 0xff000000

    };

    uLCD.BLIT(u, v, 11, 11, team1);;

}
void draw_team2(int u, int v)
{
    int team2[121] = {
        0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000

    };

    uLCD.BLIT(u, v, 11, 11, team2);;

}
void draw_team1s(int u, int v)
{
    int team1s[121] = {
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xFF0000, 0xff000000
    };

    uLCD.BLIT(u, v, 11, 11, team1s);;

}
void draw_team2s(int u, int v)
{
    int team2s[121]= {
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000, 0xff000000, 0xff00ff00, 0xff000000

    };

    uLCD.BLIT(u, v, 11, 11,team2s);;

}
void draw_team1ss(int u, int v)
{
    int team1ss[121]= {
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000,
        0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000, 0xff000000, 0xff000000, 0xFF0000, 0xff000000
    };

    uLCD.BLIT(u, v, 11, 11, team1ss);;

}
void draw_team2ss(int u, int v)
{
    int team2ss[121]= {
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00,
        0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff00ff00, 0xff00ff00, 0xff00ff00, 0xff00ff00
    };
    uLCD.BLIT(u, v, 11, 11, team2ss);;
}

void draw_player1sprite(int u, int v)
{
//    pc.printf("Drawing Player 1 Sprite\r\n");
    uLCD.filled_rectangle(u, v, u+10, v+10, RED);
}
void draw_player2sprite(int u, int v)
{
//    pc.printf("Drawing Player 2 Sprite\r\n");
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_selection(int u, int v)
{
    int cursor[121] = {

        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff7ba2c8, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000, 0xff000000,
        0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000,
        0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8,
        0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8,
        0xff000000, 0xff000000, 0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000, 0xff000000, 0xff000000,
        0xff000000, 0xff000000, 0xff000000, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff7ba2c8, 0xff000000, 0xff000000, 0xff000000

    };
//    pc.printf("Drawing Player 2 Sprite\r\n");
    uLCD.BLIT(u, v, 11, 11, cursor);
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}


