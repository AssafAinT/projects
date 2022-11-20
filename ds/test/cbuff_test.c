/*****************************************************
 * Circular Buffer                                   *
 * Assaf Ainhoren                                    *
 * Reviewer:                                         *
 * date:                                             *
 *****************************************************/

/********************************libraries includes****************************/
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "cbuff.h"

/********************************Tests*****************************************/
int main()
{
	/* Roi Herscho Test */
	size_t buffer_size = 10;
    char *to_add = "1234567890";
    char to_read[20] = "";
    char to_read2[20] = "";
    cbuff_ty *pt = CBuffCreate(buffer_size);

    assert(10 == CBuffCapacity(pt));
    assert(10 == CBuffFreeSpace(pt));
    assert(0 != CBuffIsEmpty(pt));
    printf("CBuffWrite : %ld\n", CBuffWrite(pt, to_add,5));
    
    printf("CBuffRead : %ld\n", CBuffRead(pt, to_read, 3));
    printf("%s\n", to_read);

    printf("CBuffWrite : %ld\n", CBuffWrite(pt, to_add,10));
    
    printf("CBuffRead : %ld\n", CBuffRead(pt, to_read2, 10));
    printf("%s\n", to_read2);
    
    CBuffDestroy(pt);
    
     /* My test */
	/*size_t cir_buff_capacity = 7;
	char src_buff[] = "hello";
	char src_buff2[] = "abc";
	char src_buff3[] = "123456789";
	char dest_buff[20]="";
	
	cbuff_ty *my_cir_buff = CBuffCreate(cir_buff_capacity);
	
	assert(7 == CBuffCapacity(my_cir_buff));
	assert(7 == CBuffFreeSpace(my_cir_buff));
	assert(1 == CBuffIsEmpty(my_cir_buff));
	assert(5 == CBuffWrite(my_cir_buff, src_buff, 5));
	
	CBuffWrite(my_cir_buff, src_buff2, 44);
	CBuffRead(my_cir_buff, dest_buff, 3);
	puts(dest_buff);
	CBuffWrite(my_cir_buff, src_buff3, 2);
	CBuffRead(my_cir_buff, dest_buff, 8);
	puts(dest_buff);
	CBuffWrite(my_cir_buff, src_buff3, 7);
	CBuffRead(my_cir_buff, dest_buff, 7);
	puts(dest_buff);
	assert(3 == CBuffWrite(my_cir_buff, src_buff2, 3));
	CBuffWrite(my_cir_buff, src_buff3, 3);
	CBuffRead(my_cir_buff, dest_buff, );
	puts(dest_buff);
	
	
	CBuffDestroy(my_cir_buff);
	*/
	return (0);
}

