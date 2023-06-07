#include <stdio.h>
#include <math.h>

#include <avr/io.h>
#include <util/delay.h>

#define lcdport PORTD

#define _signal PORTB

#define en PB2

#define rw PB1

#define rs PB0


#define LCD_Data_Dir DDRD
#define LCD_Command_Dir DDRB
#define LCD_Data_Port PORTD
#define LCD_Command_Port PORTB
#define EN PB2
#define RW PB1
#define RS PB0

char key;

void lcdcmd(unsigned char cmd);//lcd commands

void lcdint();//initialize lcd

void lcddata(unsigned char data);

void lcd_string(const unsigned char *str, unsigned char length);//display in lcd

int charToInt(char c);//character to integer

int displayKey();//save input

void lcd_clear();//lcd clear

void lcd_line_one();//lcd line one

void lcd_line_two();//lcd line two



void lcdint()
{
	lcdcmd(0x38);

	_delay_ms(1);

	lcdcmd(0x01);

	_delay_ms(1);

	lcdcmd(0x0E);

	_delay_ms(1);
}


void lcdcmd(unsigned char x)
{
	lcdport=x;

	_signal=(0<<rs)|(0<<rw)|(1<<en);

	_delay_ms(1);

	_signal=(0<<rs)|(0<<rw)|(0<<en);

	_delay_ms(50);
}

void lcddata(unsigned char data)
{
	lcdport= data;

	_signal= (1<<rs)|(0<<rw)|(1<<en);

	_delay_ms(1);

	_signal= (1<<rs)|(0<<rw)|(0<<en);

	_delay_ms(5);
}


void lcd_string(const unsigned char *str, unsigned char length)
{
	for(int i=0; i<length; i++)
	{
		lcddata(str[i]);
	}
}

int charToInt(char c){
	int num = 0;
	num = c - '0';

	return num;
}


void lcd_clear()
{
	lcdcmd(0x01);
}

void lcd_line_one()
{
	lcdcmd(0x80);
}

void lcd_line_two()
{
	lcdcmd(0xC0);
}

void LCD_Char (char char_data)
{
	LCD_Data_Port = char_data;
	LCD_Command_Port &= ~(1<<RW);
	LCD_Command_Port |= (1<<EN)|(1<<RS);
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

