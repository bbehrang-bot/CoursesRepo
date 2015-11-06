void fillRand3(int arr[],int size){
    int i=0;
    /*srand(time(NULL));*/
    for(i;i<size;i++){
    arr[i]=rand() %2;
    }
    int b[50]={0};


}
int checkRand3(int arr[],int size){
    int i =0;
    int out=1;
    for(i;i<size;i++){
        if(arr[i]!=0 || arr[i] !=1)
        {
            out = 0;
            break;
        }


    }
return out;
}
float meanValue(int arr[],int size){
    float avrg=0.0;
    int i=0;
    for(i;i<size;i++)
        avrg=avrg+arr[i];

    avrg=avrg/size;
return avrg;
}
int minValue(int arr[], int size){
int i=0;
int min=arr[i];
    for(i;i<size;i++)
     if(arr[i]<min)
        min = arr[i];
    return min;
}
int meanIndex(int arr[], int size){

   float avrg = meanValue(arr,size);

   float diff=fabs(avrg-arr[0]);
   int i=1;
   int index;
   for(i;i<size;i++)
   {
       if(fabs(avrg-arr[i])<diff)
    {
              diff= fabs(avrg-arr[i]);
              index=i;
   }
   }
   return index;
}
int minIndex(int arr[],int size){
int index=0;
int i=0;
int min = arr[i];
for(i;i<size;i++)
    if(arr[i]<min)
        {
            min=arr[i];
            index=i;
        }
return index;

}
int maxOccurance(int arr[], int size){
 int i=0;
 int j=0;
int answer=0;
 int occurances=1;
int index;
 int howMany[size];

 for(i;i<size;i++)
 {
      occurances=1;
     for(j=i+1;j<size;j++)
     {
         if(arr[i]==arr[j])
         {
            occurances++;
         }
     }
     howMany[i]=occurances;


 }

     /*2,4,2,1,1,1,1,1,1,1*/
     int maxOccur=howMany[0];
     answer=arr[0];
    for(i=1;i<size;i++)
    {
        if(howMany[i]>=maxOccur)
        {
            maxOccur=howMany[i];

        }
    }
     for(i=0;i<size;i++)
    {
        if(howMany[i]==maxOccur&&answer<arr[i])
        {
            answer=arr[i];

        }
    }

return answer;
}
int diff(int arr1[], int arr2[], int res[], int size)
{
    int i=0;
    int out=1;
    for(i;i<size;i++)
        res[i]=arr1[i]-arr2[i];

    for(i=0;i<size;i++)
    {
        if(res[i]!=0)
            out=0;
    }
    return out;
}
void sub(int arr1[], int arr2[], int res[], int size)
{
    int i=0;
    for(i;i<size;i++)
        res[i]=arr1[i]-arr2[2];
}
int eq(int arr1[], int arr2[], int size)
{
    int i=0;
    int isEqual=1;
    for(i;i<size;i++)
        if(arr1[i]!=arr2[i])
          isEqual=0;
    return isEqual;
}
void lxor(int arr1[], int arr2[], int res[], int size)
{
    int i=0;
    for(i;i<size;i++)
        res[i]= (arr1[i] ^ arr2[i]);
}