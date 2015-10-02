int exec(int op, int a, int b) {
   int result;
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
        result=fmax(a,b)
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
        switch(abs(b)%8)){
        case 0 :
        {
            p =sizeof(char);
            break;
        }
         case 1 :
        {
            p =sizeof(signed char);
            break;
        }
         case 2 :
        {
            p =sizeof(short);
            break;
        }
         case 3 :
        {
            p =sizeof(unsigned int);
            break;
        }
         case 4 :
        {
            p =sizeof(long);
            break;
        }
         case 5 :
        {
            p =sizeof(unsigned long long);
            break;
        }
         case 6 :
        {
            p =sizeof(float);
            break;
        }
         case 7 :
        {
            p =sizeof(double);
            break;
        }

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