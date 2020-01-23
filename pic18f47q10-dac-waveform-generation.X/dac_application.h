/* 
 * File:   application.h
 * Author: I20946
 *
 * Created on July 30, 2019, 2:51 PM
 */


#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**
      @Summary
        Generate signal using DAC1.

      @Description
        This routine call the signal switching routine 
     and this routine feed the input digital data in to DAC1 for generate the switched signal 

      @Preconditions
        The WaveGenerator() routine should be called
        prior to use this routine.

      @Param
        inputData - void.

      @Returns
        None

      @Example
        <code>

        while(1)
        {
         WaveGenerator();
        }
        </code>
     */

    void WaveGenerator(void);
    /**
      @Summary
      switch the signals from one signal to another (change the input array) 

      @Description
        This routine update the corresponding array to the pointer for change the generation of signal 
     using DAC1. (the change over variable get update when external interrupt occurs) 
      @Preconditions
        The WaveSwitch() routine should be called
        prior to use this routine.

      @Param
        inputData - switching status.

      @Returns
        None

      @Example
        <code>
       void WaveGenerator(void)
     {
       WaveSwitch();
  
      }
 
        </code>
     */
    void WaveSwitch(uint16_t sw);

    /*
     Custom user interrupt handler routine
     */
    void UserInterruptHandler(void);
#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

