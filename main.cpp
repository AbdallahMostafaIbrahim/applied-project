// Testing Colors
#include <iostream>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
int main()
{
    std::cout << RED << "Hello" << GREEN << "World!" << RESET << std::endl;
    return 0;
}
