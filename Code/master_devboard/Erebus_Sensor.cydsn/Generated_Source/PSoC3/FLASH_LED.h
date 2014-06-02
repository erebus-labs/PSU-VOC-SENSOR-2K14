/*******************************************************************************
* File Name: FLASH_LED.h  
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

#if !defined(CY_PINS_FLASH_LED_H) /* Pins FLASH_LED_H */
#define CY_PINS_FLASH_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FLASH_LED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    FLASH_LED_Write(uint8 value) ;
void    FLASH_LED_SetDriveMode(uint8 mode) ;
uint8   FLASH_LED_ReadDataReg(void) ;
uint8   FLASH_LED_Read(void) ;
uint8   FLASH_LED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define FLASH_LED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define FLASH_LED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define FLASH_LED_DM_RES_UP          PIN_DM_RES_UP
#define FLASH_LED_DM_RES_DWN         PIN_DM_RES_DWN
#define FLASH_LED_DM_OD_LO           PIN_DM_OD_LO
#define FLASH_LED_DM_OD_HI           PIN_DM_OD_HI
#define FLASH_LED_DM_STRONG          PIN_DM_STRONG
#define FLASH_LED_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define FLASH_LED_MASK               FLASH_LED__MASK
#define FLASH_LED_SHIFT              FLASH_LED__SHIFT
#define FLASH_LED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FLASH_LED_PS                     (* (reg8 *) FLASH_LED__PS)
/* Data Register */
#define FLASH_LED_DR                     (* (reg8 *) FLASH_LED__DR)
/* Port Number */
#define FLASH_LED_PRT_NUM                (* (reg8 *) FLASH_LED__PRT) 
/* Connect to Analog Globals */                                                  
#define FLASH_LED_AG                     (* (reg8 *) FLASH_LED__AG)                       
/* Analog MUX bux enable */
#define FLASH_LED_AMUX                   (* (reg8 *) FLASH_LED__AMUX) 
/* Bidirectional Enable */                                                        
#define FLASH_LED_BIE                    (* (reg8 *) FLASH_LED__BIE)
/* Bit-mask for Aliased Register Access */
#define FLASH_LED_BIT_MASK               (* (reg8 *) FLASH_LED__BIT_MASK)
/* Bypass Enable */
#define FLASH_LED_BYP                    (* (reg8 *) FLASH_LED__BYP)
/* Port wide control signals */                                                   
#define FLASH_LED_CTL                    (* (reg8 *) FLASH_LED__CTL)
/* Drive Modes */
#define FLASH_LED_DM0                    (* (reg8 *) FLASH_LED__DM0) 
#define FLASH_LED_DM1                    (* (reg8 *) FLASH_LED__DM1)
#define FLASH_LED_DM2                    (* (reg8 *) FLASH_LED__DM2) 
/* Input Buffer Disable Override */
#define FLASH_LED_INP_DIS                (* (reg8 *) FLASH_LED__INP_DIS)
/* LCD Common or Segment Drive */
#define FLASH_LED_LCD_COM_SEG            (* (reg8 *) FLASH_LED__LCD_COM_SEG)
/* Enable Segment LCD */
#define FLASH_LED_LCD_EN                 (* (reg8 *) FLASH_LED__LCD_EN)
/* Slew Rate Control */
#define FLASH_LED_SLW                    (* (reg8 *) FLASH_LED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FLASH_LED_PRTDSI__CAPS_SEL       (* (reg8 *) FLASH_LED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FLASH_LED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FLASH_LED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FLASH_LED_PRTDSI__OE_SEL0        (* (reg8 *) FLASH_LED__PRTDSI__OE_SEL0) 
#define FLASH_LED_PRTDSI__OE_SEL1        (* (reg8 *) FLASH_LED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FLASH_LED_PRTDSI__OUT_SEL0       (* (reg8 *) FLASH_LED__PRTDSI__OUT_SEL0) 
#define FLASH_LED_PRTDSI__OUT_SEL1       (* (reg8 *) FLASH_LED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FLASH_LED_PRTDSI__SYNC_OUT       (* (reg8 *) FLASH_LED__PRTDSI__SYNC_OUT) 


#if defined(FLASH_LED__INTSTAT)  /* Interrupt Registers */

    #define FLASH_LED_INTSTAT                (* (reg8 *) FLASH_LED__INTSTAT)
    #define FLASH_LED_SNAP                   (* (reg8 *) FLASH_LED__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins FLASH_LED_H */


/* [] END OF FILE */
