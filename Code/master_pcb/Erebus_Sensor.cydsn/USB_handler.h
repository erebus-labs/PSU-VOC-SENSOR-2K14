/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    USB_handler.h
 *
 * Contains macros, header file inclusions, function prototypes,
 * and structures required by USB-related functions
 *
 * ========================================
*/

#ifndef _USB_HANDLER_H_
    #define _USB_HANDLER_H_
    
    /*
     * ========================================
     * Macros
     * ========================================
    */

    /* Transmission Formatting */
    #define BUFFER_LEN          64u
    #define COMMAND_LENGTH      1
    
    /* Incoming Commands */
    #define NULL_BYTE       0x00
    #define IDENTIFY        0x01
    #define DUMP_DATA       0x02
    #define GET_SETTINGS    0x03
    #define CHANGE_SETTING  0x04
    #define RESET_PTRS      0x05
    #define UPDATE_RTC      0x06
    #define NEXT            0x07   

    /* Outgoing/Incoming Responses */
    #define REPLY_LEN   1
    #define IDENTIFIER  0x10    
    #define SUCCESS     0x20
    #define FAIL        0x30 
    
    /* Data Packet Markers */
    /* Each block of samples begins with STARTBLOCK defined as
     * 0x2000 in sample_handler.h - none of the USB functions
     * need this information, it's just an FYI */
    #define ENDDUMP     0x80
    #define PADBYTE     0x40
    #define NO_DATA     0xA0 
    
    /* EEPROM Information */
    #define EEPROM_ROWS         CYDEV_EE_SIZE / CYDEV_EEPROM_ROW_SIZE
    #define SECTOR_NUMBER       0
    #define EEPROM_BYTES_USED   0x3
    #define NUM_SETTINGS        0x3
           
    /* Real-time Clock Information */
    #define TIME_LENGTH 7
    /* TIME_LENGTH is how many bytes out of a RTC_TIME_DATE
     * structure we actually use to store a time stamp when we start
     * sampling
    */
    
    /* Rename Vbus_Read() for readability */
    #define check_usb_connection() Vbus_Read()

    
    /*
     * ========================================
     * Structures
     * ========================================
    */
    
    struct sampling_settings{
        uint8 sensor;
        uint8 sample_unit;
        uint8 sample_interval;
    };
       
    /*
     * ========================================
     * Function Prototypes
     * ========================================
    */
 
    void Run_USB();
    
#endif /* ifndef _USB_HANDLER_H */



/* [] END OF FILE */
