/*****************************
	Name : Or Beruven

	Reviewed By : Yossi

	Date Test: 13.04.2023

	Description : header file for Hash Table

*****************************/
#ifndef __ILRD_139_40__HASH_TABLE_H__
#define __ILRD_139_40__HASH_TABLE_H__

#include <stddef.h>

typedef struct hash_table hash_table_t;

/*****************************************************************************/

/*
* HashTableCreate description:
* Creates a new Hash Table.
*
* @param:
*   capacity - Number of buckets held at hash table.
* hash_func - Pointer to a hash function. The function recieves value to look for,
*               and returns the index of the appropriate bucket. If key does not match any bucket, behavior is undefined.
*               If the pointer to the hash function is invalid, behavior is undefined.
*   is_match_func - Pointer to function which is used to locate data.  The function receives lhd, an element
*               in the hash table. rhd is the the data to be matched.
*               If the function pointer is invalid, behavior is undefined.
*
* @return:
* Returns pointer to the newly created hash table.
* In case of failure, returns NULL.
*
* complexity:
* Time: O(1)
* Space O(1)
*/
hash_table_t *HashTableCreate(size_t capacity, size_t(*hash_func)(const void *value),
                    int(*is_match_func)(const void *lhd, const void *rhd));         

/*
* HashTableDestroy description:
* Deallocates the memory space of the hash table.
*
* @param:
* table - Pointer to the hash table.
*   If the pointer is invalid - the behavior is undefined
*
* @return:
* None.
*
* complexity
* Time: O(n)
* Space O(n)
*/
void HashTableDestroy(hash_table_t *table);

/*
* HashTableInsert Description:
* Inserts data to the hash table.
*
* @Params:
*   table - Pointer to the hash table. If the pointer is invalid - the behavior is undefined.
*   data - Pointer to value to insert to the hash table. The value should be valid input for both
*           is_match function as well as the hash function. 
*
* @Returns:
*   Returns zero if data inserted successfully.
*   Otherwise returns a non-zero value.
*
* @Complexity
* Time: O(1)
* Space O(1)
*/
int HashTableInsert(hash_table_t *table, void *data); 

/*
* HashTableRemove Description:
* Removes the requested data from the hash table.
*
* @Params:
*   table - Pointer to the hash table. If the pointer is invalid - the behavior is undefined.
*   data - Pointer to data which will be removed. The data should be valid input for *    both is_match and hash functions.  
*
* @Returns:
* None. 
* 
* @Complexity
* Time: O(1)
* Space: O(1)
*/
void HashTableRemove(hash_table_t *table, const void *data); 

/*
* HashTableSize Description:
*   Returns the number of elements stored in the hash table. 
*
* @Params:
*   Table - pointer to the Hash Table. If the pointer is invalid - the behavior is undefined.
*
* @Returns:
*   Return the number of elements currently stored in the hash table.
*
* @Complexity
*   Time: O(n)
*/
size_t HashTableSize(const hash_table_t *table);

/*
* HashTableIsEmpty Description:
*   Checks if the hash table is empty. 
*
* @Params:
*   table - pointer to the Hash Table.
*
* @Returns:
*   Returns 1 if the hash table is empty or 0 otherwise.
*
* @Complexity
*   Time: O(n)
*   n- is the number of buckets in the hash table
*/
int HashTableIsEmpty(const hash_table_t *table);

/*
* HashTableFind Description:
*   Search the hash table for an element that matches the given data value, and return a pointer to the matching element.
*
* @Params:
*   table - pointer to the Hash Table.
*   data - data to find.
*   
* @Returns:
*   If found- returns pointer to the data that has been found
*   If not found, returns NULL.
*
* @Complexity
*   Amortised Time: O(1)
*   Worst case time: O(n)
*/
void *HashTableFind(const hash_table_t *table, const void *data);   

/*
* HashTableForEach Description:
*   Execute a given function on all values stored in the Hash Table Array.
*
* @Params:
*   table - pointer to the Hash Table Array.
*   action_func - pointer to a given action function sent by user.
*   param - paramter for the action function.
*
* @Returns:
*   Returns action_function status. 
*   0 if succeeded. 
*   If one of the operations of the action func fails- the function stops from executing and returns value different from 0.
*
* @Complexity
*   Time: O(n)
*/
int HashTableForEach(const hash_table_t *table, 
          int (*action_func)(void *data, void *param), void *param);
  
/*
* HashLoad Description:
*   Calculate the load factor of the hash table, which is the ratio of the number of elements in the hash table to the number of buckets.
*
* @Params:
*   table - pointer to the hash Table Array.
*
* @Returns:
*   The function returns the calculated load factor as a double value.
*
* @Complexity
*   Time: O(n)
*/
double HashLoad(const hash_table_t *table);

/*
* HashSTDev Description:
*   Calculate the standard deviation of the number of elements stored in each bucket of the hash table.
*
* @Params:
*   table - pointer to the hash Table Array.
*
* @Returns:
*  The function returns the calculated standard deviation of the hash table.
*
* @Complexity
*   Time: O(n)
*/
double HashSTDev(const hash_table_t *table);

#endif
