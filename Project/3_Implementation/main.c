#include "SmartHome.h"
int main(void)
{
	int val = 0, value, flag1 = 0,start=0;
	char string;
	Display_Init(); /*LCD Initialisation*/
up:
	start = 1;
	if (start == 1)
	{ 
		Display_Clear();
		DDRC = 0xFF;
		while (1)
		{

			Display_String_ab(0, 1, "Press a key");/* Send string to display with ab position */
			Display_Command(0xc0);/*Display Initialisation with first row and required position<16*/
			char result = keyfind();
			Display_Char(result);
			if (result == '1')/*Main door Opens*/
			{

				PORTC ^= (1 << 0);
			}
			else if (result == '2')/*Main door Closes*/
			{
				PORTC ^= (1 << 1);
			}
			else if (result == '3')/*Light1 Control*/
			{ 							

				PORTC ^= (1 << 2);
			}
			else if (result == '4')/*Air Conditioner Control*/
			{
				PORTC ^= (1 << 6);
			}
			else if (result == '5')/*Room Temperature Display*/
			{
				char String[5];
				int value;
				Display_Clear();
				ADC_Init();
				Display_Init();/* Initialization Display */
				Display_Command(0xd4);/* LCD16x2 cursor position */
				Display_String("TEMP: ");/* Write string on 1st line of Display */
				value = ADC_Read(5);/* Read ADC channel 5 */
				int val = track(value, 492, 478, 20, 35); /* Calling track Function*/
				itoa(val, String, 10);/* Integer to string conversion */
			    Display_String(String);/* Initialising Display String */
				Display_String("  ");
				_delay_ms(2000);
				Display_Clear();/* Clearing Display */
				Display_Init();/* Initialisation of Display */
			}
			/* Tell the Light and AC is on or not*/
			else if (result == '*')
			{ 
				if (PORTC & (1 << 2))
				if (PORTC & (1 << 6))
				Display_Clear();
				Display_Char('l');
				Display_Char('i');
				Display_Char('g');
				Display_Char('h');
				Display_Char('t');
				Display_Char('o');
				Display_Char('n');
				_delay_ms(3000);
				_Clear(); 				/* Clearing Display */
				Display_Char('A');
				Display_Char('C');
                Display_Char('O');
                Display_Char('N');
                _Clear();
				Display_String_ab(0, 1, "Press a key");	/* Send string to Display with ab position */
			}
			
			else if (result == '#') 			/*Microcontroller Reset*/
			{
				PORTC = (0 << 0);
				PORTC = (0 << 1);
				PORTC = (0 << 2);
				PORTC = (0 << 6);

				goto up;
			}
		}
	}
}