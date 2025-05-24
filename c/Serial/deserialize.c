/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for

*****************************/

#include <stdio.h> /*using printf*/
#include <assert.h> /*using assert*/

#include "serial.h"

static float LoadFloat(FILE *fp);
static flag LoadLastName(FILE *fp, student_t *st);
static flag LoadFirstName(FILE *fp, student_t *st);

flag LoadStudent(FILE *fp, student_t *student)
{
	assert(NULL != fp);
	assert(NULL != student);
	
	if(LoadFirstName(fp, student))
	{
		printf("terminating program %d\n", __LINE__);
		return FAILURE;
	}
	
	if(LoadLastName(fp, student))
	{
		printf("terminating program %d\n", __LINE__);
		return FAILURE;
	}
	
	student->student_grades.r_grade.math = LoadFloat(fp);
	student->student_grades.r_grade.physics = LoadFloat(fp);
	student->student_grades.h_grade.sociology = LoadFloat(fp);
	student->student_grades.h_grade.psychology = LoadFloat(fp);
	student->student_grades.s_grade = LoadFloat(fp);
	
	
	return SUCCESS;
}

static float LoadFloat(FILE *fp)
{
	float to_ret = 0;
	
	assert(NULL != fp);	
		
	if(4 != fread(&to_ret, 1, 4, fp))
	{
		printf("An error occured while reading %d\n", __LINE__);
		return FAILURE;
	}
	
	return to_ret;
}

static flag LoadLastName(FILE *fp, student_t *st)
{
	int i = -1;
	
	assert(NULL != fp);
	assert(NULL != st);
	
	do
	{
		++i;
		
		if(1 != fread((st->l_name + i), 1, 1, fp))
		{
			printf("An error occured in reading %d\n", __LINE__);
			return FAILURE;
		}
		
	}while('\0' != *(st->l_name + i));
	
	return SUCCESS;
}

static flag LoadFirstName(FILE *fp, student_t *st)
{
	int i = -1;
	
	assert(NULL != fp);
	assert(NULL != st);
	
	do
	{
		++i;
		
		if(1 != fread((st->f_name + i), 1, 1, fp))
		{
			printf("An error occured in reading %d\n", __LINE__);
			return FAILURE;
		}
		
	}while('\0' != *(st->f_name + i));
	
	return SUCCESS;
}


