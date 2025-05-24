/*****************************
	Name : Or Beruven

	Reviewed By : Neviu Mamu

	Date Test: 27.1.2023

	Description : header file for atoi/itoa

*****************************/

#ifndef ATOI_H
#define ATOI_H

char *Itoa(int num, char *buffer);
int Atoi(const char *nptr);

char *ItoaForAnyBase(int num, char *buffer, int base);
int AtoiForAnyBase(const char *nptr, int base);

void ThreeArrays(char *arr, char *arr2, char *arr3);

int IsLittleEnd();

#endif
