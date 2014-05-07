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

#ifndef _EEPROM_ACCESS_H_
    #define _EEPROM_ACCESS_H_

    #include <math.h>
    #include <stdlib.h>
    #include "project.h"
    #include "Interface.h"
    #include "Macros.h"
    
    typedef struct eeprom_settings{
        uint8 sensor;
        uint8 sample_unit;
        uint8 sample_interval;
    }settings_group;
       
    uint8 get_variable(uint16 var_index);
    uint8 update_settings(settings_group new_settings);
    
#endif // ifndef _EEPROM_ACCESS_H_

/* [] END OF FILE */
