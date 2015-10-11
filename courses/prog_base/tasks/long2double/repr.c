#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double long2double(long long x){
int i = 1;
    double b[64]={0};
    double sign=0;
    double exp=0;
    double fr=0;
    double answer;
     double nLong = x;
    i=0;
if(x<0){
    x=fabs(x);
    x=x-1;
    b[0]=1;

}
else
    b[0]=0;

    while(x!=0){

        b[i]=x%2;
        x=x/2;
        i++;
    }
     if(nLong<0){

        for(i=1;i<64;i++){
            if(b[i]==0){
                b[i]=1;

            }
            else if(b[i]==1){
                b[i]=0;
            }
        }
    }
    double c[64] = {0};
    for(i=1;i<64;i++){
        c[63-i]=b[i];

    }



    if(c[0]==1)
        sign = -1;
    else
        sign= 1;


     for(i=1;i<=11;i++){


        exp = exp + c[i]*(pow(2,11-i));

     }
     int j = -1;
     for(i=12;i<=63;i++){


        fr = fr+ c[i] * (pow(2,j));
        j=j-1;

     }

     if(exp==2047&&fr!=0)
        answer =NAN;
     else if(exp==2047&&fr==0&&sign==1)
        answer = INFINITY;
     else if(exp==2047&&fr==0&&sign==-1)
        answer = -INFINITY;
     else if(exp>0&&exp<2047)
         answer = sign*(pow(2,exp-1023))*(1+fr);
     else if(exp=0&&fr!=0)
        answer = sign*pow(2,-1022)*fr;
     else if(exp=0&&fr==0&&sign==-1)
        answer = -0;
     else if(exp==0&&fr==0&&sign==1)
        answer =+0;


    return answer;

}
int main()
{

  double p = long2double(-4620000000000000000);





   printf("%.325lf",p);
    return 0;
}
