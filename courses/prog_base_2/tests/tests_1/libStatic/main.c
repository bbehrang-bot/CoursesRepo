#include <stdlib.h>
#include <stdio.h>
#include "VideoPlayer.h"

VIDEOPLAYER_STATUS videoPlayer_status = VIDEOPLAYER_NOT_INIT;
struct videoPlayer_s {
    int id;
   // film_t * filmArray[10];
   list_t list;
};
struct film_s{
    char filmName[100];
    int id;
};
film_t * film_new(char filmName[100],int id)
{
    film_t * self = malloc(sizeof(struct film_s));
    if(self==NULL)
        return;
    self->id = id;
    strcpy(self->filmName,filmName);
    return self;
}
videoPlayer_t * videoPlayer_new(int id){

    videoPlayer_t *  self = malloc(sizeof(struct videoPlayer_s));
    if(self==NULL)
    {
        videoPlayer_status = VIDEOPLAYER_NULL_PTR;
        return;
    }
    self->id = id;
    /*for(int i =0;i<10;i++)
    {
        self->filmArray[i] = film_new("",-1);
    }*/
    self->list = list_new();
    videoPlayer_status = VIDEOPLAYER_STOP;
    return self;
}
void videoPlayer_play(videoPlayer_t * vidPlayer,int index){
    printf("STARTING FILM : ");
    film_print(list_get_element(vidPlayer->list,index));
    printf("Press N to go next B to go back S to stop P to Pause O to(O P NOT WORKING NOW)\n");
    int status = 0;
    char pressed;
    for(;;){
        pressed = getch();

        if(pressed == 'n')
        {
            status = 1;
        }
        else if(pressed == 'b')
        {
            status = 2;
        }
        else if(pressed == 's')
        {
            status = 3;
        }
        if(status != 0)
            break;
        }
        if(status == 1)
        {
            videoPlayer_play(vidPlayer,index + 1);
        }
        if(status == 2)
        {
            videoPlayer_play(vidPlayer,index - 1);
        }
        if(status == 3)
        {
            puts("STOPPED");
        }


    }
void videoPlayer_add(videoPlayer_t * vidPlayer,film_t * film,int index)
{
    list_insert(vidPlayer->list,film,index);
}
void videoPlayer_free(videoPlayer_t * self){
    free(self);
}
void film_print(film_t * self){
    printf("%s %i\n",self->filmName,self->id);
}
void videoPlayer_print(videoPlayer_t * vidPlayer)
{
    int maxSize = list_get_size(vidPlayer->list);
     for(int i =0;i<maxSize;i++)
     {
         film_t * film = list_get_element(vidPlayer->list,i);
         film_print(film);
     }
}



/////////////////////////////////////////////////////



struct list_s
{
    film_t * filmArray[10];
    int size;
    int capacity;
};

list_t list_new()
{
    list_t self = (struct list_s*)malloc(sizeof(struct list_s));

    self->size = 0;
    self->capacity = MIN_CAPACITY;
    return self;
}

void list_delete(list_t list)
{
    free(list->filmArray);
    free(list);
}

/*static void increase_capacity(list_t list)
{
    int new_capacity = 2 * list->capacity;
    film * new_array = (int *)realloc(list->array, new_capacity * sizeof(int));
    list->filmArray = new_array;
    list->capacity = new_capacity;
}*/
static void shiftright(list_t list, int starting_index)
{
  // ERROR
    int end = list->size;
    for(int i = starting_index; i < end; i++)
    {
        film_t * temp = list->filmArray[i];
        film_t * prevtemp = list->filmArray[i + 1];
        list->filmArray[i + 1] = temp;
        temp = prevtemp;
    }
}
static void shiftleft(list_t list, int starting_index)
{
    int end = list->size - 1;
    for(int i = starting_index; i < end; i++)
        list->filmArray[i] = list->filmArray[i + 1];
}


//moves the value next
void list_insert(list_t list, film_t * film, int index)
{
    if(index > list->size || index < 0)
        return; // ERROR
    shiftright(list, index);
    list->filmArray[index] = film;
    list->size++;
}

void list_remove(list_t list, int index)
{
    if(index < 0 || index >= list->size)
        return; // ERROR
    shiftleft(list, index);
    list->size--;
}

int list_get_size(list_t list)
{
    return list->size;
}

int list_get_negcount(list_t list)
{
    int count = 0;
    int size = list->size;
    for(int i = 0; i < size; i++)
        if(list->filmArray[i] < 0)
            count++;
    return count;
}
int list_get_poscount(list_t list)
{
    int count = 0;
    int size = list->size;
    for(int i = 0; i < size; i++)
        if(list->filmArray[i] > 0)
            count++;
    return count;
}

int list_get_zerocount(list_t list)
{
    int count = 0;
    int size = list->size;
    for(int i = 0; i < size; i++)
        if(list->filmArray[i] == 0)
            count++;
    return count;
}

int list_get_element(list_t list, int index)
{
    if(index >= list->size || index < 0)
        return;
    return list->filmArray[index];
}
void list_print(list_t list){
    int size = list_get_size(list);
    for(int i =0;i<size;i++)
        film_print(list->filmArray[i]);


}

