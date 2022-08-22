#include"rtc-ds1307.h"

/*
    Convert BCD to decimal function
 */
uint8_t bcd_to_decimal(uint8_t number) {
  return(uint8_t)( (number >> 4) * 10 + (number & 0x0F) );
}
 

/*
    Convert decimal to BCD function
*/
uint8_t decimal_to_bcd(uint8_t number) {
  return(uint8_t)(( (number / 10) << 4) + (number % 10) );
}


/*
 void RTC_Set(RTC_Time *time_t): this function sets time and date 
 (writes time and date to the DS1307) where the variable time_t of type struct (structure)
 which collects the following unsigned 8-bit integer variables:
 
 seconds, minutes, hours, dow, day, month and year.
 Where dow is day of the week (Monday, Tuesday ?) and day is month day.
    seconds and minutes range: 0 - 59
    hours range: 0 - 23 (24-hour format)
    dow range: 1 - 7 (1 equals Sunday, 2 equals Monday )
    day range: 1 - 31 (depends on month)
    month range: 1 - 12 (1 equals January)
    year range: 0 - 99.
*/
void RTC_Set(Times *time_t)
{
  uint8_t sec_register = RTC_Read_Register(DS1307_REGISTER_SECONDS);

  // Convert decimal to BCD
  time_t->day     = decimal_to_bcd(time_t->day);
  time_t->month   = decimal_to_bcd(time_t->month);
  time_t->year    = decimal_to_bcd(time_t->year);
  time_t->hours   = decimal_to_bcd(time_t->hours);
  time_t->minutes = decimal_to_bcd(time_t->minutes);
  time_t->seconds = decimal_to_bcd(time_t->seconds);
  
  // Test if oscillator is disabled (CH bit = 1)
  if(sec_register & 0x80)
    time_t->seconds |= 0x80;

  // Write data to the RTC chip
  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_CHIP_ADDRESS);     // RTC_I2C_WRITE(0xD0);
  RTC_I2C_WRITE(DS1307_REGISTER_SECONDS); //RTC_I2C_WRITE(0x00);
  RTC_I2C_WRITE(time_t->seconds);
  RTC_I2C_WRITE(time_t->minutes);
  RTC_I2C_WRITE(time_t->hours);
  RTC_I2C_WRITE(time_t->weekdays);
  RTC_I2C_WRITE(time_t->day);
  RTC_I2C_WRITE(time_t->month);
  RTC_I2C_WRITE(time_t->year);
  RTC_I2C_STOP();
  
  __delay_ms(1000);
}


Times c_time;


/*
    Reads time and date from the DS1307,
    this function returns them as a variable of type struct (same as the previous function).
 */
Times *RTC_Get()
{  
  RTC_I2C_START();
  
  RTC_I2C_WRITE(DS1307_CHIP_ADDRESS);     // RTC_I2C_WRITE(0xD0);
  RTC_I2C_WRITE(DS1307_REGISTER_SECONDS); //RTC_I2C_WRITE(0x00);
  
  RTC_I2C_RESTART();
  
  RTC_I2C_WRITE(DS1307_CHIP_ADDRESS | 0x01); // initialize data read
  //or RTC_I2C_WRITE(0xD1);
  
  c_time.seconds = RTC_I2C_READ(0) & 0x7F;
  c_time.minutes = RTC_I2C_READ(0);
  c_time.hours   = RTC_I2C_READ(0);
  c_time.weekdays= RTC_I2C_READ(0);
  c_time.day     = RTC_I2C_READ(0);
  c_time.month   = RTC_I2C_READ(0);
  c_time.year    = RTC_I2C_READ(1);
  
  RTC_I2C_STOP();

  // Convert BCD to decimal
  c_time.seconds = bcd_to_decimal(c_time.seconds);
  c_time.minutes = bcd_to_decimal(c_time.minutes);
  c_time.hours   = bcd_to_decimal(c_time.hours);
  c_time.weekdays= bcd_to_decimal(c_time.weekdays);
  c_time.day     = bcd_to_decimal(c_time.day);
  c_time.month   = bcd_to_decimal(c_time.month);
  c_time.year    = bcd_to_decimal(c_time.year);

  return &c_time;
}


/*
    Writes 'reg_value' to register of address 'reg_address'
 */
void RTC_Write_Register(uint8_t register_address, uint8_t register_value)
{
  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_CHIP_ADDRESS);
  RTC_I2C_WRITE(register_address);
  RTC_I2C_WRITE(register_value);
  RTC_I2C_STOP();
}


/*
    This function returns the value stored 
    in register of address reg_address.
*/
uint8_t RTC_Read_Register(uint8_t register_address)
{
  uint8_t register_data;

  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_CHIP_ADDRESS);
  RTC_I2C_WRITE(register_address);
  RTC_I2C_RESTART();
  RTC_I2C_WRITE(DS1307_CHIP_ADDRESS | 0x01);
  register_data = RTC_I2C_READ(1);
  RTC_I2C_STOP();

  return register_data;
}


/*
    Check the AMPM bit in hour register (bit 5)
    PM ??
 */
int IsItPM(int _hour)
{
    if( (_hour & (TimerFormatPM) ) == TimerFormatPM)
        return 1;//PM
    else
        return 0;//AM
}


/*
 void Frequency_Set(Frequency pin_out): this function configures the SQW/OUT pin of the DS1307, 
 where pin_out is one of the following:
    OUT_OFF: output is off (internally attached to ground)
    OUT_ON: output is on (internally floating)
    OUT_1Hz: output is square wave with frequency equals to 1Hz
    OUT_4096Hz: output is square wave with frequency equals to 4096Hz
    OUT_8192Hz: output is square wave with frequency equals to 8192Hz
    OUT_32768Hz: output is square wave with frequency equals to 32768Hz
 */
void Frequency_Set(Frequency pin_out)
{
  RTC_I2C_START();
  RTC_I2C_WRITE(DS1307_CHIP_ADDRESS);
  RTC_I2C_WRITE(DS1307_REGISTER_CONTROL);
  RTC_I2C_WRITE(pin_out);
  RTC_I2C_STOP();
}


/*
    Enables RTC oscillator
 */
void Oscillator_Enable()
{
  uint8_t sec_register = RTC_Read_Register(DS1307_REGISTER_SECONDS);
  
  sec_register &= 0x7F;
  RTC_Write_Register(DS1307_REGISTER_SECONDS, sec_register);
}


/*
    Disables RTC oscillator
 */
void Oscillator_Disable()
{
  uint8_t sec_register = RTC_Read_Register(DS1307_REGISTER_SECONDS);
  sec_register |= 0x80;
  RTC_Write_Register(DS1307_REGISTER_SECONDS, sec_register);
}


/*
    Returns RTC oscillator status (true: enabled and false: disabled)
 */
uint8_t Oscillator_Status()
{
  uint8_t sec_register = RTC_Read_Register(DS1307_REGISTER_SECONDS);
  
  if(sec_register & 0x80)
    return 1;//false;

  return 0;//true;
}

