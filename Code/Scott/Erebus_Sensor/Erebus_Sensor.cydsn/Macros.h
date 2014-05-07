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

#ifndef _MACROS_H_
    #define _MACROS_H_
    
    /*      Shared      */
    
    #define SLEEP_EN    // Comment this out to remove sleep code
    
    #define SUCCESS     0x02
    #define FAIL        0x03    
    
    // RTC Time Unit Codes
    #define SAMPLE_SEC      0x00
    #define SAMPLE_MIN      0x01
    #define SAMPLE_HOUR     0x02
    #define SAMPLE_DAY      0x03    
        
    // Setting Codes
    #define SAMPLE_UNIT     0x01
    #define SAMPLE_INTERVAL 0x02
    #define SENSOR          0x03 
    
    
    
    /*      RTC         */
        
    #define TIME_LENGTH 7

    #define NONE_MASK   0x00u
    #define SECOND_MASK 0x01u
    #define MINUTE_MASK 0x02u
    #define HOUR_MASK   0x04u
    #define DAY_MASK    0x08u
    
    
    
    /*      USB         */

    #define BUFFER_LEN          64u  
    #define SPLIT_PACKET_DELAY  10
    #define MAX_ATTEMPTS        10
    #define COMMAND_LENGTH      1
    
    // Incoming commands
    #define NULL_BYTE       0x00
    #define IDENTIFY        0x01
    #define DUMP_DATA       0x02
    #define GET_SETTINGS    0x03
    #define CHANGE_SETTING  0x04
    #define HARD_RESET      0x05
    #define UPDATE_RTC      0x06
    #define NEXT            0x07   

    // Outgoing Responses
    #define REPLY_LEN   1
    #define IDENTIFIER  0x01
    
    // Data Packet Markers
    #define STARTBLOCK  0x2000 // This must be 16 bits - it is stored as uint16
    #define ENDDUMP     0x80
    #define PADBYTE     0x40
    #define NO_DATA     0xA0 
    
    
    
    /*      EEPROM      */

    // Base Information    
    #define EEPROM_ROWS CYDEV_EE_SIZE / CYDEV_EEPROM_ROW_SIZE
    #define SECTOR_NUMBER 0

    // EEPROM Array index of each user variable 
    #define EE_SENSOR           0x0
    #define EE_SAMPLE_UNIT      EE_SENSOR + 1
    #define EE_SAMPLE_INTERVAL  EE_SAMPLE_UNIT + 1

    #define EEPROM_BYTES_USED   0x3
    #define NUM_SETTINGS        0x3
       

    
    /*      EmEEPROM    */
    #define EmEEPROMSize 1024 
    
    
    
    /*      LEDs        */

    #define ALL     0x00
    #define USB     0x01
    #define MEM     0x02
    #define LOWBATT 0x03
    #define ERROR   0x04
    #define SAMPLE  0x05
    #define BUTTON  0x06
    
    #define OFF     0x00
    #define RED     0x01
    #define BLUE    0x02
    #define GREEN   0x03
    
    #define LED_DELAY 250
    
#endif

/* [] END OF FILE */
