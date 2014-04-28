/*******************************************************************************
* File Name: ButtonISR.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include <CyLib.h>
#include <ButtonISR.h>

#if !defined(ButtonISR__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ButtonISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: ButtonISR_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_Start(void) 
{
    /* For all we know the interrupt is active. */
    ButtonISR_Disable();

    /* Set the ISR to point to the ButtonISR Interrupt. */
    ButtonISR_SetVector(&ButtonISR_Interrupt);

    /* Set the priority. */
    ButtonISR_SetPriority((uint8)ButtonISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ButtonISR_Enable();
}


/*******************************************************************************
* Function Name: ButtonISR_StartEx
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    ButtonISR_Disable();

    /* Set the ISR to point to the ButtonISR Interrupt. */
    ButtonISR_SetVector(address);

    /* Set the priority. */
    ButtonISR_SetPriority((uint8)ButtonISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ButtonISR_Enable();
}


/*******************************************************************************
* Function Name: ButtonISR_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_Stop(void) 
{
    /* Disable this interrupt. */
    ButtonISR_Disable();
}


/*******************************************************************************
* Function Name: ButtonISR_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for ButtonISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(ButtonISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ButtonISR_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (ButtonISR__ES2_PATCH ))      
            ButtonISR_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: ButtonISR_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ButtonISR_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use ButtonISR_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_SetVector(cyisraddress address) 
{
    CY_SET_REG16(ButtonISR_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: ButtonISR_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress ButtonISR_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(ButtonISR_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: ButtonISR_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling ButtonISR_Start
*   or ButtonISR_StartEx will override any effect this method would 
*   have had. This method should only be called after ButtonISR_Start or 
*   ButtonISR_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_SetPriority(uint8 priority) 
{
    *ButtonISR_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: ButtonISR_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*******************************************************************************/
uint8 ButtonISR_GetPriority(void) 
{
    uint8 priority;


    priority = *ButtonISR_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: ButtonISR_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_Enable(void) 
{
    /* Enable the general interrupt. */
    *ButtonISR_INTC_SET_EN = ButtonISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: ButtonISR_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 ButtonISR_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*ButtonISR_INTC_SET_EN & (uint8)ButtonISR__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: ButtonISR_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_Disable(void) 
{
    /* Disable the general interrupt. */
    *ButtonISR_INTC_CLR_EN = ButtonISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: ButtonISR_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_SetPending(void) 
{
    *ButtonISR_INTC_SET_PD = ButtonISR__INTC_MASK;
}


/*******************************************************************************
* Function Name: ButtonISR_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ButtonISR_ClearPending(void) 
{
    *ButtonISR_INTC_CLR_PD = ButtonISR__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
