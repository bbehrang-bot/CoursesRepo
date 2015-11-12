#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
COORD pos;

void ccc(HANDLE hConsole,COORD pos)
{



int i=0;
    for(i=0;i<9;i++)
        {

            printf(" ");
            pos.X++;
            SetConsoleCursorPosition(hConsole, pos);
        }
}
void fillRectangle(COORD pos,int x,int y,int color)
{
    const long sleepTimes = 50;
     int fmt;
       int i=0;
       HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Sleep(sleepTimes);

    if(color==1)
    {
        fmt = BACKGROUND_GREEN;
    }
    else if(color==2)
    {
        fmt = BACKGROUND_RED | BACKGROUND_GREEN;
    }
     else if(color==3)
    {
        fmt = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    }
     else if(color==4)
    {
        fmt = BACKGROUND_GREEN;
    }



     SetConsoleTextAttribute(hConsole, fmt);

    pos.Y=y;
    pos.X=x;
    SetConsoleCursorPosition(hConsole, pos);
    while(pos.X>=x&&pos.X<=x+10&&pos.Y>=y-4&&pos.Y<=y)
    {
          if(pos.X==x&&pos.X<x+10)
    {
        for(i=0;i<5;i++)
        {

           ccc(hConsole,pos);
        }

            pos.Y--;
            pos.X=x;
            SetConsoleCursorPosition(hConsole, pos);



    }
    }



    }

void fillSimple()
{
    fillRectangle(pos,0,24,1);

    fillRectangle(pos,0,19,2);
    fillRectangle(pos,10,24,2);

    fillRectangle(pos,20,24,3);
    fillRectangle(pos,10,19,3);
    fillRectangle(pos,10,19,3);
    fillRectangle(pos,0,14,3);

    fillRectangle(pos,0,9,1);
    fillRectangle(pos,10,14,1);
    fillRectangle(pos,20,19,1);
    fillRectangle(pos,30,24,1);

    fillRectangle(pos,40,24,2);
    fillRectangle(pos,30,19,2);
    fillRectangle(pos,20,14,2);
    fillRectangle(pos,10,9,2);
    fillRectangle(pos,0,4,2);

    fillRectangle(pos,10,4,3);
    fillRectangle(pos,20,9,3);
    fillRectangle(pos,30,14,3);
    fillRectangle(pos,40,19,3);
    fillRectangle(pos,50,24,3);

    fillRectangle(pos,60,24,3);
    fillRectangle(pos,50,19,3);
    fillRectangle(pos,40,14,3);
    fillRectangle(pos,30,9,3);
    fillRectangle(pos,20,4,3);

    fillRectangle(pos,30,4,2);
    fillRectangle(pos,40,9,2);
    fillRectangle(pos,50,14,2);
    fillRectangle(pos,60,19,2);
    fillRectangle(pos,70,24,2);

    fillRectangle(pos,70,19,1);
    fillRectangle(pos,60,14,1);
    fillRectangle(pos,50,9,1);
    fillRectangle(pos,40,4,1);

    fillRectangle(pos,50,4,3);
    fillRectangle(pos,60,9,3);
    fillRectangle(pos,70,14,3);

    fillRectangle(pos,70,9,2);
    fillRectangle(pos,60,4,2);


    fillRectangle(pos,70,4,1);
}
void fillCorner()
{
     fillRectangle(pos,0,24,1);
    fillRectangle(pos,70,4,1);

    fillRectangle(pos,0,19,2);
    fillRectangle(pos,70,9,2);
    fillRectangle(pos,10,24,2);
    fillRectangle(pos,60,4,2);


    fillRectangle(pos,20,24,3);fillRectangle(pos,50,4,3);
    fillRectangle(pos,10,19,3);fillRectangle(pos,60,9,3);
    fillRectangle(pos,10,19,3);fillRectangle(pos,70,14,3);
    fillRectangle(pos,0,14,3);





    fillRectangle(pos,0,9,1);fillRectangle(pos,70,19,1);
    fillRectangle(pos,10,14,1);fillRectangle(pos,60,14,1);
    fillRectangle(pos,20,19,1); fillRectangle(pos,50,9,1);
    fillRectangle(pos,30,24,1); fillRectangle(pos,40,4,1);








    fillRectangle(pos,40,24,2); fillRectangle(pos,30,4,2);
    fillRectangle(pos,30,19,2);fillRectangle(pos,40,9,2);
    fillRectangle(pos,20,14,2); fillRectangle(pos,50,14,2);
    fillRectangle(pos,10,9,2);fillRectangle(pos,60,19,2);
    fillRectangle(pos,0,4,2); fillRectangle(pos,70,24,2);

    fillRectangle(pos,10,4,3);fillRectangle(pos,60,24,3);
    fillRectangle(pos,20,9,3); fillRectangle(pos,50,19,3);
    fillRectangle(pos,30,14,3);fillRectangle(pos,40,14,3);
    fillRectangle(pos,40,19,3);  fillRectangle(pos,30,9,3);
    fillRectangle(pos,50,24,3);  fillRectangle(pos,20,4,3);
}
int main()
{
    const long sleepTime = 50;
     int q=0;
      const long s=1000;
       HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("If you Want the filling to start simultaneously from both corners type 1 , otherwise type 0\n");

    scanf("%i",&q);
    system("cls");
    if(q==1)
        fillCorner();
    else
        fillSimple();
    pos.X=0;
    pos.Y=30;


     Sleep(s);
    SetConsoleCursorPosition(hConsole, pos);
    return EXIT_SUCCESS;
}
