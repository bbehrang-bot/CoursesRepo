#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "randomizer.h"
#include "zerowriter.h"
#include "thread.h"
#include "mutex.h"

int main()
{
    srand(time(NULL));
    shared_t * data = shared_new();

    HANDLE h1Random = shared_random_handler(data);
    HANDLE h2Random = shared_random_handler(data);
    HANDLE h1Zero = shared_zero_handle(data);
    HANDLE h3Random = shared_random_handler(data);
    HANDLE h4Random = shared_random_handler(data);
    HANDLE h2Zero = shared_zero_handle(data);
    HANDLE h5Random = shared_random_handler(data);

    Sleep(1000);

    TerminateThread(h1Random, 0);
    TerminateThread(h2Random, 0);
    TerminateThread(h1Zero, 0);
    TerminateThread(h3Random, 0);
    TerminateThread(h4Random, 0);
    TerminateThread(h2Zero, 0);
    TerminateThread(h5Random, 0);


    CloseHandle(h1Random);
    CloseHandle(h2Random);
    CloseHandle(h1Zero);
    CloseHandle(h3Random);
    CloseHandle(h4Random);
    CloseHandle(h2Zero);
    CloseHandle(h5Random);


    shared_free(data);
    return 0;
}
