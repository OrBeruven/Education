/***********Bit_Array_structure***********/

#ifndef BIT_ARRAY_H__
#define BIT_ARRAY_H__

typedef size_t bit_array_t;



/* 
* SetOn Description:
* Set bit value in a specific index to 1
*
* @param:
*	bitarr - the bit arr to set the bit in.	 
*	index - the index to set the bit in, should be 0-63.
*	sending an index outside this range could cause undefiend behaviour.
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArraySetOn(bit_array_t bitarr, size_t index);




/* 
* SetOff Description
*	Set bit value in a specific index to 0
*
* @param:
*	bit_arr - the bit arr to set the bit in.	 
*	index - the index to set the bit in, should be 0-63.
*	sending an index outside this range could cause undefiend behaviour.
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArraySetOff(bit_array_t bitarr, size_t index);




/* 
* SetVal Description
*	Set bit value in a specific index to either 1 or 0
*
* @param:
*	bit_arr - the bit arr to set the bit in.
*	value - the value to change the bit, should be either 0 or 1
*	sending a value outside this range could cause undefiend behaviour.
*	index - the index to set the bit in, should be 0-63.
*	sending an index outside this range could cause undefiend behaviour.
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArraySetVal(bit_array_t bitarr, size_t index, int bool_value);




/* 
* SetAll Description
*	Set all bits in arr to 1
*
* @param:
*	bit_arr - the bit arr to set the bits in.
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArraySetAll(bit_array_t bitarr);




/* 
* ResetAll Description
*	Set all bits in arr to 0
*
* @param:
*	bit_arr - the bit arr to reset the bits in.	 
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArrayResetAll(bit_array_t bitarr);




/* 
* Flip Description
*	Flips the bit value in a specific index (0 -> 1, 1 -> 0)
*
* @param:
*	bit_arr - the bit arr to flip the bit in.	 
*	index - the index to flip the bit in, should be 0-63.
*	sending an index outside this range could cause undefiend behaviour.
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArrayFlip(bit_array_t bitarr, size_t index);




/* 
* Mirror Description
*	Mirrors the bit arrr (0100 -> 0010)
*
* @param:
*	bit_arr - the bit arr to mirror. 
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArrayMirror(bit_array_t bitarr);




/* 
* Description
*	Rotates left 'rep' times the bit arr 
*
* @param:
*	bit_arr - the bit arr to rotate the bits.
*	rep - the number of rotations to do, should be 0-63
*	sending an index outside this range could cause undefiend behaviour.	 
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArrayRotateLeft(bit_array_t bitarr, size_t step);




/* 
* Description
*	Rotates right 'rep' times the bit arr 
*
* @param:
*	bit_arr - the bit arr to rotate the bits.	 
*	rep - the number of rotations to do, should be 0-63
*	sending an index outside this range could cause undefiend behaviour.
*
* @Return
*	returns the updated bit array
*
* @Complexity
*	Time: O(1)
*/
bit_array_t BitArrayRotateRight(bit_array_t bitarr, size_t step);




/* 
* CountOn Description
*	Counts the number of set bits  
*
* @param:
*	bit_arr - the bit arr to count the bits in.	 
*
* @Return
*	returns the number of set bits
*
* @Complexity
*	Time: O(n) - 64
*/
size_t BitArrayCountOn(bit_array_t bitarr);




/* 
* CountOff Description
*	Counts the number of off bits 
*
* @param:
*	bit_arr - the bit arr to count the bits in.	 
*
* @Return
*	returns the number of off bits 
*
* @Complexity
*	Time: O(n) - 64
*/
size_t BitArrayCountOff(bit_array_t bitarr);




/* 
* GetVal Description
*	Get the bit's value on a specific index 
*
* @param:
*	bit_arr - the bit arr to get the value from.	 
*	index - the specific index to get the bit value from, should be 0-63.
*	sending an index outside this range could cause undefiend behaviour.
*
* @Return
*	returns the bit value on a specific index
*
* @Complexity
*	Time: O(1)
*/
int BitArrayGet(bit_array_t bitarr, size_t index);




/* 
* ToString Description
*	Returns the string form of a bit array 
*
* @param:
*	bit_arr - the bit arr to convert to string.	 
*
* @Return
*	returns string form of the bit array
*
* @Complexity
*	Time: O(n) - 64
*/
char *BitArrayToString(bit_array_t bitarr, char *dest);

bit_array_t BitArrayMirrorLUT(bit_array_t bitarr);

void BitArrayCountLutInit();
size_t BitArrayCountLut(bit_array_t bitarr);

#endif
