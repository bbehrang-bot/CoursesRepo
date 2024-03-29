#include "intlist.h"
intList_t intList_new()
{
    int * arr = malloc(DEFAULT_LIST_CAP * sizeof(int));
    intList_t newList = malloc(sizeof(struct intList_s));
    newList->arr = arr;
    newList->size = 0;
    newList->capacity = DEFAULT_LIST_CAP;
    return newList;
}
void intList_destructor(intList_t list)
{
    free(list->arr);
    free(list);
}
void intList_increse_capacity(intList_t list)
{
    int capacity = 2 * list->capacity ;
    int * arr2 = realloc(list->arr,capacity*sizeof(int));
    list->arr = arr2;
    list->capacity = capacity;
}
int intList_getSize(intList_t list)
{
    int size = list->size;
    return list->size;
}
void intList_add(intList_t list,int value, int index)
{
    int mySize = list->size;
    int cap = list->capacity;
    if(index> list->size || index<0)
        return;
    int i=index;
    if(list->size >= list->capacity)
        intList_increse_capacity(list);
    int mysizeS = list->size;
    int first = list->arr[i];
    for(i=index;i<list->size;i++)
    {

        int second = list->arr[i+1];
        list->arr[i+1] = first;
        first = second;

    }
    list->arr[index] = value;
    int q = list->arr[index];
    list->size++;
}
void intList_removeL(intList_t list, int index){
    if(index < 0 || index >= list->size)
        return;
    int i;
 for(i=index;i<list->size -1;i++)
 {
     list->arr[i] = list->arr[i + 1];
 }
    list->size--;
}
int intList_getMax(intList_t list)
{
    int i,answer=list->arr[0];
    for(i=0;i<list->size;i++)
    {
        if(list->arr[i]>answer)
            answer = list->arr[i];
    }
    return answer;
}
int intList_getMin(intList_t list)
{
    int i,answer=list->arr[0];
    for(i=0;i<list->size;i++)
    {
        if(list->arr[i]<answer)
            answer = list->arr[i];
    }
    return answer;
}
void intList_printList(intList_t list){
int i;
for(i=0;i<list->size;i++)
    printf("%i  ",list->arr[i]);

}
