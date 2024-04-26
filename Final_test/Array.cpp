#include <iostream>

int main()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << *(array + 3) << std::endl;
}