/*******************************************************************************
* File Name: SW_3.h  
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

#if !defined(CY_PINS_SW_3_H) /* Pins SW_3_H */
#define CY_PINS_SW_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SW_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SW_3_Write(uint8 value) ;
void    SW_3_SetDriveMode(uint8 mode) ;
uint8   SW_3_ReadDataReg(void) ;
uint8   SW_3_Read(void) ;
uint8   SW_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SW_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SW_3_DM_RES_UP          PIN_DM_RES_UP
#define SW_3_DM_RES_DWN         PIN_DM_RES_DWN
#define SW_3_DM_OD_LO           PIN_DM_OD_LO
#define SW_3_DM_OD_HI           PIN_DM_OD_HI
#define SW_3_DM_STRONG          PIN_DM_STRONG
#define SW_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SW_3_MASK               SW_3__MASK
#define SW_3_SHIFT              SW_3__SHIFT
#define SW_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW_3_PS                     (* (reg8 *) SW_3__PS)
/* Data Register */
#define SW_3_DR                     (* (reg8 *) SW_3__DR)
/* Port Number */
#define SW_3_PRT_NUM                (* (reg8 *) SW_3__PRT) 
/* Connect to Analog Globals */                                                  
#define SW_3_AG                     (* (reg8 *) SW_3__AG)                       
/* Analog MUX bux enable */
#define SW_3_AMUX                   (* (reg8 *) SW_3__AMUX) 
/* Bidirectional Enable */                                                        
#define SW_3_BIE                    (* (reg8 *) SW_3__BIE)
/* Bit-mask for Aliased Register Access */
#define SW_3_BIT_MASK               (* (reg8 *) SW_3__BIT_MASK)
/* Bypass Enable */
#define SW_3_BYP                    (* (reg8 *) SW_3__BYP)
/* Port wide control signals */                                                   
#define SW_3_CTL                    (* (reg8 *) SW_3__CTL)
/* Drive Modes */
#define SW_3_DM0                    (* (reg8 *) SW_3__DM0) 
#define SW_3_DM1                    (* (reg8 *) SW_3__DM1)
#define SW_3_DM2                    (* (reg8 *) SW_3__DM2) 
/* Input Buffer Disable Override */
#define SW_3_INP_DIS                (* (reg8 *) SW_3__INP_DIS)
/* LCD Common or Segment Drive */
#define SW_3_LCD_COM_SEG            (* (reg8 *) SW_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define SW_3_LCD_EN                 (* (reg8 *) SW_3__LCD_EN)
/* Slew Rate Control */
#define SW_3_SLW                    (* (reg8 *) SW_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SW_3_PRTDSI__CAPS_SEL       (* (reg8 *) SW_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SW_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SW_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SW_3_PRTDSI__OE_SEL0        (* (reg8 *) SW_3__PRTDSI__OE_SEL0) 
#define SW_3_PRTDSI__OE_SEL1        (* (reg8 *) SW_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SW_3_PRTDSI__OUT_SEL0       (* (reg8 *) SW_3__PRTDSI__OUT_SEL0) 
#define SW_3_PRTDSI__OUT_SEL1       (* (reg8 *) SW_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SW_3_PRTDSI__SYNC_OUT       (* (reg8 *) SW_3__PRTDSI__SYNC_OUT) 


#if defined(SW_3__INTSTAT)  /* Interrupt Registers */

    #define SW_3_INTSTAT                (* (reg8 *) SW_3__INTSTAT)
    #define SW_3_SNAP                   (* (reg8 *) SW_3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins SW_3_H */


/* [] END OF FILE */
