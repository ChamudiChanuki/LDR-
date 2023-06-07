/*
 * LDRCode.c
 *
 * Created: 6/16/2022 12:41:08 PM
 * Author : Chamudi
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL // 1 MHz clock speed
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "LCD/lcd.c"
#include <stdlib.h>
#define LTHRES 500


void adc_init()
{

	ADMUX = (1<<REFS0);
	
	
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
}


uint16_t adc_read(uint8_t ch)
{
	
	
	
	ADCSRA |= (1<<ADSC);
	
	
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}

int main()
{
	DDRD=0xff;	DDRB=0x07;

	uint16_t adc_result0;
	float i, ldr, temp;
	char buffer[10];
	DDRC = 0x01;          
	
	adc_init();
	lcdint(); 

	
	_delay_ms(5);
	
	while(1)
	{
		adc_result0 = adc_read(0);    
		//i=(adc_result0*0.01/2.1);
		//ldr = (i*10.0/(5.0-i))-1;
		
		
		lcd_line_one();
		lcd_string("CIRCUIT DIGEST",14);
		
		lcd_line_two();		lcd_string("ADC val:",8);		itoa(adc_result0,buffer,10);		lcd_string(buffer,5);

		
		_delay_ms(10);

		
		
		if (adc_result0 < LTHRES){
			PORTC = 0x01;
		}
		else{
			PORTC = 0x00;
		}
		
		
		
		
	}
}


