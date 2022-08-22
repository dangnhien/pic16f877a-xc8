/* 
 * File:   main.h
 * Author: NGUYEN-DUC-DAT
 *
 * Created on 21 August, 2022, 8:16 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include <xc.h>
    #include"libraryUser/config/config.h"
    #include"libraryUser/lcd-i2c/i2c_lcd.h"
    
    void screenMove();

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

