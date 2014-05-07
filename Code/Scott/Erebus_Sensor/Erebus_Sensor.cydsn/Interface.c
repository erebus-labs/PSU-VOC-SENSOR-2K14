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
    RTC_WriteIntervalMask(RTC_int_mask);
    
    return;   
}

void StopCollection(){
    
    StartCollection_IRQ_Start();
    StopCollection_IRQ_Stop();
    RTC_WriteIntervalMask(NONE_MASK);
    
    return;   
}

void LED_on(uint8 target){
    
    switch (target){   
    
        case USB:
            /* Green */
            LED0_CTRL_Write(GREEN);
            LED1_CTRL_Write(GREEN);
            break;
        
        case ERROR:
            /* Red */
            LED0_CTRL_Write(RED);
            LED1_CTRL_Write(RED);
            break;
            
        case LOWBATT:
            /* Yellow */
            LED0_CTRL_Write(GREEN);
            LED1_CTRL_Write(RED);
            break;
        
        case SAMPLE:
            /* BLUE */
            LED0_CTRL_Write(BLUE);
            LED1_CTRL_Write(GREEN);
            break;  
            
        case MEM:
            /* Cyan */
            LED0_CTRL_Write(BLUE);
            LED1_CTRL_Write(BLUE);  
            break;
        
        case BUTTON:
            /* Magenta */
            LED0_CTRL_Write(BLUE);
            LED1_CTRL_Write(RED);
            break;
    }
    return;
}

void LED_off(uint8 target){
    
    switch (target){
        
        case ALL:
            LED0_CTRL_Write(OFF);
            LED1_CTRL_Write(OFF);
            break;
        
        case USB:
            LED0_CTRL_Write(OFF);
            LED1_CTRL_Write(OFF);
            break;
   
        case SAMPLE:
                
            if (low_power_flag){
                LED0_CTRL_Write(GREEN);
                LED1_CTRL_Write(RED);
            }
            
            else{
                LED0_CTRL_Write(OFF);
                LED1_CTRL_Write(OFF);
            }      
            break;  
            
        case MEM:         
            if (Vbus_Read()){
                LED0_CTRL_Write(GREEN);
                LED1_CTRL_Write(GREEN);
            }
            else{
                LED0_CTRL_Write(OFF);
                LED1_CTRL_Write(OFF);
            } 
            break;
            
        case BUTTON:
            LED0_CTRL_Write(OFF);
            LED1_CTRL_Write(OFF);
            break;
    }
    
    return;
}

/* [] END OF FILE */
