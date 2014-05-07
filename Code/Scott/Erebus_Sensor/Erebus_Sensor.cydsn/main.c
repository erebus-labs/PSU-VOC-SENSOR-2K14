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

#include "main.h"

/* Globals */

// Flash
const uint8 CYCODE MemoryLocation[EmEEPROMSize]; 
const volatile uint8* TailPtr = (uint8*) MemoryLocation;
const uint8 CYCODE hard_reset_flag;

// Flags
uint8 low_power_flag;
uint8 USB_waiting;
uint8 DataStart_waiting;
uint8 DataStop_waiting;

int main()
{
    low_power_flag = 0;
    USB_waiting = 0;
    DataStart_waiting = 0;
    DataStop_waiting = 0;
    
    // Check for hard reset flag
    if (hard_reset_flag){
        hard_reset();   
    }
    /* Initialization*/

    // Start Components
    EEPROM_R_Start();
    LED_PWM_Start();
    ADC_Start();
    ADC_Sleep();
    RTC_Start();
    rtc_setup();
    
    // Set interrupts for pins that can wake the chip
    CY_SET_REG8(CYREG_PICU12_INTTYPE6, 0x02); //Port 12, pin 6, falling edge
    CY_SET_REG8(CYREG_PICU3_INTTYPE0, 0x02); //Port 3, pin 0, falling edge
    CY_SET_REG8(CYREG_PICU6_INTTYPE0, 0x01); //Port 6, pin 0, rising edge
    
    // Enable global interrupts
    CyGlobalIntEnable;
    
    // Enable individual interrupts as necessary   
    Vbus_IRQ_Start();
    StartCollection_IRQ_Start();
    
    for(;;){       
        
        #ifdef SLEEP_EN 
        LED_PWM_Sleep();
        RTC_DisableInt();
        CyPmSaveClocks();        
      
        CyPmSleep(PM_SLEEP_TIME_ONE_PPS, (PM_SLEEP_SRC_ONE_PPS | PM_SLEEP_SRC_PICU));     

        CyPmRestoreClocks(); 
        RTC_EnableInt();
        LED_PWM_Wakeup();
        #endif
        
        if(USB_waiting){
            Run_USB();
            Vbus_ClearInterrupt();
            Vbus_IRQ_ClearPending();
            USB_waiting = 0;
        }
        
        else if(DataStart_waiting){
            StartCollection();
            DataStart_waiting = 0;
            CyDelay(LED_DELAY);
            StartCollection_B_ClearInterrupt();
            StartCollection_IRQ_ClearPending();
            LED_off(BUTTON);
        }
        
        else if(DataStop_waiting){
            StopCollection();
            DataStop_waiting = 0;
            CyDelay(LED_DELAY);
            StopCollection_B_ClearInterrupt();
            StopCollection_IRQ_ClearPending();
            LED_off(BUTTON);
        }
        
    }
    
    return (0);
}

/* [] END OF FILE */
