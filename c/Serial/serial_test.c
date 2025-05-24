/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : c file for serialization

*****************************/

#include <stdio.h> /*using printf*/
#include <string.h> /*using - strcpy*/
#include <stdlib.h> /*using - exit*/

#include "serial.h"

static void PrintStudent(student_t *student)
{
	printf("First Name = %s\n", student->f_name);
	printf("Last Name = %s\n", student->l_name);
	printf("Math = %.2f\n", student->student_grades.r_grade.math);
	printf("Physics = %.2f\n", student->student_grades.r_grade.physics);
	printf("Sociology = %.2f\n", student->student_grades.h_grade.sociology);
	printf("Psychology = %.2f\n", student->student_grades.h_grade.psychology);
	printf("Sport = %.2f\n", student->student_grades.s_grade);
	
	return;
}


int main(void)
{
	humanistic_grades_t or_hum;
	real_grades_t or_real;
	grades_t or_grades;
	student_t or_student;
	
	humanistic_grades_t load_hum;
	real_grades_t load_real;
	grades_t load_grades;
	student_t load_student;
	FILE *fp = fopen("test.bin", "w+");
	/*remove warnings */
	(void)load_hum;
	(void)load_real;
	(void)load_grades;
	/*remove warnings */
	
	/*initialize student */
	or_hum.sociology = 80;
	or_hum.psychology = 60;
	or_real.math = 90;
	or_real.physics = 92;
	or_grades.h_grade = or_hum;
	or_grades.r_grade = or_real;
	or_grades.s_grade = 22;
	strcpy(or_student.f_name, "Or");
	strcpy(or_student.l_name, "Beruven");
	/*SetFirstName(&or_student, f_name);
	SetLastName(&or_student, l_name);*/
	or_student.student_grades = or_grades;
	
	printf("Print first student : \n");
	PrintStudent(&or_student);
	if(SaveStudent(fp, &or_student))
	{
		printf("Failure, terminating proccess\n");
		exit(0);
	}
	
	fseek(fp, 0, SEEK_SET);
	
	if(LoadStudent(fp, &load_student))
	{
		printf("Failure, terminating proccess\n");
		exit(0);
	}		
	printf ("\n\n");
	printf("Print second student : \n");
	PrintStudent(&load_student);
	
	fclose(fp);
	
	remove("test.bin");
	
	
	return 0;
}
