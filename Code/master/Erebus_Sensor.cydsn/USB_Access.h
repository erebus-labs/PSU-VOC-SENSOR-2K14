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
    #include "Interface.h"
    #include "RTC_Handler.h"
    #include "Macros.h"
    #include "Globals.h"

    // Function Prototypes
    void Run_USB();
    uint8 retrieve(uint8* buffer, uint8 num_bytes);
    uint8 apply_settings();
    void send_settings();
    uint8 dump_data();
    void confirm_dump();
    void write_out(uint8* ExportBuffer);
    uint8 wait_next();
    uint8 update_RTC();
    void send_reply(uint8 buffer);
    void CMD_hard_reset();
    void USB_Close();

#endif // ifndef _USB_ACCESS_H_



/* [] END OF FILE */
