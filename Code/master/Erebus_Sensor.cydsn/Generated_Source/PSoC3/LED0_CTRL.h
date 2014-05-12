/*******************************************************************************
* File Name: LED0_CTRL.h  
* Version 1.70
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_LED0_CTRL_H) /* CY_CONTROL_REG_LED0_CTRL_H */
#define CY_CONTROL_REG_LED0_CTRL_H

#include "cytypes.h"


/***************************************
*         Function Prototypes 
***************************************/

void    LED0_CTRL_Write(uint8 control) ;
uint8   LED0_CTRL_Read(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define LED0_CTRL_Control        (* (reg8 *) LED0_CTRL_Sync_ctrl_reg__CONTROL_REG )
#define LED0_CTRL_Control_PTR    (  (reg8 *) LED0_CTRL_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_LED0_CTRL_H */


/* [] END OF FILE */