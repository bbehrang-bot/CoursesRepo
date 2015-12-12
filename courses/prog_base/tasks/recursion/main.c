#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char lastChar(char *myStr,int i)
{
    char l=myStr[i];
    i++;
    if(i<=strlen(myStr))
    {
    if(myStr[i]=='\0')
        {
            if(l>='a'&&l<='z')
                return l;
            else
                return '0';        }
    else
        lastChar(myStr,i);
    }
}
int main()
{
    char v[100];
    gets(v);
    char q =lastChar(v,0);
    printf("%c",q);
    return 0;
}
