#ifndef __ILRD__OL13940_KNIGHT_TOUR__
#define __ILRD__OL13940_KNIGHT_TOUR__

#define SIZE_ROW (8)
#define SIZE_COL (8)

/*
* KnightTour description:
*	Find the route for knight.
*
* @param:
*   matrix - starting board.
*	row - starting point, row location.
*	col - starting point, col location.
*	size_row - row size.
*	size_col - col size.
* 
* @return:
*   Returns - if there is a valid soultion retuen 0, else return non zero.
*
* complexity
*	Time: O(8^n).
*	Space O(1)
*/
int KnightTour(int matrix[SIZE_ROW][SIZE_COL],int row, int col);

/*
* PrintBoard description:
*	Print the soultion to the Knight Tour.
*
* @param:
*	solution - Pointer to the heap.
*	size_row - row size.
*	size_col - col size.
* 
* @return:
*    Returns - void.
*
* complexity
*	Time: O(size_row * size_col).
*	Space O(1)
*/
void PrintBoard(int solution[SIZE_ROW][SIZE_COL]);

/*

------ ADVANCED ------ :

* PrintBoard description:
*	Print the soultion to the Knight Tour, with puppy that pop and walked on places.
*
* @param:
*	solution - Pointer to the heap.
*	size_row - row size.
*	size_col - col size.
* 
* @return:
*    Returns - void.
*
* complexity
*	Time: O(size_row * size_col).
*	Space O(1)
*/
void PooingDog(int solution[SIZE_ROW][SIZE_COL]);

#endif
