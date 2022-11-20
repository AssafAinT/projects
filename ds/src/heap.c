/*****************************************************
 * heap                                              *
 * Assaf Ainhoren                                    *
 * Reviewer: Maayam Sheraizin                        *
 * date: 31.07.2022                                  *
 *****************************************************/

/********************************libraries includes****************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc ,free */
#include <stdio.h> /* printf */

#include "dynamic_vector.h"
#include "heap.h"

static const size_t g_size_of_element = sizeof(void *);
static const size_t g_element_amount = 300;

static const size_t g_root_index = 0;

static void *HeapGetParams(const heap_ty *heap);
static cmp_func HeapGetCmpFunc(const heap_ty *heap);
static status_ty HeapInit(heap_ty *heap, cmp_func cmp, void *params);
static size_t GetLastInsertedIndex(heap_ty *heap);
static size_t GetParentOfIndex(size_t index);
static void *HeapGetElementByIndex(heap_ty *heap, size_t index);
static int CmpHeap(heap_ty *heap, size_t index, size_t parent_index);
static void HeapifyUp(heap_ty *heap);
static void HeapifyDown(heap_ty *heap, size_t index);
static void HeapRemoveLastElement(heap_ty *heap);
static size_t GetRightChild(size_t index);
static size_t GetLeftChild(size_t index);
static size_t GetSmallestChild(heap_ty *heap, size_t root_index);
static void HeapPopFromIndex(heap_ty *heap, size_t start);
static bool_ty IsAParent(heap_ty *heap, size_t index);
static void SwapIndexes(heap_ty* heap, size_t index, size_t index2);

struct heap
{
    vector_ty *binary_heap;
    cmp_func cmp_func;
    void *params;
};

heap_ty *HeapCreate(cmp_func cmp, void *params)
{
    heap_ty *new_heap = NULL;

    assert(NULL != cmp);

    new_heap = (heap_ty *)malloc(sizeof(heap_ty));
    if (NULL == new_heap)
    {
        return (NULL);
    }
    if (FAIL == HeapInit(new_heap, cmp, params))
    {
        free(new_heap);
        new_heap = NULL;
        return (NULL);
    }

    return (new_heap);
}

void HeapDestroy(heap_ty *heap)
{
    VectorDestroy(heap->binary_heap);
    free(heap);
    heap = NULL;
}

status_ty HeapPush(heap_ty *heap, void *data)
{
    status_ty ret_stat = SUCCESS;
    assert(NULL != heap);
    
    ret_stat = VectorPushBack(heap->binary_heap, &data);
    if (FAIL == ret_stat)
    {
       return (FAIL);
    }
    HeapifyUp(heap);
    return (ret_stat);
}

void HeapPop(heap_ty *heap)
{
    assert(NULL != heap);
    HeapPopFromIndex(heap, g_root_index);
}

void *HeapPeek(const heap_ty *heap)
{
    assert(NULL != heap);
    return(HeapGetElementByIndex((heap_ty *)heap, g_root_index));
}

void *HeapRemove(heap_ty *heap, const void *data,
                     is_match_func is_match)
{   
    bool_ty is_found = FALSE;
    void *result = NULL;
    size_t counter = 0;

    assert(NULL != heap);
    
    for ( ; counter < HeapSize(heap) &&
            FALSE == is_found; ++counter)
    {
        is_found = is_match(HeapGetElementByIndex(heap, counter), (void *)data);
    }

	if (FALSE == is_found)
	{
		return (NULL);
	}
    result = HeapGetElementByIndex(heap, --counter); 
    HeapPopFromIndex(heap, counter);
    return (result);
}


size_t HeapSize(const heap_ty *heap)
{
    assert (NULL != heap);
    
    return (VectorSize(heap->binary_heap));
}

bool_ty HeapIsEmpty(const heap_ty *heap)
{
    assert(NULL != heap);
    
    return (!(bool_ty)VectorIsEmpty(heap->binary_heap));
}
/*advanced*/
heap_ty *HeapHeapify(void *src_array, size_t array_size,
                     cmp_func compare, const void *params);


