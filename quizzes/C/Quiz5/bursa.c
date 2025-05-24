#include <stdio.h>

int Bursa(int arr[], int size, int *low, int *high);
int BursaGood(int arr[], int size, int *low, int *high);
int BursaProfit(int a[], size_t size, int res[2]);

int main(void)
{
	/*int arr[8] = {6, 3, 80, 2, 2, 1, 9, 70};*/
	/*int arr[8] = {10, 3, 7, 2, 9, 10, 11, 12};*/
	/*int low = 0;
	int high = 0;
	int answer = 0;
	
	answer = Bursa(arr, 8, &low, &high);
	
	printf("The indexes are : %d = %d, %d = %d\nThe Profit is %d\n", low, arr[low], high, arr[high],  answer);
	*/
	
	int a[] = {6, 1, 80, 2, 81, 1, 9, 70};
	size_t size = sizeof(a)/sizeof(a[0]);
	int profit = 0;
	int result[2] = { 0 };

	profit = BursaProfit(a, size, result);

	printf("Buy at index: %d\n", result[0]);
	printf("Sell at index: %d\n", result[1]);
	printf("Your profit will be: %d\n", profit);

	return 0;
}

int BursaGood(int arr[], int size, int *low, int *high)
{
	int profit = 0;
	int i =0;
	int curr_low = 0;
	int curr_high = 1;
	int j = 0;
	
	int count_to_debbug = 0;
		
	*low = 0;
	*high = 1;
	

		
	profit = arr[*high] - arr[*low];
	

	
	for (i = 2; i < size; ++i)
	{
		while (arr[i] > arr[curr_high] && i < size)
		{
			
			curr_high = i;
			++i;	
		}
		
		for (j = curr_low + 1; j < curr_high; ++j)
		{
			if (arr[j] < arr[curr_low])
			{
				curr_low = j;
			}
		}
		
		if (arr[curr_high] - arr[curr_low] > profit)
		{
			*high = curr_high;
			*low = curr_low;
			profit = arr[*high] - arr[*low];
		}
		
		printf("Rotation %d\n", ++count_to_debbug);
	}
	return profit;		
}

int Bursa2(int arr[], int size, int *buy, int *sell)
{
	int i = 0;
	int curr_buy = 0;
	int curr_sell = 0;
	int curr_prof = 0;
	int max_prof = 0;
	
	*buy = 0;
	*sell = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (arr[i] > arr[curr_sell])
		{
			if(arr[curr_buy] > arr[curr_sell])
			{
				curr_buy = curr_sell;
			}
			
			curr_prof = arr[curr_buy] - arr[curr_sell];
		}
		
		if (curr_prof > max_prof)
		{
			max_prof = curr_prof;
			*buy = curr_buy;
			*sell = curr_sell;
		}
		
		if (arr[i-1] > arr[i])
		{
			curr_buy = i;
			curr_sell = i;
		}
	}
	return max_prof;
}

int BursaProfit(int a[], size_t size, int res[2])
{
	size_t i = 0;
	int max = a[0], profit = 0;
	int min_index = 0, max_index = 0;
	int most_min = a[0], most_min_index = 0;

	for (i = 0 ; i < size ; i++)
	{
		
		if ((a[i] - most_min > profit) || (max < a[i]))
		{
			max = a[i];
			max_index = i;
			profit = a[i] - most_min;
			min_index = most_min_index;
		}
		if (most_min > a[i])
		{
			most_min = a[i];
			most_min_index = i;
		}
		
	}

	res[0] = min_index;
	res[1] = max_index;
	
	return profit;

}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
