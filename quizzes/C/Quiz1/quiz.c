# include <stdio.h>

void Q1();
void Q2();

int main(void)
{
	Q2();
	return 0;
}

void Q1()
{
	int num = 0;
	const int num2 = 6;
	/*const int num3 = 1;
	char ch = 'a';*/
	
	printf("%d\n", num);
	scanf("%d", &num);
	printf("100 divided by %d is %f", num, 100/(float)num);
	

	
	num = num2 - 5; /*num 3 const*/
	printf("%f\n", (float)num);
	
	num = 4.7;
	
}

void Q2()
{
	if(-1 < (unsigned char)1)
	{
		printf("A");
	}
	else
	{
		printf("B");
	}
	
	
	/*Doesnt Compile
	if(-1 < (unsigned int)1)
	{
		printf("A");
	}
	else
	{
		printf("B");
	}*/
	
}
	
	
	
	
	
