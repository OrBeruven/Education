#ifndef __ILRD_OL139_40_VSA_H__
#define __ILRD_OL139_40_VSA_H__

/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 12.03.2023

	Description : h file for vsa

*****************************/

#include <stddef.h>	/*size_t*/

typedef struct vsa vsa_t;

/* VSAInit Description:
*   Creates VSA within the given memory segment.
*
* @Params:
*	memory_pool - pointer to the start of a segment given by the user.
*		      unaligned address will be cut forward to provide allignment.
*	segment_size - size in bytes of the given segment. if the size is 0, the behaviior is undefined
*
* @Returns:
*   	pointer to the VSA handler.
* 	if pointer to memory_pool is invalid, the behavior is undefined.
*
* @Complexity
*	Time: O(1)
*/
vsa_t *VSAInit(void *memory_pool, size_t segment_size);

/* VSAAlloc Description:
* 	Allocates used-defined sequential memory block. Additional metadata allocation may apply.
*	If possible de-fragmantation will occur
*
* @Params:
*	pool - handler to a memory pool to get the block from
*
* @Returns:
*	returns a pointer to the allocated address
*   	if no free memory is avialable, returns NULL
*	if block size if 0 behavior is undefined.
*
* @Complexity
*	Time: O(n)
*/
void *VSAAlloc(vsa_t *pool, size_t block_size);

/* VSAFree Description:
* 	Free memory from a given VSA block.
*
* @Params:
*   	block_pointer - pointer to a block address, which was allocated by VSAAlloc, to be freed from memory.
*
* @Returns:
*	void
*   	if block_pointer is NULL no action will be preformed
*
* @Complexity
*	Time: O(1)
*/
void VSAFree(void *block_pointer);

/* VSALargestChunkAvailable Description:
* 	returns the largest size of sequential memory block available for allocation in given vsa.
*	If possible de-fragmantation will occur
*
* @Params:
*	pool - handler to a segment to get the size from
*
* @Returns:
*	the size in bytes of the largest sequential memory block available for allocation
*   	if vsa is NULL the behavior is undefined
*
* @Complexity
*	Time: O(n)
*/
size_t VSALargestChunkAvailable(vsa_t *pool);

#endif
