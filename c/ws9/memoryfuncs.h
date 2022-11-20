#ifndef MEMORYFUNCS_H_ /*include guard */
#define MEMORYFUNCS_H_

#define ALIGN_TO  sizeof(void *)

#define WORD sizeof(size_t)
/*fills the first n bytes of the memory area pointed to by s with the constant byte c*/
void *MemSet(void *source, int c, size_t n);
/*Auxiliary function to create a buffer*/
size_t MakeBuffer(unsigned char value);
/*copies n bytes from memory area src to memory area dest. the memory may not overlap*/
void *MemCpy(void *dest, const void *src, size_t n);
/*copies n bytes from memory area src to memory area dest.  The memory areas may overlap*/
void *MemMove(void *dest, const void *src, size_t n);
/* check for aligned addresses */
int IsAlign(size_t address);
#endif /*closing header-guard */
