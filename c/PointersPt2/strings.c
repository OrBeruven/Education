#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*	calculate the length of the string	*/
int Strlen(const char* str);

/*	compare size of two strings	*/
int Strcmp(const char* str1, const char* str2);

/*	making a copy of the second string	*/
char *Strcpy(char* dest, const char* source);

/*	copying string 1 into string2 for count amount of arguments	*/
char *Strncpy(char *dest, const char *source, size_t count);

/*	comparing like strcmp but for n arguments	*/
int Strncmp(const char *str1, const char *str2, size_t num);

/*	compate strings without case sensitive	*/
int Strcasecmp(const char *str1, const char *str2);

/*	finds the address where char wanted found and returns pointer to it*/
char *Strchr(const char *str, int c);

/*	making a duplicate via malloc	*/
char *Strdup(const char *str);

/*	making string of dest+source	*/
char *Strcat(char *dest, const char *source);

/*	making string of dest+source by n characters	*/
char *Strncat(char *dest, const char *src, size_t n);

/*	searching sub-text in main str	*/
char *Strstr(const char *source, const char *find);

/*	searching sub in source	*/
size_t Strspn(const char *source, const char *find);

/*	check if palindrome	*/
int IsPalindrome(const char *pal);

void SevenBoom(int from, int to);


int main(void)
{
	char *str = "123";
	
	*str = 'a';
	
	/*
	char *str = "dabaasdvdd";
	char *find = "dcvb";
	char *temp = Strchr(str, *find);
	printf("The strchr returns : %s\n", temp);
	printf("The number of times found in string : %ld\n", Strspn(str, find));
	*/
	return 0;
}

/*	returning the count	*/
int Strlen(const char* str)
{
	int count = 0;
	
	/*	adding assert for extreme case	*/
	assert(NULL != str);
	
	if(*str)
	{
		while(*(str+count) != '\0')
		{
			count++;
		}
	}
	
	return count;
}

/*	if first string is lexocraphy bigger, return positive
	if second is bigger return negetive,
	if equal returns 0									*/
int Strcmp(const char* str1, const char* str2)
{
	/*	adding assert for extreme case	*/
	assert(NULL != str1 && NULL != str2);
	
	if(*str1 || *str2)
	{
		while(*str1 == *str2 && '\0' != *str1)
		{
			str1++;
			str2++;
		}
	}
	
	return *str1 - *str2;
}

/*	input value of string2 into string1	*/
char* Strcpy(char* dest, const char* source)
{
	int count = 0;
	
	assert(dest && source);
	
	while('\0' != *(source+count))
	{
		*(dest + count) = *(source + count);
		count++;
	}
	
	*(dest+count) = '\0';
	
	return dest;
}

/*	copying string 1 into string2 for count amount of arguments	*/
char *Strncpy(char *dest, const char *source, size_t count)
{
	size_t i = 0;
	assert(dest && source);
	
	while(i < count)
	{
		while('\0' != *(source + i) && i < count)
		{
			*(dest + i) = *(source + i);
			i++;
		}
		*(dest +i ) = '\0';
		i++;
	}
	
	return dest;
}

/*	comparing like strcmp but for n arguments	*/
int Strncmp(const char *str1, const char *str2, size_t num)
{	
	/*	Checking if memory is available, if not sending an error message */
	if(NULL == str1 || NULL == str2)
	{
		printf("\n\n***\tERROR FINIDING MEMORY\t***\n***\tRETURNING VALUE 0  \t***\n\n");
		return 0;
	}
	
	while(1 < num && '\0' != *str1 && *str1 == *str2)
	{
		str1++;
		str2++;
		num--;
	}
	
	return *str1 - *str2;
}

/*	comparing the two strings without case sensitive	*/
int Strcasecmp(const char *str1, const char *str2)
{
	/*	Checking if memory is available, if not sending an error message */
	if(NULL == str1 || NULL == str2)
	{
		printf("\n\n***\tERROR FINIDING MEMORY\t***\n***\tRETURNING VALUE 0  \t***\n\n");
		return 0;
	}
	
	while('\0' != *str1 && tolower(*str1) == tolower(*str2))
	{
		str1++;
		str2++;
	}
	
	return tolower(*str1) - tolower(*str2);
}

/*	searching for the character wanted and returning his address	*/
char* Strchr(const char *str, int c)
{
	/*	Checking if memory is available, if not sending an error message */
	if(NULL == str || '\0' == *str)
	{
		printf("\n\n***\tERROR FINIDING MEMORY\t***\n***\tRETURNING VALUE 0  \t***\n\n");
		return NULL;
	}
	
	while('\0' != *str)
	{
		if (c == (int)*str)
		{
			return (char *)str;
		}
		str++;
	}
	return NULL;
}

