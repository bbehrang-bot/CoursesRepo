#import <math.h>
double calc(double x, double y, double z) {
   double a;
  double n0 =5;
  double n1 = 2;
  double a0,a1,a2;

if(x-y<0||x+y==0||z+abs(x-y)==0||x-y==0||z==0)
{
    a = NAN;
}
else{
  a0 = pow(x,y+1)/pow(x-y,1/z);

  a1 = y/((n0+1)*abs(x+y));
  a2 = pow(n1+sin(y),cos(x)/z+abs(x-y))	;

     a=a0+a1+a2;
 }


   return a;
}