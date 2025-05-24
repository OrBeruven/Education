/*********************

Written by - or.beruven
Reviewed by - neviu.mamo

*********************/

#include <stdio.h> /*using - getchar, printf */
#include <stdlib.h> /*using - system function */

/*local lib */
#include "InputKey.h"

/*moving the typedef to main to improve readability
, a point from the reviewer*/
#define SIZE 256
typedef void(*lut[SIZE])(void);
lut pf;

void LutInputKey()
{
	unsigned char ch = 0;
	int i = 0;
	
	/* initialzing all pf functions to an empty */
	for (i = 0; SIZE > i; ++i)
	{
		pf[i] = empty;
	}
	
	/* hard coding initializing for specific cases */
	pf[97] = &a;
	pf[65] = &a;
	pf[116] = t;
	pf[84] = t;
	
	/*disabling the echo and special characters */
	system("stty -icanon -echo");
	printf("Press 'Esc' to exit\nA and T for Message\n");
	do
	{
		ch = getchar();
		
		pf[(int)ch]();
		
	} while(27 != ch);
	
	/* enabling again the echo and special characters */
	system("stty icanon echo");	
	printf("BYEEE\n");
	return;
}
/*A pressed */
void a(void)
{
	printf("A pressed\n");
	return;
}

/*T pressed */
void t(void)
{
	printf("T pressed\n");
	return;
}

/*Empty fucntion for all other cases in pf */
void empty(void)
{
	return;
}

/* If implementation */
void IfInputKey()
{
	char ch = 0;
	
	system("stty -icanon -echo");
	printf("Press 'Esc' to exit\nA and T for Message\n");
	while(27 != ch)
	{
		ch = getchar();
		
		if (65 == ch || 97 == ch)
		{
			printf("A pressed\n");
		}
		else if (84 == ch || 116 == ch)
		{
			printf("T pressed\n");
		}
	}
	system("stty icanon echo");	
	printf("BYEEEEE\n");
	return;
}

/*Switch implementation */
void SwitchInputKey()
{
	char ch = 0;
	
	system("stty -icanon -echo");
	printf("Press 'Esc' to exit\nA and T for Message\n");
	
	while (27 != ch)
	{
		ch = getchar();
		
		switch (ch)
		{
			/* in case of 65 ('A') and 97 ('a') do them both */
			case 65:
			case 97:
				printf("A pressed\n");
				break;
			/* in case of 84 ('T') and 116 ('t') do them both */
			case 84:
			case 116:
				printf("T pressed\n");
				break;
				
			/*In any other case (Esc / other) no need for specific case */
		}
	}
		
	system("stty icanon echo");
	printf("BYEEEEE\n");
	
	return;
}
