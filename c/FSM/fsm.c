/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h>

#define ASCII_TO_INT(ch) ((ch) - 48)

typedef enum { IDLE, FIRST_0, ERROR_STATE, ACCEPT_STATE, MAX_STATES }state_t;

typedef enum { ZERO, ONE, BREAK, MAX_EVENTS }event_t;

static event_t ReadEvent(void);
int IfElse(void);
int STT(char *str);

int stt[MAX_STATES][MAX_EVENTS - 1] = 	{{FIRST_0, ERROR_STATE},
										{ACCEPT_STATE, FIRST_0},
										{ERROR_STATE, ERROR_STATE},
										{ACCEPT_STATE, FIRST_0}};

state_t state = IDLE;
event_t event = ONE;

int main(void)
{
	char *str1 = "1001011100010";
	char *str2 = "0000101010101";
	char *str3 = "0111100101010";

	STT(str1);
	STT(str2);
	STT(str3);
	
	return 0;
}

int STT(char *str)
{
	state = IDLE;
	
	while ('\0' != *str)
	{
		state = stt[state][ASCII_TO_INT(*str)];
		++str;
	}
	
	if (ACCEPT_STATE == state)
	{
		printf("Valid Input\n");
		return 0;
	}
	else
	{	
		printf("InValid Input\n");
		return 1;
	}
}

int IfElse(void)
{
	while (1)
	{
		event = ReadEvent();
		
		if (ONE != event && ZERO != event && BREAK != event)
		{
			printf("Invalid Input\n");
			continue;
		}
		else if (BREAK == event)
		{
			break;
		}
		
		if (IDLE == state)
		{
			if (ZERO == event)
			{
				state = FIRST_0;
			}
			else
			{
				state = ERROR_STATE;
			}
		}
		else if (FIRST_0 == state)
		{
			if (ZERO == event)
			{
				state = ACCEPT_STATE;
			}
		}
		else if (ACCEPT_STATE == state)
		{
			if (ONE == event)
			{
				state = FIRST_0;
			}
		}
		
		printf("state %d\n", state);
	
	}	
	
	if (ACCEPT_STATE == state)
	{
		printf("VALID INPUT\n");
	}
	else
	{
		printf("IN_VALID INPUT\n");
	}
	
	return 0;
}

static event_t ReadEvent(void)
{
	int to_ret = ONE;
	printf("Enter %d, %d or %d :", ZERO, ONE, BREAK);
	scanf("%d", &to_ret);
	return (event_t)to_ret;
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
