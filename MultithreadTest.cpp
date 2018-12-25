//
// Created by Michael Chen on 15/12/2018.
//

#include <iostream>
#include <pthread.h>
#include <vector>

int main()
{
    std::vector<int> arg, kwarg;
    std::vector<int>* argPtr = &arg;
    arg= {0,1,2,3};

    kwarg = {(*argPtr)[0],4,5,6};
    for (int element; element < kwarg.size(); element++)
    {
        std::cout << kwarg[element];
    }

    return 0;
}