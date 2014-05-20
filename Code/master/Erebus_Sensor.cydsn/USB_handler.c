/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    USB_handler.c
 *
 * Handles USB communication and USB host-initiated tasks
 *
 * ========================================
*/

#include "USB_handler.h"

void Run_USB(){
    
    // Power has just been applied to the Vbus pin, so we enter USB communication mode

    uint8 result = 0;
    uint8 command = 0;
    
    RTC_WriteIntervalMask(NONE_MASK);
    StartCollection_IRQ_Stop();
    StopCollection_IRQ_Stop();
    Vbus_IRQ_Stop();

    USBUART_Start(0u, USBUART_5V_OPERATION);
    
    /* Wait for Device to enumerate */
    while(!USBUART_GetConfiguration() && Vbus_Read());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_CDC_Init();
    
    while(Vbus_Read())
    {  
        if (USBUART_DataIsReady() != 0u){   /* Check for input data from PC */
            result = retrieve_from_buffer(&command, COMMAND_LENGTH);
            
            // Discard null bytes
            if (command == NULL_BYTE){
                continue;
            }
        
            if (result == SUCCESS){
                
                switch (command){
                
                    case IDENTIFY:
                        send_reply(IDENTIFIER);
                        break;
                    
                    case DUMP_DATA:
                        if (export_samples()){
                            confirm_export();
                        }
                        else{
                            send_reply(FAIL);
                        }
                        break;
                        
                    case GET_SETTINGS:
                        send_settings();
                        break;
                        
                    case CHANGE_SETTING:
                        send_reply(SUCCESS);
                        if (apply_settings() == SUCCESS){
                            send_reply(SUCCESS);
                        }
                        else{
                            send_reply(FAIL);
                        }                  
                        break;
                        
                    case UPDATE_RTC:
                        send_reply(SUCCESS);
                        if (update_RTC() == SUCCESS){
                            send_reply(SUCCESS);
                        }
                        else{
                            send_reply(FAIL);
                        }
                        break;
                     
                    case RESET_PTRS:
                        reset_sample_pointers();
                        send_reply(SUCCESS);
                        break;
                        
                    default:
                        send_reply(FAIL);
                        break;
                }
            }   
            else{
                send_reply(FAIL);
            }
        }
    }
    
    USB_Close();
    
    return;
}

uint8 retrieve_from_buffer(uint8* buffer, uint8 num_bytes){
    uint16 count = 0;
    uint8 attempts = 0;
    uint8 result = FAIL;
    
    count = USBUART_GetCount(); 
    
    /* If data in buffer is the right amount retrieve_from_buffer it */
    if (count == num_bytes){
        USBUART_GetData(buffer, num_bytes);
        result = SUCCESS;
    }
    /* Otherwise, flush the USB buffer and report fail */
    else if (count > 0){
        USBUART_GetChar();
    }
    
    return result;
}

void send_reply(uint8 message){
   
    while(!USBUART_CDCIsReady() && Vbus_Read());
    
    if (Vbus_Read()){
        USBUART_PutData(&message, REPLY_LEN);
    }
    
    return;
}

void send_settings(){
    
    uint8 settings[NUM_SETTINGS];
    
    settings[0] = get_EEPROM_variable(EE_SENSOR);
    settings[1] = get_EEPROM_variable(EE_SAMPLE_UNIT);
    settings[2] = get_EEPROM_variable(EE_SAMPLE_INTERVAL);
    
    while(!USBUART_CDCIsReady() && Vbus_Read());
    
    if (Vbus_Read()){
        USBUART_PutData((uint8*) &settings, sizeof(settings));
    }
    
    return;   
}

