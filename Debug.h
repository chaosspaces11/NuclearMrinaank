//
// Created by Michael Chen on 31/08/2018.
//

#ifndef NUCLEARMRINAANK_DEBUG_H
#define NUCLEARMRINAANK_DEBUG_H
#include <iostream>


// Prints out the data of an array
void arrayDebugOutput(int arrayPtr[], int arrayLength)
{
    int dataLength = arrayLength;
    std::cout << "[";
    for (int index = 0; index < dataLength; index++)
    {
        if ((index + 1) != dataLength)
        {
            std::cout << arrayPtr[index] << ",";
        }
        else if (index + 1 == dataLength)
        {
            std::cout << arrayPtr[index] << "]" << std::endl;
        }
        else
        {
            std::cout << "This message should never be printed" << std::endl;
        }
    }
}


#endif //NUCLEARMRINAANK_DEBUG_H
