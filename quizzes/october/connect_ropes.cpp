#include <iostream> // std::cout
#include <queue> // std::queue
#include <cassert> // assert

using namespace std;

size_t ConnectRopesMinCost(int *arr, size_t size)
{
    assert(size > 1);        
    priority_queue<size_t,
                   vector<size_t>,
                   greater<size_t>>min_heap(arr, arr+size);
    
    size_t cost = 0;

    while (1 < min_heap.size())
    {
        size_t rope_a = min_heap.top();
        min_heap.pop();

        size_t rope_b = min_heap.top();
        min_heap.pop();

        size_t sum_to_push = rope_a + rope_b;
        cost += sum_to_push;

        min_heap.push(sum_to_push);
    }

    return cost;
}

int main(void)
{
    int ropes[] = {2, 3, 4, 6};
    //int ropes2[] = {2};
    size_t ropes_n = sizeof(ropes)/ sizeof(ropes[0]);
    //size_t ropes2_n = sizeof(ropes2)/ sizeof(ropes2[0]);
    cout << " min cost to connect ropes: " <<
    ConnectRopesMinCost(ropes, ropes_n)<<endl;

    //cout << " min cost to connect ropes: " <<
    //ConnectRopesMinCost(ropes2, ropes2_n)<<endl;

    return 0;
}