uint8 apply_settings(){
    uint8 result = FAIL;
    uint8 settings_buffer[NUM_SETTINGS] = {0};
    struct sampling_settings new_settings;
    
    while (!USBUART_DataIsReady() && Vbus_Read());
    
    if (Vbus_Read()){
        if (retrieve_from_buffer(settings_buffer, NUM_SETTINGS) == SUCCESS){
            new_settings.sensor = settings_buffer[0];
            new_settings.sample_unit = settings_buffer[1];
            new_settings.sample_interval = settings_buffer[2];
            
            result = update_settings(new_settings);   
        }
    } 
    
    return result;
}

uint8 update_settings(struct sampling_settings new_settings){
    
    uint8* buffer;
    float rows_used = 0;
    uint16 remainder = 0;
    uint8* src_ptr;
    uint8* dst_ptr;
    uint8 i = 0; // loop var
    float bytes_used = EEPROM_BYTES_USED;
    uint8 result = SUCCESS;
    cystatus status;
    
    /* Allocate array to hold EEPROM variables */
    
    rows_used = ceil(bytes_used/CYDEV_EEPROM_ROW_SIZE);
    buffer = malloc(((uint16) rows_used) * CYDEV_EEPROM_ROW_SIZE);
    
    dst_ptr = buffer;
    remainder = (rows_used * 16) - EEPROM_BYTES_USED;
    
    /* Copy all variables into SRAM */
    for (i=0; i<EEPROM_BYTES_USED; ++i){
        *dst_ptr = CY_GET_REG8(CYDEV_EE_BASE + i);
        ++dst_ptr;      
    }
    
    /* Fill remainder of buffer with zeros */
    while (i < remainder){
        *dst_ptr = 0;
        ++i;
    }
    
    /* Modify variables in SRAM */
    buffer[0] = new_settings.sensor;
    buffer[1] = new_settings.sample_unit;
    buffer[2] = new_settings.sample_interval;
    
    /* Disable interrupts and erase EEPROM */
    CyGlobalIntDisable;
    status = Re_EEPROM_EraseSector(SECTOR_NUMBER);
    CyGlobalIntEnable;
    
    if (status != CYRET_SUCCESS){
        result = FAIL;
        goto exit;
    }
    
    /* Write back modified EEPROM Variables */
    i = 0;
    src_ptr = buffer;
    while ((i < rows_used) && (i < EEPROM_ROWS)){
        /* Disable interrupts during EEPROM write operation */
        CyGlobalIntDisable;
        status = Re_EEPROM_Write(src_ptr, i);
        CyGlobalIntEnable;
        
        if (status != CYRET_SUCCESS){
           result = FAIL;
        goto exit;
    }
        src_ptr = src_ptr + CYDEV_EEPROM_ROW_SIZE;
        ++i;
    }
     
    free(buffer);
    
exit:   
    return result;   
}

uint8 export_samples(){
    
    uint8 result = SUCCESS;
    uint8 export_buffer[BUFFER_LEN];
    uint16 export_index = sample_head_index; 
    uint16 byte_count = 0;
    uint8 i = 0;
    
    if ((export_index == sample_tail_index) && !mem_full_flag){
        export_buffer[0] = NO_DATA;
        
        for (i=1; i< BUFFER_LEN; ++i){
            export_buffer[i] = PADBYTE;
        }
        load_buffer(export_buffer);
                
        goto exit;
    }
            
    /* Loop 1: Iterate over data samples until export pointer meets the tail */
    do
    {   
        /* Loop 2: Iterate over the 64-byte USB buffer, copying bytes into it */
        while (i < BUFFER_LEN)
        {
            export_buffer[i] = sample_block[export_index];
            ++i;
            ++export_index;
            ++byte_count;

            /* Check to make sure we're not incrementing export_ptr past
             * the bounds of our sample array - wrap around to first element if true */
            if (export_index >= SAMPLE_BLOCK_SIZE){
                    export_index = 0;
            }

            /* Once the last sample byte has been put in the buffer,
             * add a pad byte to mark the end of this packet */
            if (export_index == sample_tail_index){
                export_buffer[i] = PADBYTE;
                break;
            }           
        }
        
        /* Send 64-byte packet to host */
        load_buffer(export_buffer);
        i = 0;
        
        /* Wait for permission from host to send next packet */
        if (wait_for_continue() == FAIL){
            result = FAIL;
            goto exit;
        }
    } while (export_index != sample_tail_index);
    
    /* Add the size trailer packet to get total transmission size,
     * excluding pad bytes */
    byte_count = byte_count + 4;
    
    /* Trailer Packet to Identify End of Sampled Data in Memory */ 
    export_buffer[0] = 0x80; // End of Data Identifier
    export_buffer[1] = 0x00;
    
    /* Byte count may be up to 16-bits long - pack into two bytes
     * and copy to buffer */
    export_buffer[2] = (uint8)(byte_count >> 8);
    export_buffer[3] = (uint8)0x00FF & byte_count;
    
    load_buffer(export_buffer);

exit:
    
    return result;
}

