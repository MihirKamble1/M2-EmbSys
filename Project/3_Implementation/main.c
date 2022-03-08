#include "SmartHome.h"
int main(void)
{
	int c1 = 0, c2 = 0, c3 = 0, result = 0, value, flag1 = 0;
	char string;
	Display_Init(); /*LCD Initialisation*/
up:
	res = password(arr);
	if (res == 1)
	{ /*Gives access to Keypad if password matches*/
		LCD_Clear();
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
			else if (result == '6')/*Air Conditioner Control*/
			{
				PORTC ^= (1 << 6);
			}
			else if (result == '9')/*Room Temperature Display*/
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
					count1++;
				if (PORTC & (1 << 6))
					count2++;
				Display_Clear();
				Display_Char('l');
				Display_Char('i');
				Display_Char('g');
				Display_Char('h');
				Display_Char('t');
				Display_Char('o');
				Display_Char('n');
				Display_Char(':');
				char charvalue = count1 + '0';/*Converts int value into char but only happens for 0-9*/
				Display_Char(charvalue);
				_delay_ms(2500);
				_Clear(); 				/* Clearing LCD */
				Display_Char('F');
				Display_Char('a');
				Display_Char('n');
				Display_Char('o');
				Display_Char('n');
				Display_Char(':');
				char charvalue1 = count2 + '0';
				Display_Char(charvalue1);
				c2 = 0;
				c3 = 0;
				_delay_ms(2000);
				Display_Clear();/* Clearing Display */
				Display_String_xy(0, 1, "Press a key");	/* Send string to LCD with xy position */
			}
			else if (result == '0') 			/*Password Reset*/
			{
				int result = 0;
				result = password(arr);
				if (result == 1)
				{
					LCD_Clear();
					LCD_Init();
					LCD_String("Resetpwd:");
					for (int i = 0; i < 4; i++)
					{
						int res1 = keyfind();
						arr[i] = res1;
						LCD_Char(res1);
					}
					LCD_Clear();
				}
			}
			else if (result == '#') 			/*Microcontroller Reset*/
			{
				PORTC = (0 << 0);
				PORTC = (0 << 1);
				PORTC = (0 << 2);
				PORTC = (0 << 3);
				PORTC = (0 << 4);
				PORTC = (0 << 6);
				PORTB = (0 << 1);
				PORTB = (0 << 2);

				goto up;
			}
		}
	}
}