/*******************************static_functions*******************************/
static status_ty HeapInit(heap_ty *heap, cmp_func cmp, void *params)
{
    heap->binary_heap = VectorCreate(g_element_amount, g_size_of_element);
    if (NULL == heap->binary_heap)
    {
        return (FAIL);
    }
    heap->cmp_func = cmp;
    heap->params = params;
    return (SUCCESS);
}

static cmp_func HeapGetCmpFunc(const heap_ty *heap)
{
    return (heap->cmp_func);
}

static void *HeapGetParams(const heap_ty *heap)
{
    return (heap->params);
}

static size_t GetLastInsertedIndex(heap_ty *heap)
{
    return (VectorSize(heap->binary_heap) -1);
}

static size_t GetParentOfIndex(size_t index)
{
    return ((index - 1)/2);
}

static void *HeapGetElementByIndex(heap_ty *heap, size_t index)
{
    return (*(void **)VectorGetElement(heap->binary_heap, index));
}

static int CmpHeap(heap_ty *heap, size_t index, size_t parent_index)
{
    return (HeapGetCmpFunc(heap)(HeapGetElementByIndex(heap, index), 
            HeapGetElementByIndex(heap, parent_index),
            HeapGetParams(heap)));
}

static void HeapifyUp(heap_ty *heap)
{
    size_t binary_heap_index = GetLastInsertedIndex(heap);

    for ( ; 0 != binary_heap_index && 
            0 > CmpHeap(heap, binary_heap_index,
            GetParentOfIndex(binary_heap_index));
            binary_heap_index = GetParentOfIndex(binary_heap_index))
    {
        SwapIndexes(heap, binary_heap_index,GetParentOfIndex(binary_heap_index));
      
    }

}

static void HeapifyDown(heap_ty *heap, size_t index)
{
    size_t smallest_child = index;
    size_t curr_smallest_child = 0;

    for ( ; IsAParent(heap, smallest_child) &&
            (0 < CmpHeap(heap, smallest_child,
            GetSmallestChild(heap, smallest_child)));
            smallest_child = curr_smallest_child)
    {
        curr_smallest_child = GetSmallestChild(heap, smallest_child);
        SwapIndexes(heap, smallest_child, curr_smallest_child);
    }
    

}
static size_t GetSmallestChild(heap_ty *heap, size_t root_index)
{  
    size_t right_index = GetRightChild(root_index);
    size_t left_index = GetLeftChild(root_index);
    size_t last_index = GetLastInsertedIndex(heap);
    
    if (!IsAParent(heap, root_index))
    {
        return (0);
    }

    else if (left_index > last_index)
    {
        return (right_index);
    }

    else if (right_index > last_index)
    {
        return (left_index);
    }

    return (0 > CmpHeap(heap, left_index, right_index) ?
            left_index : right_index);
}
static size_t GetRightChild(size_t index)
{

    return ((2 * index) + 2);
}
static size_t GetLeftChild(size_t index)
{

    return ((2 * index) + 1);
}
static void HeapRemoveLastElement(heap_ty *heap)
{
    VectorPopBack(heap->binary_heap);
}
static bool_ty IsAParent(heap_ty *heap, size_t index)
{
    return (index < HeapSize(heap)/2);
}

static void HeapPopFromIndex(heap_ty *heap, size_t start)
{
    size_t binary_heap_index = GetLastInsertedIndex(heap);
    assert (NULL != heap);

    SwapIndexes(heap, start, binary_heap_index);

    HeapRemoveLastElement(heap);
    HeapifyDown(heap, start);
}
static void SwapIndexes(heap_ty* heap, size_t index, size_t index2)
{
    USwap(VectorGetElement(heap->binary_heap, index),
    VectorGetElement(heap->binary_heap, index2), g_size_of_element);
}
/************PrintHeap************/
void PrintHeap(heap_ty *heap)
{
	size_t i = 0;
	size_t size = HeapSize(heap);
	
	printf("HEAP |");
	
	for( ; i < size ; ++i)
	{
		printf("%d |", *(int *)HeapGetElementByIndex(heap, i));
	}
	
	printf("\n");
}

