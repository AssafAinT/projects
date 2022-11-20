/*****************************************************
 * heap                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Maayam Sheraizin                        *
 * date: 31.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include "heap.h"
#define UNUSED(x) (void)x

int DataCompare(const void *heap_data, const void *user_data, void *params);
bool_ty MatchData(const void *ds_data, const void *user_data);
static void HeapCreateTest(void);
static void HeapSizeTest(void);
static void HeapEmptyTest(void);
static void HeapInsertTest(void);
static void HeapPopTest(void);
static void HeapRemoveTest(void);
int main(void)
{
    HeapCreateTest();
    HeapSizeTest();
    HeapEmptyTest();
    HeapInsertTest();
    HeapPopTest();
    HeapRemoveTest();
    return (0);
}

static void HeapCreateTest(void)
{
    heap_ty *first_heap = HeapCreate(DataCompare, NULL);
    HeapDestroy(first_heap);
}

static void HeapSizeTest(void)
{
    heap_ty *heap_for_size = HeapCreate(DataCompare, NULL);
    assert(0 == HeapSize(heap_for_size));
    HeapDestroy(heap_for_size);
}

static void HeapEmptyTest(void)
{
    heap_ty *heap_is_empty = HeapCreate(DataCompare, NULL);
    assert (TRUE == HeapIsEmpty(heap_is_empty));
    HeapDestroy(heap_is_empty);
}
static void HeapInsertTest(void)
{
    int arr_to_insert[9] = {100, 19, 36, 17, 3 ,25, 1, 2, 7};
    size_t i = 0;
    heap_ty *first_heap = HeapCreate(DataCompare, NULL);
    for ( ; i < 9 ;++i)
    {
        assert(SUCCESS == HeapPush(first_heap, &arr_to_insert[i]));
    }
    assert(9 == HeapSize(first_heap));
    PrintHeap(first_heap);
    HeapDestroy(first_heap);
}

static void HeapPopTest(void)
{
    int arr_to_insert[9] = {100, 19, 36, 17, 3 ,25, 1, 2, 7};
    
    size_t i = 0;
    heap_ty *first_heap = HeapCreate(DataCompare, NULL);
    for ( ; i < 9 ;++i)
    {
        assert(SUCCESS == HeapPush(first_heap, &arr_to_insert[i]));

    }
    assert(9 == HeapSize(first_heap));
    PrintHeap(first_heap);

    while (0 != HeapSize(first_heap))
    {
        HeapPop(first_heap);
        PrintHeap(first_heap);
    }
    
    HeapDestroy(first_heap);
}
static void HeapRemoveTest(void)
{
    int arr_to_insert[9] = {100, 19, 36, 17, 3 ,25, 1, 2, 7};
    size_t i = 0;

    heap_ty *first_heap = HeapCreate(DataCompare, NULL);
    for ( ; i<9 ;++i)
    {
        assert(SUCCESS == HeapPush(first_heap, &arr_to_insert[i]));
    }
    assert(9 == HeapSize(first_heap));
    PrintHeap(first_heap);
    assert(100 == *(int *)HeapRemove(first_heap, &arr_to_insert[0], MatchData));
    PrintHeap(first_heap);
    assert(8 == HeapSize(first_heap));
    HeapRemove(first_heap, &arr_to_insert[8], MatchData);
    assert(7 == HeapSize(first_heap));
    PrintHeap(first_heap);
    HeapRemove(first_heap, &arr_to_insert[1], MatchData);
    assert(6 == HeapSize(first_heap));
    PrintHeap(first_heap);
    HeapDestroy(first_heap);
}
int DataCompare(const void *heap_data, const void *user_data, void *params)
{
    UNUSED(params);
	return (*(int *)heap_data - *(int *)user_data);
}

bool_ty MatchData(const void *ds_data, const void *user_data)
{
    return(*(int *)ds_data == *(int *)user_data);
}
