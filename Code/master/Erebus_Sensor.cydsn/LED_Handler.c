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

#include "LED_Handler.h"

void USB_LED_on(){
    USB_Blink_TI_Start();
    return;
}

void USB_LED_off(){
    USB_Blink_TI_Stop();
    return;
}

void EEPROM_LED_on(){
    EEPROM_Blink_TI_Start();
    return;
}

void EEPROM_LED_off(){
    EEPROM_Blink_TI_Stop();
    return;
}

void flash_LED_on(){
    Flash_Blink_TI_Start();
    return;
}

void flash_LED_off(){
    Flash_Blink_TI_Stop();
    return;
}


/* [] END OF FILE */
