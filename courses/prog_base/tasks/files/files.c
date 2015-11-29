#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void fprocess(const char * pread, const char * pwrite)
{
    FILE * fpr;
    fpr = fopen(pread,"r");
     if (NULL == fpr) {
        puts("Error!");
        return EXIT_FAILURE;
    }
    char a[2];
    a[0]=fgetc(fpr);
    a[1]='\0';
    int line=0;
    int count=1;
    int lineLength=0;
    char q;
    char *tmp;
    while(1)
    {
        if(line==24)
        {

            while(a[0]!=EOF)
            {
                lineLength++;
                a[0]=fgetc(fpr);

            }
            int s = lineLength*sizeof(char);
            tmp=malloc(lineLength*sizeof(char));
            strcpy(tmp,"");
            fseek(fpr,-lineLength-1,SEEK_END);
            fgets(tmp,lineLength,fpr);
            break;
        }
        if(a[0]=='\n')
        {
            line++;

        }


        a[0]=fgetc(fpr);
    }

    int i;
    char *tmpResult;
    int g = lineLength*sizeof(char);
    tmpResult = malloc(lineLength*sizeof(char));
    strcpy(tmpResult,"");
    for(i=0;i<strlen(tmp);i++)
    {


        a[0]=tmp[i];
        strcat(tmpResult,a);
        strcat(tmpResult," ");


    }
    fclose(fpr);
    FILE *result;
    result = fopen(pwrite,"w");


    fprintf(result,"%s",tmpResult);








}

int main(void) {

    fprocess("1.txt","result.txt");

    return 0;
}
