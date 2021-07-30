/**
 * DAC1 Generated Driver API Header File
 * 
 * @file dac1.h
 * 
 * @defgroup  dac1 DAC1
 * 
 * @brief This is the generated header file for the DAC1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 *
 * @version DAC1 Driver Version 2.1.0
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
 * @ingroup dac1
 * @brief  This routine initializes the DAC1 and must be called only once, before any other DAC1 routine is called.
 * @param void
 * @return void
 */
void DAC1_Initialize(void);

/**
 * @ingroup dac1
 * @brief  his routine pass the digital input data intoDAC1 voltage reference control register.
 * @param inputData - 8bit digital data to DAC1.
 * @return void
 */
void DAC1_SetOutput(uint8_t inputData);

/**
 * @ingroup dac1
 * @brief  This routine reads the digital input data fed to DAC1 voltage reference control register.
 * @param void
 * @return uint8_t inputData - digital data fed to DAC1
 */
uint8_t DAC1_GetOutput(void);

#endif // DAC1_H
/**
 End of File
*/
