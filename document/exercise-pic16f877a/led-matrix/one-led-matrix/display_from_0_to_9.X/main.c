/*
 * File:   main_led_matrix.c
 * Author: DAT PC
 *
 * Created on 26 January, 2022, 7:01 PM
 */

#include "config.h"
#include "main.h"
#include "ledMatrix.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

void Display_Led_Matrix(char Index, char *array);

void hienThiViTriCoDinhN();
void run_char();


void initSystem();

void main(void) {
    
    initSystem();
    
    while(1)
    {
        //light_from_0_to_9();
        light_character_k(11);
    }
    
    return;
}

void initSystem()
{
    // Turn off ADC moudule
    ADCON1 = 0x06;  
    
    // Port as output pin
    TRIS_COLUMN_LED = 0x00;
    TRIS_ROW_LED = 0x00;
    
    //turn led matrix
    COLUMN_LED=0xFF;
    ROW_LED=0x00;
}




void Display_Led_Matrix(char Index, char *array){
    char Code_Shift = 0x01;//0b 0000 0001 =>0b 1111 1110
    char Code;
    char i;
    
    for(i=Index; i<= Index+7; i++){//
        Code = ~Code_Shift;//dao ma dich
        ROW = array[i];
        COLUMN = Code;
        __delay_ms(1);
        COLUMN = 0xFF;
        Code_Shift = (char)(Code_Shift << 1);
    }
}

//hien thi nhieu ky tu tai 1 vi tri co dinh
void hienThiViTriCoDinhN()
{
    char Array[] = {
    0xFF,0xFF,0x00,0x6E,0x6E,0x91,0xFF,0xFF,// ma ky tu B
    0xFF,0xBB,0xBD,0x80,0xBF,0xBF,0xFF,0xFF,// ma so 1
    0xFF,0xBD,0x7E,0x66,0x66,0x99,0xFF,0xFF // ma so 3
    };
    
    /*
    Index=0 --> hien thi B
    Index=8 --> hien thi 1
    Index=16 --> hien thi 3
    */
    for(char Index=0; Index <=16; Index=Index+8)
    {
        for(char i=0; i<30; i++){    //tang so lan hien thi cua 1 ky tu  --> hien thi cham lai
            Display_Led_Matrix(Index, Array);
            __delay_ms(10); //tre 30*10 = 1=300 ms de hien thi 1 ky tu
        }
    }
 }


//chay chu
void run_char()
{
    char Array[]={
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//ma xoa trang matrix
    0xFF,0x83,0xF5,0xF6,0xF5,0x83,0xFF,0xFF,//ma chu A
    0xFF,0xFF,0x80,0xB6,0xB6,0xC1,0xFF,0xFF,//ma chu B
    0xFF,0x81,0x7E,0x7E,0x7E,0xBD,0xFF,0xFF,//ma chu C
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF//ma xoa trang matrix
    };
    
    //strlen(Array)+1-10 : 10 la so phan tu 0xFF cuoi cung cua Array
    for(char Index = 0; Index<=(char)(strlen(Array)+1-10); Index++)//hien thi tu ben phai
    //for(Index = (char)(strlen(Array)+1-10); Index>=0; Index--)//hien thi tu ben trai //// __bi loi // chi chay duoc 1 lan
    {
        for(char i=0; i<=10; i++)
        {
            Display_Led_Matrix(Index, Array);
            __delay_ms(10); //10*10 = 100 ms moi hien thi 1 so
        }
    }

}