/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef _SAMPLE_HANDLER_H_
    #define _SAMPLE_HANDLER_H_
    
    #include "project.h"
    #include "EmEEPROM_Access.h"
    #include "EEPROM_Access.h"
    #include "RTC.h"
    #include "LED_Handler.h"
    
    #define SLEEPMASK 2112
    
    void rtc_setup(void);
    void take_sample(void);
    void sample_counter(void);
    void RTC_Int_Handler(void);
    
#endif

/* [] END OF FILE */
