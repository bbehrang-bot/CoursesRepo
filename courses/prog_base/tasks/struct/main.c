#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
struct myStruct
{
    char fileName[100];
    int chars;
    char myStr[100];

};
void print(struct myStruct * pVar)
{
    printf("file name is : %s, number of characters  are : %i, string stored in file is : %s \n",pVar->fileName,pVar->chars,pVar->myStr);
}
int count(int size, struct myStruct arr[size])
{
int i=0;
int j=0;
int k=0;
int count =0;
char *tmp;
tmp = malloc(256);
strcpy(tmp,"");
char tmpChar[2];
tmpChar[1]='\0';
int length;
int letters=0;
for(i;i<size;i++)
{
   j=0;
   letters=0;
   length=strlen(arr[i].fileName);
   while(arr[i].fileName[j]!='.')
   {
    letters++;
    j++;
   }


    for(k=0;k<length-letters;k++)
    {
        tmpChar[0]= arr[i].fileName[j];
        strcat(tmp,tmpChar);
        j++;
    }
    if(strcmp(tmp,".txt")==0)
    {
        count++;
    }
    strcpy(tmp,"");

}
free(tmp);
return count;
}

void change(struct myStruct * pVar, const char * newValue)
{

 int i=0;
int j=0;
int k=0;
int count =0;
char *tmp;
char *fileqw;
tmp = malloc(256);
fileqw=malloc(256);
strcpy(tmp,"");
char tmpChar[2];
tmpChar[1]='\0';
char ty[20];
int length;
int letters=0;

   j=0;
   letters=0;

   length=strlen(pVar->fileName);
   while(pVar->fileName[j]!='.')
   {

    letters++;
    j++;
   }


    for(k=0;k<length-letters;k++)
    {
        tmpChar[0]= pVar->fileName[j];
        strcat(tmp,tmpChar);
        j++;
    }

    strcpy(fileqw,"");
    strcpy(fileqw,newValue);
    strcat(fileqw,tmp);

    strcpy(pVar->fileName,fileqw);
    free(tmp);
    free(fileqw);



}
int main()
{
    srand(time(NULL));
   struct myStruct st[3] ={{"file1.txt",5,"hello"},{"file1.doc",6,"hello1"},{"file1.mp3",7,"hello11"}};




   int i;
   for(i=0;i<3;i++)
    print(&st[i]);


    printf("Number of txt files are : %i",count(3,st));
    int index;
    scanf("%i",&index);
    change(&st[index],"alireza");

    printf(&st[index]);
    return 0;
}
