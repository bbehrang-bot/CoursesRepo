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
void destructor_intList(intList_t list);
void increse_capacity(intList_t list);
void add(intList_t list,int value, int index);
void removeL(intList_t list, int index);
int getMax(intList_t list);
int getMin(intList_t list);
void printList(intList_t list);
#endif // INTLIST_H_INCLUDED
