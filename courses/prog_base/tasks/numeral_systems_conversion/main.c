#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int sizeBeforeFrac(char* number)
{
    int i=0;
    int countBeforeFraction=0;
    while(number[i]!='\0')
    {
        if(number[i]!='.')
            countBeforeFraction++;
        else
            break;
    i++;
    }
    return countBeforeFraction;
}

int sizeAfterFrac(char* number)
{
    int i=sizeBeforeFrac(number)+1;

    int countAfterFraction=0;
    while(number[i]!='\0')
    {
        countAfterFraction++;
        i++;
    }
    return countAfterFraction;
}
int giveMeInt(char myChar)
{

        if(myChar>='0'&&myChar<='9')
            return myChar - '0';
        else if(myChar>='a'&&myChar<='z')
            return myChar - 87;
        else if(myChar>='A'&&myChar<='Z')
            return myChar - 55;
        else
            return -1;

}
char giveMeChar(long long int myInt)
{
    if(myInt<10)
    {

        return myInt + '0';
    }
    else
    {

         return myInt + 55;
    }
}
void initBeforeFrac(int size,int bfrac[size],char* number)
{
    int i=0;
    int j=0;
    while(number[i]!='\0'&&number[i]!='.')
    {
        if(number[i]>='0' && number[i] <= '9')
        {
            bfrac[j]=number[i]-'0';
            j++;
            i++;
        }
        else if(number[i]>='a' && number[i] <= 'z')
        {
            bfrac[j]=number[i]-87;
            j++;
            i++;

        }
        else if(number[i]>='A' && number[i] <= 'Z')
        {
            bfrac[j]=number[i]-55;
            int tmp=bfrac[j];
            j++;
            i++;

        }

    }
}
void initAfterFrac(int size,double afrac[size],char* number)
{
    int i=sizeBeforeFrac(number)+1;
    int j=0;
    while(number[i]!='\0'&&number[i]!='.')
    {
        if(number[i]>='0' && number[i] <= '9')
        {
            afrac[j]=number[i]-'0';
            double tmp = afrac[j];
            j++;
            i++;
        }
        else if(number[i]>='a' && number[i] <= 'z')
        {
            afrac[j]=number[i]-87;
            j++;
            i++;

        }
        else if(number[i]>='A' && number[i] <= 'Z')
        {
            afrac[j]=number[i]-55;
            j++;
            i++;

        }

    }
}
int checkTask(char* number, unsigned int sourceBase, unsigned int destBase)
{
    int i=0;
    while(number[i]!='\0')
    {
        if(number[i]!='.')
           {
         if(giveMeInt(number[i])>=sourceBase || giveMeInt(number[i])==-1 )
            {

                return -1;
                break;
            }
        else if(number[i]=='-')
        {
            return -1;
                break;
        }
           }
            i++;

    }
    return 1;
}
char* ns_convert(char* number, unsigned int sourceBase, unsigned int destBase)
{
    if(checkTask(number,sourceBase,destBase)==-1)
        return '\0';
    int isFraction=0;
    int countAfterFrac=0;
    long long int inBaseTen=0;
    double inBaseTenFraction=0;
    double multiply,power;
    int countBeforeFrac = sizeBeforeFrac(number);
    int bFrac[countBeforeFrac];

    initBeforeFrac(countBeforeFrac,bFrac,number);
    int i=0;
    for(i=countBeforeFrac-1;i>=0;i--)
    {
         power = pow(sourceBase,countBeforeFrac-1-i);
         multiply = power*bFrac[i];
         //bFrac[i]=multiply;
         inBaseTen+=multiply;
    }
    int resultDigits=0;
    long long int tmpInBTen=inBaseTen;
    while(tmpInBTen>=destBase)
    {
        tmpInBTen/=destBase;
        resultDigits++;
    }
    resultDigits++;
    int ssize = resultDigits+countAfterFrac;
    char resultBFraction[ssize];
    strcpy(resultBFraction,"");
    tmpInBTen=inBaseTen;
    char tmpG[2];
    tmpG[1]='\0';
    for(i=0;i<resultDigits;i++)
    {
        if(i==resultDigits-1)
        {
            tmpG[0]=giveMeChar(tmpInBTen);
            strcat(resultBFraction,tmpG);
            break;
        }
         tmpG[0]=giveMeChar(tmpInBTen%destBase);
         strcat(resultBFraction,tmpG);
        tmpInBTen/=destBase;
    }
    strrev(resultBFraction);

if (countBeforeFrac!=strlen(number))
    {
        tmpG[0]='.';
        strcat(resultBFraction,tmpG);
        isFraction=1;
        countAfterFrac=sizeAfterFrac(number);
        double aFrac[countAfterFrac];
        initAfterFrac(countAfterFrac,aFrac,number);
        int j;
        for(j=0;j<countAfterFrac;j++)
        {
            power = pow(sourceBase,-1*(j+1));
            multiply = power*aFrac[j];
           // aFrac[j]=multiply;
           inBaseTenFraction+=multiply;
        }
         for(j=0;j<12;j++)
        {
            inBaseTenFraction*=destBase;
            int result =(int)inBaseTenFraction;
            tmpG[0]=giveMeChar(result);
            strcat(resultBFraction,tmpG);
            inBaseTenFraction-=result;

        }



    }


    number=resultBFraction;
    printf("%s",number);
    return number;

}
int main() {
    char *s=ns_convert("-1", 2  , 3);

    return 0;
}


