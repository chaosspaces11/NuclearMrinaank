#include <iostream>
#include "Cell.cpp"
#include "Grid.cpp"

//
void arrayDebugOutput(int arrayPtr[], int arrayLength)
{
    int dataLength = arrayLength/sizeof(arrayPtr[0]);
    std::cout << "[";
    for (int index = 0; index < dataLength; index++)
    {
        if ((index + 1) != dataLength)
        {
            std::cout << *(arrayPtr + index) << ",";
        }
        else if (index + 1 == dataLength)
        {
            std::cout << *(arrayPtr + index) << "]" << std::endl;
        }
        else
        {
            std::cout << "This message should never be printed" << std::endl;
        }
    }
}

int main()
{
    int testing[4] = {1,2,3,4};
    arrayDebugOutput(testing, sizeof(testing));

    Grid test2;
    Cell test;
    return 0;
}