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
    


    /*
      @Description
        Custom user interrupt handler routine for IOC on switch press
      @Preconditions
         None
      @Param
        None
      @Returns
        None      
    */
    void UserInterruptHandler(void);
    
    /*
      @Description
        interrupt handler routine for timer overflow
      @Preconditions
         None
      @Param
        None
      @Returns
        None      
    */ 
    void TmrUserInterruptHandler(void);

    /*
      @Description
     initialize LUT pointer for generating first waveform at power up
      @Preconditions
         None
      @Param
        None
      @Returns
        None      
    */    
    void InitWaveform(void);
    

    


#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

