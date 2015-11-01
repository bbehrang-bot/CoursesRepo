 char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr){



    int i=0;
    char h[100]={0};
    char ans[100];
    int j = 0;
    int counter=0;
    int howmany=0;


    for(i;i<linesNum;i++)
    {
        counter =0;
        for(j=0;j<strlen(textLines[i]);j++)
        {
            if (textLines[i][j] != ' '&&textLines[i][j] != '\0')
				counter++;

        }
        if(counter<10)
        {
            howmany++;
            strcat(resultStr,textLines[i]);
            strcat(resultStr,",");
        }
    }

    sprintf(h,"%i",howmany);
    strcpy(ans,h);
    strcat(ans," ");
    strcat(ans,resultStr);
    strcpy(resultStr,ans);





return resultStr;
}