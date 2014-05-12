/*******************************************************************************
* File Name: StartCollection_IRQ.c  
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
#include <StartCollection_IRQ.h>

#if !defined(StartCollection_IRQ__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START StartCollection_IRQ_intc` */
    #include "Interface.h"
    #include "Globals.h"
    #include "Macros.h"
/* `#END` */


/*******************************************************************************
* Function Name: StartCollection_IRQ_Start
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
void StartCollection_IRQ_Start(void) 
{
    /* For all we know the interrupt is active. */
    StartCollection_IRQ_Disable();

    /* Set the ISR to point to the StartCollection_IRQ Interrupt. */
    StartCollection_IRQ_SetVector(&StartCollection_IRQ_Interrupt);

    /* Set the priority. */
    StartCollection_IRQ_SetPriority((uint8)StartCollection_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    StartCollection_IRQ_Enable();
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_StartEx
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
void StartCollection_IRQ_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    StartCollection_IRQ_Disable();

    /* Set the ISR to point to the StartCollection_IRQ Interrupt. */
    StartCollection_IRQ_SetVector(address);

    /* Set the priority. */
    StartCollection_IRQ_SetPriority((uint8)StartCollection_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    StartCollection_IRQ_Enable();
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_Stop
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
void StartCollection_IRQ_Stop(void) 
{
    /* Disable this interrupt. */
    StartCollection_IRQ_Disable();
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for StartCollection_IRQ.
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
CY_ISR(StartCollection_IRQ_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START StartCollection_IRQ_Interrupt` */

    DataStart_waiting = 1;
    
    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (StartCollection_IRQ__ES2_PATCH ))      
            StartCollection_IRQ_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling StartCollection_IRQ_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use StartCollection_IRQ_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void StartCollection_IRQ_SetVector(cyisraddress address) 
{
    CY_SET_REG16(StartCollection_IRQ_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_GetVector
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
cyisraddress StartCollection_IRQ_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(StartCollection_IRQ_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling StartCollection_IRQ_Start
*   or StartCollection_IRQ_StartEx will override any effect this method would 
*   have had. This method should only be called after StartCollection_IRQ_Start or 
*   StartCollection_IRQ_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void StartCollection_IRQ_SetPriority(uint8 priority) 
{
    *StartCollection_IRQ_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_GetPriority
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
uint8 StartCollection_IRQ_GetPriority(void) 
{
    uint8 priority;


    priority = *StartCollection_IRQ_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_Enable
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
void StartCollection_IRQ_Enable(void) 
{
    /* Enable the general interrupt. */
    *StartCollection_IRQ_INTC_SET_EN = StartCollection_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_GetState
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
uint8 StartCollection_IRQ_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*StartCollection_IRQ_INTC_SET_EN & (uint8)StartCollection_IRQ__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_Disable
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
void StartCollection_IRQ_Disable(void) 
{
    /* Disable the general interrupt. */
    *StartCollection_IRQ_INTC_CLR_EN = StartCollection_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_SetPending
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
void StartCollection_IRQ_SetPending(void) 
{
    *StartCollection_IRQ_INTC_SET_PD = StartCollection_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: StartCollection_IRQ_ClearPending
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
void StartCollection_IRQ_ClearPending(void) 
{
    *StartCollection_IRQ_INTC_CLR_PD = StartCollection_IRQ__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