void load_buffer(uint8* export_buffer){
    
    while(!USBUART_CDCIsReady() && Vbus_Read());
    USBUART_PutData(export_buffer, BUFFER_LEN);
   
    /* Add zero-length packet so host completes transaction */
    while(!USBUART_CDCIsReady() && Vbus_Read());
    USBUART_PutData(export_buffer, 0);

    return;
}
    
uint8 wait_for_continue(){
    uint8 reply = 0;
    uint8 retrieve_from_buffer_status = 0;
    uint8 continue_status = FAIL;

    while(!reply && Vbus_Read()){
            
        while(!USBUART_GetCount() && Vbus_Read()); 
        retrieve_from_buffer_status = retrieve_from_buffer(&reply, COMMAND_LENGTH);
        
        if (retrieve_from_buffer_status == SUCCESS && reply == NEXT){

            continue_status = SUCCESS;
            break;
        }
        
        else if (retrieve_from_buffer_status == SUCCESS){
            continue_status = FAIL;            
        }
    }    
    
    return continue_status;
}

void confirm_export(){
    uint8 command = 0;
    
    while(Vbus_Read()){
        while(!USBUART_DataIsReady() && Vbus_Read());
                
        if (retrieve_from_buffer(&command, COMMAND_LENGTH) == SUCCESS){
            
            if (command == SUCCESS){
                clear_samples();           
                break;
            }
            
            else if (command == NEXT){
                send_reply(FAIL);
                break;   
            }
            
            else if (command == FAIL){
                break;
            }            
        }
    }
    
    return;
}

uint8 update_RTC(){
    uint8 result = FAIL;
    uint8 time_buffer[TIME_LENGTH] = {0};
    RTC_TIME_DATE new_time;
    
    while (!USBUART_DataIsReady() && Vbus_Read());
    
    if (Vbus_Read()){
        if (retrieve_from_buffer(time_buffer, TIME_LENGTH) == SUCCESS){
            new_time.Year = ((uint16) time_buffer[0]) << 0x8;
            new_time.Year = new_time.Year | ((uint16) time_buffer[1]);
            new_time.Sec = time_buffer[2];
            new_time.Min = time_buffer[3];
            new_time.Hour = time_buffer[4];
            new_time.DayOfMonth = time_buffer[5];
            new_time.Month = time_buffer[6];
            
            RTC_WriteTime(&new_time);
            
            result = SUCCESS;

        }
    }
    
    return result;
}

void reset_sample_pointers(){

    reset_pointers();
    
    return;
}

void USB_Close(){
    
    /* Clear pending interrupts that occurred while plugged into host */
    USBUART_Stop();
    Vbus_ClearInterrupt();
    Vbus_IRQ_ClearPending();
    clear_button_interrupts();
    USB_waiting = 0;
    
    /* Reapply EEPROM variables to sample parameters in case they were changed */
    sampling_setup(); 
    
    /* Re-enter normal operating mode */
    StartCollection_IRQ_Start();
    Vbus_IRQ_Start();   

    return;
}

/* [] END OF FILE */
