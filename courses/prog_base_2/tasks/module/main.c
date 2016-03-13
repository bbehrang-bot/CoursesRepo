#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"
int main()
{
    intList_t list1 = intList_new();
    const int size = 5;
    list1->arr = malloc(size * sizeof(int));
    list1->capacity = size;
    intList_add(list1,-1,0);
    intList_add(list1,1,1);
    intList_add(list1,2,2);
    intList_add(list1,3,3);
    intList_add(list1,4,4);
    intList_add(list1,5,5);
    intList_add(list1,22,2);
    intList_removeL(list1,3);
    int v = intList_getMax(list1);
    printf("%i\n",v);
    v = intList_getMin(list1);
    printf("%i\n",v);

    intList_printList(list1);
    intList_destructor(list1);
    return 0;
}
