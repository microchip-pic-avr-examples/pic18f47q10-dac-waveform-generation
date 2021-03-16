/**
 DAC1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    dac1.h

  @Summary
    This is the generated header file for the DAC1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This Header file provides APIs.
    
    Generation Information :
        Driver Version    :   2.1.0
    The generated drivers are tested against the following:
        Compiler          :   XC8 v2.20
        MPLAB             :   MPLABX v5.40
*/
/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/

#ifndef DAC1_H
#define DAC1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

/**
  Section: DAC1 APIs
*/

/**
  @Summary
    Initializes the DAC1

  @Description
    This routine initializes the DAC1.
    This routine must be called before any other DAC1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    DAC1_Initialize();
    </code>
*/
void DAC1_Initialize(void);

/**
  @Summary
    Set Input data into DAC1.

  @Description
    This routine pass the digital input data into
    DAC1 voltage reference control register.

  @Preconditions
    The DAC1_Initialize() routine should be called
    prior to use this routine.

  @Param
    inputData - 8bit digital data to DAC1.

  @Returns
    None

  @Example
    <code>
    uint8_t count=0;

    DAC1_Initialize();

    for(count=0; count<=30; count++)
    {
        DAC1_SetOutput(count);
    }

    while(1)
    {
    }
    </code>
*/
void DAC1_SetOutput(uint8_t inputData);

/**
  @Summary
    Read input data fed to DAC1.

  @Description
    This routine reads the digital input data fed to
    DAC1 voltage reference control register.

  @Preconditions
    The DAC1_Initialize() routine should be called
    prior to use this routine.

  @Param
    None

  @Returns
    uint8_t inputData - digital data fed to DAC1

  @Example
    <code>
    uint8_t count=0;
    uint8_t inputData;

    DAC1_Initialize();

    inputData = DAC1_GetOutput();

    while(1)
    {
    }
    </code>
*/
uint8_t DAC1_GetOutput(void);

#endif // DAC1_H
/**
 End of File
*/