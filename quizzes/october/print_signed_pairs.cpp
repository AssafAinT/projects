#include <iostream> // 
#include <cstdio> // std::
using namespace std;

void PrintSignedPairs(int *arr, size_t size)
{
    for (size_t i = 0; i < (size -1); ++i)
    {
        bool is_match = false;
        for (size_t j = i+1; j < size && !is_match; ++j)
        {
            if (arr[i] == (-1) *arr[j])
            {
                printf("Pair: %d, %d\n", arr[i], arr[j]);
                is_match = true;
            }
        }
    }
}

int main(void)
{
    int arr[] = {-1,3, 5, 6, -3, 1, 5};
    

    PrintSignedPairs(arr, sizeof(arr)/sizeof(arr[0]));

    return 0;
}