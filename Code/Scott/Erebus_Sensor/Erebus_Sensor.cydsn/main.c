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
uint8 Sample_waiting;

// RTC
uint8 sample_interval;

// Sampling
uint16 sample_int_count;


int main()
{
    low_power_flag = 0;
    USB_waiting = 0;
    DataStart_waiting = 0;
    DataStop_waiting = 0;
    Sample_waiting = 0;
    sample_int_count = 0;
    
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
    
    // Enable global interrupts
    CyGlobalIntEnable;
    
    // Enable individual interrupts as necessary   
    Vbus_IRQ_Start();
    StartCollection_IRQ_Start();
    
    for(;;){       

        if (Sample_waiting){
            ++sample_int_count;
    
            if (sample_int_count == sample_interval)
            {
                LED_on(BLUE);
                take_sample();
                
                sample_int_count = 0;
                
                CyDelay(LED_DELAY);
                LED_off();
            }
            Sample_waiting = 0;
        }
                
        else if(DataStart_waiting){
            LED_on(GREEN);
            clear_buttons();            
            StartCollection();
            CyDelay(LED_DELAY);
            LED_off();
        }
        
        else if(DataStop_waiting){
            LED_on(RED);            
            clear_buttons();            
            StopCollection();           
            CyDelay(LED_DELAY);
            LED_off();
        }
        
        else if(USB_waiting){
            LED_PWM_Wakeup();
            LED_on(CYAN);
            usb_prep();
            Run_USB();
            usb_exit();
            clear_vbus();
            LED_off();
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
