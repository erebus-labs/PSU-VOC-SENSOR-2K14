/*******************************************************************************
* File Name: StopCollection_B.h  
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

#if !defined(CY_PINS_StopCollection_B_H) /* Pins StopCollection_B_H */
#define CY_PINS_StopCollection_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "StopCollection_B_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    StopCollection_B_Write(uint8 value) ;
void    StopCollection_B_SetDriveMode(uint8 mode) ;
uint8   StopCollection_B_ReadDataReg(void) ;
uint8   StopCollection_B_Read(void) ;
uint8   StopCollection_B_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define StopCollection_B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define StopCollection_B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define StopCollection_B_DM_RES_UP          PIN_DM_RES_UP
#define StopCollection_B_DM_RES_DWN         PIN_DM_RES_DWN
#define StopCollection_B_DM_OD_LO           PIN_DM_OD_LO
#define StopCollection_B_DM_OD_HI           PIN_DM_OD_HI
#define StopCollection_B_DM_STRONG          PIN_DM_STRONG
#define StopCollection_B_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define StopCollection_B_MASK               StopCollection_B__MASK
#define StopCollection_B_SHIFT              StopCollection_B__SHIFT
#define StopCollection_B_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define StopCollection_B_PS                     (* (reg8 *) StopCollection_B__PS)
/* Data Register */
#define StopCollection_B_DR                     (* (reg8 *) StopCollection_B__DR)
/* Port Number */
#define StopCollection_B_PRT_NUM                (* (reg8 *) StopCollection_B__PRT) 
/* Connect to Analog Globals */                                                  
#define StopCollection_B_AG                     (* (reg8 *) StopCollection_B__AG)                       
/* Analog MUX bux enable */
#define StopCollection_B_AMUX                   (* (reg8 *) StopCollection_B__AMUX) 
/* Bidirectional Enable */                                                        
#define StopCollection_B_BIE                    (* (reg8 *) StopCollection_B__BIE)
/* Bit-mask for Aliased Register Access */
#define StopCollection_B_BIT_MASK               (* (reg8 *) StopCollection_B__BIT_MASK)
/* Bypass Enable */
#define StopCollection_B_BYP                    (* (reg8 *) StopCollection_B__BYP)
/* Port wide control signals */                                                   
#define StopCollection_B_CTL                    (* (reg8 *) StopCollection_B__CTL)
/* Drive Modes */
#define StopCollection_B_DM0                    (* (reg8 *) StopCollection_B__DM0) 
#define StopCollection_B_DM1                    (* (reg8 *) StopCollection_B__DM1)
#define StopCollection_B_DM2                    (* (reg8 *) StopCollection_B__DM2) 
/* Input Buffer Disable Override */
#define StopCollection_B_INP_DIS                (* (reg8 *) StopCollection_B__INP_DIS)
/* LCD Common or Segment Drive */
#define StopCollection_B_LCD_COM_SEG            (* (reg8 *) StopCollection_B__LCD_COM_SEG)
/* Enable Segment LCD */
#define StopCollection_B_LCD_EN                 (* (reg8 *) StopCollection_B__LCD_EN)
/* Slew Rate Control */
#define StopCollection_B_SLW                    (* (reg8 *) StopCollection_B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define StopCollection_B_PRTDSI__CAPS_SEL       (* (reg8 *) StopCollection_B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define StopCollection_B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) StopCollection_B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define StopCollection_B_PRTDSI__OE_SEL0        (* (reg8 *) StopCollection_B__PRTDSI__OE_SEL0) 
#define StopCollection_B_PRTDSI__OE_SEL1        (* (reg8 *) StopCollection_B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define StopCollection_B_PRTDSI__OUT_SEL0       (* (reg8 *) StopCollection_B__PRTDSI__OUT_SEL0) 
#define StopCollection_B_PRTDSI__OUT_SEL1       (* (reg8 *) StopCollection_B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define StopCollection_B_PRTDSI__SYNC_OUT       (* (reg8 *) StopCollection_B__PRTDSI__SYNC_OUT) 


#if defined(StopCollection_B__INTSTAT)  /* Interrupt Registers */

    #define StopCollection_B_INTSTAT                (* (reg8 *) StopCollection_B__INTSTAT)
    #define StopCollection_B_SNAP                   (* (reg8 *) StopCollection_B__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins StopCollection_B_H */


/* [] END OF FILE */
