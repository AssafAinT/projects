#include <stdio.h>
int main (void)
{
    const int i = 3;
    int *ip = (int *)&i;
    *ip = 5;
    int arr[i];

    printf("%d %d\n", i, *ip);
    printf("%d %d\n", i, arr[i]);


    for (size_t il = 0; il < i; il++)
    {
        printf("%d ", arr[il]);
    }
    return 0;
}