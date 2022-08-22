/* 
 * File:   main.h
 * Author: NGUYEN-DUC-DAT
 *
 * Created on 21 August, 2022, 7:30 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    #include <xc.h>
    #include <pic16f877a.h>

    #include"libraryUser/config/config.h"
    #include"libraryUser/i2c-mater/i2c-master.h"
    #include"libraryUser/lcd-4-wire/lcd.h"
    #include"libraryUser/rtc-ds1307/rtc-ds1307.h"

    #define button1      RB0  
    #define button2      RB1   

    void RTC_Print();
    
    __bit Debounce ();
    
    void Blink();
    
    uint8_t Edit(uint8_t x, uint8_t y, uint8_t parameter);
    
    void ADC_Off();
    

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

