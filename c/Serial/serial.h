/*****************************
	Name : Or Beruven

	Reviewed By :

	Date Test:

	Description : header file for serialization

*****************************/

#ifndef SERIAL_H
#define SERIAL_H

#define NAME_SIZE 16

typedef enum {SUCCESS, FAILURE}flag;


typedef struct real_grades
{
    float math;
    float physics;
}real_grades_t;

typedef struct humanistic_grades
{
    float sociology;
    float psychology;
}humanistic_grades_t;

typedef struct grades
{
    humanistic_grades_t h_grade;
    real_grades_t r_grade;
    float s_grade;
}grades_t;

typedef struct student
{
    char f_name[NAME_SIZE];
    char l_name[NAME_SIZE];
    grades_t student_grades;
}student_t;

flag SaveStudent(FILE *fp, student_t *student);
flag LoadStudent(FILE *fp, student_t *st);
#endif
