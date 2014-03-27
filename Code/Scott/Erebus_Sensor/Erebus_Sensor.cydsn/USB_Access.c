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

void USB_ISR(){
    
    // Power has just been applied to the Vbus pin, so we enter USB communication mode

    uint8 buffer[BUFFER_LEN];
    uint8 result = 0;
    command instruction = {0,0,0};
    
    uint8 temp = 0xFF;
  
    // Start EEPROM
    EEPROM_R_Start();
        
    /* Start USBFS Operation with 5V operation */
    USBUART_Start(0u, USBUART_5V_OPERATION);
    
    /* Wait for Device to enumerate */
    while(!USBUART_GetConfiguration() && Vbus_Read());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_CDC_Init();
      
    while(Vbus_Read())
    {    
        temp = USBUART_DataIsReady();
        if(temp != 0u){   /* Check for input data from PC */
            result = retrieve(buffer, &instruction);
        
            if (result == SUCCESS){
                
                switch (instruction.command){
                
                    case IDENTIFY:
                        send_reply(IDENTIFIER);
                        break;
                    
                    case DUMP_DATA:
                        dump_data();
                        send_reply(SUCCESS);
                        break;
                        
                    case CHANGE_SETTING:
                        apply_setting(instruction);
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
    
    return;
}

uint8 retrieve(uint8* buffer, command* instruction){
    uint16 count = 0;
    uint8 attempts = 0;
    uint8 result = SUCCESS;
    
    count = USBUART_GetCount(); 
    
    // If data in buffer is the right amount for a command,
    // retrieve it
    if(count == COMMAND_LENGTH){
        USBUART_GetData(buffer, RETRIEVE_LEN);
        instruction -> command = buffer[0];
        instruction -> target = buffer[1] & (buffer[2] << 0x8);
        instruction -> value = buffer[3] & (buffer[4] << 0x8);
    }
    // Otherwise, flush the USB buffer and report fail
    else{
        USBUART_GetAll(buffer);
        result = FAIL;
    }
    
    return result;
}

void apply_setting(command instruction){
    
    update_variable(instruction.target, instruction.value);    
    
    return;
}

void dump_data(){
    // Not Yet Implemented
    
    return;
}

void send_reply(uint8 message){
   
    while(!USBUART_CDCIsReady() && Vbus_Read());
    
    if(Vbus_Read()){
        USBUART_PutData(&message, REPLY_LEN);
    }
    
    return;
}


void USB_Close(){
    
    EEPROM_R_Stop();
    USBUART_Stop();
    CySoftwareReset();
    
    return;
}


/* [] END OF FILE */
