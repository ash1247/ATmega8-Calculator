#include <avr\io.h>
#include <util\delay.h>
#include "keypad.h"

void KEYPAD_Init()
{
	RowColDirection=0xf0;   // Configure Row lines as O/P and Column lines as I/P
}

void KEYPAD_WaitForKeyRelease()
{
	unsigned char key;
	do
	{
		ROW=0x0f;         // Pull the ROW lines to low and Column high low.
		key=COL & 0x0f;   // Read the Columns, to check the key press
	}while(key!=0x0f);   // Wait till the Key is released,
	// If no Key is pressed, Column lines will remain high (0x0f)
}

void KEYPAD_WaitForKeyPress()
{
	unsigned char key;
	do
	{
		do
		{
			ROW=0x0f;	   // Pull the ROW lines to low and Column lines high.
			key=COL & 0x0F;   // Read the Columns, to check the key press
		}while(key==0x0f); // Wait till the Key is pressed,
		// if a Key is pressed the corresponding Column line go low
		
		_delay_ms(1);		  // Wait for some time(debounce Time);
		
		ROW=0x0f;		  // After debounce time, perform the above operation
		key=COL & 0x0F;	  // to ensure the Key press.
		
	}while(key==0x0f);
	
}

unsigned char KEYPAD_ScanKey()
{
	
	unsigned char ScanKey = 0xe0,i, key;
	
	for(i=0;i<0x04;i++)           // Scan All the 4-Rows for key press
	{
		ROW=ScanKey + 0x0F;         // Select 1-Row at a time for Scanning the Key
		key=COL & 0x0F;             // Read the Column, for key press
		
		if(key!= 0x0F)             // If the KEY press is detected for the selected
		break;                   // ROW then stop Scanning,
		
		ScanKey=(ScanKey<<1)+ 0x10; // Rotate the ScanKey to SCAN the remaining Rows
	}
	
	key = key + (ScanKey & 0xf0);  // Return the row and COL status to decode the key
	
	return(key);
}

unsigned char KEYPAD_GetKey()
{
	unsigned char key;
	
	KEYPAD_WaitForKeyRelease();    // Wait for the previous key release
	_delay_ms(1);
	
	KEYPAD_WaitForKeyPress();      // Wait for the new key press
	_delay_ms(1);
	key = KEYPAD_ScanKey();        // Scan for the key pressed.
	_delay_ms(1);

	switch(key)                       // Decode the key
	{
		case 0xd7: key='0'; break;
		case 0xee: key='1'; break;
		case 0xde: key='2'; break;
		case 0xbe: key='3'; break;
		case 0xed: key='4'; break;
		case 0xdd: key='5'; break;
		case 0xbd: key='6'; break;
		case 0xeb: key='7'; break;
		case 0xdb: key='8'; break;
		case 0xbb: key='9'; break;
		case 0x7e: key='+'; break;
		case 0x7d: key='-'; break;
		case 0x7b: key='x'; break;
		case 0x77: key='/'; break;
		case 0xb7: key='='; break;
		case 0xe7: key='C'; break;
		default: key='z';
	}
	return(key);                      // Return the key
}

unsigned char KEYPAD_GetKeyNum()
{
	unsigned char key;
	
	KEYPAD_WaitForKeyRelease();    // Wait for the previous key release
	_delay_ms(50);
	
	KEYPAD_WaitForKeyPress();      // Wait for the new key press
	_delay_ms(50);
	key = KEYPAD_ScanKey();        // Scan for the key pressed.
	_delay_ms(50);

	switch(key)                       // Decode the key
	{
		case 0xd7: key='0'; break;
		case 0xee: key=0x01; break;
		case 0xde: key=0x02; break;
		case 0xbe: key=0x03; break;
		case 0xed: key=0x04; break;
		case 0xdd: key=0x05; break;
		case 0xbd: key=0x06; break;
		case 0xeb: key=0x07; break;
		case 0xdb: key=0x08; break;
		case 0xbb: key=0x09; break;
		case 0x7e: key=0x0A; break;
		case 0x7d: key=0x0B; break;
		case 0x7b: key=0x0C; break;
		case 0x77: key=0x0D; break;
		case 0xb7: key=0x0E; break;
		case 0xe7: key=0x0F; break;
		default: key='z';
	}
	return(key);                      // Return the key
}