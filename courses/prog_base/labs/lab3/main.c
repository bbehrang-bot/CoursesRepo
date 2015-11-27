#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>
void setUpUI(int *x,int *y)
{

    COORD pos;
    pos.X=0;
    pos.Y=*x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    for(pos.X=0;pos.X<80;pos.X++)
    {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
            setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            printf("*");
    }
    *y= pos.Y;
}
void cleanRow(int *y)
{
    COORD pos;
    int i=0;
    pos.Y = *y + 16;
    for(pos.X=0;pos.X<240;pos.X++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
            setConsoleColor(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            printf(" ");
    }
    pos.Y=*y -1;
    for(pos.X=0;pos.X<80;pos.X++)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
            setConsoleColor(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            printf(" ");
    }
}
void setUpCommands(int *x,int *y)
{



    COORD pos;
    pos.Y = *y + *x +5;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor( BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    printf("Type any of the commands to begin...\n\n");
    printf("1.          ");
    printf("delete          ");
    printf("Deletes your string\n");


      printf("2.          ");
    printf("changerandom    ");
    printf("Changes your string with random characters \n");


      printf("3.          ");
    printf("new             ");
    printf("changes your string with a new one entered by you\n");


      printf("4.          ");
    printf("correctchange   ");
    printf("deletes non alphabetic letters\n");


      printf("5.          ");
    printf("printwords      ");
    printf("prints words in your string\n");


      printf("6.          ");
    printf("wordsamount     ");
    printf("prints amount of words in your string\n");


      printf("7.          ");
    printf("longestword     ");
    printf("prints longest word in your string\n");


      printf("8.          ");
    printf("length          ");
    printf("prints length of your string\n");


      printf("9.          ");
    printf("find            ");
    printf("prints number of character occurances\n");


      printf("10.         ");
    printf("numbers         ");
    printf("prints amount of numbers in your string\n");


      printf("11.         ");
    printf("deletespace     ");
    printf("Deletes blank spaces\n");


      printf("12.         ");
    printf("dividers        ");
    printf("prints all dividers of your string\n");


      printf("13.         ");
    printf("exit            ");
    printf("closes the program\n");

}
void fillConsoleBackground(int x)
{
    COORD pos;
    pos.X=0;
    pos.Y=0;
    int i,j;
    for(pos.X=0;pos.X<80;pos.X++)
    {
        for(pos.Y=0;pos.Y<x;pos.Y++)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
            setConsoleColor(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            printf(" ");
        }
    }
}

void printSample(char *myStr,int *x,int *y)
{

   COORD pos;


   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
   gets(myStr);
   system("cls");
   fillConsoleBackground(50);

   setUpUI(x,y);


}

void allinone(char *myStr,int *y,int *x)
{

            *x = strlen(myStr)/80 +10;
            *y=0;
            int v= *x;
            system("cls");
            fillConsoleBackground(*x);
            setUpUI(x,y);
            setUpCommands(x,y);
            COORD pos;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
            setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);


            pos.X=0;
            pos.Y = 0;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
            puts(myStr);

}
void toDoo(char *myStr,int *y,int *x)
{
    COORD pos;


    pos.X=0;
    pos.Y = *y + 17;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

    char *command;
    command = malloc(256);

    gets(command);
    int i;
    cleanRow(y);
    char tmp[strlen(command)];
    strcpy(tmp,command);
    char *included[]={"delete","changerandom","new","correctchange",
    "printwords","wordsamount","longestword","length","find","numbers",
    "deletespace","dividers","exit"};
    int size = strlen(*included);
    char *s;
    s = malloc(256);
    strcpy(s,"");
    s = *(included[0]);
    for(i=0;i<13;i++)
    {
        char oo[strlen(included[i])];
        strcpy(oo,included[i]);
        if(strcmp(tmp,included[i])==0)
        {
            break;
        }

    }

    i = i+1;


    switch(i)
    {
    case 1:
        {
            eraseChar(myStr);
            allinone(myStr,y,x);
            toDoo(myStr,y,x);
            break;
        }

    case 2:
        {
            replaceWithRandom(myStr);
         allinone(myStr,y,x);
            toDoo(myStr,y,x);
            break;
        }
    case 3:
        {
            changeMyStr(myStr,y);
       allinone(myStr,y,x);
            toDoo(myStr,y,x);
            break;
        }
    case 4:
        {
            correctMystr(myStr);
       allinone(myStr,y,x);
            toDoo(myStr,y,x);
            break;
        }

    case 5:
        {
            putSymInWords(myStr,y,x);

            toDoo(myStr,y,x);
            break;
        }

    case 6:
        {
            countWords(myStr,y);

            toDoo(myStr,y,x);

            break;
        }


    case 7:
        {
            findLongest(myStr,y);

            toDoo(myStr,y,x);
            allinone(myStr,y,x);
            break;
        }


    case 8:
        {
            findLength(myStr,y);

            toDoo(myStr,y,x);
            break;
        }


    case 9:
        {
            findUserValue(myStr,y);
            toDoo(myStr,y,x);
            break;
        }



     case 10:
        {
            findNumbers(myStr,y);
            toDoo(myStr,y,x);
            break;
        }


     case 11:
        {
            deleteSpaces(myStr);
            allinone(myStr,y,x);
            toDoo(myStr,y,x);
            break;
        }

      case 12:
        {
            divisor(myStr,y,x);

            toDoo(myStr,y,x);
            break;
        }


       case 13:
        {
            return EXIT_SUCCESS;
            break;
        }
       default:
        {
             COORD pos;
            pos.X=0;
            pos.Y=*y -1;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
            setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            printf("Command not found , try again");
            toDoo(myStr,y,x);
            break;
        }



    }

}
void setConsoleColor(int color)
{
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}



void eraseChar(char *myStr)
{
        myStr = strcpy(myStr,"");
}
void replaceWithRandom(char myStr[])
{
    int i=0;

    while(myStr[i]!='\0')
    {
        myStr[i]= (char)(32 +rand() %96);
        i++;
    }
}
void changeMyStr(char *myStr,int *y)
{
    COORD pos;
    pos.X = 0;
    pos.Y = *y + 18;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor( BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);


     char *tmp;
     tmp = malloc(256);

     gets(tmp);
     strcpy(myStr,tmp);
     free(tmp);
}
void correctMystr(char *myStr)
{
    int i=0;

    int index=0;
    char tmp[strlen(myStr)];
    strcpy(tmp,myStr);
    strcpy(myStr,"");
    while(tmp[i]!='\0')
    {
        if((tmp[i] >= 'a' && tmp[i]<='z') || (tmp[i] >='A' && tmp[i] <='Z'))
           {


                myStr[index]=tmp[i];
                myStr[index+1]='\0';
                i++;
                index++;
           }
           else
           {
                i++;
           }
    }

}
void putSymInWords(char *myStr,int *y,int *x)
{
    int i=0;
    int index=0;
    char random;
    int size = strlen(myStr);
    char tmp[strlen(myStr)];



    strcpy(tmp,"");

int howMany=0;
     int countSymbols=0;
     while(myStr[i]!='\0')
    {

        char charTmp[2];
        charTmp[1]='\0';
        random=32 +rand() %96;
        while((random >= 'a' && random<='z') || (random >='A' && random <='Z'))
        {
            random = 32 +rand() %96;
        }
        if((myStr[i] >= 'a' && myStr[i]<='z') || (myStr[i] >='A' && myStr[i] <='Z'))
        {
           countSymbols=0;
           charTmp[0]=myStr[i];
           strcat(tmp,charTmp);
        }
        else
        {
            howMany++;
            countSymbols++;
            if(countSymbols==1)
            {
                strcat(tmp,"\n");
            }




        }
         i++;
    }



     COORD pos;
     fillConsoleBackground(howMany+50);
     *x = *x + howMany;
    setUpUI(x,y);
    setUpCommands(x,y);
int jfjfj = *y;
    setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    pos.Y=0;
     pos.X=0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    puts(myStr);
    pos.X=0;
    pos.Y=*y -1-howMany;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    puts(tmp);
    free(tmp);

}
int countWords(char *myStr,int *y)
{
    int count=0;
    int words = 0;
    int i=0;
    int index=0;
    for(i=0;i<strlen(myStr);i++)
    {
        if((myStr[i] >= 'a' && myStr[i]<='z') || (myStr[i] >='A' && myStr[i] <='Z'))
           {


                index++;
                count++;
           }
           else
           {
               if(index!=0)
               {
               words = words + count/index;
               count=0;
               index=0;
               }

           }
    }
    if(count!=0)
        words++;



    COORD pos;
    pos.X=0;
    pos.Y=*y -1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    printf("Number of words is : %i",words);
    return words;

}
int findWordLength(char *myStr,int *indexL)
{
    int i=*indexL;
    int wordLength=0;
    while((myStr[i] >= 'a' && myStr[i]<='z') || (myStr[i] >='A' && myStr[i] <='Z'))
    {

             wordLength++;
           i++;





    }



    *indexL = i+1;
    return wordLength;
}
void findLongest(char *myStr,int *y)
{
   int i=0;
   int j = 0;
     int size = strlen(myStr);
    char tmp[strlen(myStr)];
    strcpy(tmp,"");
   char charTm[2];
   charTm[1]='\0';
   int len;
   int tmpIndex=0;
    int numberOfLetters=0;
    while(numberOfLetters==0)
    {
         tmpIndex=i;
         numberOfLetters =findWordLength(myStr,&i);
    }

   for(j=tmpIndex;j<i-1;j++)
   {
       if((myStr[j] >= 'a' && myStr[j]<='z') || (myStr[j] >='A' && myStr[j] <='Z'))
   {
        charTm[0]=myStr[j];
        strcat(tmp,charTm);
   }
   }

   int numNext=0;


   for(i;i<strlen(myStr);i++)
   {
       len = findWordLength(myStr,&i);
       if(numberOfLetters<len)
       {
            strcpy(tmp,"");
            for(j=i-len-1;j<i-1;j++)
            {
                charTm[0]=myStr[j];
                strcat(tmp,charTm);
            }
       }
       i--;
   }
   len=strlen(tmp);
    COORD pos;
    pos.X=0;
    pos.Y=*y -1;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

    setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    printf("longest  word is : %s and its length is : %i",tmp,len);



}
void findLength(char *myStr,int *y)
{
    COORD pos;
    pos.X=0;
     pos.Y=*y -1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    printf("length of your string is %i\n",strlen(myStr));
}
void findUserValue(char *myStr,int *y)
{
    COORD pos;
    pos.X = 0;
    pos.Y = *y + 18;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor( BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    char *b;
    char user = '-';
     gets(b);
    if(strlen(b)>1)
    {
          pos.Y=*y -1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
     printf("input is not a character");
     return -1;
    }
    else
    {
        user = b[0];
    }


    int count=0;
    int i=0;
    for(i;i<strlen(myStr);i++)
    {
        if(myStr[i]==user)
            count++;
    }
     pos.Y=*y -1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    printf("%i",count);
}
void findNumbers(char *myStr,int *y)
{
    int count=0;
    int i = 0;

    for(i;i<strlen(myStr);i++)
    {
        if(myStr[i]>='0' && myStr[i]<='9' )
            count++;
    }
     COORD pos;
     pos.Y=*y -1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    printf("%i\n",count);
}
void deleteSpaces(char *myStr)
{
    int spacesCount;
    char tmp[strlen(myStr)];
    strcpy(tmp,myStr);
    strcpy(myStr,"");
    int i=0;
    char tmpChar[2];
    tmpChar[1]='\0';
    for(i;i<strlen(tmp);i++)
    {
        if(tmp[i]!=' ')
            {
                spacesCount=0;
                tmpChar[0]=tmp[i];
                strcat(myStr,tmpChar);
            }
        else
        {
            spacesCount++;
            if(spacesCount>80)
            {
                strcat(myStr," ");
                spacesCount=0;
            }
        }
    }
    free(tmp);
}
void divisor(char *myStr,int *y,int *x)
{
    COORD pos;
    int i=0;
    int j=0;
    int size = strlen(myStr);
    int number[size];
    int isor;
    while(myStr[i]!='\0')
    {
        if((myStr[i] >= '0' && myStr[i]<='9'))
        {
             number[i]=myStr[i] - '0';
              isor=1;

        }
        else
        {
              pos.Y=*y -1;
              SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
              setConsoleColor(FOREGROUND_RED  |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            puts("Input is not a number");
            isor=0;
            break;

        }
        i++;
    }


int num=0;
if(isor!=0)
{
    for(i=0;i<size;i++)
{
    double q =  pow(10,(size-i-1));
    num = num + number[i] * q;
}
    pos.Y= 0;
    pos.X=0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    for(j=1;j<=num;j++)
    {
        if(num%j==0)
        {
            printf("%i, ",j);
        }
    }

}
}

int main()
{


    srand(time(NULL));
    char *s;
    s = malloc(256);
    int x=25;
    int y=0;
    fillConsoleBackground(50);
    COORD pos;
    pos.X = 0;pos.Y = 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    setConsoleColor(FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED |BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    puts("Please Enter you string to begin:");
    gets(s);
    pos.Y+=1;
    allinone(s,&x,&y);

    toDoo(s,&y,&x);

    return 0;
}
