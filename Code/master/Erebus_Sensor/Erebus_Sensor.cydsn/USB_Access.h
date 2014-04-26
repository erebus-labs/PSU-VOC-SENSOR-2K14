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
    #include "Utility.h"
    #include "LED_Handler.h"

    // Macros
    #define BUFFER_LEN          64u  
    #define SPLIT_PACKET_DELAY  10
    #define MAX_ATTEMPTS        10
    #define COMMAND_LENGTH      5
        
    /* Message Codes for USB Communications */
    
    // Incoming commands
    #define IDENTIFY        0x01
    #define DUMP_DATA       0x02
    #define GET_SETTINGS    0x03
    #define CHANGE_SETTING  0x04
    #define HARD_RESET      0x05
    
    // Setting Codes
    #define SAMPLE_UNIT     0x01
    #define SAMPLE_INTERVAL 0x02
    #define SENSOR          0x03    

    // Outgoing Responses
    #define REPLY_LEN   1
    #define IDENTIFIER  0x01
    #define SUCCESS     0x02
    #define FAIL        0x03
    
    // Data Packet Markers
    #define STARTBLOCK  0x4000 // This must be 16 bits - it is stored as uint16
    #define ENDDUMP     0x80
    #define PADBYTE     0x40
    
          
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
    void send_settings();
    void dump_data();
    void confirm_dump();
    void send_reply(uint8 buffer);
    void CMD_hard_reset();
    void USB_Close();

#endif // ifndef _USB_ACCESS_H_



/* [] END OF FILE */
