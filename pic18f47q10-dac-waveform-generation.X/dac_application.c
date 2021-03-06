/**
 application.c for application functionalities
 
  @Company
    Microchip Technology Inc.
 
  @File Name
    application.c
 
  @Summary
    This source file contains functions to generate four different waves  
 
  @Description
    This source file provides implementations for wave generation APIs.
    Generation Information :
        Product Revision      :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device                :  PIC18F47Q10
        Driver Version used   :  2.11
    The API's are tested against the following:
        Compiler          :  XC8 2.00 or later
        MPLAB             :  MPLAB X 5.20
 */
#include <pic18.h>
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/dac1.h"
#include "dac_application.h"

#define XTAL_FREQ XTLA 1000000  
#define POINTS 127                //Number of Inputs in array
#define REFERENCE_VOL1 0x10        //Digital value for 3.14V/2
#define REFERENCE_VOL2 0x1f       //Digital value for 3.14V
#define FUNCTION_COUNT 5          //Number of functionality 3 signals + 2 reference voltage  

volatile unsigned int swcnt; //variable to handle the interrupt counts for update the signal switch
uint16_t *LUT_ptr; //Pointer to feed the input to DAC1

// array to generate the sine wave signal 
const uint16_t sineLUT[] = {
    0x10, 0x10, 0x11, 0x12, 0x13, 0x13, 0x14, 0x15,
    0x15, 0x16, 0x17, 0x17, 0x18, 0x19, 0x19, 0x1a,
    0x1a, 0x1b, 0x1b, 0x1c, 0x1c, 0x1d, 0x1d, 0x1e,
    0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e,
    0x1e, 0x1e, 0x1d, 0x1d, 0x1c, 0x1c, 0x1b, 0x1b,
    0x1a, 0x1a, 0x19, 0x19, 0x18, 0x17, 0x17, 0x16,
    0x15, 0x15, 0x14, 0x13, 0x13, 0x12, 0x11, 0x10,
    0x10, 0xf, 0xe, 0xd, 0xc, 0xc, 0xb, 0xa,
    0xa, 0x9, 0x8, 0x8, 0x7, 0x6, 0x6, 0x5,
    0x5, 0x4, 0x4, 0x3, 0x3, 0x2, 0x2, 0x1,
    0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1,
    0x1, 0x1, 0x2, 0x2, 0x3, 0x3, 0x4, 0x4,
    0x5, 0x5, 0x6, 0x6, 0x7, 0x8, 0x8, 0x9,
    0xa, 0xa, 0xb, 0xc, 0xc, 0xd, 0xe, 0xf
};

// array to generate the square wave signal 
const uint16_t squareLUT[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f
};

//array to generate the triangle wave 
const uint16_t triangleLUT[] = {
    0x0, 0x1, 0x1, 0x2, 0x2, 0x3, 0x3, 0x4,
    0x4, 0x5, 0x5, 0x6, 0x6, 0x7, 0x7, 0x8,
    0x8, 0x9, 0x9, 0xa, 0xa, 0xb, 0xb, 0xc,
    0xc, 0xd, 0xd, 0xe, 0xe, 0xf, 0xf, 0x10,
    0x10, 0x10, 0x11, 0x11, 0x12, 0x12, 0x13, 0x13,
    0x14, 0x14, 0x15, 0x15, 0x16, 0x16, 0x17, 0x17,
    0x18, 0x18, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b,
    0x1c, 0x1c, 0x1d, 0x1d, 0x1e, 0x1e, 0x1f, 0x1f,
    0x1f, 0x1e, 0x1e, 0x1d, 0x1d, 0x1c, 0x1c, 0x1b,
    0x1b, 0x1a, 0x1a, 0x19, 0x19, 0x18, 0x18, 0x17,
    0x17, 0x16, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13,
    0x13, 0x12, 0x12, 0x11, 0x11, 0x10, 0x10, 0x10,
    0xf, 0xf, 0xe, 0xe, 0xd, 0xd, 0xc, 0xc,
    0xb, 0xb, 0xa, 0xa, 0x9, 0x9, 0x8, 0x8,
    0x7, 0x7, 0x6, 0x6, 0x5, 0x5, 0x4, 0x4,
    0x3, 0x3, 0x2, 0x2, 0x1, 0x1, 0x0, 0x0
};

//array to generate the sawtooth wave 
const uint16_t sawtoothLUT[] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03,
    0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05,
    0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07,
    0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09,
    0x0a, 0x0a, 0x0a, 0x0a, 0x0b, 0x0b, 0x0b, 0x0b,
    0x0c, 0x0c, 0x0c, 0x0c, 0x0d, 0x0d, 0x0d, 0x0d,
    0x0e, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x0f,
    0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11,
    0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13,
    0x14, 0x14, 0x14, 0x14, 0x15, 0x15, 0x15, 0x15,
    0x16, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x17,
    0x18, 0x18, 0x18, 0x18, 0x19, 0x19, 0x19, 0x19,
    0x1a, 0x1a, 0x1a, 0x1a, 0x1b, 0x1b, 0x1b, 0x1b,
    0x1c, 0x1c, 0x1c, 0x1c, 0x1d, 0x1d, 0x1d, 0x1d,
    0x1e, 0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f
};

const uint16_t setRefVol1[] = {REFERENCE_VOL1};
const uint16_t setRefVol2[] = {REFERENCE_VOL2};

const uint16_t defaultLUT[] = {0x1f};

const uint16_t *signals[] = {
    setRefVol1,
    setRefVol2,
    sineLUT,
    triangleLUT,
    squareLUT,
    sawtoothLUT,
    defaultLUT
};

void WaveGenerator(void)
{
    uint16_t i = 0;
    WaveSwitch(swcnt);
    if (swcnt >= (FUNCTION_COUNT - 3))
    {
        for (i = 0; i <= POINTS; i++)
        {
            DAC1_SetOutput(*LUT_ptr++);
        }
    } 
    else 
    {
        DAC1_SetOutput(*LUT_ptr);
    }
}

void WaveSwitch(uint16_t sw) 
{
    LUT_ptr = (uint16_t*) signals[sw];
    __delay_us(20);
}

void UserInterruptHandler(void) 
{
    LED_Toggle();
    if (swcnt < FUNCTION_COUNT) 
    {
        swcnt++; //Updating the switch pointer 
    }
    else {
        swcnt = 0;
    }
}