#include <iostream> /* std::cout */
#include "temp_header.hpp"
int main(void)
{
    int arr[12];
    char arr1[12];
    std::cout << Max<int>(3, 5) << "" << Max<double>(3.7, 12.9) << "" ;
    std::cout << Max<int *>(arr, arr + 8) << std::endl;
    std::cout << Max('a', 'b') << std::endl;
    std::cout << Max<char *> (arr1, arr1 + 8) << std::endl;
    std::cout << Max<size_t>(123456678, 1212121212)<< std::endl;
    return 0;
}