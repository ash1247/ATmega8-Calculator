#ifndef KEYPAD_H
#define KEYPAD_H

#include <avr\io.h>
#include <util\delay.h>
#define RowColDirection DDRD //Data Direction Configuration for keypad
#define ROW PORTD            //Lower four bits of PORTD are used as ROWs
#define COL PIND

//Rows are connected to lower 4-bits of PORTD
//Cols are connected to higher 4-bits of PORTD
void KEYPAD_Init();


//Description  : This function the rows and columns for keypad scan
//ROW lines are configured as Output.
//Column Lines are configured as Input.
//I/P Arguments:none
//Return value : none
void KEYPAD_WaitForKeyRelease();

//Description  : This function waits till the previous key is released.
//All the ROW lines are pulled low.
//Column Lines are read to check the key press.
//If all the Keys are released then Column lines will remain high(0x0f)
//I/P Arguments:none
//Return value	: none
void KEYPAD_WaitForKeyPress();

//Description  : This function waits till a new key is pressed.
//All the ROW lines are pulled low.
//Column Lines are read to check the key press.
//If any Key is pressed then corresponding Column Line goes low.
//Wait for Some time and perform the above operation to ensure the True Key Press before decoding the KEY.
//I/P Arguments:none
//Return value	: none
unsigned char KEYPAD_ScanKey();

//Description  :This function scans all the rows to decode the key pressed.
//Each time a ROW line is pulled low to detect the KEY.
//Column Lines are read to check the key press.
//If any Key is pressed then corresponding Column Line goes low.
//Return the ScanCode(Combination of ROW & COL) for decoding the key.
//I/P Arguments:none
//Return value	: char--> Scancode of the Key Pressed
unsigned char KEYPAD_GetKey();

unsigned char KEYPAD_GetKeyNum();

#endif //KEYPAD_H