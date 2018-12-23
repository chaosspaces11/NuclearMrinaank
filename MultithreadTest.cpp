//
// Created by Michael Chen on 15/12/2018.
//

#include <iostream>
#include <pthread.h>
#include <vector>
struct managers
        {
        int arg;
        int kwarg;
        };

void* fightClub(void* number)
{
    int *numberPtr = (int *) number;
    std::cout << numberPtr << std::endl;
    while (true)
    {
        if (*numberPtr = 3)
        {
            *numberPtr = 3;
            std::cout << "3"<<std::endl;
        }
    }
}

int main()
{
    pthread_t id;
    int rc;
    int qwerty = 3;
    int* qwertyPtr = &qwerty;
    rc = pthread_create(&id, NULL, fightClub, (void*) qwertyPtr);
    std::cout << qwertyPtr << std::endl;

    while (true)
    {
        if (qwerty = 3)
        {
            qwerty = 2;
            std::cout << qwerty << std::endl;
        }
    }

    return 0;
}