//
// Created by Michael Chen on 15/12/2018.
//

#include <iostream>
#include <pthread.h>
#include <vector>

int main()
{
    int test[4][2] = {{0,1},{2,3},{4,5},{6,7}};
    std::cout << std::endl;
    std::cout << *(&test[0][0] + 3) << std::endl;


    return 0;
}