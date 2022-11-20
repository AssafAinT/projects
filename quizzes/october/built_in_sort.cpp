/****************************************************
* built_in_sort                                                *
* Assaf Ainhoren                                    *
* Reviewer: Herscho the king                        *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
bool compare(int a, int b)
{
    if ((a >0 && b > 0) ||
        (a < 0 && b < 0) ||
        (a > 0 && b < 0))
    {
        return false;
    }
    if (a < 0 && b > 0)
    {
        return true;
    }
    if ((a == 0 && b < 0 ) ||
        (a > 0 && b == 0))
    {
        return false;
    }
    if ((a == 0 && b > 0 ) ||
    (a < 0 && b == 0))
    {
        return true;
    }
}
int main(void)
{
    int arr[] = {12, 11, 13, 18, -9, -13, -1 ,17};



    size_t n = sizeof(arr)/sizeof(arr[0]);
    for (size_t i = 0; i < n; ++i)
    {
        cout<< arr[i] << " ";
    }
    cout << endl;
    sort(arr, arr+ n, compare);

    for (size_t i = 0; i < n; ++i)
    {
        cout<< arr[i] << " ";
    }
    cout << endl;

    return (0);
}