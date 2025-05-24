/*****************************
	Name : Or Beruven

	Reviewed By : Harel Salhuv
	
	Date Test: 01.02.2023

	Description : c file for bit_array implementation

*****************************/

#include <stddef.h> /*using - size_t*/
#include <assert.h> /*using - assert*/

#include "../include/bit_array.h"

#define BIT_LENGTH 64

static char lut_count[256] = {0};

bit_array_t BitArraySetOn(bit_array_t bitarr, size_t index)
{	
	return bitarr | ((size_t)1 << index);
}

bit_array_t BitArraySetOff(bit_array_t bitarr, size_t index)
{
	return bitarr & (~((size_t)1 << index));
}

bit_array_t BitArraySetVal(bit_array_t bitarr, size_t index, int bool_value)
{
	return bool_value ? BitArraySetOn(bitarr, index) : BitArraySetOff(bitarr, index);
}

bit_array_t BitArraySetAll(bit_array_t bitarr)
{/*no need for first line, could return ~(0)*/
	bitarr = ~(0);
	return bitarr;
}

bit_array_t BitArrayResetAll(bit_array_t bitarr)
{/*no need for first line, could return 0*/
	bitarr = 0;
	return bitarr;
}

int BitArrayGet(bit_array_t bitarr, size_t index)
{
	return (bitarr >> index) & 1;
}

bit_array_t BitArrayFlip(bit_array_t bitarr, size_t index)
{
	return BitArraySetVal(bitarr, index, !BitArrayGet(bitarr, index));
} 

bit_array_t BitArrayMirror(bit_array_t bitarr)
{
	bitarr = ((bitarr & 0xffffffff00000000) >> 32) | ((bitarr & 0x00000000ffffffff) << 32);
	bitarr = ((bitarr & 0xffff0000ffff0000) >> 16) | ((bitarr & 0x0000ffff0000ffff) << 16);
	bitarr = ((bitarr & 0xff00ff00ff00ff00) >> 8) | ((bitarr & 0x00ff00ff00ff00ff) << 8);
	bitarr = ((bitarr & 0xf0f0f0f0f0f0f0f0) >> 4) | ((bitarr & 0x0f0f0f0f0f0f0f0f) << 4);
	bitarr = ((bitarr & 0xcccccccccccccccc) >> 2) | ((bitarr & 0x3333333333333333) << 2);
	bitarr = ((bitarr & 0xaaaaaaaaaaaaaaaa) >> 1) | ((bitarr & 0x5555555555555555) << 1);

	return bitarr;
}

bit_array_t BitArrayRotateLeft(bit_array_t bitarr, size_t step)
{	
	return bitarr << step | bitarr >> (BIT_LENGTH - step);
}


bit_array_t BitArrayRotateRight(bit_array_t bitarr, size_t step)
{
	return BitArrayRotateLeft(bitarr, -step);
}

size_t BitArrayCountOn(bit_array_t bitarr)
{
	size_t count_set = 0;
	
	while(bitarr)
	{
		bitarr = bitarr & (bitarr - 1);
		++count_set;
	}
	
	return count_set;
}

size_t BitArrayCountOff(bit_array_t bitarr)
{
	return BIT_LENGTH - BitArrayCountOn(bitarr);
} 

char *BitArrayToString(bit_array_t bitarr, char *dest)
{
	int i = 0;
	char *runner = dest;
	
	assert(NULL != dest);
	
	for (i = BIT_LENGTH - 1; i >= 0; --i)
	{
		*runner = (char)(BitArrayGet(bitarr, i) + '0');
		++runner;
	}
	
	*runner = '\0';
	
	return dest;
}


bit_array_t BitArrayMirrorLUT(bit_array_t bitarr)
{
	static bit_array_t bitarr_lut[256] = {2};
	static bit_array_t i = 0;
	bit_array_t answer = 0;
	
	
	if (2 == bitarr_lut[0])
	{
		while (i < 256)
		{
			
			bitarr_lut[i] = BitArrayMirror(i) >> 56;
			++i;
		}
	}
	
	for (i = 0; i < 7; ++i)
	{
	
		answer |= bitarr_lut[bitarr & 255] & 255;
		answer = answer << 8;
		bitarr = bitarr >> 8;
	}
	answer |= bitarr_lut[bitarr & 255];
	
	return answer;
}

void BitArrayCountLutInit()
{
	size_t i = 0;
	size_t j = 0;
	size_t count = 0;
	
	for (i = 0; i < 256; ++i)
	{
		count = 0;
		
		for(j = 0; j < 8; ++j)
		{
			if(i & (i << j))
			{
				++count;
			}
		}
		
		lut_count[i] = count;
	}
}

size_t BitArrayCountLut(bit_array_t bitarr)
{
	return (lut_count[bitarr & 0xff] +
			lut_count[(bitarr >> 8) & 0xff] +
			lut_count[(bitarr >> 16) & 0xff] +
			lut_count[(bitarr >> 24) & 0xff] +
			lut_count[(bitarr >> 32) & 0xff] +
			lut_count[(bitarr >> 40) & 0xff] +
			lut_count[(bitarr >> 48) & 0xff] +
			lut_count[(bitarr >> 56) & 0xff]);
}


















