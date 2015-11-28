#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void readFile(char *input)
{
    FILE * fp;
    fp = fopen(input,"r");
    if(NULL == fp)
    {
         puts("error");
    }
    char *tmp;
    tmp = malloc(256);
    strcpy(tmp,"");
 char v[2];
    v[1]='\0';
    v[0]=fgetc(fp);
    int i =0;
    int indexString=0;
    FILE * tmpFP;
    char b[255]={0};
    while(1)
    {
        if(v[0]==EOF)
        {
            sprintf(b,"%i.txt",i);
            tmpFP = fopen(b,"w");
            fprintf(tmpFP,tmp);
            strcpy(tmp,"");
            fclose(tmpFP);
            break;
        }
        if(v[0]!= '\n')
        {
        strcat(tmp,v);

        v[0]=fgetc(fp);
        }
        else
        {

            sprintf(b,"%i.txt",i);
            tmpFP = fopen(b,"w");
            fprintf(tmpFP,tmp);
            v[0]=fgetc(fp);
            strcpy(tmp,"");
            fclose(tmpFP);
            i++;


        }


    }
    fclose(fp);


}
int main()
{
    readFile("input.txt");
    return 0;
}
