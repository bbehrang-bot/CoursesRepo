#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>
struct lessons{
    const char lessonName[100];
    float mark;

};
struct group{
    char name[100];
    struct lessons groupLessons[5];
};
struct student{
    char firstName[100];
    char lastName[100];
    int id;
    float averageGrades;
    struct group studentGroup;

};
void setpos(int *x , int *y)
{
    COORD pos={*x,*y};
    HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void setColor(WORD color)
{
    HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(cons,color);
}
void setBackground()
{
system("color F0");
}
void getKey(int studentsCount,struct student st[studentsCount])
{
    int entered=0;
    commands(0);
    int now=0;
    char v;
    while(1)
    {
    v=getch();
    v=getch();
    if(v==80)
    {
        now++;
    }
    else if(v==72)
    {
        now--;
    }
    else if(v!=13&&v!=80&&v!=72)
        v=getch();
    if(now>9)
        now=0;
    else if(now<0)
        now=9;
     commands(now);
     if(v==13)
    {
        setColor(63);
        system("cls");
        commands(now);
        setColor(240);
        entered=1;
        int x=0;int y=0;
        setpos(&x,&y);
        if(entered==1)
        {


        switch(now)
        {
        case 0:
            {

                printStudentList(studentsCount,st);
                entered=0;
                break;
            }
        case 1:
            {
                addStudent(studentsCount,st);
                entered=0;
                break;
            }
        case 2:
            {
                editStudent(studentsCount,st);
                entered=0;
                break;
            }
            case 3:
            {
                deleteStudent(studentsCount,st);
                entered=0;
                break;
            }
            case 4:
            {
                int index;
                editId(studentsCount,st,&index);
                int myIndex = goGetMyIndex(studentsCount,st,index);
                stdFull(&st[myIndex]);
                break;
            }
             case 5:
            {
                int index;
                editId(studentsCount,st,&index);
                int myIndex = goGetMyIndex(studentsCount,st,index);

                checkMarks(&st[myIndex]);
                entered=0;
                break;
            }
             case 6:
            {
                failedList(studentsCount,st);
                entered=0;
                break;
            }
             case 7:
            {

                whoGetsCholar(studentsCount,st);
                entered=0;
                break;
            }
            case 8:
            {

                getLessonName(studentsCount,st);
                entered=0;
                break;
            }
             case 9:
            {

                higs(studentsCount,st);
                entered=0;
                break;
            }


        }
    }
     }
    }


}
void comWindow()
{
    int x;
    int y;
    x=60;
    y=0;
    setpos(&x,&y);
    WORD v = 22;
    setColor(63);
    while(x<80&& y<70)
    {
        printf(" ");
        x++;
        if(x==79)
        {
            y++;
            x=60;
        }
        if(y==69)
        {
             int oi=1;
        }

       setpos(&x,&y);

    }



}
void fill(int y)
{

                int x=60;
                int maxY= y +4;
                setpos(&x,&y);
                setColor(191);

                while(x<80&& y<maxY)
                {
                printf(" ");
                x++;
                if(x==79)
                {
                    y++;
                    x=60;
                }
                 setpos(&x,&y);
                }
}

void commands(int start)
{

    int x=60;
    int y=0;
    char com[100];
    setBackground();
    comWindow();
    int i=0;
    for(i=0;i<10;i++)
    {
        setColor(63);
        if(i==start)
        {
            fill(4*i+1);
        }
        switch(i)
        {
            case 0:
            {
                y=2;
                x=62;
                setpos(&x,&y);
                printf("Get Student");
                break;
            }
            case 1:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Add student");
                    break;
                }
            case 2:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Edit student");
                    break;
                }
            case 3:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Delete student");
                    break;
                }
            case 4:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("View student");
                    break;
                }
                case 5:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Check Marks");
                    break;
                }
                case 6:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Success & Fails");
                    break;
                }
                case 7:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Scholar Status");
                    break;
                }
                case 8:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Lesson Average");
                    break;
                }
                case 9:
                {
                    y+=4;
                    setpos(&x,&y);
                    printf("Highest Mark");
                    break;
                }


        }
    }





}




