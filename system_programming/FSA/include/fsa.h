/*****************************
	Name : Blue Heart

	Reviewed By :

	Date Test:

	Description : API for FSMA

*****************************/
#ifndef __ILRD_OL139_40_FSA_H__
#define __ILRD_OL139_40_FSA_H__

#include <stddef.h> /*size_t*/

typedef struct fsa fsa_t;

/* FSAInit Description:
*   Creates FSA within the given memory segment. memory blocks are word alligned.
*
* @Params:
*	memory_segment - pointer to the start of a segment given by the user.
*	segment_size - size in bytes of the given segment. if the size is 0, the behaviior is undefined
*	block_size - minimun number of bytes for each block. if the size is 0, the behaviior is undefined
*
* @Returns:
*   pointer to the FSA handler.
*   if pointer to memory_segment is invalid, the behavior is undefined.
*
* @Complexity
*	Time: O(n)
*/
fsa_t *FSAInit(void *memory_segment, size_t segment_size, size_t block_size);

/* FSAAlloc Description:
* 	Allocates 'Fixed Sized Memory' block.
*
* @Params:
*	fsa - handler to a segment to get the block from
*
* @Returns:
*	returns a pointer to the allocated address
*   if no free memory is avialable, returns NULL
*
* @Complexity
*	Time: O(1)
*/
void *FSAAlloc(fsa_t *fsa);

/* FSAFree Description:
* 	Free memory from a given 'Fixed Sized Memory' block.
*
* @Params:
*	fsa - handler to a segment to free the block from
*   block_pointer - pointer to a block address, which was allocated by FSAAlloc, to be freed from memory.
*
* @Returns:
*	void
*   if block_pointer is NULL no action will be preformed
*   if fsa is NULL the behavior is undefined
*
* @Complexity
*	Time: O(1)
*/
void FSAFree(fsa_t *fsa, void *block_pointer);

/* FSACountFree Description:
* 	Counts the number of free blocks in the segment
*
* @Params:
*	fsa - handler to a segment to get the block from
*
* @Returns:
*	the number of free blocks in a given segment
*   if fsa is NULL the behavior is undefined
*
* @Complexity
*	Time: O(n)
*/
size_t FSACountFree(const fsa_t *fsa);

/* FSASuggestSize Description:
* 	Suggest to the user a size to be allocated in order to perform the requested properties
*
* @Params:
*	num_of_blocks - number of blocks the user wants to have
*   block_size - minimum size of the block in bytes
*
* @Returns:
*	returns the suggested size of the memory segment to allocate in order to perform the requested properties
*
* @Complexity
*	Time: O(1)
*/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);
#endif
