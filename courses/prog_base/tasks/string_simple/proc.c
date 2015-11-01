const char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr){
    int size= strlen(textLines);
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
            sprintf(index,"%i",i+1); /*if its number of line i+1 , if its the index i */
            strcat(resultStr,index);
            strcat(resultStr," ");
            strcat(resultStr,textLines[i]);
            strcat(resultStr,",");
        }
    }



return resultStr;
}
