const char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr){

    char h[100];
    char *index;
    int i=0;
    int j = 0;
    int counter=0;
    const char blank = ' ';
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
            char c[100]={0};
            sprintf(c,"%i",i+1);
            strcat(h,c);
            strcat(h," ");
            strcat(h,textLines[i]);
            strcat(h,",");
        }
    }

strcat(resultStr,h);

return resultStr;
}