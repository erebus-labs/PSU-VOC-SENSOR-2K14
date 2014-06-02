/*******************************************************************************
* File Name: Sample.h  
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

#if !defined(CY_PINS_Sample_H) /* Pins Sample_H */
#define CY_PINS_Sample_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sample_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Sample_Write(uint8 value) ;
void    Sample_SetDriveMode(uint8 mode) ;
uint8   Sample_ReadDataReg(void) ;
uint8   Sample_Read(void) ;
uint8   Sample_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Sample_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Sample_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Sample_DM_RES_UP          PIN_DM_RES_UP
#define Sample_DM_RES_DWN         PIN_DM_RES_DWN
#define Sample_DM_OD_LO           PIN_DM_OD_LO
#define Sample_DM_OD_HI           PIN_DM_OD_HI
#define Sample_DM_STRONG          PIN_DM_STRONG
#define Sample_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Sample_MASK               Sample__MASK
#define Sample_SHIFT              Sample__SHIFT
#define Sample_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sample_PS                     (* (reg8 *) Sample__PS)
/* Data Register */
#define Sample_DR                     (* (reg8 *) Sample__DR)
/* Port Number */
#define Sample_PRT_NUM                (* (reg8 *) Sample__PRT) 
/* Connect to Analog Globals */                                                  
#define Sample_AG                     (* (reg8 *) Sample__AG)                       
/* Analog MUX bux enable */
#define Sample_AMUX                   (* (reg8 *) Sample__AMUX) 
/* Bidirectional Enable */                                                        
#define Sample_BIE                    (* (reg8 *) Sample__BIE)
/* Bit-mask for Aliased Register Access */
#define Sample_BIT_MASK               (* (reg8 *) Sample__BIT_MASK)
/* Bypass Enable */
#define Sample_BYP                    (* (reg8 *) Sample__BYP)
/* Port wide control signals */                                                   
#define Sample_CTL                    (* (reg8 *) Sample__CTL)
/* Drive Modes */
#define Sample_DM0                    (* (reg8 *) Sample__DM0) 
#define Sample_DM1                    (* (reg8 *) Sample__DM1)
#define Sample_DM2                    (* (reg8 *) Sample__DM2) 
/* Input Buffer Disable Override */
#define Sample_INP_DIS                (* (reg8 *) Sample__INP_DIS)
/* LCD Common or Segment Drive */
#define Sample_LCD_COM_SEG            (* (reg8 *) Sample__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sample_LCD_EN                 (* (reg8 *) Sample__LCD_EN)
/* Slew Rate Control */
#define Sample_SLW                    (* (reg8 *) Sample__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sample_PRTDSI__CAPS_SEL       (* (reg8 *) Sample__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sample_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sample__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sample_PRTDSI__OE_SEL0        (* (reg8 *) Sample__PRTDSI__OE_SEL0) 
#define Sample_PRTDSI__OE_SEL1        (* (reg8 *) Sample__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sample_PRTDSI__OUT_SEL0       (* (reg8 *) Sample__PRTDSI__OUT_SEL0) 
#define Sample_PRTDSI__OUT_SEL1       (* (reg8 *) Sample__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sample_PRTDSI__SYNC_OUT       (* (reg8 *) Sample__PRTDSI__SYNC_OUT) 


#if defined(Sample__INTSTAT)  /* Interrupt Registers */

    #define Sample_INTSTAT                (* (reg8 *) Sample__INTSTAT)
    #define Sample_SNAP                   (* (reg8 *) Sample__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Sample_H */


/* [] END OF FILE */
