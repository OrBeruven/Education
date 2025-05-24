#include <stdio.h>

#define ARR_SIZE 9

int MaxSubArr(int arr[], int size, int *left_indice, int *right_indice)
{
	int curr_max = 0;
	int temp_max = 0;
	int i = 0;
	int left_indice_max = 0;
	int bigger_left = 0;
	
	*left_indice = 0;
	*right_indice = 1;
	
	for( i = 2; i < size; ++i)
	{
		if (arr[i] > arr[bigger_left])
		{
			bigger_left = i;
		}
		
		temp_max = curr_max + arr[i];
		left_indice_max = 0;
		
		if (temp_max > curr_max)
		{
			curr_max = temp_max;
			*right_indice = i;
		}
		
		if (left_indice_max > curr_max)
		{
			curr_max = left_indice_max;
			*left_indice = bigger_left;
			*right_indice = i;
		}
	}
	
	return curr_max;
}

int maxSubArraySum(int arr[], int size, int *ptr1, int *ptr2)
{
    int i =0;
    int max_so_far = 0;
    int max_ending_here = 0;
    int counter = 0;
    
    for ( i = 0; i < size; i++)
    {
        
        max_ending_here += arr[i];
        
        if (max_ending_here < 0)
        {
            max_ending_here = 0;   
            counter = 0;
        }
        
        if (max_so_far < max_ending_here)
        {
            max_so_far = max_ending_here;
            ++counter;
            *ptr1 = i - counter;
            *ptr2 = i;
        }
    }
    return max_so_far;
}

int main(void)
{
	int arr[ARR_SIZE] = {-2, -3, -3, 4, -1, -2, -19, -5, 4};
	int left_indx = 0;
	int right_indx = 0;
	int maxSum = 0;
	
	printf("%d is the max int indexes %d and %d\n", (MaxSubArr(arr, ARR_SIZE, &left_indx, &right_indx)), left_indx, right_indx);
	
	    
	maxSum = maxSubArraySum(arr, ARR_SIZE, &left_indx, &right_indx);
    
	printf("%d is the max int indexes %d and %d\n", maxSum, left_indx, right_indx);

	
	return 0;
}
