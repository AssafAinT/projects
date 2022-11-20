#include <stdio.h>
float farty = 3.5;
const float fart = 3.6;
static const float farti = 3.7;
int main (void)
{
    const int i = 3;
    int *ip = (int *)&i;
    *ip = 5;
    int arr[i];
    //int arr[i] = { 1 ,2 , 3};

    for (size_t il = 0; il < i; il++)
    {
        printf("%d ", arr[il]);
    }
    

   // printf("%d %d\n", i, *ip);
    return 0;
}