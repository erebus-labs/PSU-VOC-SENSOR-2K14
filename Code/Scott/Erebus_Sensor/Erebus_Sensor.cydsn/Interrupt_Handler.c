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

#include "Interrupt_Handler.h"

void clear_buttons(){
                
    // Clear any pending stop or start interrupts
    StopCollection_B_ClearInterrupt();
    StopCollection_IRQ_ClearPending();
    DataStop_waiting = 0;
    StartCollection_B_ClearInterrupt();
    StartCollection_IRQ_ClearPending();  
    DataStart_waiting = 0;  
    
    return;
}

void clear_vbus(){
    
    Vbus_ClearInterrupt();
    Vbus_IRQ_ClearPending();
    USB_waiting = 0; 
    return;
}

void usb_prep(){
    
    StartCollection_IRQ_Stop();
    StopCollection_IRQ_Stop();
    Vbus_IRQ_Stop();
    RTC_WriteIntervalMask(NONE_MASK);
    return;
}

void usb_exit(){
    
    StartCollection_IRQ_Start();
    Vbus_IRQ_Start();
    
    // We don't reset the RTC_WriteIntervalMask register on the
    // way out - that will be done when a new sample collection
    // block starts
       
    return;
}

/* [] END OF FILE */
