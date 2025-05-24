#include <stdio.h>
#include <stdlib.h>

/*bad version from test (mine) */
int *IsSumFound(int arr[], int sum, int size);

/*	Good version 	*/
int *IsSumFoundGood(int arr[], int sum, int size);

int main(void)
{
	int arr[5] = {2, 4, 7, 12, 14};
	int *answer;
	answer = IsSumFoundGood(arr, 21, 5);
	
	printf("The answer indexes are %d + %d\n", answer[0] ,answer[1]);
	
	free(answer);
	return 0;
}

int *IsSumFound(int arr[], int sum, int size)
{
	int i = 0;
	int j = 0;
	
	/*to_ret is a local variable,
	needs to be change to dynamic */
	int *to_ret;
	to_ret	= (int *)malloc(sizeof(int) * 2);
	
	for (i = 0; i < size; ++i)
	{
		/*making j = i saves me all numbers
		between 0 to i */
		for (j = (i + 1); j < size; ++j)
		{
			if (arr[i] + arr[j] == sum)
			{
				to_ret[0] = i;
				to_ret[1] = j;
				
				/*i can set i to size to break both loops
				and have only 1 return at the end */
				return to_ret;
			}
			
			if (arr[i] + arr[j] > sum)
			{
				break;
			}
		}
	}
	
	return to_ret;
}

int *IsSumFoundGood(int arr[], int sum, int size)
{
	int left = 0;
	int right = size - 1;
	int *to_ret;
	to_ret	= (int *)malloc(sizeof(int) * 2);
	
	while (left < right)
	{
		if ((arr[left] + arr[right]) == sum)
		{
			to_ret[0] = left;
			to_ret[1] = right;
			
			/*exit loop to send return */
			right = left;
		}
		else if	((arr[left] + arr[right]) > sum)
		{
			--right;
		}
		else if ((arr[left] + arr[right]) < sum)
		{
			++left;
		}
	}
	
	return to_ret;
}
























