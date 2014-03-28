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

    uint8 buffer[BUFFER_LEN];
    uint8 result = 0;
    command instruction = {0,0,0};
    
    uint8 temp = 0xFF;
  
        
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
                        //send_reply(SUCCESS);
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
        USBUART_GetData(buffer, COMMAND_LENGTH);
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
    uint8  ExportBuffer[BUFFER_LEN]; // 64 Bytes per USB data packet.
    uint8* ExportPtr =(uint8*) MemoryLocation; 
    uint16 DataCnt = 0;
    uint8  CntSplit1, CntSplit2;
    uint8  i = 0;
    
    /* Operator */
    while (ExportPtr <= TailPtr)
    {   
        while (i < BUFFER_LEN)
        {
            if (ExportPtr <= TailPtr)
            {
                ExportBuffer[i] = *ExportPtr; // Copy sampled data from flash at *ExportPtr to buffer for send over usb com 
                ++i;
                ExportPtr++;
                ++DataCnt;
            }
            else
            {
                ExportBuffer[i] = 0x00;
                ++i;
            }
            
        }
        
        USBUART_PutData(ExportBuffer, BUFFER_LEN); // Send 64 byte packet of data from memory
        i = 0;
    }
    /* Trailer Packet to Identify End of Sampled Data in Memory */
    ExportBuffer[0] = 0x80;               // End of Data Identifier
    ExportBuffer[1] = 0x00;
    CntSplit1 = (uint8)0xFF00 & DataCnt;  //2 byte Count split into two 1 byte packages to be arrayed.
    CntSplit2 = (uint8)0x00FF & DataCnt;
    ExportBuffer[2] = CntSplit1;          // Count of Total Samples Sent
    ExportBuffer[3] = CntSplit2;
    USBUART_PutData(ExportBuffer, 4u); 
    
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
