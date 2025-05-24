/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 12/03/2023

	Description : c file for vsa implementation

*****************************/

#include <stdio.h>	/*perror*/
#include <assert.h>	/*assert*/
#include <errno.h>	/*errno*/

#include "vsa.h"	/*vsa_t, stddef.h*/

#define WORD_SIZE sizeof(void *)
#define HEAD_SIZE sizeof(head_t)
#define VSA_SIZE sizeof(vsa_t)
#define END_OF_POOL (head_t *)((char *)pool + pool->end)

struct vsa
{
	size_t end;
};

typedef struct header head_t;

struct header
{
	size_t metadata;
};

/*************** Static Functions ***************/
static void DeFragmentation(vsa_t *vsa);
static size_t AlignToWord(size_t to_align);
static void *AlignAddressToWord(void *to_align, size_t *address_size);
/************************************************/

vsa_t *VSAInit(void *memory_pool, size_t segment_size)
{
	vsa_t *vsa = NULL;
	head_t *header = NULL;
	
	assert(NULL != memory_pool);
	
	memory_pool = AlignAddressToWord(memory_pool, &segment_size);
	
	vsa = (vsa_t *)memory_pool;
	vsa->end = segment_size;
	
	header = (head_t *)((char *)memory_pool + HEAD_SIZE);
	header->metadata = segment_size - VSA_SIZE - HEAD_SIZE;
	
	return vsa;
}
	
void *VSAAlloc(vsa_t *pool, size_t block_size)
{
	head_t *block_runner = NULL;
	head_t *new_block = NULL;
	void *pointer_to_return = NULL;
	size_t struct_size = HEAD_SIZE;
	
	assert(NULL != pool);
	assert(0 != block_size);
	
	block_runner = (head_t *)((char *)pool + VSA_SIZE);
	
	block_size = AlignToWord(block_size);
	
	DeFragmentation(pool);
	
	while (block_runner != END_OF_POOL)
	{
		if (0 == (block_runner->metadata & 1) && block_runner->metadata >= block_size)
		{
			if (block_runner->metadata >= block_size + struct_size)
			{
				new_block = (head_t *)((char *)block_runner + struct_size + block_size);
				new_block->metadata = block_runner->metadata - block_size - struct_size;
			}
			
			block_runner->metadata = block_size | 1;
			
			pointer_to_return = (char *)block_runner + struct_size;
			
			break;
		}
		
		block_runner = (head_t *)((char *)block_runner + block_runner->metadata + struct_size - (block_runner->metadata & 1));
	}
	
	if (NULL == pointer_to_return)
	{
		errno = ENOMEM;
		perror("VSAAlloc");
	}
	
	return pointer_to_return;
}

void VSAFree(void *block_pointer)
{
	head_t *block_header = NULL;
	
	if(NULL != block_pointer)
	{
		block_header = (head_t *)((char *)block_pointer - HEAD_SIZE);
		--block_header->metadata;
	}
}

size_t VSALargestChunkAvailable(vsa_t *pool)
{
    size_t largest = 0;
    head_t *header = NULL;
    size_t struct_size = HEAD_SIZE;
    
    assert(NULL != pool);

    DeFragmentation(pool);
    header = (head_t *)((char *)pool + VSA_SIZE);
    
    while ((char *)header != (char *)pool + pool->end)
    {
        if (0 == (header->metadata & 0x01) && header->metadata > largest)
        {
			largest = header->metadata;
		}
      
		header = (head_t *)((char *)header + struct_size + header->metadata - (header->metadata & 1));
	}
    
    return largest < struct_size ? 0 : largest;
}

static void DeFragmentation(vsa_t *pool)
{
	head_t *block_runner = NULL;
	head_t *next_block = NULL;

	size_t struct_size = HEAD_SIZE;
	
	assert(NULL != pool);
	
	block_runner = (head_t *)((char *)pool + VSA_SIZE);

	while (block_runner != END_OF_POOL)
	{
		if (0 == (block_runner->metadata & 0x01))
		{
			next_block = (head_t *)((char *)block_runner + block_runner->metadata + struct_size);
			
			while ((head_t *)next_block != END_OF_POOL && 0 == (next_block->metadata & 0x01))
			{
				block_runner->metadata += next_block->metadata + struct_size;
				next_block = (head_t *)((char *)next_block + next_block->metadata + struct_size);
			}
			
			block_runner = next_block;
		}
		else
		{
			block_runner = (head_t *)((char *)block_runner + block_runner->metadata + struct_size - (block_runner->metadata & 1));
		}
	}
}

/*************** Static Functions ***************/
static size_t AlignToWord(size_t to_align)
{
	char align = to_align % sizeof(void *);
		
	if (0 != align)
	{
		align = sizeof(void *) - align;
		to_align += align;
	}
	
	return to_align;
}

static void *AlignAddressToWord(void *to_align, size_t *address_size)
{
	char align = (size_t)to_align % WORD_SIZE;
		
	if (0 != align)
	{
		align = sizeof(void *) - align;
		to_align = (char *)to_align + align;
		*address_size -= align;
	}
	
	align = *address_size % WORD_SIZE;
	if (0 != align)
	{
		*address_size = *address_size - (size_t)align;
	}
	
	return to_align;
}
/*************** Static Functions ***************/
