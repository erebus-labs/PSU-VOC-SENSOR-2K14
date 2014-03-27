/*******************************************************************************
* File Name: USB_UART_Dm.h  
* Version 1.90
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

#if !defined(CY_PINS_USB_UART_Dm_H) /* Pins USB_UART_Dm_H */
#define CY_PINS_USB_UART_Dm_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "USB_UART_Dm_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    USB_UART_Dm_Write(uint8 value) ;
void    USB_UART_Dm_SetDriveMode(uint8 mode) ;
uint8   USB_UART_Dm_ReadDataReg(void) ;
uint8   USB_UART_Dm_Read(void) ;
uint8   USB_UART_Dm_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define USB_UART_Dm_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define USB_UART_Dm_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define USB_UART_Dm_DM_RES_UP          PIN_DM_RES_UP
#define USB_UART_Dm_DM_RES_DWN         PIN_DM_RES_DWN
#define USB_UART_Dm_DM_OD_LO           PIN_DM_OD_LO
#define USB_UART_Dm_DM_OD_HI           PIN_DM_OD_HI
#define USB_UART_Dm_DM_STRONG          PIN_DM_STRONG
#define USB_UART_Dm_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define USB_UART_Dm_MASK               USB_UART_Dm__MASK
#define USB_UART_Dm_SHIFT              USB_UART_Dm__SHIFT
#define USB_UART_Dm_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define USB_UART_Dm_PS                     (* (reg8 *) USB_UART_Dm__PS)
/* Data Register */
#define USB_UART_Dm_DR                     (* (reg8 *) USB_UART_Dm__DR)
/* Port Number */
#define USB_UART_Dm_PRT_NUM                (* (reg8 *) USB_UART_Dm__PRT) 
/* Connect to Analog Globals */                                                  
#define USB_UART_Dm_AG                     (* (reg8 *) USB_UART_Dm__AG)                       
/* Analog MUX bux enable */
#define USB_UART_Dm_AMUX                   (* (reg8 *) USB_UART_Dm__AMUX) 
/* Bidirectional Enable */                                                        
#define USB_UART_Dm_BIE                    (* (reg8 *) USB_UART_Dm__BIE)
/* Bit-mask for Aliased Register Access */
#define USB_UART_Dm_BIT_MASK               (* (reg8 *) USB_UART_Dm__BIT_MASK)
/* Bypass Enable */
#define USB_UART_Dm_BYP                    (* (reg8 *) USB_UART_Dm__BYP)
/* Port wide control signals */                                                   
#define USB_UART_Dm_CTL                    (* (reg8 *) USB_UART_Dm__CTL)
/* Drive Modes */
#define USB_UART_Dm_DM0                    (* (reg8 *) USB_UART_Dm__DM0) 
#define USB_UART_Dm_DM1                    (* (reg8 *) USB_UART_Dm__DM1)
#define USB_UART_Dm_DM2                    (* (reg8 *) USB_UART_Dm__DM2) 
/* Input Buffer Disable Override */
#define USB_UART_Dm_INP_DIS                (* (reg8 *) USB_UART_Dm__INP_DIS)
/* LCD Common or Segment Drive */
#define USB_UART_Dm_LCD_COM_SEG            (* (reg8 *) USB_UART_Dm__LCD_COM_SEG)
/* Enable Segment LCD */
#define USB_UART_Dm_LCD_EN                 (* (reg8 *) USB_UART_Dm__LCD_EN)
/* Slew Rate Control */
#define USB_UART_Dm_SLW                    (* (reg8 *) USB_UART_Dm__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define USB_UART_Dm_PRTDSI__CAPS_SEL       (* (reg8 *) USB_UART_Dm__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define USB_UART_Dm_PRTDSI__DBL_SYNC_IN    (* (reg8 *) USB_UART_Dm__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define USB_UART_Dm_PRTDSI__OE_SEL0        (* (reg8 *) USB_UART_Dm__PRTDSI__OE_SEL0) 
#define USB_UART_Dm_PRTDSI__OE_SEL1        (* (reg8 *) USB_UART_Dm__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define USB_UART_Dm_PRTDSI__OUT_SEL0       (* (reg8 *) USB_UART_Dm__PRTDSI__OUT_SEL0) 
#define USB_UART_Dm_PRTDSI__OUT_SEL1       (* (reg8 *) USB_UART_Dm__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define USB_UART_Dm_PRTDSI__SYNC_OUT       (* (reg8 *) USB_UART_Dm__PRTDSI__SYNC_OUT) 


#if defined(USB_UART_Dm__INTSTAT)  /* Interrupt Registers */

    #define USB_UART_Dm_INTSTAT                (* (reg8 *) USB_UART_Dm__INTSTAT)
    #define USB_UART_Dm_SNAP                   (* (reg8 *) USB_UART_Dm__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins USB_UART_Dm_H */


/* [] END OF FILE */
