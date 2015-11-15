#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
COORD pos;
void check(int *x,int *y)
{
    if(*x<0)
        *x=0;
    if(*y<0)
        *y=4;
    if(*y>24)
        *y=24;
}
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
    int directionX = 1;
    int directionY = -1;
    int color=1;
    int state=1;
    int i,j;
    int x=0;
    int y=24;
    for(i=0;i<13;i++)
    {
        switch(state)
        {
        case 1 :
            {
              fillRectangle(pos,x,y,color);
            if(x==70)
            {
                state=33;
                break;
            }
              color++;
              state++;
              break;
            }
        case 2 :
            {



                y = y + (directionY*5);
                directionY=directionY*-1;
                fillRectangle(pos,x,y,color);
                if(directionY==-1)
                {
                    directionX=-1;
               x = x + (directionX*10);
                y = y + (directionY*5);
                fillRectangle(pos,x,y,color);
                 x = 70;
                 color=1;
                 state=1;
                }
                else
                {
                 x = x + (directionX*10);
                y = y + (directionY*5);
                fillRectangle(pos,x,y,color);
                x = x + (directionX*10);
                 color++;
            state++;
                }



              break;
            }
        case 3:
            {
              j=0;
            directionY=-1*directionY;
            directionX=-1 *directionX;
              for(j;j<3;j++)
              {
                    fillRectangle(pos,x,y,color);

                    x = x + (directionX*10);
                     y = y + (directionY*5);
              }
              if(directionY==1)
              {
                  x=70;y=4;
                  color=2;
                  state--;
              }
              else{ color=1;
            state++;}

            check(&x,&y);
                break;
            }
             case 4:
            {
              j=0;
             directionY=-1*directionY;
            directionX=-1 *directionX;
              for(j;j<4;j++)
              {
                    fillRectangle(pos,x,y,color);

                    x = x + (directionX*10);
                    y = y + (directionY*5);
              }
               if(directionY==-1)
            {
                state--;
                color=3;
                x=50;

            }
            else
            {
                   color++;
            state++;
            }

            check(&x,&y);
                break;
            }
            case 5:
            {
              j=0;
            directionY=-1*directionY;
            directionX=-1*directionX;
              for(j;j<5;j++)
              {
                    fillRectangle(pos,x,y,color);

                    x = x + (directionX*10);
                     y = y + (directionY*5);
              }
            color++;
            if(directionY==1)
            {
                state--;
                color=1;
                y=19;
                x=70;
            }
            else
            {
                  state++;
            }

           check(&x,&y);
                break;
            }
             case 6:
            {
             j=0;
            directionY=  directionY*-1;
            directionX=directionX*-1;
              for(j;j<5;j++)
              {
                     x = x + (directionX*10);
                    fillRectangle(pos,x,y,color);


                     y = y + (directionY*5);
              }


            if(directionY==-1)
            {
                state=5;
                color=2;
                x+=10;

            }
            else
            {
                x=70;
            }

           check(&x,&y);
                break;
            }

        }
    }

    /*fillRectangle(pos,0,24,1)
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
    */
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

        fillSimple();
    pos.X=0;
    pos.Y=30;


     Sleep(s);
    SetConsoleCursorPosition(hConsole, pos);
    return EXIT_SUCCESS;
}
