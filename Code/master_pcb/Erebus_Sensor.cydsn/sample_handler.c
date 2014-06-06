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
    
/*
 * ========================================
 * Header Files
 * ========================================
*/

/* Cypress Headers */
#include "project.h"

/* Project Headers */
#include "globals.h"
#include "utility.h"
#include "sample_handler.h"

/*
 * ========================================
 * Function Definitions
 * ========================================
*/

void sampling_setup(){
/*
 * Retrieves sample unit and interval settings from EEPROM and sets RTC interrupt masks
 * accordingly. The Second and Minute interrupts from the RTC are always enabled 
 * low battery blinking and battery level checking, respectively. 
*/

    uint8 RTC_int_mask = MINUTE_MASK | SECOND_MASK; 
    
    sample_unit = get_EEPROM_variable(EE_SAMPLE_UNIT);
    sample_interval = get_EEPROM_variable(EE_SAMPLE_INTERVAL);
    
    switch (sample_unit){
        
    case SAMPLE_HOUR: 
        RTC_int_mask = RTC_int_mask | HOUR_MASK;
        break;
    case SAMPLE_DAY: 
        RTC_int_mask = RTC_int_mask | DAY_MASK;
        break;
    }
    
    RTC_WriteIntervalMask(RTC_int_mask);
    RTC_EnableInt();
    
    return;
 }

static uint8 store_in_flash(uint8* buffer, uint8 num_bytes){  
/* 
 * Is a helper function to store data in the sample array. Before storing the buffer
 * in Flash, it first confirms that there is enough from for it. It also tracks the 
 * sample tail index's position in the array so it can be moved to element 0 if the
 * end of the array is reached.
*/

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
    if ((sample_tail_index + num_bytes) <= SAMPLE_BLOCK_SIZE){

        Em_EEPROM_Write(buffer, (uint8*) &(sample_block[sample_tail_index]), num_bytes);
        sample_tail_index = sample_tail_index + num_bytes;
        
        if (sample_tail_index == SAMPLE_BLOCK_SIZE){
            sample_tail_index = 0;
        }
    }
    else{
        /* It didn't fit, so now we have to do extra work to split the buffer 
         * Start by writing whatever will fit before the end of the array */
        remaining_bytes = SAMPLE_BLOCK_SIZE - sample_tail_index;
        Em_EEPROM_Write(buffer, 
                        (uint8*) &(sample_block[sample_tail_index]), 
                        remaining_bytes);
        
        /* Write remaining bytes at the top of the array */
        Em_EEPROM_Write((buffer + remaining_bytes), 
                        sample_block, 
                        num_bytes - remaining_bytes);

        sample_tail_index = num_bytes - remaining_bytes;
    }
    
    /* Store new tail pointer in Flash */
    Em_EEPROM_Write((uint8*) &sample_tail_index, 
                    (uint8*) &(current_sample_indices[pointer_tail_index]), 
                    sizeof(sample_tail_index));
    
    /* If we head is now equal to tail, we have filled our buffer */
    if (sample_tail_index == sample_head_index){
        result = 1;
    }
        
exit:
    return (result);
}

void start_collection(){
/*
 * Triggered when sampling is not currently active and the user pushes the Start 
 * Sampling button. Stores a timestamp, the sensor being used, the sample interval, and
 * the interval unit in Flash as a header to the samples.
*/
    
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
    
    if (store_in_flash((uint8*) &header, sizeof(header))){
        memory_full();
        stop_collection();
        goto exit;
    }
    
    stop_collection_enabled = 1;
    start_collection_enabled = 0;
    sample_enable_flag = 1;
    sample_interrupt_count = 0;
    
    /* Note:
     * Having the sensor take the first sample whenever sampling is started was considered,
     * but rejected because the sampling can begin asynchronously with the real-time clock.
     * If the user is choosing to sample every three minutes but starts sampling at the two
     * minute mark, the second sample will be taken 3.5 minutes after the first one, skewing
     * the time stamps for all remaining samples.
    */

exit:
    return;   
}