char *Strdup(const char *str)
{
	char *to_ret;
	
	if(NULL == str)
	{
		printf("\n\n***\tERROR FINIDING MEMORY\t***\n***\tRETURNING VALUE NULL  \t***\n\n");
		return NULL;
	}
	
	to_ret = (char *) malloc(Strlen(str) + 1 * sizeof(char));
	
	if(NULL == to_ret)
	{
		printf("\n\n***\tERROR ALLOCATING MEMORY\t***\n***\tRETURNING VALUE NULL  \t***\n\n");
		return NULL;
	}
		
	return Strcpy(to_ret, str);
}

/*	making string of dest+source	*/
char *Strcat(char *dest, const char *source)
{
	char *ptr = dest;
	
	if(NULL == dest || NULL == source)
	{
		printf("\n\n***\tERROR ALLOCATING MEMORY\t***\n***\tRETURNING VALUE NULL  \t***\n\n");
		return NULL;
	}
	
	while('\0' != *dest)
	{
		dest++;
	}
	
	while('\0' != *source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
	return ptr;
}


/*	making string of dest+source by n characters	*/
char *Strncat(char *dest, const char *source, size_t n)
{	
	/*	same basiic code as Strcat
		only difference is in while loop
		we make n comparison and lowering its value	*/
	char *ptr = dest;
	
	if(NULL == dest || NULL == source)
	{
		printf("\n\n***\tERROR ALLOCATING MEMORY\t***\n***\tRETURNING VALUE NULL  \t***\n\n");
		return NULL;
	}
	
	while('\0' != *dest)
	{
		dest++;
	}
	
	while('\0' != *source && 0 < n)
	{
		*dest = *source;
		dest++;
		source++;
		n--;
	}
	*dest = '\0';
	return ptr;
}	

/*	searching sub-text in main str	
	returns NULL if didnt found ot had
	a problem							*/
char *Strstr(const char *source, const char *find)
{
	char *main_ptr;
	char *sub_ptr;

	if(NULL == source || NULL == find)
	{
		printf("\n\n***\tERROR ALLOCATING MEMORY\t***\n***\tRETURNING VALUE NULL  \t***\n\n");
		return NULL;
	}
	
	while('\0' != *source)
	{
		sub_ptr = (char *)find;
		main_ptr = (char *)source;
		
		while (*sub_ptr == *main_ptr)
		{
			if('\0' == *(sub_ptr + 1))
			{
				return (char *)source;
			}
			else if('\0' == *main_ptr)
			{
				return NULL;
			}
			
			sub_ptr++;
			main_ptr++;
		}
		
		source++;
	}
	
	return NULL;
}	

/**/	
size_t Strspn(const char *source, const char *find)
{
	size_t count = 0;
	char *find_head = (char *)find;
	while('\0' != *source)
	{
		find = find_head;
		while ('\0' != *find)
		{
			if (*source == *find)
			{
				count++;
				break;
			}
			else
			{
				find++;
			}
		}
		source++;
	}
	
	return count;
}
	
	
/*	check if palindrome	*/
int IsPalindrome(const char *pal)
{
	int len = Strlen(pal) - 1;
	
	/*	Checking if memory is available, if not sending an error message */
	if (NULL == pal)
	{
		printf("\n\n***\tERROR ALLOCATING MEMORY\t***\n***\tRETURNING VALUE 0  \t***\n\n");
		return 0;
	}
	
	while ((pal + len) > pal)
	{
		if(*pal != *(pal + len))
		{
			printf("Isnt palindrome...\n");
			return 0;
		}
		
		pal++;
		len -= 2;
	}
	printf("Is palindrome...\n");
	return 1;
}		


void SevenBoom(int from, int to)
{
	int temp =0;
	while (from <= to)
	{	
		temp = from;
		
		if (from % 7 == 0)
		{
			printf("BOOM prec \n");
		}
		else
		{
			while (from > 1)
			{
				if ((from % 10) == 7)
				{
					temp++;
					printf("BOOM / \n");
					from = 1;
					break;
				}
				else
				{
					from /= 10;
				}
			}
			from = temp;
			printf("%d\n", from);
		}
		
		from = temp + 1;
		
	}
	
	printf("%d\n", temp);
	return;
}
			
		
		
		
		
		
	
	
	
	
	
		
		