void opSuccess()
{
    setColor(250);
    printf("\nOperation Completed,Navigate through menu for further\noperations");
    setColor(240);
}
void stdFull(struct student *st)
{
    printStruct(st);
    checkMarks(st);
    printScholar(st);
    cantContinueEDU(st);
}
void initLessonNames(struct student *st)
{



            if(strcmp(st->studentGroup.name,"kp-51") == 0)
           {
            strcpy(st->studentGroup.groupLessons[0].lessonName,"math");
            strcpy(st->studentGroup.groupLessons[1].lessonName,"physics");
            strcpy(st->studentGroup.groupLessons[2].lessonName,"chemistry");
            strcpy(st->studentGroup.groupLessons[3].lessonName,"history");
            strcpy(st->studentGroup.groupLessons[4].lessonName,"geography");
           }
           else if(strcmp(st->studentGroup.name,"kp-52") == 0)
           {
            strcpy(st->studentGroup.groupLessons[0].lessonName,"algebria");
            strcpy(st->studentGroup.groupLessons[1].lessonName,"physics");
            strcpy(st->studentGroup.groupLessons[2].lessonName,"chemistry");
            strcpy(st->studentGroup.groupLessons[3].lessonName,"informationtheory");
            strcpy(st->studentGroup.groupLessons[4].lessonName,"geography");
           }
           else if(strcmp(st->studentGroup.name,"kp-53") == 0)
           {
            strcpy(st->studentGroup.groupLessons[0].lessonName,"ukrainian");
            strcpy(st->studentGroup.groupLessons[1].lessonName,"discretemath");
            strcpy(st->studentGroup.groupLessons[2].lessonName,"geometry");
            strcpy(st->studentGroup.groupLessons[3].lessonName,"history");
            strcpy(st->studentGroup.groupLessons[4].lessonName,"english");
           }
           else
           {


            strcpy(st->studentGroup.groupLessons[0].lessonName,"Unknown(Check group name)");
            strcpy(st->studentGroup.groupLessons[1].lessonName,"Unknown(Check group name)");
            strcpy(st->studentGroup.groupLessons[2].lessonName,"Unknown(Check group name)");
            strcpy(st->studentGroup.groupLessons[3].lessonName,"Unknown(Check group name)");
            strcpy(st->studentGroup.groupLessons[4].lessonName,"Unknown(Check group name)");

            }

}
void readGroupFromFile(int studentsCount,struct student st[studentsCount])
{
    FILE * listFile;
    listFile = fopen("students.txt","r");
    int i;
    char lines[100];
    int maxStd = findLastStudent("students.txt");
    for(i=0;i<maxStd;i++)
    {
      fgets(lines,100,listFile);
      sscanf(lines,"%s %s %i %s %f %f %f %f %f",
            &st[i].firstName,
            &st[i].lastName,
            &st[i].id,
            &st[i].studentGroup. name,
            &st[i].studentGroup.groupLessons[0].mark,
            &st[i].studentGroup.groupLessons[1].mark,
            &st[i].studentGroup.groupLessons[2].mark,
            &st[i].studentGroup.groupLessons[3].mark,
             &st[i].studentGroup.groupLessons[4].mark
            );

            initLessonNames(&st[i]);
            calculateAvrg(&st[i]);
           // printStruct(&st[i]);


    }
    fclose(listFile);

}
void printStudentList(int studentsCount,struct student st[studentsCount])
{
    int i;
    int maxStd = findLastStudent("students.txt");
    for(i=0;i<maxStd;i++)
    {
         printStruct(&st[i]);

         printf("_________________________________________\n\n");


    }

}
void printStruct(struct student *st)
{
    printf("%s %s  \nStudent ID: %i  \nGroup: %s \n%s: %f \n%s: %f \n%s %f \n%s %f \n%s %f\n\n",st->firstName,
           st->lastName,
           st->id,
           st->studentGroup.name,
           st->studentGroup.groupLessons[0].lessonName,
           st->studentGroup.groupLessons[0].mark,
           st->studentGroup.groupLessons[1].lessonName,
           st->studentGroup.groupLessons[1].mark,
           st->studentGroup.groupLessons[2].lessonName,
           st->studentGroup.groupLessons[2].mark,
           st->studentGroup.groupLessons[3].lessonName,
           st->studentGroup.groupLessons[3].mark,
           st->studentGroup.groupLessons[4].lessonName,
           st->studentGroup.groupLessons[4].mark

           );



}
int findLastStudent(char *fileName)
{
    FILE * listFile;
    listFile = fopen(fileName,"r");
    int i;
    int linesCount=0;
    char lines[100];
    while(!feof(listFile))
    {
        fgets(lines,100,listFile);
         linesCount++;
    }
    fclose(listFile);
    return linesCount;



}
void getStudentMarks(struct student *st,int i)
{
        float mark;
        printf("Enter student's mark for %s :   ",st->studentGroup.groupLessons[i].lessonName);
        int state=0;
        while(state==0)
        {
            if(scanf("%f",&mark) != 1)
               {
                    state=0;
                    printf("Wrong value , make sure you are entering a number and its within [0,100]\n");
                   while (!isspace((float)(mark = getchar())));
                         ungetc(mark, stdin);
                    continue;
               }
             if(mark>100 || mark <0)
                {
                      state=0;
                      printf("Wrong value , make sure you are entering a number and its within [0,100]\n");
                      continue;
                }
            else if(mark<=100 && mark >=0 )
            {
                st->studentGroup.groupLessons[i].mark = mark;
                state=1;
                break;
            }


        }


    }
