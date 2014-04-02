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
    command instruction = {0,0,0};
           
    /* Start USBFS Operation with 5V operation */
    USBUART_Start(0u, USBUART_5V_OPERATION);
    
    /* Wait for Device to enumerate */
    while(!USBUART_GetConfiguration() && Vbus_Read());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_CDC_Init();
      
    while(Vbus_Read())
    {  
        if(USBUART_DataIsReady() != 0u){   /* Check for input data from PC */
            result = retrieve(&instruction);
        
            if (result == SUCCESS){
                
                switch (instruction.command){
                
                    case IDENTIFY:
                        send_reply(IDENTIFIER);
                        break;
                    
                    case DUMP_DATA:
                        dump_data();
                        confirm_dump();
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

uint8 retrieve(command* instruction){
    uint8 buffer[BUFFER_LEN];
    uint16 count = 0;
    uint8 attempts = 0;
    uint8 result = SUCCESS;
    
    count = USBUART_GetCount(); 
    
    // If data in buffer is the right amount for a command,
    // retrieve it
    if(count == COMMAND_LENGTH){
        USBUART_GetData(buffer, COMMAND_LENGTH);
        instruction -> command = buffer[0];
        instruction -> target = (((uint16) buffer[1]) << 0x8) | buffer[2];
        instruction -> value = (((uint16) buffer[3]) << 0x8) | buffer[4];
    }
    // Otherwise, flush the USB buffer and report fail
    else{
        USBUART_GetChar();
        result = FAIL;
    }
    
    return result;
}

void apply_setting(command instruction){
    uint16 target = 0;

    switch (instruction.target){
        case SAMPLE_UNIT:
            target = EE_SAMPLE_UNIT;
            break;
        
        case SAMPLE_INTERVAL:
            target = EE_SAMPLE_INTERVAL;
            break;
        
        case SENSOR:
            target = EE_SENSOR;
            break;
    }
    
    update_variable(target, instruction.value);    
    
    return;
}

void dump_data(){
    uint8  ExportBuffer[BUFFER_LEN]; // 64 Bytes per USB data packet.
    uint8* ExportPtr =(uint8*) MemoryLocation; 
    uint16 DataCnt = 0;
    uint8  i = 0;
    
    /* Operator */
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
                ExportBuffer[i] = 0x40;
                ++i;
            }           
        }
        
        while(!USBUART_CDCIsReady() && Vbus_Read());
        USBUART_PutData(ExportBuffer, BUFFER_LEN); // Send 64 byte packet of data from memory
        i = 0;
    }
    
    /* Trailer Packet to Identify End of Sampled Data in Memory */
    ExportBuffer[0] = 0x80;               // End of Data Identifier
    ExportBuffer[1] = 0x00;
    
    //2 byte Count split into two 1 byte packages to be arrayed.
    ExportBuffer[2] = (uint8)(DataCnt >> 8);;          // Count of Total Bytes Sent
    ExportBuffer[3] = (uint8)0x00FF & DataCnt;
    while(!USBUART_CDCIsReady() && Vbus_Read());
    USBUART_PutData(ExportBuffer, 64u); 
    
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
    command instruction = {0,0,0};
    
    while(1){
        while(!USBUART_DataIsReady() && Vbus_Read());
        
        result = retrieve(&instruction);
        
        if(result == SUCCESS){
            if (instruction.command == SUCCESS){
                TailPtr = (uint8*) MemoryLocation;
            }
            break;
        }
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
