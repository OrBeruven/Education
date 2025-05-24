/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

char *FlipWord(char *sentence, int word_start, int word_end)
{
	char temp = 0;
	
	for(; word_start < word_end; ++word_start, --word_end)
	{
		temp = sentence[word_start];
		sentence[word_start] = sentence[word_end - 1];
		sentence[word_end - 1] = temp;
	}
	
	return sentence;
} 

char *RevWords(char *str)
{
	size_t word_length = 1;
	size_t i = 0;
	
	while ('\0' != str[i])
	{
		if((char)32 == str[i])
		{
			str = FlipWord(str, i - word_length + 1, i);
			word_length = 0;
		}
		
		++word_length;
		++i;
	}
	
	str = FlipWord(str, i - word_length + 1, i);
	
	str = FlipWord(str, 0, i);


	return str;
}	


int main(void)
{
	char sentence[30] = " Pleasebeupside down";
	
	printf("normal string : %s\n", sentence);
	
	RevWords(sentence);
	
	printf("after reverse : %s\n", sentence);
	
	return 0;
}
