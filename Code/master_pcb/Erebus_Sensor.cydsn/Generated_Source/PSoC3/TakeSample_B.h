/*******************************************************************************
* File Name: TakeSample_B.h  
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

#if !defined(CY_PINS_TakeSample_B_H) /* Pins TakeSample_B_H */
#define CY_PINS_TakeSample_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TakeSample_B_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TakeSample_B_Write(uint8 value) ;
void    TakeSample_B_SetDriveMode(uint8 mode) ;
uint8   TakeSample_B_ReadDataReg(void) ;
uint8   TakeSample_B_Read(void) ;
uint8   TakeSample_B_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TakeSample_B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define TakeSample_B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define TakeSample_B_DM_RES_UP          PIN_DM_RES_UP
#define TakeSample_B_DM_RES_DWN         PIN_DM_RES_DWN
#define TakeSample_B_DM_OD_LO           PIN_DM_OD_LO
#define TakeSample_B_DM_OD_HI           PIN_DM_OD_HI
#define TakeSample_B_DM_STRONG          PIN_DM_STRONG
#define TakeSample_B_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define TakeSample_B_MASK               TakeSample_B__MASK
#define TakeSample_B_SHIFT              TakeSample_B__SHIFT
#define TakeSample_B_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TakeSample_B_PS                     (* (reg8 *) TakeSample_B__PS)
/* Data Register */
#define TakeSample_B_DR                     (* (reg8 *) TakeSample_B__DR)
/* Port Number */
#define TakeSample_B_PRT_NUM                (* (reg8 *) TakeSample_B__PRT) 
/* Connect to Analog Globals */                                                  
#define TakeSample_B_AG                     (* (reg8 *) TakeSample_B__AG)                       
/* Analog MUX bux enable */
#define TakeSample_B_AMUX                   (* (reg8 *) TakeSample_B__AMUX) 
/* Bidirectional Enable */                                                        
#define TakeSample_B_BIE                    (* (reg8 *) TakeSample_B__BIE)
/* Bit-mask for Aliased Register Access */
#define TakeSample_B_BIT_MASK               (* (reg8 *) TakeSample_B__BIT_MASK)
/* Bypass Enable */
#define TakeSample_B_BYP                    (* (reg8 *) TakeSample_B__BYP)
/* Port wide control signals */                                                   
#define TakeSample_B_CTL                    (* (reg8 *) TakeSample_B__CTL)
/* Drive Modes */
#define TakeSample_B_DM0                    (* (reg8 *) TakeSample_B__DM0) 
#define TakeSample_B_DM1                    (* (reg8 *) TakeSample_B__DM1)
#define TakeSample_B_DM2                    (* (reg8 *) TakeSample_B__DM2) 
/* Input Buffer Disable Override */
#define TakeSample_B_INP_DIS                (* (reg8 *) TakeSample_B__INP_DIS)
/* LCD Common or Segment Drive */
#define TakeSample_B_LCD_COM_SEG            (* (reg8 *) TakeSample_B__LCD_COM_SEG)
/* Enable Segment LCD */
#define TakeSample_B_LCD_EN                 (* (reg8 *) TakeSample_B__LCD_EN)
/* Slew Rate Control */
#define TakeSample_B_SLW                    (* (reg8 *) TakeSample_B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TakeSample_B_PRTDSI__CAPS_SEL       (* (reg8 *) TakeSample_B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TakeSample_B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TakeSample_B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TakeSample_B_PRTDSI__OE_SEL0        (* (reg8 *) TakeSample_B__PRTDSI__OE_SEL0) 
#define TakeSample_B_PRTDSI__OE_SEL1        (* (reg8 *) TakeSample_B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TakeSample_B_PRTDSI__OUT_SEL0       (* (reg8 *) TakeSample_B__PRTDSI__OUT_SEL0) 
#define TakeSample_B_PRTDSI__OUT_SEL1       (* (reg8 *) TakeSample_B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TakeSample_B_PRTDSI__SYNC_OUT       (* (reg8 *) TakeSample_B__PRTDSI__SYNC_OUT) 


#if defined(TakeSample_B__INTSTAT)  /* Interrupt Registers */

    #define TakeSample_B_INTSTAT                (* (reg8 *) TakeSample_B__INTSTAT)
    #define TakeSample_B_SNAP                   (* (reg8 *) TakeSample_B__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins TakeSample_B_H */


/* [] END OF FILE */
