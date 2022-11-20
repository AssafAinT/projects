#include "waitable_q.hpp"
#include <iostream>
#include <thread>
#include <cstdio>

void TEST_1();

void Producer(ilrd::WaitableQueue<size_t> *myQueue);
void Consumer(ilrd::WaitableQueue<size_t> *myQueue, int i);


int main()
{
    TEST_1();
    return 0;
}

void TEST_1()
{
    using namespace ilrd;
    WaitableQueue<size_t> myQueue;
    
    std::thread first(Producer, &myQueue);
    std::thread second(Consumer, &myQueue, 1);
    std::thread third(Consumer, &myQueue, 2);
    
    first.join();
    second.join();
    third.join();
}

void Producer(ilrd::WaitableQueue<size_t> *myQueue)
{
    size_t counter = 100;
    
    while(counter)
    {
        /* sleep(1); */
        (*myQueue).Enqueue(counter);
        counter--;
    }
}
void Consumer(ilrd::WaitableQueue<size_t> *myQueue, int i)
{
    size_t out_p;
    sleep(2);
    while ((*myQueue).Dequeue(out_p, 50000))
    {
        printf("Consumer --> %d    %lu\n", i, out_p);
    }

    if ((*myQueue).IsEmpty())
    {
        printf("Queue is empty and time is out --> Consumer: %d\n", i);
    }
    
}