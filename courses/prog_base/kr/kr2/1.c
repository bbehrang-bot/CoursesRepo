#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void reverseStr(char *freading,char *fwriting)
{

    FILE *fr;
    fr = fopen(freading,"r");
    if(fr==NULL)
    {
        printf("FILE NOT FOUND\n");
        return EXIT_FAILURE;
    }
    char myStr[100];
    fgets(myStr,100,fr);
    fclose(fr);
    int size = strlen(myStr);
    char tmp[size+1];
    char tmpResult[size+1];
    char end[2];
    end[1]='\0';
    strcpy(tmp,"");
    int i=0;
    int j =0;
    for(i=size-1;i>=0;i--)
    {
        if((myStr[i]>='a'&&myStr[i]<='z')||(myStr[i]>='A'&&myStr[i]<='Z')||(myStr[i]>='0' &&myStr[i]<='9')||(myStr[i]==' '))
        {
            end[0]=myStr[i];
            strcat(tmp,end);

        }
    }
    FILE *fo;
    fo=fopen(fwriting,"w");
    fputs(tmp,fo);
    fclose(fo);
    return EXIT_SUCCESS;

}
int main()
{
    reverseStr("str.txt","result.txt");
    //struct film filmTest;
    //struct film filmSecond;
   // struct director d1;
   // filmTest.filmDirector=&d1;
    //dynamicAllocDirector(&d1);
   // freeFilm(&filmTest);
    //dynamicAllocFilm(&filmTest);
    //dynamicAllocFilm(&filmSecond);
    //initiateFilm(&filmTest);
    //getFilm(&filmTest);
    //printFilm(&filmTest);
    //getFilm(&filmSecond);
    //printFilm(&filmSecond);
    //checkSellBudget()
    return 0;
}