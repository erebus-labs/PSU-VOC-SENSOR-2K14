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

#include "Interface.h"

void StartCollection(){
    
    struct header_package header;
    uint8 header_size = sizeof(struct header_package);
    RTC_TIME_DATE* datetime = RTC_ReadTime();
    
    /* Store Header */
    header.start_block = STARTBLOCK;
    header.sample_sensor = get_variable(EE_SENSOR);
    header.sample_unit = get_variable(EE_SAMPLE_UNIT);
    header.sample_interval = get_variable(EE_SAMPLE_INTERVAL);
    header.second = datetime -> Sec;
    header.minute = datetime -> Min;
    header.hour = datetime -> Hour;
    header.day = datetime -> DayOfMonth;
    header.month = datetime -> Month;
    header.year = datetime -> Year;

    Em_EEPROM_Write((uint8*) (&header), TailPtr, header_size);
    TailPtr = TailPtr + header_size;
    
    StopCollection_IRQ_Start();
    StartCollection_IRQ_Stop();
    sample_enable = 1;
    sample_int_count = 0;
    
    return;   
}

void StopCollection(){
    
    StartCollection_IRQ_Start();
    StopCollection_IRQ_Stop();
    sample_enable = 0;
    
    return;   
}

void LED_on(uint8 color){
    
    switch (color){   
    
        case RED:
        case GREEN:
        case BLUE:
            SOLID_LED_CTRL_Write(color);
            break;
            
        case MAGENTA:
            PWM0_CTRL_Write(PWM_BLUE);
            PWM1_CTRL_Write(PWM_RED);
            break;
                
        case YELLOW:
            PWM0_CTRL_Write(PWM_GREEN);
            PWM1_CTRL_Write(PWM_RED);
            break;
        
        case CYAN:
            PWM0_CTRL_Write(PWM_GREEN);
            PWM1_CTRL_Write(PWM_BLUE);
            break;          
            
    }
    return;
}

void LED_off(){
    
    SOLID_LED_CTRL_Write(OFF);
    PWM0_CTRL_Write(OFF);
    PWM1_CTRL_Write(OFF);   
    
    return;
}

/* [] END OF FILE */
