/* 
 * File:   ledMatrix.h
 * Author: NGUYEN-DUC-DAT
 *
 * Created on 22 August, 2022, 6:31 PM
 */

#ifndef LEDMATRIX_H
#define	LEDMATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdio.h>
#include <string.h>
    
    //#define _XTAL_FREQ 16000000
    #define COLUMN_LED PORTC  
    #define ROW_LED PORTB

    #define TRIS_COLUMN_LED TRISC
    #define TRIS_ROW_LED TRISB
    
    void light_character_k(int k);
    void light_from_0_to_9();
    

#ifdef	__cplusplus
}
#endif

#endif	/* LEDMATRIX_H */

