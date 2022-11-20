/*****************************************************
* VSA                                               *
* Assaf Ainhoren                                    *
* Reviewer: Mark Galperin                           *
* date: 27.06.2022                                  *
*****************************************************/



/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "vsa.h"




void InitTest(void);
void AllocTest(void);
void FreeTest(void);
void BiggestChunkTest(void);

int main(void)
{
	InitTest();
	AllocTest(); 
	FreeTest();
	BiggestChunkTest();
	return (0);
}

void InitTest(void)
{
	/* first test case */
	char data[500] = {0};
	size_t pool_size = 500;
	/* second test case */
	int data2[1] = {0};
	
	/* third test case */
	unsigned int data3[60] = {0};
	size_t pool_size3 = 60;
	
	vsa_ty *pool = VsaInit(data, pool_size);
	vsa_ty *pool2 = VsaInit(data2, 1);
	vsa_ty *pool3 = VsaInit((data3+1),pool_size3);
	
	assert(data  == (void *)pool);
	assert((void *)data2 != (void *)pool2);
	assert((void *)data3 != (void *)pool3);
	
	printf("----------------------------Init SUCCESSED!--------------------\n");
}

void AllocTest(void)
{
	char data[160] = {0};
	vsa_ty *vsa = NULL;
	void *runner = NULL;
	void *runner2 = NULL;
	int num = 12;
	int num2= 2021;
	printf("\v-------------------------alloc test---------------------------\n");

	vsa = VsaInit(data, 160);
	assert(128 == VsaBiggestChunkAvailable(vsa));
	runner = VsaAlloc(vsa, sizeof(int));
	*(int *)runner = num;
	printf("\ndiffrence between addresses: %ld\n",
	      (size_t)runner - (size_t)vsa);
	printf("\ninside runner %d\n", *(int *)runner);
	printf("\n%ld is biggest chunk\n", VsaBiggestChunkAvailable(vsa));

	runner = VsaAlloc(vsa, sizeof(int));
	*(int *)runner = num2;
	
	printf("\ndiffrence between addresses: %ld\n",
	      (size_t)runner - (size_t)vsa);
	
	printf("\ninside runner %d\n", *(int *)runner);
	runner2 = VsaAlloc(vsa, sizeof(int));
	printf("\ndiffrence between addresses: %ld\n",
	      (size_t)runner2 - (size_t)vsa);
	
	runner = VsaAlloc(vsa, sizeof(int));
	
	/*assert(NULL == runner);
	*/
	printf("\v----------------------alloc test successed--------------------\n");	
}
void FreeTest(void)
{
	
	char data[250] = {0};
	vsa_ty *vsa = NULL;
	void *runner = NULL;
	int num = -120;
	int num2= 202;
	printf("\v-------------------------free test----------------------------\n");
	vsa = VsaInit(data, 250);
	assert(216 == VsaBiggestChunkAvailable(vsa));
	printf("\n%ld after init is biggest chunk\n",
	      VsaBiggestChunkAvailable(vsa));
	runner = VsaAlloc(vsa, sizeof(int));
	*(int *)runner = num;
	printf("\n%ld is biggest chunk avail after one alloc\n",
	       VsaBiggestChunkAvailable(vsa));
	
	VsaFree(runner);

	printf("\n%ld is biggest chunk after first alloced free\n", 
	        VsaBiggestChunkAvailable(vsa));
	
	while (24 != VsaBiggestChunkAvailable(vsa))
	{
		runner = VsaAlloc(vsa, sizeof(int));
		*(int *)runner = num2;
	
		printf("\n%ld is biggest chunk avail after alloc\n",
	       VsaBiggestChunkAvailable(vsa));
	} 
	VsaFree(runner);
	
	printf("\n%ld is biggest chunk  after one free\n",
	       VsaBiggestChunkAvailable(vsa));
	printf("\v------------------------free test successed!!-----------------\n");
}

void BiggestChunkTest(void)
{
	/* first test case */
	char data[500] = {0};
	size_t pool_size = 500;
	/* second test case */
	unsigned int data3[60] = {0};
	size_t pool_size3 = 60;
	void *ptr = NULL;
	float fdata =12.2;
	vsa_ty *pool = VsaInit(data+1, pool_size);
	vsa_ty *pool2 = VsaInit(data3, pool_size3);
	printf("\v-------------------------biggest chunk-------------------------\n");
	assert(456 == VsaBiggestChunkAvailable(pool));
	ptr = VsaAlloc(pool, sizeof(size_t));
	*(float *)ptr = fdata;
	assert(432 == VsaBiggestChunkAvailable(pool));
	assert(24 == VsaBiggestChunkAvailable(pool2));
	
	printf("\v-------------------------testing done goodbye!---------------\n");
}
