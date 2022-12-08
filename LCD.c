#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

#include "LCD.h"

#define LCD_WDATA PORTD
#define LCD_WINST PORTD
#define LCD_RDATA PIND
#define LCD_CTRL PORTF
#define LCD_EN 0 
#define LCD_RW 1
#define LCD_RS 2

void LCD_Comm(char command){
   LCD_CTRL &= ~(1<<LCD_RS);
   LCD_CTRL &= ~(1<<LCD_RW);
   LCD_CTRL |= (1<<LCD_EN);
   _delay_us(50);
   LCD_WINST = command;
   _delay_us(50);
   LCD_CTRL &= ~(1<<LCD_EN);
}

void LCD_Data(char ch){
   LCD_CTRL |= (1<<LCD_RS);
   LCD_CTRL &= ~(1<<LCD_RW);
   LCD_CTRL |= (1<<LCD_EN);
   _delay_us(50);
   LCD_WDATA = ch;
   _delay_us(50);
   LCD_CTRL &= ~(1<<LCD_EN);
}

void LCD_PORT_Init(void){
   DDRD = 0xff;
   DDRF = 0x0f;
}

void LCD_Init(void){
   LCD_PORT_Init();
   LCD_Comm(0x38);
   _delay_ms(2);
   LCD_Comm(0x38);
   _delay_ms(2);
   LCD_Comm(0x38);
   _delay_ms(2);
   LCD_Comm(0x0e);
   _delay_ms(2);
   LCD_Comm(0x01);
   _delay_ms(30);
   LCD_Comm(0x06);
   _delay_ms(2);
}

void LCD_Pos(unsigned char x, unsigned char y){
   LCD_Comm(0x80|(x*0x40 + y));
}

void LCD_Char(unsigned char ch){
   _delay_ms(1);
   LCD_Data(ch);
}

void LCD_STR(unsigned char *str){
   while(*str!=0){
      LCD_Char(*str);
      str++;
   }
}

void LCD_Clear(void){
    LCD_Comm(0x01);
    _delay_ms(2);
}
