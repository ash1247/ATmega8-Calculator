/*
* main.c
*
*  Created: 30-Dec-18 2:47:42 PM
*  Author: Ashik
*/

#ifndef F_CPU

#define F_CPU 1000000UL

#endif

#include "calculator.h"

int main(void) {
	cal_init();

	lcd_gotoxy(0, 0);
	lcd_puts("Press AC");
	lcd_gotoxy(1, 4);
	lcd_puts("to begin");
	//dis_string(0,0,"Press AC");
	//dis_string(1,4,"to begin");
	
	_delay_ms(100);
	
	//for (int start = 0; start < 25; ++start) {
		//_delay_ms(5);
		//dis_shift('L');
	//}

	while(1) {
		calculate();
	}
}