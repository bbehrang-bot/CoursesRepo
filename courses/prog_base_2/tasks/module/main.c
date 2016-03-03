#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"
int main()
{
    intList_t list1 = intList_new();
    const int size = 5;
    list1->arr = malloc(size * sizeof(int));
    list1->capacity = size;
    add(list1,-1,0);
    add(list1,1,1);
    add(list1,2,2);
    add(list1,3,3);
    add(list1,4,4);
    add(list1,5,5);
    add(list1,22,2);
    removeL(list1,3);
    int v = getMax(list1);
    printf("%i\n",v);
    v = getMin(list1);
    printf("%i\n",v);

    printList(list1);
    destructor_intList(list1);
    return 0;
}
