#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char *tmp;
    tmp=malloc(100*sizeof(char));
    int *countLetters;
    int *countNumbers;
    countLetters = malloc(sizeof(int));
    countNumbers = malloc(sizeof(int));
    *countLetters = 0 ;
    *countNumbers = 0 ;
    gets(tmp);
    int *i;

    i = malloc(sizeof(int));

    *i=0;

    for((*i)=0;*i<strlen(tmp);(*i)++)
    {


        if(((tmp[*i]) >= 'a' && (tmp[*i])<='z') || ((tmp[*i]) >= 'A' && (tmp[*i])<='Z'))
        {
            (*countLetters)++;
        }

        else if (((tmp[*i])) >= '0' && (tmp[*i])<='9')
        {
            (*countNumbers)++;
        }

    }
    printf("Number of letters in your string is : %i\nNumber of numbers in your string is : %i",*countLetters,*countNumbers);
    return 0;
}
