#include <iostream> // std
#include <unordered_map> // std::map

using namespace std;

void FindTopThree(int *arr, size_t size)
{
    unordered_map<int, int> freq;

    for (size_t i = 0; i < size; ++i) 
    {
        ++freq[arr[i]];
    }

    
}


int main(void)
{
    int arr[] = { 3, 4, 2, 3, 16, 15, 16, 15, 16, 15, 15, 16, 2, 3};
    size_t size = sizeof(arr)/sizeof(arr[0]);
} 