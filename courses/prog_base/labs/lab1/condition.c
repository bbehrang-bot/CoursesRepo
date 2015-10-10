int satisfies(int a, int b, int c)
{
    int result;
    int n0 = 5;
    int n1 = 2;
    int modmin;
    int sum2;
    if(a<0 && b<0 && c<0)
    {
        if(a<=b && a<=c)
        {

            modmin = abs(a);
            sum2 = b+c;
        }

        else if(b<=a && b<=c)
        {
            modmin = fabs(b);
            sum2=a+c;
        }

        else if(c<=a && c<=b)
        {
            modmin = abs(c);
            sum2 = a+b;
        }
        int modminP = modmin;
        int checkModmin;
        while (((modminP % 2) == 0))
        {
            modminP /= 2;
            if (modminP == 2)
                break;
        }
        if (modminP == 2)
        {
            checkModmin =1;
        }
        else
        {
            checkModmin=0;
        }

        if(sum2<-256&&checkModmin==1&&modmin<256)
        {
            result= 1;
        }
        else if(abs(sum2)>modmin && sum2>-256)
    {

        result= 1;
    }
    else result = 0;


}

 if ((int)(log2(modmin))%1==0) //2.4555


else if(a>=0 || b>=0||c>=0)
    {

        int d[3] = {a,b,c};
        int negativeCount=0;
        int negativeNums[2];
        int arrayC=0;
        int i;
        for(i = 0; i<3; i++)
        {

            if(d[i]<0)
            {
                negativeCount++;
                negativeNums[arrayC] = d[i];
                arrayC++;
            }
        }
        int max = d[0];
        int min = d[0];
         i =0;

        for(i = 1; i<3; i++)
        {

            if(d[i]>max)
            {
                max = d[i];

            }
        }

        for(i = 1; i<3; i++)
        {

            if(d[i]<min)
            {
                min = d[i];

            }
        }
        if(negativeCount==1)
        {
            if(negativeNums[0]>-256)
            {
                result = 1;

            }
            else
            {
                result= 0;
            }
        }
        else if(negativeCount==2)
        {

            int sumNegatives = (negativeNums[0]+negativeNums[1])*(n0+n1);
            if(sumNegatives>-256)
                result = 1;
            else result=0;
        }
        else if(negativeCount == 0)
        {

            if((max-min)>32)
                    result = 1;
                    else
                        result = 0;
            }

         else
            result = 0;

}

return result;
}
