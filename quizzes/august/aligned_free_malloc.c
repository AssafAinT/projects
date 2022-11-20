/****************************************************
* aligned_malloc_free                               *
* Assaf Ainhoren                                    *
* Reviewer: Ester Shpoker                           *
* date: 18.07.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

void *AlignedMalloc(size_t bytes, size_t align);
void AlignedFree(void *ptr);
static size_t SetAdress(size_t data, size_t align);
int main(void)
{
    void *ptr1 = NULL;
	void *ptr2 = NULL;
	ptr1 = AlignedMalloc(100, 64);
	printf("%p\n", ptr1);
	
	ptr2 = AlignedMalloc(40, 16);
	printf("%p\n", ptr2);
	AlignedFree(ptr1);
	AlignedFree(ptr2);

    return (0);
}

void *AlignedMalloc(size_t bytes, size_t align)
{
    void *pool = NULL;
    void *ret = NULL;

    assert(0 < align);

    pool = malloc(sizeof(void *) + (bytes + align - 1));
    if (pool == NULL)
    {
        return NULL;
    }
    
    ret = (void *)SetAdress((size_t)pool, align);
    *((size_t *)ret - 1) = (size_t)pool;
    return ret;

}

void AlignedFree(void *ptr)
{
    assert(NULL != ptr);

    free((void *)(*((size_t *)ptr -1)));
    ptr = NULL;
}

static size_t SetAdress(size_t data, size_t align)
{
    size_t new_addr = (data + sizeof(void *) + align - 1);
    return(new_addr - (new_addr % (align - 1)));
}