#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "main.h"
void randomRain(queue_t * self)
{
    puts("Raining starts in 3 seconds");
    Sleep(300);
    system("cls");
    int random = 0;
    random = rand() % 6;
    queue_enqueue(self,random);
    queue_print(self);
    Sleep(500);
    system("cls");

}
void reaction(queue_t * self)
{
    puts("Starting reaction function");
    Sleep(300);
    size_t mySize = queue_getSize(self);
    if(mySize < 7)
    {
        puts("Week is not completed yet");
        Sleep(300);
        system("cls");
    }
    else{
        int weekRain = 0;
        int tail = queue_getTail(self);
        if(tail<7){
            for(int i = mySize - (7 - tail); i < mySize;i++) {
                weekRain += queue_getByInd(self, i);
            }
            for(int i = 0; i < tail; i++) {
                weekRain += queue_getByInd(self, i);
            }
        }
        else {
            for(int i = tail - 7; i < tail; i++) {
                weekRain += queue_getByInd(self, i);
            }

        }
        if(weekRain > 20){
            puts("RAINY");
            printf("Last week rain amount is : %i\n", weekRain);
            queue_print(self);
            puts("Press ANY KEY to proceed...");
            _getch();
            system("cls");
        }
        else {
            printf("Last week rain amount is : %i\n", weekRain);
            puts("Wasnt a rainy week at all!!!");
            Sleep(500);
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
