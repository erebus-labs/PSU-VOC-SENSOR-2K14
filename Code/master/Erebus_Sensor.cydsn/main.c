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
uint8 low_power_flag = 0;
uint8 USB_waiting = 0;
uint8 DataStart_waiting = 0;
uint8 DataStop_waiting = 0;
uint8 Sample_waiting = 0;
uint8 BatteryCheck_waiting = 0;
uint8 LowPowerBlink_waiting = 0;

// RTC
uint8 sample_interval = 0;
uint8 sample_enable = 0;

// Sampling
uint8 sample_int_count = 0;
uint8 sample_unit = 0;
uint8 battery_check_count = 0;
uint8 low_batt_blink_count = 0;

int main()
{

    
    // Check for hard reset flag
    if (hard_reset_flag){
        hard_reset();   
    }
    /* Initialization*/

    // Start Components
    EEPROM_R_Start();
    RTC_Start();
    rtc_setup();
    LED_PWM_Start();
    LED_PWM_Sleep();
    ADC_Start();
    ADC_Sleep();
    ADC_MUX_Start();
    ADC_MUX_Select(SAMPLE_PIN);
    
    // Enable global interrupts
    CyGlobalIntEnable;
    
    // Enable individual interrupts as necessary   
    Vbus_IRQ_Start();
    StartCollection_IRQ_Start();
        
    for(;;){       

        if (Sample_waiting){
            LED_on(BLUE);
            take_sample();          
            CyDelay(LED_DELAY);
            LED_off();
            Sample_waiting = 0;
        }
         
        if(DataStart_waiting){
            LED_on(GREEN);
            clear_buttons();            
            StartCollection();
            CyDelay(LED_DELAY);
            LED_off();
        }
        
        if(DataStop_waiting){
            LED_on(RED);            
            clear_buttons();            
            StopCollection();           
            CyDelay(LED_DELAY);
            LED_off();
        }
        
        if(USB_waiting){
            LED_PWM_Wakeup();
            LED_on(CYAN);
            usb_prep();
            Run_USB();
            usb_exit();
            clear_vbus();
            LED_off();
        }        
        
        if (BatteryCheck_waiting){
            check_battery();
            BatteryCheck_waiting = 0;
        }
        
        if(LowPowerBlink_waiting){
            LED_PWM_Wakeup();
            LED_on(YELLOW);
            CyDelay(LOWBATT_BLINK_DELAY);
            LED_off();
            LowPowerBlink_waiting = 0;
        }
                
        #ifdef SLEEP_EN 
        RTC_DisableInt();
        CyPmSaveClocks();        
      
        CyPmSleep(PM_SLEEP_TIME_NONE, (PM_SLEEP_SRC_ONE_PPS | PM_SLEEP_SRC_PICU));     

        CyPmRestoreClocks(); 
        RTC_EnableInt();

        #endif
       
    }
    
    return (0);
}

/* [] END OF FILE */
