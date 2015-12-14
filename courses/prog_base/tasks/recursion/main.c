#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Sorry I was checking only the result of exam and totally forgot about this task
char lastChar(char *myStr,int i,char result)
{

    char l=myStr[i];
    i++;
    if(i<=strlen(myStr))
    {
    if(l>='a'&&l<='z')
    {
        result = l;
    }
    lastChar(myStr,i,result);
    }
    else
        return result;

}
int main()
{
    char v[100];
    char result;
    gets(v);
    char q =lastChar(v,0,'0');
    printf("%c",q);
    return 0;
}
