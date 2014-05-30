/* ========================================
 *
 * (c) Erebus Labs Ltd. 2014
 *
 * Project: Erebus Labs Sensor
 * File:    main.h
 *
 * Contains macros and header file inclusions required by main()
 *
 * ========================================
*/

#ifndef _MAIN_H_
    #define _MAIN_H_
    
    /*
     * ========================================
     * Header Files
     * ========================================
    */
    
    /* C Library Headers */
    #include <stdlib.h>
    
    /* Cypress Headers */
    #include "project.h"

    /* Project Headers */
    #include "LED_handler.h"
    #include "USB_handler.h"
    #include "utility.h"
    #include "sample_handler.h"
    #include "globals.h"
    
    /*
     * ========================================
     * Macros
     * ========================================
    */  

    /* Comment this out to remove sleep-related code */
    #define SLEEP_EN

#endif /* ifndef _MAIN_H_ */

/* [] END OF FILE */
