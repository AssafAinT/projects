#include <iostream>
#include <thread>
#include "scopedblock.hpp"
using namespace std;
mutex mut;
void GeneralFunction(int x)
{
    ilrd::ScopedLock<mutex> sl(mut);
    cout << rand() % x << endl;
    sleep(2);
}

int main(void)
{
    thread first (GeneralFunction, 655);     // spawn new thread that calls foo()
    thread second (GeneralFunction,100);  // spawn new thread that calls bar(0)

    cout << "main, foo and bar now execute concurrently...\n";

    // synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes

    cout << "GeneralFunction finished.\n";

    return 0;
}

