#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>
//#include <conio.h>

#include "UART1.h"

//#define UP 65
//#define DOWN 66
//#define LEFT 68
//#define RIGHT 67
//#define STOP 32

int main(void)
{
	//char motor_left = 0x05;   // 0000 0'1'01
	//char motor_right = 0x28;  // 0010 '1'000
	char motor_left = 0x00;
	char motor_right = 0x00;
	
	int cnt = 0;
	int data;
	
	DDRB = 0xFF;
	
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1A |= (1 << COM1B1);
	TCCR1B |= (1 << CS12);
	
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2A |= (1 << COM2A1);
	TCCR2B |= (1 << CS22);
	
	PORTB = 0x00;
	
	//OCR1B = 10;
	//OCR2A = 10;
	
	UART_1_init(); // UART1 초기화
	
	//_delay_ms(1000);
	
	while(1)
	{
		PORTB = motor_left | motor_right;
		_delay_ms(50);
		PORTB = 0x00;
		data = UART1_receive();
		
		if(data >= 15){ // right
			OCR1B = 100;
			OCR2A = 100;
			motor_left = 0x05;
			motor_right = 0x28;
		}
		else if(data <= -15){ // left
			OCR1B = 100;
			OCR2A = 100;
			motor_left = 0x06;
			motor_right = 0x18;
		}
		//else if(data == 'B'){ // down
		//	OCR1B = 150;
		//	OCR2A = 150;
			
		//	motor_left = 0x06;  // 0000 0'1'10
		//	motor_right = 0x28; // 0010 '1'000
		//}
		//else if(data == 'S'){
		//	OCR1B = 0;
		//	OCR2A = 0;
		//	motor_left = 0x00;
		//	motor_right = 0x00;
		//}
		else{ // go
			OCR1B = 200;
			OCR2A = 200;  
			
			motor_left = 0x05;  // 0000 0'1'01
			motor_right = 0x18; // 0001 '1'000
		}
	}
	return 0;
}