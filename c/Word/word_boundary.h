/*****************************
	Name : Or Beruven

	Reviewed By :	Noam Gazit

	Date Test:	23.01.2023

	Description : header file for word_boundary

*****************************/

#ifndef WORD_BOUNDARY_H
#define WORD_BOUNDARY_H

void *MemSet(void *s, int c, size_t n);
void *MemSetWord(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);

#endif
