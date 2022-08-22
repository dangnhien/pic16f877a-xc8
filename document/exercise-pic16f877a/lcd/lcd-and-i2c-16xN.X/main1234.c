/*
 * File:   main_i2c_lcd.c
 * Author: Nguyen Duc Dat
 *
 * Created on 5 December, 2021, 10:50 PM
 */

#include "main.h"

void main(void) 
{
//  OSCCON = 0x70;      // set internal oscillator to 8MHz
    ADCON1=0x07;
    
    LCD_Init(0x4E, 100);// Initialize LCD module with I2C address = 0x4E
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String("  Duc Dat");
    LCD_Set_Cursor(2,1);
    LCD_Write_String("  NS 2000");
    __delay_ms(2500);
 
  while(1)
  {
    screenMove();
  }
    return;
}


void screenMove()
{
    LCD_SR();
    __delay_ms(350);
    LCD_SR();
    __delay_ms(350);
    LCD_SL();
    __delay_ms(350);
    LCD_SL();
    __delay_ms(350);
}