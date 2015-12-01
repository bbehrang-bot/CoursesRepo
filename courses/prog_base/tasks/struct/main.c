#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include <ctype.h>
struct myStruct
{
    char fileName[100];
    //int chars;
    char myStr[100];
    char fileType[100];

};
/*void rint(struct myStruct * pVar)
{
  printf("file name is : %s, number of characters  are : %i, string stored in file is : %s \n",pVar->fileName,pVar->chars,pVar->myStr);
}
void hange(struct myStruct * pVar, const char * newValue)
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
int cont(int size, struct myStruct arr[size])
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
*/
void print(struct myStruct * pVar)
{
    printf("File name is: %s\nText written in file is: %s\nFile type is: %s\n",pVar->fileName,pVar->myStr,pVar->fileType);
}
int count(int size,struct myStruct arr[size])
{
    int count=0;
    int i;
    for(i=0;i<size;i++)
    {
        if(strcmp(arr[i].fileType,".txt")==0)
        {
            count++;
        }
    }
    return count;
}
void change(struct myStruct * pVar, const char * newValue)
{
    strcpy(pVar->fileName,newValue);

}

int main()
{
   // srand(time(NULL));
 //  struct myStruct st[3] ={{"file1.txt",5,"hello"},{"file1.doc",6,"hello1"},{"file1.mp3",7,"hello11"}};
     struct myStruct st[3] = {{"file1","hello",".txt"},{"file2","goodbye",".doc"},{"file3","good evening",".mp3"}};;




   int i;
   for(i=0;i<3;i++)
   print(&st[i]);


   printf("Number of txt files are : %i\n",count(3,st));
   int index=sizeof(st)/sizeof(st[0])+1;

   while(index>sizeof(st)/sizeof(st[0]))
   {
       printf("Enter element index you want to change\n");

       while(scanf("%d",&index)!=1)
      {
       while(!isspace(index=getchar()));
       ungetc(index,stdin);
       printf("Wrong value , make sure you are entering a number and its within the range\n");
       continue;

     };
   }
   char newName[100];
   printf("Enter new Name for your file : \n");
   scanf("%s",newName);
   change(&st[index],newName);

   print(&st[index]);
    return 0;
}
