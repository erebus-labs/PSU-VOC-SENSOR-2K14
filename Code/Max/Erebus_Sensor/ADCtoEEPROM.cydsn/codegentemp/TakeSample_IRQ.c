/*******************************************************************************
* File Name: TakeSample_IRQ.c  
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
#include <TakeSample_IRQ.h>

#if !defined(TakeSample_IRQ__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START TakeSample_IRQ_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: TakeSample_IRQ_Start
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
void TakeSample_IRQ_Start(void) 
{
    /* For all we know the interrupt is active. */
    TakeSample_IRQ_Disable();

    /* Set the ISR to point to the TakeSample_IRQ Interrupt. */
    TakeSample_IRQ_SetVector(&TakeSample_IRQ_Interrupt);

    /* Set the priority. */
    TakeSample_IRQ_SetPriority((uint8)TakeSample_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TakeSample_IRQ_Enable();
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_StartEx
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
void TakeSample_IRQ_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    TakeSample_IRQ_Disable();

    /* Set the ISR to point to the TakeSample_IRQ Interrupt. */
    TakeSample_IRQ_SetVector(address);

    /* Set the priority. */
    TakeSample_IRQ_SetPriority((uint8)TakeSample_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    TakeSample_IRQ_Enable();
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_Stop
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
void TakeSample_IRQ_Stop(void) 
{
    /* Disable this interrupt. */
    TakeSample_IRQ_Disable();
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for TakeSample_IRQ.
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
CY_ISR(TakeSample_IRQ_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START TakeSample_IRQ_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (TakeSample_IRQ__ES2_PATCH ))      
            TakeSample_IRQ_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling TakeSample_IRQ_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use TakeSample_IRQ_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void TakeSample_IRQ_SetVector(cyisraddress address) 
{
    CY_SET_REG16(TakeSample_IRQ_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_GetVector
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
cyisraddress TakeSample_IRQ_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(TakeSample_IRQ_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling TakeSample_IRQ_Start
*   or TakeSample_IRQ_StartEx will override any effect this method would 
*   have had. This method should only be called after TakeSample_IRQ_Start or 
*   TakeSample_IRQ_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void TakeSample_IRQ_SetPriority(uint8 priority) 
{
    *TakeSample_IRQ_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_GetPriority
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
uint8 TakeSample_IRQ_GetPriority(void) 
{
    uint8 priority;


    priority = *TakeSample_IRQ_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_Enable
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
void TakeSample_IRQ_Enable(void) 
{
    /* Enable the general interrupt. */
    *TakeSample_IRQ_INTC_SET_EN = TakeSample_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_GetState
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
uint8 TakeSample_IRQ_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*TakeSample_IRQ_INTC_SET_EN & (uint8)TakeSample_IRQ__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_Disable
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
void TakeSample_IRQ_Disable(void) 
{
    /* Disable the general interrupt. */
    *TakeSample_IRQ_INTC_CLR_EN = TakeSample_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_SetPending
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
void TakeSample_IRQ_SetPending(void) 
{
    *TakeSample_IRQ_INTC_SET_PD = TakeSample_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: TakeSample_IRQ_ClearPending
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
void TakeSample_IRQ_ClearPending(void) 
{
    *TakeSample_IRQ_INTC_CLR_PD = TakeSample_IRQ__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
