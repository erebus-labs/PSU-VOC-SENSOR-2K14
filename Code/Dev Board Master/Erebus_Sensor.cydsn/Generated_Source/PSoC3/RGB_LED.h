/*******************************************************************************
* File Name: RGB_LED.h  
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

#if !defined(CY_PINS_RGB_LED_H) /* Pins RGB_LED_H */
#define CY_PINS_RGB_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RGB_LED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RGB_LED_Write(uint8 value) ;
void    RGB_LED_SetDriveMode(uint8 mode) ;
uint8   RGB_LED_ReadDataReg(void) ;
uint8   RGB_LED_Read(void) ;
uint8   RGB_LED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RGB_LED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define RGB_LED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define RGB_LED_DM_RES_UP          PIN_DM_RES_UP
#define RGB_LED_DM_RES_DWN         PIN_DM_RES_DWN
#define RGB_LED_DM_OD_LO           PIN_DM_OD_LO
#define RGB_LED_DM_OD_HI           PIN_DM_OD_HI
#define RGB_LED_DM_STRONG          PIN_DM_STRONG
#define RGB_LED_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define RGB_LED_MASK               RGB_LED__MASK
#define RGB_LED_SHIFT              RGB_LED__SHIFT
#define RGB_LED_WIDTH              3u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RGB_LED_PS                     (* (reg8 *) RGB_LED__PS)
/* Data Register */
#define RGB_LED_DR                     (* (reg8 *) RGB_LED__DR)
/* Port Number */
#define RGB_LED_PRT_NUM                (* (reg8 *) RGB_LED__PRT) 
/* Connect to Analog Globals */                                                  
#define RGB_LED_AG                     (* (reg8 *) RGB_LED__AG)                       
/* Analog MUX bux enable */
#define RGB_LED_AMUX                   (* (reg8 *) RGB_LED__AMUX) 
/* Bidirectional Enable */                                                        
#define RGB_LED_BIE                    (* (reg8 *) RGB_LED__BIE)
/* Bit-mask for Aliased Register Access */
#define RGB_LED_BIT_MASK               (* (reg8 *) RGB_LED__BIT_MASK)
/* Bypass Enable */
#define RGB_LED_BYP                    (* (reg8 *) RGB_LED__BYP)
/* Port wide control signals */                                                   
#define RGB_LED_CTL                    (* (reg8 *) RGB_LED__CTL)
/* Drive Modes */
#define RGB_LED_DM0                    (* (reg8 *) RGB_LED__DM0) 
#define RGB_LED_DM1                    (* (reg8 *) RGB_LED__DM1)
#define RGB_LED_DM2                    (* (reg8 *) RGB_LED__DM2) 
/* Input Buffer Disable Override */
#define RGB_LED_INP_DIS                (* (reg8 *) RGB_LED__INP_DIS)
/* LCD Common or Segment Drive */
#define RGB_LED_LCD_COM_SEG            (* (reg8 *) RGB_LED__LCD_COM_SEG)
/* Enable Segment LCD */
#define RGB_LED_LCD_EN                 (* (reg8 *) RGB_LED__LCD_EN)
/* Slew Rate Control */
#define RGB_LED_SLW                    (* (reg8 *) RGB_LED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RGB_LED_PRTDSI__CAPS_SEL       (* (reg8 *) RGB_LED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RGB_LED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RGB_LED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RGB_LED_PRTDSI__OE_SEL0        (* (reg8 *) RGB_LED__PRTDSI__OE_SEL0) 
#define RGB_LED_PRTDSI__OE_SEL1        (* (reg8 *) RGB_LED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RGB_LED_PRTDSI__OUT_SEL0       (* (reg8 *) RGB_LED__PRTDSI__OUT_SEL0) 
#define RGB_LED_PRTDSI__OUT_SEL1       (* (reg8 *) RGB_LED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RGB_LED_PRTDSI__SYNC_OUT       (* (reg8 *) RGB_LED__PRTDSI__SYNC_OUT) 


#if defined(RGB_LED__INTSTAT)  /* Interrupt Registers */

    #define RGB_LED_INTSTAT                (* (reg8 *) RGB_LED__INTSTAT)
    #define RGB_LED_SNAP                   (* (reg8 *) RGB_LED__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins RGB_LED_H */


/* [] END OF FILE */
