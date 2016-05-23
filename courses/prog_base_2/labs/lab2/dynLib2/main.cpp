#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "main.h"
void randomRain(queue_t * self) {
    puts("Raining starts in 3 seconds");
    Sleep(300);
    system("cls");
    int random;
    random = rand()%2;
    queue_enqueue(self, random);
    queue_print(self);
    Sleep(1000);
    system("cls");
}

void reaction(queue_t * self) {
    puts("Reaction starting");
    Sleep(300);
    size_t mySize = queue_getSize(self);
    if(mySize < 3) {
        printf("Not 3 days yet\n");
        Sleep(300);
        system("cls");
    }
    else {
        int threeDaysRain = 0;
        int tail = queue_getTail(self);
        if(tail < 3) {
            for(int i = mySize - (3 - tail); i < mySize;i++) {
                threeDaysRain += queue_getByInd(self, i);
            }
            for(int i = 0; i < tail; i++) {
                threeDaysRain += queue_getByInd(self, i);
            }
        }
        else {
            for(int i = tail - 3; i < tail; i++) {
                threeDaysRain += queue_getByInd(self, i);
            }
        }
        if(threeDaysRain == 0){
            puts("STILL SUNNY");
            printf("Last 3 days rain amount is : %i\n", threeDaysRain);
            queue_print(self);
            puts("Press ANY KEY to proceed...");
            getch();
            system("cls");
        }
        else {
             printf("Last 3 days rain amount is : %i\n", threeDaysRain);
            puts("moving on");
            Sleep(300);
            system("cls");
        }
    }
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