void getStudentId(struct student *st)
{

    printf("Enter student's ID:");


    while(scanf("%i",&st->id) != 1)
    {
         while (!isspace(st->id = getchar()));
              ungetc(st->id, stdin);
        printf("Wrong value , make sure you are entering a number\n");

    }



}
void checkIfIdexists(int studentsCount,struct student st[studentsCount],int index)
{
    int idExists=0;
    int idi=0;
    while(idExists==0)
    {
          getStudentId(&st[index]);
          int mm=st[index].id;
          for(idi=0;idi<studentsCount;idi++)
          {
              int cubid = st[idi].id;
                if(idi!=index)
                {
                    if(st[index].id==st[idi].id)
                    {
                        setColor(252);
                        printf("ID already exists,Try again\n");
                        setColor(240);
                        idExists=0;
                        break;
                    }
                    else
                        idExists=1;
                }
          }
    }
}
void editId(int studentsCount,struct student st[studentsCount],int *index)
{
    int idExists=0;
    int idi=0;
    int state=1;
    int last = findLastStudent("students.txt");
    while(idExists==0)
    {
         printf("Enter student's id:\n");
        while(scanf("%i",index) != 1)
            {
         while (!isspace(*index = getchar()));
              ungetc(*index, stdin);
               setColor(252);
            printf("Wrong value , make sure you are entering a number\n");
             setColor(240);

        }

          for(idi=0;idi<last;idi++)
          {
              int fk = st[idi].id;
                if(st[idi].id!=*index)
                {

                 state=0;
                }
                else
                {
                     idExists=1;
                     state=1;
                     break;
                }

          }
          if(state==0)
          {
               setColor(252);
              printf("ID not found\n");
               setColor(240 );
          }

    }
}
void getName(struct student *st)
{
    printf("Enter student's first name:");
    scanf("%s",&st->firstName);
}
void getLastName(struct student *st)
{
   printf("Enter student's lasr name:");
   scanf("%s",&st->lastName);

}
void getGroup(struct student *st)
{
    int state=0;
    printf("Choose Students group(Write the name without any spaces):\nkp-51\nkp-52\nkp-53\n");
    char tmpGroupNumber[100];
    scanf("%s",&tmpGroupNumber);
    while(state==0)
    {
        if((strcmp(tmpGroupNumber,"kp-51")==0 )|| (strcmp(tmpGroupNumber,"kp-52")==0 )||(strcmp(tmpGroupNumber,"kp-53")==0 ))
        {
            strcpy(st->studentGroup.name,tmpGroupNumber);
            state=1;
        }
        else
        {
             setColor(252);
             printf("Oops,something went wrong enter the group name again:\n");
             setColor(240);
             scanf("%s",&tmpGroupNumber);
        }
    }
}
void addStudent(int studentsCount,struct student st[studentsCount])
{
    int index =findLastStudent("students.txt");
    getName(&st[index]);
    getLastName(&st[index]);
    checkIfIdexists(studentsCount,st,index);
    getGroup(&st[index]);
    initLessonNames(&st[index]);
    getStudentMarks(&st[index],0);
    getStudentMarks(&st[index],1);
    getStudentMarks(&st[index],2);
    getStudentMarks(&st[index],3);
    getStudentMarks(&st[index],4);
    FILE *fileList;
    fileList = fopen("students.txt","r");
    FILE *filetmp;
    filetmp = fopen("studentsTmp.txt","w");
    if(fileList==NULL)
    {
        printf("FILE NOT FOUND");
    }
    int i;
    char tmp[100];
    for(i=0;i<index;i++)
    {
        fgets(tmp,100,fileList);
        fputs(tmp,filetmp);
    }
    fprintf(filetmp,"\n");
    fprintf(filetmp,"%s %s %i %s %f %f %f %f %f",st[index].firstName,
            st[index].lastName,
            st[index].id,
            st[index].studentGroup. name,
            st[index].studentGroup.groupLessons[0].mark,
            st[index].studentGroup.groupLessons[1].mark,
            st[index].studentGroup.groupLessons[2].mark,
            st[index].studentGroup.groupLessons[3].mark,
            st[index].studentGroup.groupLessons[4].mark
            );
            fclose(fileList);
            fclose(filetmp);

            fileList = fopen("students.txt","w");
            filetmp = fopen("studentsTmp.txt","r");
            for(i=0;i<=index;i++)
            {
            fgets(tmp,100,filetmp);
            fputs(tmp,fileList);
            }
            fclose(fileList);
            fclose(filetmp);

    calculateAvrg(&st[index]);

opSuccess();
}
int goGetMyIndex(int studentsCount,struct student st[studentsCount],int id)
{
    int i;
    for(i=0;i<studentsCount;i++)
    {
        if(st[i].id==id)
            return i;
    }

        printf("NOT FOUND");



}
void editStudent(int studentsCount,struct student st[studentsCount])
{

        int index;
        editId(studentsCount,st,&index);
        int myIndex= goGetMyIndex(studentsCount,st,index);
        setColor(241);
        printf("\nYou are now editing :\n%s %s with id of %d\n\n",st[myIndex].firstName,st[myIndex].lastName,st[myIndex].id);
          setColor(240);
        char whatToEdit[100];


        while(1)
        {
            printf("What do you want to edit?:\n\nname\tlastname\tid\tgroup\tmarks\n");
            scanf("%s",whatToEdit);
            if(strcmp(whatToEdit,"name")==0)
            {
                getName(&st[myIndex]);
                break;
            }
            else  if(strcmp(whatToEdit,"lastname")==0)
            {
                getLastName(&st[myIndex]);
                break;
            }

            else  if(strcmp(whatToEdit,"id")==0)
            {

            checkIfIdexists(studentsCount,st,myIndex);
                break;
            }
            else  if(strcmp(whatToEdit,"group")==0)
            {

               getGroup(&st[myIndex]);
               initLessonNames(&st[myIndex]);
               break;
            }
            else if(strcmp(whatToEdit,"marks")==0)
            {
                printf("which lesson mark do you want to edit?\n%s\t%s\t%s\t%s\t%s\n",
                       st[myIndex].studentGroup.groupLessons[0].lessonName,
                       st[myIndex].studentGroup.groupLessons[1].lessonName,
                       st[myIndex].studentGroup.groupLessons[2].lessonName,
                       st[myIndex].studentGroup.groupLessons[3].lessonName,
                       st[myIndex].studentGroup.groupLessons[4].lessonName);
                       char tmpLessonName[100];
                       int i;
                       int state=0;
                       while(state==0)
                       {
                            scanf("%s",tmpLessonName);


                        for(i=0;i<5;i++)
                        {
                        if(strcmp(tmpLessonName,st[myIndex].studentGroup.groupLessons[i].lessonName)==0)
                        {
                           getStudentMarks(&st[myIndex],i);
                           state=1;
                           break;
                        }
                        }
                        if(state==1)
                            break;
                            setColor(252);
                         printf("Lesson not found\n");
                         setColor(240);

                        }
                        if(state==1)
                            break;

            }
            else
            {

                setColor(252);
                printf("Command not found try again\n");
                setColor(240);
            }

        }
        FILE * fileList;
        FILE * fwriteme;
        fileList = fopen("students.txt","r");
        fwriteme = fopen("studentsTmp.txt","w");
        int lastStudentis = findLastStudent("students.txt");
        int i;
        char read[100];

        for(i=0;i<myIndex;i++)
        {

            fgets(read,100,fileList);
            fputs(read,fwriteme);


        }

           fprintf(fwriteme,"%s %s %i %s %f %f %f %f %f",st[myIndex].firstName,
            st[myIndex].lastName,
            st[myIndex].id,
            st[myIndex].studentGroup. name,
            st[myIndex].studentGroup.groupLessons[0].mark,
            st[myIndex].studentGroup.groupLessons[1].mark,
            st[myIndex].studentGroup.groupLessons[2].mark,
            st[myIndex].studentGroup.groupLessons[3].mark,
            st[myIndex].studentGroup.groupLessons[4].mark
            );
         if(myIndex!=lastStudentis-1)
            fprintf(fwriteme,"\n");

        myIndex++;
        fgets(read,100,fileList);
        for(i=myIndex;i<lastStudentis;i++)
        {
            if(!feof(fileList))
            {
            fgets(read,100,fileList);
            fputs(read,fwriteme);
            }


        }
        fclose(fileList);
        fclose(fwriteme);
        fileList = fopen("students.txt","w");
        fwriteme = fopen("studentsTmp.txt","r");
        for(i=0;i<lastStudentis;i++)
        {
            fgets(read,100,fwriteme);
            fputs(read,fileList);
        }
         fclose(fileList);
        fclose(fwriteme);
        opSuccess();
        readGroupFromFile(studentsCount,st);






}
void deleteStudent(int studentsCount,struct student st[studentsCount])
{

        int index;
        editId(studentsCount,st,&index);
        int myIndex= goGetMyIndex(studentsCount,st,index);
        FILE * fileList;
        FILE * fwriteme;
        fileList = fopen("students.txt","r");
        fwriteme = fopen("studentsTmp.txt","w");
        int lastStudentis = findLastStudent("students.txt");
        int i;
        char read[100];

        for(i=0;i<lastStudentis;i++)
        {
            if(!feof(fileList))
            {
            if(i!=myIndex)
            {
                fgets(read,100,fileList);
                fputs(read,fwriteme);
            }
                else
                    fgets(read,100,fileList);
            }
        }
        fclose(fileList);
        fclose(fwriteme);
        fileList = fopen("students.txt","w");
        fwriteme = fopen("studentsTmp.txt","r");
        for(i=0;i<lastStudentis-1;i++)
        {
            if(!feof(fwriteme))
            {

            fgets(read,100,fwriteme);
            if(i==lastStudentis-2)
            {
            int px = strlen(read);
             char p = read[strlen(read)-1];
             read[strlen(read)-1]='\0';
             int okok=3;
            }
            fputs(read,fileList);
            }

        }

        fclose(fileList);
        fclose(fwriteme);
        opSuccess();
        readGroupFromFile(studentsCount,st);

}
void calculateAvrg(struct student *st)
{

    double avrg = (st->studentGroup.groupLessons[0].mark +
                   st->studentGroup.groupLessons[1].mark +
                   st->studentGroup.groupLessons[2].mark +
                   st->studentGroup.groupLessons[3].mark +
                   st->studentGroup.groupLessons[4].mark ) /5;

    st->averageGrades = avrg;

}
int checkMarks(struct student *st)
{
            int fails=0;
            char state[10];
            int i,j;
            printf("%s %s from group %s :\n",st->firstName,st->lastName,st->studentGroup.name);

            for(j=0;j<5;j++)
            {
            if(st->studentGroup.groupLessons[j].mark<60)
            {
                 strcpy(state,"Failed");
                 setColor(252);
                 fails++;
            }
            else
            {
                strcpy(state,"Passed");
                setColor(250);
            }

            printf("%s %s\n",state,st->studentGroup.groupLessons[j].lessonName);
            setColor(240);
            }

            return fails;

}
int incheckMarks(struct student *st)
{
            int fails=0;
            char state[10];
            int i,j;

            for(j=0;j<5;j++)
            {
            if(st->studentGroup.groupLessons[j].mark<60)
            {

                 fails++;
            }


            }

            return fails;

}
void printScholar(struct student *st)
{
    int Scholar = checkScholar(st);
    if(Scholar==1)
    {
        setColor(250);
        printf("%s %s from group %s gets scholarship\n\n",st->firstName,st->lastName,st->studentGroup.name);
        setColor(240);
    }
    else
    {
        setColor(252);
        printf("%s %s from group %s doesnt get scholarship\n\n",st->firstName,st->lastName,st->studentGroup.name);
        setColor(240);
    }

}
int checkScholar(struct student *st)
{
   if(st->averageGrades>=95)
    return 1;
   else
    return 0;
}
void whoGetsCholar(int studentsCount,struct student st[studentsCount])
{
    int i,max=findLastStudent("students.txt");
    for(i=0;i<max;i++)
    {
        printScholar(&st[i]);
    }
}
void cantContinueEDU(struct student *st)
{
    int fails  = incheckMarks(st);
    if(fails>=3)
    {
         setColor(252);
         printf("%s %s from group %s\nhas failed %i lessons\nand cannot continue to next Semester\n\n",st->firstName,st->lastName,st->studentGroup.name,fails);
         setColor(240);
    }
    else
    {
         setColor(250);
         printf("%s %s from group %s\nhas failed only %i lesson(s)\nand can continue to next Semester\n\n",st->firstName,st->lastName,st->studentGroup.name,fails);
         setColor(240);
    }

}
void failedList(int studentsCount,struct student st[studentsCount])
{
    int i,max=findLastStudent("students.txt");
    for(i=0;i<max;i++)
    {
        cantContinueEDU(&st[i]);
    }
}
void getLessonName(int studentsCount,struct student st[studentsCount])
{
    int state=0;
    int lessonFound=0;
    int i,j;
    int count=0;
    float avrg=0;
    int max = findLastStudent("students.txt");
    printf("Write lesson's name\n");
    char lessonName[100];
    scanf("%s",&lessonName);
    while(state==0)
    {
         for(i=0;i<max;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(strcmp(st[i].studentGroup.groupLessons[j].lessonName,lessonName)==0)
                    {
                        lessonFound=1;
                        count++;
                        avrg+=st[i].studentGroup.groupLessons[j].mark;
                    }
                }

            }
            if(lessonFound==1)
            {
                avrg=avrg/count;
                printf("Average mark of %s is %f\n",lessonName,avrg);
                state=1;
            }
            else
            {
             setColor(252);
             printf("Lesson not found try Again:\n");
             setColor(240);
             scanf("%s",&lessonName);
            }
    }
}
void higs(int studentsCount,struct student st[studentsCount])
{
        float maxMark=0;
        int i,j;
        int state=0;
        printf("Enter Lesson's name:\n");
        int max = findLastStudent("students.txt");
        int lessonFound=0;
        char lessonName[100];
         scanf("%s",&lessonName);
        while(state==0)
        {
         for(i=0;i<max;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(strcmp(st[i].studentGroup.groupLessons[j].lessonName,lessonName)==0)
                    {
                        lessonFound=1;
                    }
                }
            }
            if(lessonFound==1)
            {
                state=1;
            }
            else
        {
             setColor(252);
             printf("Lesson not found try Again:\n");
             setColor(240);
             scanf("%s",&lessonName);
        }
    }
    char result[200];
    strcpy(result,"");
            for(i=0;i<max;i++)
            {

                for(j=0;j<5;j++)
                {
                    if((strcmp(st[i].studentGroup.groupLessons[j].lessonName,lessonName)==0) && st[i].studentGroup.groupLessons[j].mark>maxMark)
                    {
                        strcpy(result,"");
                        lessonFound=1;
                        maxMark=st[i].studentGroup.groupLessons[j].mark;
                        strcat(result,st[i].firstName);
                        strcat(result," ");
                        strcat(result,st[i].lastName);

                    }
                    else if((strcmp(st[i].studentGroup.groupLessons[j].lessonName,lessonName)==0) && st[i].studentGroup.groupLessons[j].mark==maxMark)
                    {
                        strcat(result,"\n");
                        strcat(result,st[i].firstName);
                        strcat(result," ");
                        strcat(result,st[i].lastName);
                    }
                }
            }
             strcat(result,"\nHave(s) the highest Mark in ");
                        strcat(result,lessonName);
                        strcat(result,"\nwith the score of:");
                        printf("%s %f",result,maxMark);


}
int main()
{
    //int y;
    //printf("%i",giveNumberFromString("123a"));
    struct student s[100];
    readGroupFromFile(100,s);
   // higs(100,s);
    getKey(100,s);
   //readGroupFromFile(100,s);
   //addStudent(100,s);
   //editStudent(100,s);
    //  deleteStudent(100,s);



    return 0;
}
