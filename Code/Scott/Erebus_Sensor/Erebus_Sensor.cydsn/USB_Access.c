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

#include "USB_Access.h"

/* This file provides function definitions for USB interactions */

void Run_USB(){
    
    // Power has just been applied to the Vbus pin, so we enter USB communication mode

    uint8 result = 0;
    uint8 command = 0;

    USBUART_Start(0u, USBUART_5V_OPERATION);
    
    /* Wait for Device to enumerate */
    while(!USBUART_GetConfiguration() && Vbus_Read());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_CDC_Init();
    
    while(Vbus_Read())
    {  
        if(USBUART_DataIsReady() != 0u){   /* Check for input data from PC */
            result = retrieve(&command, COMMAND_LENGTH);
            
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
                        if (dump_data()){
                            confirm_dump();
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
                     
                    case HARD_RESET:
                        CMD_hard_reset();
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

uint8 retrieve(uint8* buffer, uint8 num_bytes){
    uint16 count = 0;
    uint8 attempts = 0;
    uint8 result = FAIL;
    
    count = USBUART_GetCount(); 
    
    // If data in buffer is the right amount retrieve it
    if(count == num_bytes){
        USBUART_GetData(buffer, num_bytes);
        result = SUCCESS;
    }
    // Otherwise, flush the USB buffer and report fail
    else if (count > 0){
        USBUART_GetChar();
    }
    
    return result;
}

uint8 apply_settings(){
    uint8 result = FAIL;
    uint8 settings_buffer[NUM_SETTINGS] = {0};
    settings_group new_settings;
    
    while (!USBUART_DataIsReady() && Vbus_Read());
    
    if (Vbus_Read()){
        if (retrieve(settings_buffer, NUM_SETTINGS) == SUCCESS){
            new_settings.sensor = settings_buffer[0];
            new_settings.sample_unit = settings_buffer[1];
            new_settings.sample_interval = settings_buffer[2];
            
            result = update_settings(new_settings);   
        }
    } 
    
    return result;
}

void send_settings(){
    
    uint8 settings[NUM_SETTINGS];
    
    settings[0] = get_variable(EE_SENSOR);
    settings[1] = get_variable(EE_SAMPLE_UNIT);
    settings[2] = get_variable(EE_SAMPLE_INTERVAL);
    
    while(!USBUART_CDCIsReady() && Vbus_Read());
    
    if(Vbus_Read()){
        USBUART_PutData((uint8*) &settings, sizeof(settings));
    }
    
    return;   
}

uint8 dump_data(){
    
    uint8 result = SUCCESS;
    uint8 export_buffer[BUFFER_LEN];
    uint16 export_index = sample_head_index; 
    uint16 byte_count = 0;
    uint8 i = 0;
    
    if(export_index == sample_tail_index){
        export_buffer[0] = NO_DATA;
        
        for (i=1; i< BUFFER_LEN; ++i){
            export_buffer[i] = PADBYTE;
        }
        write_out(export_buffer);
        
        if (wait_next() == FAIL){
            result = FAIL;
        }
        
        goto exit;
    }
            
    /* Loop 1: Iterate over data samples until export pointer meets the tail */
    while (export_index != sample_tail_index)
    {   
        /* Loop 2: Iterate over the 64-byte USB buffer, copying bytes into it */
        while (i < BUFFER_LEN)
        {
            if (export_index != sample_tail_index)
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
            }
            else
            {
                export_buffer[i] = PADBYTE;
                ++i;
            }           
        }
        
        /* Send 64-byte packet to host */
        write_out(export_buffer);
        i = 0;
        
        /* Wait for permission from host to send next packet */
        if (wait_next() == FAIL){
            result = FAIL;
            goto exit;
        }
    }
    
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
    
    write_out(export_buffer);

exit:
    
    return result;
}

void write_out(uint8* export_buffer){
    
    while(!USBUART_CDCIsReady() && Vbus_Read());
    USBUART_PutData(export_buffer, BUFFER_LEN);
  
    return;
}
    
uint8 wait_next(){
    uint8 reply = 0;
    uint8 retrieve_status = 0;
    uint8 continue_status = FAIL;

    while(!reply && Vbus_Read()){
            
        while(!USBUART_GetCount() && Vbus_Read()); 
        retrieve_status = retrieve(&reply, COMMAND_LENGTH);
        
        if(retrieve_status == SUCCESS){
            if(reply == NEXT){
                continue_status = SUCCESS;
                break;
            }
            else if(reply == FAIL){
                continue_status = FAIL;
            }
        }
    }    
    
    return continue_status;
}

void send_reply(uint8 message){
   
    while(!USBUART_CDCIsReady() && Vbus_Read());
    
    if(Vbus_Read()){
        USBUART_PutData(&message, REPLY_LEN);
    }
    
    return;
}

void confirm_dump(){
    uint8 result = 0;
    uint8 command = 0;
    
    while(Vbus_Read()){
        while(!USBUART_DataIsReady() && Vbus_Read());
        
        result = retrieve(&command, COMMAND_LENGTH);
        
        if(result == SUCCESS){
                    
            if (command == SUCCESS){
                /* Data was successfully dumped, so bring head pointer up to current tail 
                 * to "erase" the old data */
                sample_head_index = sample_tail_index;
                Em_EEPROM_Write((uint8*) &sample_tail_index, (uint8*) &(current_sample_indices[pointer_head_index]), sizeof(uint16));
                mem_full_flag = 0;
                Em_EEPROM_Write(&mem_full_flag, &mem_full_flash_flag, sizeof(uint8));
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
        if (retrieve(time_buffer, TIME_LENGTH) == SUCCESS){
            new_time.Year = ((uint16) time_buffer[0]) << 0x8;
            new_time.Year = new_time.Year | ((uint16) time_buffer[1]);
            new_time.Sec = time_buffer[2];
            new_time.Min = time_buffer[3];
            new_time.Hour = time_buffer[4];
            new_time.DayOfMonth = time_buffer[5];
            new_time.Month = time_buffer[6];
            
            result = sync_RTC(&new_time);

        }
    }
    
    return result;
}

void CMD_hard_reset(){

    reset_pointers();
    
    return;
}

void USB_Close(){
    
    rtc_setup();   
    USBUART_Stop();

    return;
}

/* [] END OF FILE */