void take_sample() {
/*
 * Triggered when the sample interrupt counter reaches the sample interval. Wakes up 
 * the ADC, takes a 16-bit sample, scales it to 12 bits, and stores the result in 
 * Flash. 
*/

    uint16 sample = 0;
    ADC_Wakeup();
    
    sample = ADC_Read16(); 
    sample = (sample >> SAMPLE_SHIFT) & SAMPLE_MASK;
    
    if (store_in_flash((uint8*) &sample, sizeof(sample))){
        memory_full();
        stop_collection();
    }
    
    ADC_Sleep();
    return;    
}

void stop_collection(){
/*
 * Triggered when sampling is currently active and the user pushes the Stop
 * Sampling button. Stores a timestamp, the sensor being used, the sample interval, and
 * the interval unit in Flash as a header to the samples.
*/
    
    start_collection_enabled = 1;
    stop_collection_enabled = 0;
    sample_enable_flag = 0;
    
    return;   
}


void clear_samples(){
/* 
 * Called after data has been dumped through the GUI. Moves the current head index
 * up to the same location as the current tail. If this means the head pointer is
 * advanced past the end of the array and wrapped around, then it is time to increment
 * the master sample indices and store the sample head/tail indices in a new location in
 * their array for wear levelling.
*/

    /* If we just wrapped our sampling around the end of the array, it's time to 
     * bump the sample pointers to the next Flash row for wear-levelling */
    if (sample_head_index > sample_tail_index){
        pointer_head_index += FLASH_ROW_LENGTH;
        
        if (pointer_head_index >= FLASH_ROW_LENGTH * MASTER_ROWS){
            pointer_head_index = HEAD_INDEX;
        }
        
        pointer_tail_index = pointer_head_index + TAIL_INDEX;
        
        /* Save the new indexes of the head and tail pointers */
        Em_EEPROM_Write((uint8*) &pointer_head_index, 
                        (uint8*) &(master_sample_indices[HEAD_INDEX]), 
                        sizeof(pointer_head_index));

        Em_EEPROM_Write((uint8*) &pointer_tail_index, 
                        (uint8*) &(master_sample_indices[TAIL_INDEX]), 
                        sizeof(pointer_tail_index));
        
        /* Copy current tail to its new location */
        Em_EEPROM_Write((uint8*) &sample_tail_index, 
                        (uint8*) &(current_sample_indices[pointer_tail_index]), 
                        sizeof(sample_tail_index));
    }
    
    /* Update bring head up to current tail position */
    sample_head_index = sample_tail_index; 
    Em_EEPROM_Write((uint8*) &sample_tail_index, 
                    (uint8*) &(current_sample_indices[pointer_head_index]), 
                    sizeof(sample_tail_index));
    
    /* If memory full flag was set, clear it */
    if (mem_full_flag){
        mem_full_flag = 0;
        Em_EEPROM_Write(&mem_full_flag, &mem_full_flash_flag, sizeof(mem_full_flag));
    }
            
    return;
}

void reset_pointers(){
/* 
 * Only invoked by the user through the GUI. Initializes the sample indexes to the tops
 * of both the sample and sample indices arrays. This must be run once after programming
 * before attempting to store any samples.
*/
    
    pointer_head_index = HEAD_INDEX;
    pointer_tail_index = TAIL_INDEX;
    sample_head_index = 0x0;
    sample_tail_index = 0x0;
        
    /* reset master pointers */
    Em_EEPROM_Write((uint8*) &pointer_head_index, 
                    (uint8*) &(master_sample_indices[HEAD_INDEX]), 
                    sizeof(pointer_head_index));

    Em_EEPROM_Write((uint8*) &pointer_tail_index, 
                    (uint8*) &(master_sample_indices[TAIL_INDEX]), 
                    sizeof(pointer_tail_index));
    
    /* reset sample pointers to the top of the sample block */
    Em_EEPROM_Write((uint8*) &sample_head_index, 
                    (uint8*) &(current_sample_indices[HEAD_INDEX]), 
                    sizeof(sample_head_index));

    Em_EEPROM_Write((uint8*) &sample_tail_index, 
                    (uint8*) &(current_sample_indices[TAIL_INDEX]), 
                    sizeof(sample_tail_index));
    
    return;
}
   
/* [] END OF FILE */
