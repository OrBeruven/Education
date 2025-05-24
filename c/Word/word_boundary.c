/*****************************
	Name : Or Beruven

	Reviewed By : Noam Gazit

	Date Test :	23.01.2023

	Description : c file for word_boundary

*****************************/

#include <stdio.h> /*using printf, sizeof */
#include <stdint.h> /*using - uintptr_t*/
#include <assert.h> /*using - assert */

#include "word_boundary.h"

void *MemSet(void *s, int c, size_t n)
{
    unsigned char *ptr = s;
    
    while(0 < n)
    {
        *ptr = (unsigned char)c;
        ++ptr;
        --n;
    }
    
    
    return s;
}

static void MakeEightWord(unsigned char str[sizeof(uintptr_t)], int c)
{
	size_t i = 0;
	
	for (i = 0; i < sizeof(uintptr_t); ++i)
	{
		str[i] = (unsigned char)c;
	}
	
	return;
}

void *MemSetWord(void *s, int c, size_t n)
{
    unsigned char *runner = s;
    size_t size_of_word = 0;
    unsigned char swap_word[sizeof(uintptr_t)];
    size_of_word = sizeof(uintptr_t);
    
    if (NULL == s)
    {
        return (NULL);
    }
    
    MakeEightWord(swap_word, c);
    
    while (0 < n)
    {
        /* setting byte by byte */
        if (n < size_of_word || (((uintptr_t)runner & (size_of_word - 1)) != 0))
        {
            *runner = (unsigned char)c;
            ++runner;
            --n;
        }
        else
        {
            /* setting a whole word */
            *((void **)runner) = *((void **)swap_word);
            runner += size_of_word;
            n -= size_of_word;
        }
    }
    
    return s;
}


void *MemCpy(void *dest, const void *src, size_t n)
{
	unsigned char *d_runner = dest;
	unsigned char *s_runner = (unsigned char *)src;
	size_t size_of_word = sizeof(uintptr_t);
	
	if (NULL == src || NULL == dest)
    {
        return (NULL);
    }
    
	while (0 < n)
	{
		if (n < size_of_word || (((uintptr_t)d_runner & (size_of_word -1)) != 0))
		{
			*d_runner = (unsigned char)*s_runner;
			++d_runner;
			--n;
			++s_runner;
		}
		else
		{	
			*((void **)d_runner) = *((void **)s_runner);
			d_runner += size_of_word;
			s_runner += size_of_word;
			n -= size_of_word;
		}
	}
	
	return dest;
}

void *MemMove(void *dest, const void *src, size_t n)
{
	unsigned char *d_runner = dest;
	unsigned char *s_runner = (unsigned char *)src;
	
	assert(NULL != dest);
	
	if (NULL == src)
	{
		return NULL;
	}
	
	if( (((size_t)dest > (size_t)src) && (size_t)dest <= ((size_t)src + n)) )
	{
		d_runner += n - 1;
		s_runner += n - 1;
		while (0 < n)
		{
			*d_runner = (unsigned char)*s_runner;
			--d_runner;
			--s_runner;
			--n;
		}			
	}
	else
	{
		dest = MemCpy(dest, src, n);
	} 
	
	return dest;
}















