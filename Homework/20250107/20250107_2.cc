#include <iostream>
#include <stdlib.h>
int main()
{
    char a[200] = {0};
    std::cin.getline(a, 200, ' ');
    std::cout << a;
    return 0;
}

