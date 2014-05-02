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

void Hibernate_ISR(){
    
    return;   
}

void StartCollection_ISR(){
    
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
    TakeSample_IRQ_Start();
    
    return;   
}

void StopCollection_ISR(){
    
    StartCollection_IRQ_Start();
    StopCollection_IRQ_Stop();
    TakeSample_IRQ_Stop();
    
    return;   
}

/* [] END OF FILE */
