/* 
 * File:   DS1307.h
 * Author: NGUYEN DUC DAT
 *
 * Created on 5 January, 2022, 3:08 PM
 */

#ifndef RTC_DS1307_H
#define	RTC_DS1307_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include"./../i2c-mater/i2c-master.h"

#define RTC_I2C_START    I2C_Start
#define RTC_I2C_RESTART  I2C_Restart
#define RTC_I2C_WRITE    I2C_Write_Char
#define RTC_I2C_READ     I2C_Read_Char
#define RTC_I2C_STOP     I2C_Stop

#define DS1307_WriteMode 0xD0
#define DS1307_ReadMode 0xD1
    
#define DS1307_CHIP_ADDRESS      0xD0
#define DS1307_REGISTER_SECONDS  0x00
#define DS1307_REGISTER_CONTROL  0x07

/*
    Format 12h --> bit 6 == 1 --> ( 0x40 = 0100.0000)
    Format 24h --> bit 6 == 0
*/
#define TimeFormat12    0x40    
    
/*
    If format 12h
    bit 5 == 1 --> PM --> ( 0x20 = 0010.0000 )
    bit 5 == 0 --> AM
*/
#define TimerFormatPM   0x20

typedef enum
{
  OUT_OFF = 0x00,
  OUT_ON  = 0x80,
  OUT_1Hz = 0x10,
  OUT_4096Hz  = 0x11,
  OUT_8192Hz  = 0x12,
  OUT_32768Hz = 0x13
} Frequency;

typedef enum
{
  SUNDAY = 1,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
} Weekdays;

char *day_in_week[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

typedef enum
{
  JANUARY = 1,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
} Month;

typedef struct rtc_tm
{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  Weekdays weekdays;
  uint8_t day;
  Month month;
  uint8_t year;
} Times;

uint8_t bcd_to_decimal(uint8_t number);                        
uint8_t decimal_to_bcd(uint8_t number);                        

int IsItPM(int _hour );

void RTC_Set(Times *time_t);                              

Times *RTC_Get();                                          
                                   
uint8_t RTC_Read_Register(uint8_t register_address);                     

void RTC_Write_Regisger(uint8_t register_address, uint8_t register_value);    

void Oscillator_Enable();                                   
void Oscillator_Disable();      
uint8_t Oscillator_Status();

void Frequency_Set(Frequency pin_out);                                  

#ifdef	__cplusplus
}
#endif

#endif	/* DS1307_H */

