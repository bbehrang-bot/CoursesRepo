#ifndef INTLIST_H_INCLUDED
#define INTLIST_H_INCLUDED
#define DEFAULT_LIST_CAP 5
struct intList_s{
    int * arr;
    int size;
    int capacity;
};
typedef struct intList_s * intList_t;
intList_t intList_new();
void intList_destructor(intList_t list);
void intList_increse_capacity(intList_t list);
void intList_add(intList_t list,int value, int index);
void intList_removeL(intList_t list, int index);
int intList_getMax(intList_t list);
int intList_getMin(intList_t list);
void intList_printList(intList_t list);
#endif // INTLIST_H_INCLUDED
