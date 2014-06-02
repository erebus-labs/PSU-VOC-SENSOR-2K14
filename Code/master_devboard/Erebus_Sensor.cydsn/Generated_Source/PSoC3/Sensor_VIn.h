/*******************************************************************************
* File Name: Sensor_VIn.h  
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

#if !defined(CY_PINS_Sensor_VIn_H) /* Pins Sensor_VIn_H */
#define CY_PINS_Sensor_VIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sensor_VIn_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Sensor_VIn_Write(uint8 value) ;
void    Sensor_VIn_SetDriveMode(uint8 mode) ;
uint8   Sensor_VIn_ReadDataReg(void) ;
uint8   Sensor_VIn_Read(void) ;
uint8   Sensor_VIn_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Sensor_VIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Sensor_VIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Sensor_VIn_DM_RES_UP          PIN_DM_RES_UP
#define Sensor_VIn_DM_RES_DWN         PIN_DM_RES_DWN
#define Sensor_VIn_DM_OD_LO           PIN_DM_OD_LO
#define Sensor_VIn_DM_OD_HI           PIN_DM_OD_HI
#define Sensor_VIn_DM_STRONG          PIN_DM_STRONG
#define Sensor_VIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Sensor_VIn_MASK               Sensor_VIn__MASK
#define Sensor_VIn_SHIFT              Sensor_VIn__SHIFT
#define Sensor_VIn_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sensor_VIn_PS                     (* (reg8 *) Sensor_VIn__PS)
/* Data Register */
#define Sensor_VIn_DR                     (* (reg8 *) Sensor_VIn__DR)
/* Port Number */
#define Sensor_VIn_PRT_NUM                (* (reg8 *) Sensor_VIn__PRT) 
/* Connect to Analog Globals */                                                  
#define Sensor_VIn_AG                     (* (reg8 *) Sensor_VIn__AG)                       
/* Analog MUX bux enable */
#define Sensor_VIn_AMUX                   (* (reg8 *) Sensor_VIn__AMUX) 
/* Bidirectional Enable */                                                        
#define Sensor_VIn_BIE                    (* (reg8 *) Sensor_VIn__BIE)
/* Bit-mask for Aliased Register Access */
#define Sensor_VIn_BIT_MASK               (* (reg8 *) Sensor_VIn__BIT_MASK)
/* Bypass Enable */
#define Sensor_VIn_BYP                    (* (reg8 *) Sensor_VIn__BYP)
/* Port wide control signals */                                                   
#define Sensor_VIn_CTL                    (* (reg8 *) Sensor_VIn__CTL)
/* Drive Modes */
#define Sensor_VIn_DM0                    (* (reg8 *) Sensor_VIn__DM0) 
#define Sensor_VIn_DM1                    (* (reg8 *) Sensor_VIn__DM1)
#define Sensor_VIn_DM2                    (* (reg8 *) Sensor_VIn__DM2) 
/* Input Buffer Disable Override */
#define Sensor_VIn_INP_DIS                (* (reg8 *) Sensor_VIn__INP_DIS)
/* LCD Common or Segment Drive */
#define Sensor_VIn_LCD_COM_SEG            (* (reg8 *) Sensor_VIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sensor_VIn_LCD_EN                 (* (reg8 *) Sensor_VIn__LCD_EN)
/* Slew Rate Control */
#define Sensor_VIn_SLW                    (* (reg8 *) Sensor_VIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sensor_VIn_PRTDSI__CAPS_SEL       (* (reg8 *) Sensor_VIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sensor_VIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sensor_VIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sensor_VIn_PRTDSI__OE_SEL0        (* (reg8 *) Sensor_VIn__PRTDSI__OE_SEL0) 
#define Sensor_VIn_PRTDSI__OE_SEL1        (* (reg8 *) Sensor_VIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sensor_VIn_PRTDSI__OUT_SEL0       (* (reg8 *) Sensor_VIn__PRTDSI__OUT_SEL0) 
#define Sensor_VIn_PRTDSI__OUT_SEL1       (* (reg8 *) Sensor_VIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sensor_VIn_PRTDSI__SYNC_OUT       (* (reg8 *) Sensor_VIn__PRTDSI__SYNC_OUT) 


#if defined(Sensor_VIn__INTSTAT)  /* Interrupt Registers */

    #define Sensor_VIn_INTSTAT                (* (reg8 *) Sensor_VIn__INTSTAT)
    #define Sensor_VIn_SNAP                   (* (reg8 *) Sensor_VIn__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Sensor_VIn_H */


/* [] END OF FILE */
