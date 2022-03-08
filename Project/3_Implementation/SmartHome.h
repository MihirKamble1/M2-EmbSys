#ifndef __SmartHome__H__
#define __SmartHome__H__
#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif
#define F_CPU 8000000UL                     /*CPU Frequency*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

/**
 * PORT B
 * Allotting LCD data port direction
 * Allotting Register Select pin
 * Allotting LCD data port
 * Allotting Enable signal pin
 */
#define Display_Dir DDRB                       /* Allotting Display data port direction */
#define Display_Port PORTB                     /* Allotting Display data port */
#define RegS PB0                             /* Allotting Register Select pin */
#define EnableN PB1                             /* Define Enable signal pin */

/**
 * For PortC
 * Allotting data port direction for Output
 * Allotting data port for Output
 * Allotting data read pin for Output
 */
#define DIS_DDR DDRC                        /* Allotting data port direction for Output */
#define DIS_PRT PORTC                       /* Allotting data port for Output*/
#define DIS_PIN PINC                        /* Allotting data read pin for Output*/

/**
 * PORT D
 * Allotting data port direction for Keypad
 * Allotting data port for keypad
 * Allotting data read pin for Keypad
 */
#define KEY_DDR DDRD                        /* Allotting data port direction for Keypad */
#define KEY_PRT PORTD                       /* Allotting data port for keypad*/
#define KEY_PIN PIND                        /* Allotting data read pin for Keypad*/

/**
 * @brief Performs all the Display commands
 * @param cmmnd
 */
void Display_Command(unsigned char cmmnd);     /*Display Commands initialisation*/

/**
 * @brief Prints Character on the Display
 * @param data
 */
void Display_Char(unsigned char data);/*Prints character on display*/

/**
 * @brief Initialises Display
 */
void Display_Init(void);/* Display Initialize function */

/**
 * @brief Prints string on the LCD Screen
 * @param str
 */
void Display_String(char *str);/* Send string to Display function */

/**
 * @brief Displays string by selecting exact rows and columns
 * @param row
 * @param position
 * @param str
 */
void Display_String_ab(char row, char position, char *str); /* Send string to Display with ab position */

/**
 * @brief Clears Display
 */
void Display_Clear();/*It Clears the display*/

/**
 * @brief Detect the Kepad button we press
 * @return char
 */
char keyfind();                          /*Keypad Check Initialisation*/

/**
 * @brief 
 * @param i
 * @param min_input
 * @param max_input
 * @param min_output
 * @param max_output
 * @return int
 */
int track(int i, int min_input, int max_input, int min_output, int max_output); /*Initialising Function to track values*/

/**
 * @brief Reads Analog bits and convert them into digital
 * @param channel
 * @return int
 */
int ADC_Read(char channel);              /*Initialising Analog to Digital Conversion*/

/**
 * @brief Initialises analog to digital conversion
 */
void ADC_Init();                         /*Initialising Analog Data Read*/
#endif