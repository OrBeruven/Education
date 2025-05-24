/*****************************
	Name : Or Beruven

	Reviewed By : Daniel

	Date Test: 07.03.2023

	Description : c file for fsa implementation

*****************************/

#include <assert.h>	/*assert*/
#include <errno.h>	/*errno, ENOMEM*/
#include <stdio.h> 	/*perror*/

#include "fsa.h"	/*fsa_t*/

#define WORD_SIZE sizeof(void *)
#define END_FLAG 0

struct fsa
{
	size_t free;
};

fsa_t *FSAInit(void *memory_segment, size_t segment_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	size_t i = 0;
	size_t num_of_blocks = 0;
	char align = 0;
	
	assert(NULL != memory_segment);
	assert(0 != segment_size);
	assert(0 != block_size);
	
	align = ((size_t)memory_segment % WORD_SIZE);
	
	if (0 != align)
	{
		align = WORD_SIZE - align;
		memory_segment = (char *)memory_segment + align;
		segment_size -= align;
	}
	
	fsa = (fsa_t *)memory_segment;
	fsa->free = sizeof(fsa_t);
	
	segment_size -= sizeof(fsa_t);
	
	if (0 != block_size % WORD_SIZE)
	{
		block_size += WORD_SIZE - (block_size % WORD_SIZE);
	}
	
	num_of_blocks = segment_size / block_size;
	
	--num_of_blocks;
	for (i = 0; i < num_of_blocks; ++i)
	{
		*(size_t *)((char *)fsa + fsa->free + (i * block_size)) = ((i + 1) * block_size) + fsa->free;
	}
	
	*(size_t *)((char *)fsa + fsa->free + (num_of_blocks * block_size)) = END_FLAG;
	
	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
    void *location = NULL;
    
    assert(NULL != fsa);
    
    if (END_FLAG == fsa->free)
    {
    	errno = ENOMEM;
        perror("FSAAlloc");
    }
    else
    {
        location = (void *)((char *)fsa + fsa->free);
        fsa->free = *(size_t *)((char *)fsa + fsa->free);
    }
    
	return location;
}

void FSAFree(fsa_t *fsa, void *block_pointer)
{
    assert(NULL != fsa);
    assert(NULL != block_pointer);
    
    *(size_t *)block_pointer = fsa->free;
    fsa->free = (size_t)block_pointer - (size_t)fsa;
}
	
size_t FSACountFree(const fsa_t *fsa)
{
    size_t count = 0;
    size_t runner = 0;
    
    assert(NULL != fsa);
    
    runner = fsa->free;
    
    while (END_FLAG != runner)
    {
        ++count;
        runner = *(size_t *)((char *)fsa + runner);
    }
    
    return count;
}
	
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
    size_t suggested_size = sizeof(fsa_t);
    
    if (0 != block_size % WORD_SIZE)
	{
		block_size += WORD_SIZE - (block_size % WORD_SIZE);
	}
	
    suggested_size += (block_size * num_of_blocks);
    
    return suggested_size;
}
	
	
	
	
	
	
	
	
	
