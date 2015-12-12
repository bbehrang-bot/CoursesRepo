#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
struct director
{
    char name[100];
    int films;
};
struct film
{
    char name[100];
    int budget;
    int sell;
    struct director *filmDirector;
};
void initiateDirector(struct director *cinemaDirector)
{
    cinemaDirector->films=0;
    strcpy(cinemaDirector->name,"");
}
void initiateFilm(struct film *cinemaFilms)
{
    strcpy(cinemaFilms->name,"");
    cinemaFilms->budget=0;
    cinemaFilms->sell=0;
    initiateDirector(cinemaFilms->filmDirector);
}
void getDirector(struct director *cinemaDirector)
{
    printf("Enter director name:\n");
    char q[100];
    scanf("%s",q);
    strcpy(cinemaDirector->name,q);
    printf("How many films he created :\n");
    scanf("%i",&(cinemaDirector->films));
}
void getFilm(struct film *cinemaFilms)
{
    printf("Enter film name:\n");
    char q[100];
    scanf("%s",q);
    strcpy(cinemaFilms->name,q);
    printf("Enter film budget:\n");
    scanf("%i",&(cinemaFilms->budget));
    printf("Enter film sell:\n");
    scanf("%i",&(cinemaFilms->sell));
    getDirector(cinemaFilms->filmDirector);
}
struct director * dynamicAllocDirector()
{
        struct director *x = malloc(sizeof *x);
        return x;
}
struct film * dynamicAllocFilm()
{
        //dynamicAllocDirector(cinemaFilm->filmDirector);
        struct director *x = malloc(sizeof *x);
        return x;
}
void freeDirector(struct director *cinemaDirector)
{
    free(cinemaDirector);
}
void freeFilm(struct film *cinemaFilm)
{
    freeDirector(cinemaFilm->filmDirector);
    free(cinemaFilm);
}
void printDirector(struct director *cinemaDirector)
{
    printf("director name is:\n");
    printf("%s\n",cinemaDirector->name);
    printf("amount of films he created:\n");
    printf("%i\n",cinemaDirector->films);
}
void printFilm(struct film *cinemaFilm)
{
    printf("Film name is :\n");
    printf("%s\n",cinemaFilm->name);
    printf("Film budget is:\n");
    printf("%i\n",cinemaFilm->budget);
    printf("film sold :\n");
    printf("%i\n",cinemaFilm->sell);
    printDirector(cinemaFilm->filmDirector);

}
void printArrayFilm(int size,struct film cinemaFilm[size])
{
    int i=0;
    for(i;i<size;i++)
        printFilm(&cinemaFilm[i]);
}
void checkSellBudget(int size,struct film cinemaFilm[size])
{
    int i=0;
    for(i=0;i<size;i++)
    {
    if((cinemaFilm[i].sell>3*cinemaFilm[i].budget) &&(cinemaFilm[i].filmDirector->films >10))
        printFilm(&cinemaFilm[i]);
    }
}
int compareDirectors(struct director *cinemadirFirst,struct director *cinemadirSecond)
{
        if(strcmp(cinemadirFirst->name,cinemadirSecond->name)==0)
            if(cinemadirFirst->films==cinemadirSecond->films)
                return 1;
        else
            return 0;
}
int compareFilms(struct film *cinemaFilmFirst,struct film *cinemaFilmSecond)
{
    if(strcmp(cinemaFilmFirst->name,cinemaFilmSecond->name)==0)
          if(cinemaFilmFirst->budget==cinemaFilmSecond->budget)
            if(cinemaFilmFirst->sell==cinemaFilmSecond->sell)
                return 1;
        else
            return 0;
}

void reverseStr(char *freading,char *fwriting)
{
    FILE *fr;
    fr = fopen(freading,"r");
    if(fr==NULL)
    {
        printf("FILE NOT FOUND\n");
        return EXIT_FAILURE;
    }
    char myStr[100];
    fgets(myStr,100,fr);
    fclose(fr);
    int size = strlen(myStr);
    char tmp[size+1];
    char tmpResult[size+1];
    char end[2];
    end[1]='\0';
    strcpy(tmp,"");
    int i=0;
    int j =0;
    for(i=size-1;i>=0;i--)
    {
        if((myStr[i]>='a'&&myStr[i]<='z')||(myStr[i]>='A'&&myStr[i]<='Z')||(myStr[i]>='0' &&myStr[i]<='9')||(myStr[i]==' '))
        {
            end[0]=myStr[i];
            strcat(tmp,end);

        }
    }
    FILE *fo;
    fo=fopen(fwriting,"w");
    fputs(tmp,fo);
    fclose(fo);
    return EXIT_SUCCESS;

}
int main()
{
    //reverseStr("str.txt","result.txt");
    //struct film filmTest;
    //struct film filmSecond;
   // struct director d1;
   // filmTest.filmDirector=&d1;
    //dynamicAllocDirector(&d1);
   // freeFilm(&filmTest);
    //dynamicAllocFilm(&filmTest);
    //dynamicAllocFilm(&filmSecond);
    //initiateFilm(&filmTest);
    //getFilm(&filmTest);
    //printFilm(&filmTest);
    //getFilm(&filmSecond);
    //printFilm(&filmSecond);
    //checkSellBudget()
    return 0;
}
