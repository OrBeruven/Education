/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for serialization

*****************************/

#include <stdio.h> /*using fwrite, printf */
#include <assert.h> /*using - assert*/
#include <string.h> /*using - strlne*/

#include "serial.h"

static flag SerialFloat(FILE *fp, float *f);
static flag SerialFirstName(FILE *fp, student_t *st);
static flag SerialLastName(FILE *fp, student_t *st);


flag SaveStudent(FILE *fp, student_t *student)
{
	size_t i = 0;
	
	assert(NULL != fp);
	assert(NULL != student);
	
	if(SerialFirstName(fp, student))
	{
		return FAILURE;
	}
	else if(SerialLastName(fp, student))
	{
		return FAILURE;
	}
	else
	{
		/*sending to load each grade in a loop from realistic grades*/
		/*will be faster if we'll have more grades*/
		for(i = 0; sizeof(student->student_grades.r_grade) / 4 > i; ++i)
		{
			if(SerialFloat(fp, (float *)(&student->student_grades.r_grade) + i))
			{
				return FAILURE;
			}
		}
		
		/*sending to load each grade in a loop from humanistic grades*/
		for(i = 0; sizeof(student->student_grades.r_grade) / 4 > i; ++i)
		{
			if(SerialFloat(fp, (float *)(&student->student_grades.h_grade) + i))
			{
				return FAILURE;
			}
		}
		
		if(SerialFloat(fp, &student->student_grades.s_grade))
		{
			return FAILURE;
		}
		
		return SUCCESS;
	}
}


static flag SerialFloat(FILE *fp, float *f)
{
	assert(NULL != fp);
	assert(NULL != f);
	if(sizeof(float) != fwrite(f, 1, sizeof(float), fp))
	{
		printf("An error occured in writing %d\n", __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}

static flag SerialFirstName(FILE *fp, student_t *st)
{
	char ch = '\0';
	
	assert(NULL != fp);
	assert(NULL != st);
	
	/*loading the whole buffer wich is first name*/
	if(1 != fwrite(st->f_name, strlen(st->f_name), sizeof(char), fp))
	{
		printf("An error occured in writing %d\n", __LINE__);
		return FAILURE;
	}
	
	/*adding the null terminator*/
	if(sizeof(char) != fwrite(&ch, 1, sizeof(char), fp))
	{
		printf("An error occured in writing %d\n", __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}


static flag SerialLastName(FILE *fp, student_t *st)
{
	char ch = '\0';
	
	assert(NULL != fp);
	assert(NULL != st);
	
	/*loading the whole buffer wich is Last name*/
	if(1 != fwrite(st->l_name, strlen(st->l_name), sizeof(char), fp))
	{
		printf("An error occured in writing %d\n", __LINE__);
		return FAILURE;
	}
	
	/*adding the null terminator*/
	if(sizeof(char) != fwrite(&ch, 1, sizeof(char), fp))
	{
		printf("An error occured in writing %d\n", __LINE__);
		return FAILURE;
	}
	
	return SUCCESS;
}














