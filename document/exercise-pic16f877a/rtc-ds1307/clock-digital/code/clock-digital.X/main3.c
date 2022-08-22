#include "main.h"

uint8_t  i;

Times *mytime;

void main(void)
{
    ADC_Off();
    
    // Initialize I2C bus with clock frequency of 100kHz
    I2C_Master_Init(100000);   
    
    // Initialize LCD module
    LCD_Init();        
    LCD_Set_Cursor(1,1);
    LCD_Write_String("CLOCK");
    __delay_ms(1000);
 
    while(1)
    { 
        if( button1==0 )           // If button B1 is pressed
            if( Debounce() == 1)   // Call debounce function (make sure if B1 is pressed)
            {
                i = 0;
                mytime->hours   = Edit(1, 1, mytime->hours);
                mytime->minutes = Edit(1, 4, mytime->minutes);
                mytime->day     = Edit(2, 5, mytime->day);
                mytime->month   = Edit(2, 8, mytime->month);
                mytime->year    = Edit(2, 13,mytime->year);

                // Call debounce function (wait for button B1 to be released)
                while( Debounce() );  

                // Write time and date to the RTC chip
                RTC_Set(mytime);

                __delay_ms(200);                
            }
        
        // Read current time and date from the RTC chip
        mytime = RTC_Get();
        
        // Print them
        RTC_Print();
        __delay_ms(100);  // wait 100 ms
  }
}


void RTC_Print()
{
    char buffer[25];
 
    // Print time
    sprintf( buffer, "%02u:%02u:%02u", (int)mytime->hours, (int)mytime->minutes, (int)mytime->seconds);
    
    if( ( (int)mytime->hours >= 1 ) && ( (int)mytime->hours <= 12) )
        strcat(buffer, " AM");
    else
        strcat(buffer, " PM");
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String( buffer);
    
    // Print date
    sprintf( buffer, "%s %02u/%02u/%02u", day_in_week[(int)mytime->weekdays-1], (int)mytime->day, (int)mytime->month, 2000 + (int)mytime->year);
    
    LCD_Set_Cursor(2,1);
    LCD_Write_String( buffer);
}

/*
    A small function for button1 (B1) debounce
    Sample while(button ==0){} 
        debounce : su suy doi/suy giam
 */
__bit Debounce ()
{
  uint8_t count = 0;
  
  for(uint8_t i = 0; i < 5; i++) 
  {
    if (button1 == 0)
      count++;
    __delay_ms(10);
  }
  
  if(count > 2)  
      return 1; // Press button to working
  else           
      return 0; // Press the button too fast --> not working
}
 
/*
    Make editing parameter blinks function.
     
    Blink when both button not press
*/
void Blink()
{
  uint8_t j = 0;
  
  while(j < 100 && button1 == 1 && button2 == 1) 
  {
    j++;
    __delay_ms(5);
  }
}

 
/*
    Edit time and date function
 */
uint8_t Edit(uint8_t x, uint8_t y, uint8_t parameter)
{
  // Call debounce function( wait for button 1 to be released)
  while( Debounce() == 1 );  
 
  while(1) 
  {
        while(button2 == 0)    // If button button 2 is pressed
        {
          parameter++;
          if(i == 0 && parameter > 23)   // if hours > 23 ==> hours = 0
            parameter = 0;
          
          if(i == 1 && parameter > 59)   // if minutes > 59 ==> minutes = 0
            parameter = 0;
          
          if(i == 2 && parameter > 31)   // if date > 31 ==> date = 1
            parameter = 1;
          
          if(i == 3 && parameter > 12)   // if month > 12 ==> month = 1
            parameter = 1;
          
          if(i == 4 && parameter > 99)   // if year > 99 ==> year = 0
            parameter = 0;

          LCD_Set_Cursor( x, y );
          LCD_Write_Char( (char)(parameter / 10 + '0') );
          LCD_Write_Char( (char)(parameter % 10 + '0') );

          __delay_ms(200);
        }

        LCD_Set_Cursor(x, y);
        LCD_Write_String("  ");  // Print 2 spaces
        Blink();

        LCD_Set_Cursor(x, y);
        LCD_Write_Char((char)(parameter / 10 + '0'));
        LCD_Write_Char((char)(parameter % 10 + '0'));
        Blink();

        if(button1 == 0)            // If button B1 is pressed
            if( Debounce() == 1 )   // Call debounce function( make sure if button 1 is pressed)
            {
              i++;                  // Increment 'i' for the next parameter
              return parameter;     // Return parameter value and exit
            }
    }
}

void ADC_Off()
{
    ADCON1 = 0x06;
}

