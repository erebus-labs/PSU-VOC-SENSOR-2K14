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

#include "Utility.h"

void hard_reset(){
    
    uint8 reset_flag = 0x00;
    
    /*  
    
    resetting data pointers needs to happen here
    
    */
    
    
    // End by clearing reset flag and reset again
    
    Em_EEPROM_Write(&reset_flag, &hard_reset_flag, 1u);
    CySoftwareReset();
    
    return;
}


/* [] END OF FILE */
