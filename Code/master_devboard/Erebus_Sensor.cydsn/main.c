/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    main.c
 *
 * Contains initializations and main()
 *
 * ========================================
*/

#include "main.h"

/*
 * ========================================
 * Global Variable Definitions
 * ========================================
*/

/* Awaiting Action Flags */ 
uint8 start_sampling_waiting = 0;
uint8 stop_sampling_waiting = 0;
uint8 take_sample_waiting = 0;
uint8 USB_waiting = 0;
uint8 battery_check_waiting = 0;
uint8 low_battery_blink_waiting = 0;

/* Condition Flags */
uint8 sample_enable_flag = 0;
uint8 low_power_flag = 0;
uint8 mem_full_flag = 0;

uint8 stop_collection_enabled = 0;
uint8 start_collection_enabled = 0;

/* Counters for Events */
uint8 sample_interrupt_count = 0;
uint8 battery_check_count = 0;
uint8 low_batt_blink_count = 0;

/* RTC Parameters */
uint8 sample_unit;
uint8 sample_interval;    

/* Nonvolatile Variables stored in Flash */
const uint8 CYCODE sample_block[SAMPLE_BLOCK_SIZE]; 
const uint16 CYCODE current_sample_indices[MASTER_ROWS * FLASH_ROW_LENGTH];
const uint16 CYCODE master_sample_indices[MASTER_PTR_COUNT];
const uint8 CYCODE mem_full_flash_flag;

/* SRAM Head/Tail Indexes */
volatile uint16 pointer_head_index;
volatile uint16 pointer_tail_index;
volatile uint16 sample_head_index;
volatile uint16 sample_tail_index;

int main()
{

    /*
     * ========================================
     * Initialization
     * ========================================
    */
    
    /* Retrieve sample pointers from Flash */
    pointer_head_index = master_sample_indices[HEAD_INDEX];
    pointer_tail_index = master_sample_indices[TAIL_INDEX];
    sample_head_index = current_sample_indices[pointer_head_index];
    sample_tail_index = current_sample_indices[pointer_tail_index];
    
    /* Start Components */
    Re_EEPROM_Start();
    RTC_Start();
    LED_PWM_Start();
    LED_PWM_Sleep();
    ADC_Start();
    ADC_Sleep();
    ADC_MUX_Start();
    ADC_MUX_Select(SAMPLE_PIN);
    
    /* Retrieve sampling parameters and set RTC masks appropriately */
    sampling_setup();
    
    /* Enable global interrupts */
    CyGlobalIntEnable;
    
    /* Enable Individual Component Interrupts */  
    Vbus_IRQ_Start();
    ModifyCollection_IRQ_Start();
    start_collection_enabled = 1;
    
    
    /* Retrieve Full Memory Flag from Flash */
    mem_full_flag = mem_full_flash_flag;
    if (mem_full_flag){
        memory_full();
    }
    
    /* Initial check of battery level */
    check_battery();
    
    /*
     * ========================================
     * Main Loop
     * ========================================
    */
    
    for(;;){       

        #ifdef SLEEP_EN 
        /* Prepare for sleep */
        RTC_DisableInt();
        CyPmSaveClocks();        
      
        /* Go to sleep for 1 second, allow waking from GPIO interrupts or RTC second pulse */
        CyPmSleep(PM_SLEEP_TIME_NONE, (PM_SLEEP_SRC_ONE_PPS | PM_SLEEP_SRC_PICU));     

        /* Restore on wakeup */
        CyPmRestoreClocks(); 
        RTC_EnableInt();
        #endif
        

        
        /* Cycle through and check each flag that may have been set while asleep */
        if (USB_waiting){
            LED_PWM_Wakeup();
            LED_on(CYAN);
            Run_USB();
            clear_button_interrupts();
            LED_off();
        }
        
        if (mem_full_flag){
            LED_on(RED);
            continue;
        }
        
        if (take_sample_waiting){
            LED_on(BLUE);
            take_sample();          
            CyDelay(LED_DELAY);
            LED_off();
            take_sample_waiting = 0;
        }
         
        if (start_sampling_waiting){
            LED_on(GREEN);
            clear_button_interrupts();            
            start_collection();
            CyDelay(LED_DELAY);
            LED_off();
        }
        
        if (stop_sampling_waiting){
            LED_on(RED);            
            clear_button_interrupts();            
            stop_collection();           
            CyDelay(LED_DELAY);
            LED_off();
        }        
        
        if (battery_check_waiting){
            check_battery();
            battery_check_waiting = 0;
        }
        
        if (low_battery_blink_waiting){
            LED_PWM_Wakeup();
            LED_on(YELLOW);
            CyDelay(LOWBATT_BLINK_DELAY);
            LED_off();
            low_battery_blink_waiting = 0;
        }               
    }
    
    return (0);
}

/* [] END OF FILE */

