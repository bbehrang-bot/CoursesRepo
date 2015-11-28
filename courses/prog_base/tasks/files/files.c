void fprocess(const char * pread, const char * pwrite)
{
    FILE * fpr;
    fpr = fopen(pread,"r");
     if (NULL == fpr) {
        puts("Error!");
        return EXIT_FAILURE;
    }
    char a[2];
    a[0]=fgetc(fpr);
    a[1]='\0';
    int line=0;
    int count=1;
    int lineLength=0;
    char q;
    char *tmp;
    while(1)
    {
        if(line==24)
        {

            while(a[0]!=EOF)
            {
                lineLength++;
                q= a[0];
                a[0]=fgetc(fpr);

            }
            tmp=malloc(lineLength);
            strcpy(tmp,"");
            fseek(fpr,-lineLength,SEEK_END);
            fgets(tmp,lineLength+1,fpr);
            break;
        }
        if(a[0]=='\n')
        {
            line++;

        }


        a[0]=fgetc(fpr);
    }


    fclose(fpr);
    FILE *result;
    result = fopen(pwrite,"w");
    fprintf(result,tmp);
    free(tmp);


}