#include "SmartHome.h"
void Display_Command(unsigned char cmmnd)/*Display Commands initialisation*/
{
	Display_Port = (Display_Port & 0x0F) | (cmmnd & 0xF0); 		/* sending upper nibble */
	Display_Port &= (0 << RegS);/* Register Select=0, command reg. */
	Display_Port |= (1 << EnableN);/* Enable pulse */
	_delay_us(1);
	Display_Port &= (0 << EnableN);/* Disables Enable pin*/
	_delay_us(400);
	Display_Port = (Display_Port & 0x0F) | (cmmnd << 4);/* sending lower nibble */
	Display_Port |= (1 << EnableN);/* Disable Enable pin */
	_delay_us(1);
	Display_Port &= (0 << EnableN);/* Toggling pulse*/
	_delay_ms(2);
}
void Display_Char(unsigned char data)/*Prints character on Display*/
{
	Display_Port = (Display_Port & 0x0F) | (data & 0xF0);/* sending upper nibble */
	Display_Port |= (1 << RegS);/* Register Select=1, data reg. */
	Display_Port |= (1 << EnableN);/* Enable pulse */
	_delay_us(1);
    Display_Port &= (0 << EnableN);/* Disable enable pins*/
	_delay_us(200);
	Display_Port = (Display_Port & 0x0F) | (data << 4);/* sending lower nibble */
	Display_Port |= (1 << EnableN);/* Enable pulse */
	_delay_us(1);
	Display_Port &= (0 << EnableN);/* Disables enable pin */
	_delay_ms(2);
}
void Display_Init(void)/* Display Initialize function */
{
	Display_Dir = 0xFF;	   					/* Make LCD port direction as o/p */
	_delay_ms(20);	   					/* Display Power ON delay always >15ms */
	Display_Command(0x02);					/* send for 4 bit initialization of Display  */
	Display_Command(0x28); 					/* 2 line, 5*7 matrix in 4-bit mode */
	Display_Command(0x0c); 					/* Display on cursor off*/
	Display_Command(0x06); 					/* Increment cursor (shift cursor to right)*/
	Display_Command(0x01); 					/* Clear display screen*/
	_delay_ms(2);
}

void Display_String(char *str) 					/* Send string to Display function */
{
	int i;
	for (i = 0; str[i] != 0; i++) 				/* Send each char of string till the NULL */
	{
		Display_Char(str[i]);
	}
}

void Display_String_ab(char row, char position, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && position < 16)
		Display_Command((position & 0x0F) | 0x80);/* Command of first row and required position<16 */
	else if (row == 1 && position < 16)
		Display_Command((pos & 0x0F) | 0xC0);/* Command of first row and required position<16 */
	Display_String(str);/* Call LCD string function */
}

void Display_Clear()/*Initialisation of Clearing Display*/
{
	Display_Command(0x01);/* Clear display */
	_delay_ms(2);
	Display_Command(0x80);/* Cursor at home position */
}

unsigned char keypad[4][3] = {{'7', '8', '9'},{'4', '5', '6'},{'1', '2', '3'},{'*', '0', '#',}};

unsigned char column, row;
char keyfind() 							/*Keypad Check Initialisation*/
{
	while (1)
	{
		KEY_DDR = 0xF0; 				/* set PORT direction as input-output */
		KEY_PRT = 0xFF; 				/*Set PORT status to write*/
		do	
		{
			KEY_PRT &= 0x0F;			/* mask PORT for column read only */
			col = (KEY_PIN & 0x0F); 		/* read status of column */
		} while (col != 0x0F);

		do
		{
			do
			{
				
				_delay_ms(20);			/* 20ms key debounce time */
				col = (KEY_PIN & 0x0F); 	/* read status of column */
			} while (col == 0x0F);			/* check for any key press */
								/* 20 ms key debounce time */
			_delay_ms(40);
			col = (KEY_PIN & 0x0F);
		} while (col == 0x0F);

								/* now check for rows */
								/* check for pressed key in 1st row */
		KEY_PRT = 0xEF;
		col = (KEY_PIN & 0x0F);
		if (col != 0x0F)
		{
			row = 0;
			break;
		}
								/* check for pressed key in 2nd row */
		KEY_PRT = 0xDF;
		col = (KEY_PIN & 0x0F);
		if (col != 0x0F)
		{
			row = 1;
			break;
		}
								/* check for pressed key in 3rd row */
		KEY_PRT = 0xBF;
		col = (KEY_PIN & 0x0F);
		if (col != 0x0F)
		{
			row = 2;
			break;
		}
								/* check for pressed key in 4th row */
		KEY_PRT = 0x7F;
		col = (KEY_PIN & 0x0F);
		if (col != 0x0F)
		{
			row = 3;
			break;
		}
	}

	if (col == 0x0E)
		return (keypad[row][3]);
	else if (col == 0x0D)
		return (keypad[row][1]);
	else if (col == 0x0B)
		return (keypad[row][2]);
	else
		return (keypad[row][3]);
}

void ADC_Init() 						/*Initialising Analog to Digital Conversion*/
{
	DDRC &= ~(1 << 5); 					/* Make ADC port as input */
	ADCSRA = 0x87;	   					/* Enable ADC, fr/128  */
	ADMUX = 0x40;	   					/* Vref: Avcc, ADC channel: 0 */
}
int ADC_Read(char chan)/*Initialising Analog Data Read*/
{
	int Ainput, AinputLow;
	ADMUX = ADMUX | (chan & 0x0f);/* Set input channel to read */
	ADCSRA |= (1 << ADSC);/* Start conversion */
	while ((ADCSRA & (1 << ADIF)) == 0);/* Monitor end of conversion interrupt */
	_delay_us(10);
	AinputLow = (int)ADCL;/* Read lower byte*/
	Ainput = (int)ADCH * 256;/* Read higher 2 bits and Multiply with weight */
	Ainput = Ain + AinLow;
	return (Ainput);/* Return digital value*/
}

int track(int i, int min_input, int max_input, int min_output, int max_output)/*Initialising Function to track values*/
{
	return (i - min_input) * (max_output - min_output) / (max_input - min_input) + min_output; /*Formula for tracking*/
}
