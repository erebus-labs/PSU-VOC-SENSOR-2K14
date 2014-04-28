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
#include "EmEEPROM_Access.h" // Location of sampled data in flash
/* This file provides function definitions for USB interactions */

void USB_ISR(){
    
    // Power has just been applied to the Vbus pin, so we enter USB communication mode

    uint8 result = 0;
    uint8 command = 0;
    USB_LED_on();
           
    /* Start USBFS Operation with 5V operation */
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
                        dump_data();
                        confirm_dump();
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
                     
                    case HARD_RESET:
                        hard_reset();
                        send_reply(SUCCESS);
                        break;
                        
                    default:
                        send_reply(FAIL);
                }
            }   
            else{
                send_reply(FAIL);
            }
        }
    }
    
    USB_Close();
    USB_LED_off();
    
    return;
}

uint8 retrieve(uint8* buffer, uint8 num_bytes){
    uint16 count = 0;
    uint8 attempts = 0;
    uint8 result = SUCCESS;
    
    count = USBUART_GetCount(); 
    
    // If data in buffer is the right amount for a command,
    // retrieve it
    if(count == num_bytes){
        USBUART_GetData(buffer, num_bytes);
    }
    // Otherwise, flush the USB buffer and report fail
    else{
        USBUART_GetChar();
        result = FAIL;
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

void dump_data(){
    uint8  ExportBuffer[BUFFER_LEN]; // 64 Bytes per USB data packet.
    uint8* ExportPtr =(uint8*) MemoryLocation; 
    uint16 DataCnt = 0;
    uint8  i = 0;
    
    flash_LED_on();
    while (ExportPtr < TailPtr)
    {   
        while (i < BUFFER_LEN)
        {
            if (ExportPtr < TailPtr)
            {
                ExportBuffer[i] = *ExportPtr; // Copy sampled data from flash at *ExportPtr to buffer for send over usb com 
                ++i;
                ++ExportPtr;
                ++DataCnt;
            }
            else
            {
                ExportBuffer[i] = PADBYTE;
                ++i;
            }           
        }
        
        while(!USBUART_CDCIsReady() && Vbus_Read());
        USBUART_PutData(ExportBuffer, BUFFER_LEN); // Send 64 byte packet of data from memory
        i = 0;
    }
    
    // Add the size trailer packet to get total transmission size
    DataCnt = DataCnt + 4;
    
    /* Trailer Packet to Identify End of Sampled Data in Memory */
    ExportBuffer[0] = 0x80;               // End of Data Identifier
    ExportBuffer[1] = 0x00;
    
    //2 byte Count split into two 1 byte packages to be arrayed.
    ExportBuffer[2] = (uint8)(DataCnt >> 8);;          // Count of Total Bytes Sent
    ExportBuffer[3] = (uint8)0x00FF & DataCnt;
    
    // Wait for UART to be ready
    while(!USBUART_CDCIsReady() && Vbus_Read());
    USBUART_PutData(ExportBuffer, 64u);
    
    flash_LED_off();
    
    return;
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
    
    while(1){
        while(!USBUART_DataIsReady() && Vbus_Read());
        
        result = retrieve(&command, COMMAND_LENGTH);
        
        if(result == SUCCESS){
            if (command == SUCCESS){
                TailPtr = (uint8*) MemoryLocation;
            }
            break;
        }
    }
    
    return;
}

void CMD_hard_reset(){

    uint8 reset_flag = 0xFF;
    
    flash_LED_on();
    Em_EEPROM_Write(&reset_flag, &hard_reset_flag, 1u);
    flash_LED_off();
    
    return;
}

void USB_Close(){
    
    EEPROM_R_Stop();
    USBUART_Stop();
    CySoftwareReset();
    
    return;
}




/* [] END OF FILE */
