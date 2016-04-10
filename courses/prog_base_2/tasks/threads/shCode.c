#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "mutex.h"
#include "randomizer.h"
#include "zerowriter.h"

struct shared_s {
    int data;
    HANDLE mu;
};

shared_t * shared_new(){
    shared_t * shared = malloc(sizeof(struct shared_s));
    shared->mu = CreateMutex(
        NULL,
        FALSE,
        NULL);
    return shared;
}

void shared_free(shared_t * shared){
    CloseHandle(shared->mu);
    free(shared);
}

void shared_random_generator(LPVOID args){
    shared_t * data = (shared_t *)args;
    //WaitForSingleObject should always be inside. Sometimes there are positive numbers, if it's outside (4 threads)
    while(1){
        WaitForSingleObject(data->mu, INFINITE);
        data->data = rand() % 21 - 10;
        ReleaseMutex(data->mu);
    }
}

void shared_write_zero(LPVOID args){
    shared_t * data = (shared_t *)args;
    while(1){
        WaitForSingleObject(data->mu, INFINITE);
        if(data->data == 0){
            printf("%i\n", data->data);
        }
        ReleaseMutex(data->mu);
    }
}

HANDLE shared_random_handler(shared_t * data){
    DWORD tId;
    HANDLE shared_random_handler = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) shared_random_generator,
        data,
        0,
        &tId);
    return shared_random_handler;
}

HANDLE shared_zero_handle(shared_t * data){
    DWORD tId;
    HANDLE shared_zero_handle = CreateThread(
        NULL,
        0,
        (LPTHREAD_START_ROUTINE) shared_write_zero,
        data,
        0,
        &tId);
    return shared_zero_handle;
}

