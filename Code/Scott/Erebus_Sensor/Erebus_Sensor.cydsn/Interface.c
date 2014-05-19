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
    int byte_diff = 0;
    int remaining_bytes = 0;
    RTC_TIME_DATE* datetime = RTC_ReadTime();
    
    /* First, confirm that there is room to store the header */
    /* Calculate number of bytes remaining in the sample block */ 
    remaining_bytes = sample_head_index - sample_tail_index;
    if (remaining_bytes < 0){
        remaining_bytes = SAMPLE_BLOCK_SIZE + remaining_bytes;
    }

    if (remaining_bytes < header_size && (sample_head_index != sample_tail_index)){
        memory_full();
        goto exit;
    }               
    
    /* Construct Header */
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
        
    /* Check to see if the whole header can fit within the sample block
     * This will usually be the case */
    if ((sample_tail_index + header_size) < SAMPLE_BLOCK_SIZE){
        Em_EEPROM_Write((uint8*) (&header), (uint8*) &(sample_block[sample_tail_index]), header_size);
        sample_tail_index = sample_tail_index + header_size;    
    }
    else{
        /* It didn't fit, so now we have to do extra work to split the header */
        remaining_bytes = SAMPLE_BLOCK_SIZE - sample_tail_index;        
        /* Taking advantage of struct being contiguous in memory - write as many bytes
         * as we can as if it were a buffer, up to the end of the sample array */
        Em_EEPROM_Write((uint8*) &header, (uint8*) &(sample_block[sample_tail_index]), remaining_bytes);
        /* Write remaining bytes at the top of the array */
        Em_EEPROM_Write((uint8*) (&header + remaining_bytes), sample_block, header_size - remaining_bytes);
        sample_tail_index = header_size - remaining_bytes;
    }
    
    /* Store new tail pointer in Flash */
    Em_EEPROM_Write((uint8*) &sample_tail_index, (uint8*) &(current_sample_indices[pointer_tail_index]), sizeof(uint16));
    
    StopCollection_IRQ_Start();
    StartCollection_IRQ_Stop();
    sample_enable = 1;
    sample_int_count = 0;

exit:
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
