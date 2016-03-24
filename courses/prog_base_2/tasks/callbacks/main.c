#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
typedef (*cb)(char*,int i);
void shiftLeft(char keys[10])
{
    int i;
    for(i=0;i<10;i++)
        keys[i] = keys[i+1];
}
void cmpLastThreeSimiliar(char keys[10],int i){
        printf("last three symbols are : %c\n",keys[i-1]);

}
void threeSimiliar(char keys[10],int i){
             printf("found three similar symbols:\n");
             printf("%c\n",keys[i]);
             printf("The whole sequence was:");
             int in=0;
             while(in<10)
             {
                  printf("%c",keys[in]);
                  in++;
             }

             printf("\n\n");

}

int findThreeSimiliar(char keys[10],int *index){
int i,j,count;
    for(i=0;i<10;i++)
    {
        count =0;
        for(j=0;j<10;j++)
        {
            char p = keys[i];
            if(keys[i]==keys[j] && keys[i]!='\0')
                count++;
        }
        if(count>=3)
        {
            *index =i;
            return 1;
        }

    }

}
void detect(cb threeInRowCB,cb threeCB)
{
    char keys[10];
    strcpy(keys,"");
    int i =0;
    for(;;)
    {

        char pressed = getch();
        if(pressed != 'e')
        {
            if(i<10)
            {
                 keys[i] = pressed;
                 keys[i+1] = '\0';
                 i++;
            }
            else
            {
                i=9;
                shiftLeft(keys);
                keys[i] = pressed;
                keys[i+1] = '\0';
            }
        }
        else
        {
            if(keys[i-1] == keys[i-2]&& keys[i-2] == keys[i-3])
                threeInRowCB(keys,i);
            if(findThreeSimiliar(keys,&i) == 1)
                threeCB(keys,i);
                break;
        }

    }

}
int main(void)
{
    printf("Loop starting, you can stop the loop by pressing E\n");
    detect(cmpLastThreeSimiliar,threeSimiliar);
    return 0;
}
