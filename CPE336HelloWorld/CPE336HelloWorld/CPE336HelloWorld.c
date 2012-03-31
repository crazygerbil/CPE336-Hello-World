/*
 * CPE336HelloWorld.c
 *
 * Created: 3/31/2012 1:08:33 PM
 *  Author: Harry
 */ 
/*
 * AVRGCC1.c
 *
 * Created: 3/30/2012 2:17:34 PM
 *  Author: Bubba
 */ 



#include <avr/io.h>				// registers locations and some other things
#include <util/delay.h>			// software delay functions

#define F_CPU 16000000UL		// tells compiler the freq of your processor
#define DDR_LCD_COM_PORT DDRD	//DDR COM PORT 
#define LCD_COM_PORT PORTD		//DECLARE PORT D COM PORT
#define DDR_LCD_CONTROL DDRB	//DDR CONTROL PORT
#define LCD_CONTROL_PORT PORTB	//DECLARE PORT B CONTROL PORT
#define LCD_STARTUP_TIME 35		//STARTUP TIME CONSTANT
#define LCD_RS 0				//PB0 - PIN 8
#define LCD_RW 1				//PB1 - PIN 9
#define LCD_E  2				//PB2 - PIN 10

int main(void)
{
	_delay_ms(LCD_STARTUP_TIME);	//delay while lcd boots

	DDR_LCD_CONTROL |= ((1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_E) | (1<<PB3));	//SET CONTROL PORTS TO OUTPUT
	LCD_CONTROL_PORT |= (1<<LCD_E);

	//DDRB |= (1<<PB3);

/*while(1)
{ // infinite loop
	PORTB |= (1<<PB3); // write a 1 to B5
	_delay_ms(1000); //Wait 1 second
	PORTB &= ~(1<<PB3); //Turn led off
	_delay_ms(1000); //Wait another second
}*/
	LCD_CONTROL_PORT |= (1<<PB3);
	
	_delay_ms(30000);
	
	//INITIALIZE LCD
	DDR_LCD_COM_PORT = 0xFF;										//SET COM PORT TO OUTPUT
	LCD_COM_PORT = 0b00111100;										//FUNCTION SET
	_delay_us(45);
	LCD_COM_PORT = 0b00001111;										//DISPLAY ON/OFF CONTROL
	_delay_us(45);
	LCD_COM_PORT = 0b00000001;										//CLEAR DISPLAY
	_delay_ms(2);
	LCD_COM_PORT = 0b00000110;										//ENTRY MODE SET
	_delay_ms(2);
	//END INITIALIZATION
	
	LCD_CONTROL_PORT &= ~(1<<PB3);
	
	DDR_LCD_COM_PORT = 0x00;		//SET COM PORT TO INPUT
	
	LCD_CONTROL_PORT |= (1<<LCD_RW);		//READ BUSY FLAG
	LCD_CONTROL_PORT &= ~(1<<LCD_RS);		//READ BUSY FLAG
	
	_delay_ms(10);
	while (LCD_COM_PORT >= 0x80);		//DELAY UNTIL NOT BUSY
	
	_delay_ms(10);	
	
	DDR_LCD_COM_PORT = 0xFF;			//SET COM PORT TO OUTPUT
	
	
		LCD_CONTROL_PORT |= (1<<LCD_RS);		//SET TO WRITE
		LCD_CONTROL_PORT &= ~(1<<LCD_RW);		//SET TO WRITE
		LCD_COM_PORT = 'A';	
	_delay_ms(10);
	//DDR_LCD_COM_PORT = 0xFF;										//SET COM PORT TO OUTPUT
	
	
return 1;
}