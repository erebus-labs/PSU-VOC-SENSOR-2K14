/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    sample_handler.c
 *
 * Handles sampling and manages the sample block pointers
 *
 * ========================================
*/

#include "sample_handler.h"

void sampling_setup()
{
    /* Second and Minute RTC interrupts are always enabled for battery checking
     * and LED blinking if necessary */
    uint8 RTC_int_mask = MINUTE_MASK | SECOND_MASK;  
    sample_unit = get_EEPROM_variable(EE_SAMPLE_UNIT);
    sample_interval = get_EEPROM_variable(EE_SAMPLE_INTERVAL);
    
    switch (sample_unit)
    {
        case SAMPLE_HOUR: /* Hours */
            RTC_int_mask = RTC_int_mask | HOUR_MASK;
            break;
        case SAMPLE_DAY: /* Days */
            RTC_int_mask = RTC_int_mask | DAY_MASK;
            break;
    }
    
    RTC_WriteIntervalMask(RTC_int_mask);
    RTC_EnableInt();
    
    return;
 }

void start_collection(){
    
    struct header_package header;
    RTC_TIME_DATE* datetime = RTC_ReadTime();
    
     /* Construct Header */
    header.start_block = STARTBLOCK;
    header.sample_sensor = get_EEPROM_variable(EE_SENSOR);
    header.sample_unit = get_EEPROM_variable(EE_SAMPLE_UNIT);
    header.sample_interval = get_EEPROM_variable(EE_SAMPLE_INTERVAL);
    header.second = datetime -> Sec;
    header.minute = datetime -> Min;
    header.hour = datetime -> Hour;
    header.day = datetime -> DayOfMonth;
    header.month = datetime -> Month;
    header.year = datetime -> Year;
    
    if (store_in_flash((uint8*) &header, sizeof(struct header_package))){
        memory_full();
        stop_collection();
        goto exit;
    }
    
    StopCollection_IRQ_Start();
    StartCollection_IRQ_Stop();
    sample_enable_flag = 1;
    sample_interrupt_count = 0;

exit:
    return;   
}

void take_sample()
{
    uint16 sample = 0;
    ADC_Wakeup();
    
    sample = ADC_Read16(); 
    
    if (store_in_flash((uint8*) &sample, sizeof(uint16))){
        memory_full();
        stop_collection();
    }
    
    ADC_Sleep();
    return;    
}

void stop_collection(){
    
    StartCollection_IRQ_Start();
    StopCollection_IRQ_Stop();
    sample_enable_flag = 0;
    
    return;   
}

uint8 store_in_flash(uint8* buffer, uint8 num_bytes){  
    int byte_diff = 0;
    int remaining_bytes = 0;
    uint8 result = 0;
      
    /* Calculate number of bytes remaining in the sample block */ 
    remaining_bytes = sample_head_index - sample_tail_index;
    if (remaining_bytes < 0){
        remaining_bytes = SAMPLE_BLOCK_SIZE + remaining_bytes;
    }

    /* Confirm there is enough space left */
    /* Ignore case where head and tail are the same location - that is allowed
     * when there are currently no samples or headers stored */
    if (remaining_bytes < num_bytes && (sample_head_index != sample_tail_index)){
        result = 1;
        goto exit;
    }
    
    /* Check to see if the whole buffer can fit before the end of the array
     * This will usually be the case */
    if ((sample_tail_index + num_bytes) < SAMPLE_BLOCK_SIZE){
        Em_EEPROM_Write(buffer, (uint8*) &(sample_block[sample_tail_index]), num_bytes);
        sample_tail_index = sample_tail_index + num_bytes;    
    }
    else{
        /* It didn't fit, so now we have to do extra work to split the buffer 
         * Start by writing whatever will fit before the end of the array */
        remaining_bytes = SAMPLE_BLOCK_SIZE - sample_tail_index;
        Em_EEPROM_Write(buffer, (uint8*) &(sample_block[sample_tail_index]), remaining_bytes);
        
        /* Write remaining bytes at the top of the array */
        Em_EEPROM_Write((buffer + remaining_bytes), sample_block, num_bytes - remaining_bytes);
        sample_tail_index = num_bytes - remaining_bytes;
    }
    
    /* Store new tail pointer in Flash */
    Em_EEPROM_Write((uint8*) &sample_tail_index, (uint8*) &(current_sample_indices[pointer_tail_index]), sizeof(uint16));
    
    /* If we head is now equal to tail, we have filled our buffer */
    if (sample_tail_index == sample_head_index){
        result = 1;
    }
        
exit:
    return (result);
}

void clear_samples(){

    /* If we just wrapped our sampling around the end of the array, it's time to 
     * bump the sample pointers to the next Flash row for wear-levelling */
    if (sample_head_index > sample_tail_index){
        pointer_head_index += FLASH_ROW_LENGTH;
        
        if (pointer_head_index >= FLASH_ROW_LENGTH * MASTER_ROWS){
            pointer_head_index = HEAD_INDEX;
        }
        
        pointer_tail_index = pointer_head_index + TAIL_INDEX;
        
        /* Save the new indexes of the head and tail pointers */
        Em_EEPROM_Write((uint8*) &pointer_head_index, (uint8*) &(master_sample_indices[HEAD_INDEX]), sizeof(uint16));
        Em_EEPROM_Write((uint8*) &pointer_tail_index, (uint8*) &(master_sample_indices[TAIL_INDEX]), sizeof(uint16));
        
        /* Copy current tail to its new location */
        Em_EEPROM_Write((uint8*) &sample_tail_index, (uint8*) &(current_sample_indices[pointer_tail_index]), sizeof(uint16));
    }
    
    /* Update bring head up to current tail position */
    sample_head_index = sample_tail_index; 
    Em_EEPROM_Write((uint8*) &sample_tail_index, (uint8*) &(current_sample_indices[pointer_head_index]), sizeof(uint16));
    
    /* If memory full flag was set, clear it */
    if (mem_full_flag){
        mem_full_flag = 0;
        Em_EEPROM_Write(&mem_full_flag, &mem_full_flash_flag, sizeof(uint8));
    }
            
    return;
}

void reset_pointers(){
    
    pointer_head_index = HEAD_INDEX;
    pointer_tail_index = TAIL_INDEX;
    sample_head_index = 0x0;
    sample_tail_index = 0x0;
        
    /* reset master pointers */
    Em_EEPROM_Write((uint8*) &pointer_head_index, (uint8*) &(master_sample_indices[HEAD_INDEX]), sizeof(uint16));
    Em_EEPROM_Write((uint8*) &pointer_tail_index, (uint8*) &(master_sample_indices[TAIL_INDEX]), sizeof(uint16));
    
    /* reset sample pointers to the top of the sample block */
    Em_EEPROM_Write((uint8*) &sample_head_index, (uint8*) &(current_sample_indices[HEAD_INDEX]), sizeof(uint16));
    Em_EEPROM_Write((uint8*) &sample_tail_index, (uint8*) &(current_sample_indices[TAIL_INDEX]), sizeof(uint16));
    
    return;
}
   
/* [] END OF FILE */
