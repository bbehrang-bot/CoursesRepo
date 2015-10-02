int exec(int op, int a, int b) {
   int result;
   int n0 = 5;
int n1 = 2;
   switch(op)
   {
   case 0:
   {
    result = -1*a;
    break;
   }
   case 1:
    {
        result=a+b;
        break;
    }
    case 2:
    {
        result=a-b;
        break;
    }
    case 3:
    {
        result=a*b;
        break;
    }
    case 4:
    {
        if(b==0)
            result = NAN;
        else
            result=a/b;
        break;
    }
    case 5:
    {
        result=abs(a);
        break;
    }
    case 6:
    {
        result=pow(a,b);
        break;
    }
    case 7:
    {
        result=a%b;
        break;
    }
    case 13:
    {
        result=a%b;
        break;
    }
    case 77:
    {
        result=a%b;
        break;
    }
    case 8:
    {
        result=fmax(a,b);
        break;
    }
    case 9:
    {
        result=fmin(a,b);
        break;
    }
    case 10:
    {
        int p=0;
        int q = abs(b)%8;
        if(q==0)

        {
            p =sizeof(char);

        }
        else if (q==1)

        {
            p =sizeof(signed char);

        }
         else if (q==2)

        {
            p =sizeof(short);

        }
        else if (q==3)

        {
            p =sizeof(unsigned int);

        }
          else if (q==4)

        {
            p =sizeof(long);

        }
         else if (q==5)

        {
            p =sizeof(unsigned long long);

        }
         else if (q==6)

        {
            p =sizeof(float);
            break;
        }
         else if (q==7)

        {
            p =sizeof(double);

        }


        return abs(a)*p;
        break;
    }
    case 11:
    {
        result= tan(a*M_PI) / ((n0-b)*n1+1);
        break;
    }
    default : {
    if(op<100){

     result = (op%abs(a+1)) + op%abs(b+1);
    }
    else if(op>=100)
        result = -1;

    }
break;
    }





   return result;
}
