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

#ifndef _USB_ACCESS_H_
    #define _USB_ACCESS_H_

    // File Inclusions
    #include "Project.h"
    #include "EEPROM_Access.h"

    // Macros
    #define BUFFER_LEN          64u  
    #define SPLIT_PACKET_DELAY  10
    #define MAX_ATTEMPTS        10
    #define COMMAND_LENGTH      5
        
    /* Message Codes for USB Communications */
    
    // Incoming commands
    #define IDENTIFY        0x49    // "I"
    #define DUMP_DATA       0x44    // "D"
    #define CHANGE_SETTING  0x43    // "C"
    
    // Setting Codes
    #define SAMPLE_UNIT     0x55    // "U"
    #define SAMPLE_INTERVAL 0x56    // "V"
    #define SENSOR          0x53    // "S"    

    // Outgoing Responses
    #define REPLY_LEN   1
    #define IDENTIFIER  0x45    // "E"
    #define SUCCESS     0x59    // "Y"
    #define FAIL        0x4E    // "N"
    
          
    // Structures
    typedef struct usb_command{
        uint8 command;
        uint16 target;
        uint16 value;
    }command;
    
    // Function Prototypes
    void USB_ISR();
    uint8 retrieve(command* instruction);
    void apply_setting(command instruction);
    void dump_data();
    void confirm_dump();
    void send_reply(uint8 buffer);
    void USB_Close();

#endif // ifndef _USB_ACCESS_H_



/* [] END OF FILE */
