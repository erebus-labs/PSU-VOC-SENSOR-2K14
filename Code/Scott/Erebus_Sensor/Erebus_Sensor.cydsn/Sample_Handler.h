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
    #include "Interface.h"
    #include "Globals.h"
    
    void rtc_prep(void);
    void take_sample(void);
    void sample_counter(void);
    void RTC_Int_Handler(void);
    
#endif

/* [] END OF FILE */
