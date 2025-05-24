#ifndef INPUT_KEY_H
#define INPUT_KEY_H

/*********************

Written by - or.beruven
Reviewed by - neviu.mamo

*********************/


/* main function to call to */
void IfInputKey();
void SwitchInputKey();
void LutInputKey();

/*all lut funtions */
/*functions that LutInputKey will call */
void a(void);
void t(void);
void empty(void);

/*dicleration of 256 (sizeof(ASCII)) functions - one for each character */
/*#define SIZE 256
typedef void(*lut[SIZE])(void);
static lut pf;
*/

#endif
