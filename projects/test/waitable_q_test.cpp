#include <thread>
#include <iostream>
#include "waitable_q.hpp"

using namespace std;
using namespace ilrd;

WaitableQueue<int> q;

void *WriterThread(void *nothing)
{
    for (int indx = 0; 9 > indx; ++indx)
    {
        q.Enqueue(indx);   
    }
   

    return NULL;
}
void *ReadThread(void *nothing)
{    
    for (int indx = 0; 3 > indx; ++indx)
    {
        int ret = 0;
        std::cout << "timed out stat "<<q.Dequeue(ret, 9000000)<<std::endl;
        std::cout << ret <<std::endl;
        
    }
   
    if (q.IsEmpty())
    {
        std::cout << "queue is empty" <<std::endl;
    }
    return NULL;
}
int main(void)
{
    
    pthread_t threads[4];
    pthread_create(threads, NULL,ReadThread, NULL);
    pthread_create(threads + 1, NULL,ReadThread, NULL);
    pthread_create(threads + 2, NULL,ReadThread, NULL);
    pthread_create(threads + 3, NULL,WriterThread, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);

}