/*******************************************************************************
* File Name: USBUART_1_Vbus_ps.h  
* Version 1.80
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_USBUART_1_Vbus_ps_H) /* CY_STATUS_REG_USBUART_1_Vbus_ps_H */
#define CY_STATUS_REG_USBUART_1_Vbus_ps_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Function Prototypes
***************************************/

uint8 USBUART_1_Vbus_ps_Read(void) ;
void USBUART_1_Vbus_ps_InterruptEnable(void) ;
void USBUART_1_Vbus_ps_InterruptDisable(void) ;
void USBUART_1_Vbus_ps_WriteMask(uint8 mask) ;
uint8 USBUART_1_Vbus_ps_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define USBUART_1_Vbus_ps_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define USBUART_1_Vbus_ps_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define USBUART_1_Vbus_ps_Status             (* (reg8 *) USBUART_1_Vbus_ps_sts_sts_reg__STATUS_REG )
#define USBUART_1_Vbus_ps_Status_PTR         (  (reg8 *) USBUART_1_Vbus_ps_sts_sts_reg__STATUS_REG )
#define USBUART_1_Vbus_ps_Status_Mask        (* (reg8 *) USBUART_1_Vbus_ps_sts_sts_reg__MASK_REG )
#define USBUART_1_Vbus_ps_Status_Aux_Ctrl    (* (reg8 *) USBUART_1_Vbus_ps_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_USBUART_1_Vbus_ps_H */


/* [] END OF FILE */
