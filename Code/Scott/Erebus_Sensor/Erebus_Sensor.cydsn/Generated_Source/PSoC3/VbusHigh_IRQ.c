/*******************************************************************************
* File Name: VbusHigh_IRQ.c  
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
#include <VbusHigh_IRQ.h>

#if !defined(VbusHigh_IRQ__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START VbusHigh_IRQ_intc` */

#include "USB_Access.h"
#include "project.h"

/* `#END` */


/*******************************************************************************
* Function Name: VbusHigh_IRQ_Start
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
void VbusHigh_IRQ_Start(void) 
{
    /* For all we know the interrupt is active. */
    VbusHigh_IRQ_Disable();

    /* Set the ISR to point to the VbusHigh_IRQ Interrupt. */
    VbusHigh_IRQ_SetVector(&VbusHigh_IRQ_Interrupt);

    /* Set the priority. */
    VbusHigh_IRQ_SetPriority((uint8)VbusHigh_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    VbusHigh_IRQ_Enable();
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_StartEx
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
void VbusHigh_IRQ_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    VbusHigh_IRQ_Disable();

    /* Set the ISR to point to the VbusHigh_IRQ Interrupt. */
    VbusHigh_IRQ_SetVector(address);

    /* Set the priority. */
    VbusHigh_IRQ_SetPriority((uint8)VbusHigh_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    VbusHigh_IRQ_Enable();
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_Stop
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
void VbusHigh_IRQ_Stop(void) 
{
    /* Disable this interrupt. */
    VbusHigh_IRQ_Disable();
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for VbusHigh_IRQ.
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
CY_ISR(VbusHigh_IRQ_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START VbusHigh_IRQ_Interrupt` */

    // Power has just been applied to the Vbus pin, so we enter USB communication mode

    uint8 buffer[BUFFER_LEN];
  
    VbusLow_IRQ_Start();
    USB_LED_Write(1);

    /* Start USBFS Operation with 5V operation */
    USBUART_Start(0u, USBUART_5V_OPERATION);
    
    /* Wait for Device to enumerate */
    while(!USBUART_GetConfiguration());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    USBUART_CDC_Init();

    /* Main Loop: */
    // This is an infinite loop because when power is removed from the Vbus pin,
    // an interrupt will be generated (of higher priority) that will force a software
    // reset and apply any new settings that have been added to EEPROM
    for(;;)
    {
        if(USBUART_DataIsReady() != 0u)               /* Check for input data from PC */
        {   
            count = USBUART_GetData(buffer);           /* Read received data and re-enable OUT endpoint */
            if(count != 0u)
            {
                while(USBUART_CDCIsReady() == 0u);    /* Wait till component is ready to send more data to the PC */ 
                USBUART_PutData(buffer, count);       /* Send data back to PC */
            }
        }  
        
        state = USBUART_IsLineChanged();              /* Check for Line settings changed */
    }   


    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (VbusHigh_IRQ__ES2_PATCH ))      
            VbusHigh_IRQ_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling VbusHigh_IRQ_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use VbusHigh_IRQ_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void VbusHigh_IRQ_SetVector(cyisraddress address) 
{
    CY_SET_REG16(VbusHigh_IRQ_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_GetVector
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
cyisraddress VbusHigh_IRQ_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(VbusHigh_IRQ_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling VbusHigh_IRQ_Start
*   or VbusHigh_IRQ_StartEx will override any effect this method would 
*   have had. This method should only be called after VbusHigh_IRQ_Start or 
*   VbusHigh_IRQ_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void VbusHigh_IRQ_SetPriority(uint8 priority) 
{
    *VbusHigh_IRQ_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_GetPriority
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
uint8 VbusHigh_IRQ_GetPriority(void) 
{
    uint8 priority;


    priority = *VbusHigh_IRQ_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_Enable
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
void VbusHigh_IRQ_Enable(void) 
{
    /* Enable the general interrupt. */
    *VbusHigh_IRQ_INTC_SET_EN = VbusHigh_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_GetState
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
uint8 VbusHigh_IRQ_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*VbusHigh_IRQ_INTC_SET_EN & (uint8)VbusHigh_IRQ__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_Disable
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
void VbusHigh_IRQ_Disable(void) 
{
    /* Disable the general interrupt. */
    *VbusHigh_IRQ_INTC_CLR_EN = VbusHigh_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_SetPending
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
void VbusHigh_IRQ_SetPending(void) 
{
    *VbusHigh_IRQ_INTC_SET_PD = VbusHigh_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: VbusHigh_IRQ_ClearPending
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
void VbusHigh_IRQ_ClearPending(void) 
{
    *VbusHigh_IRQ_INTC_CLR_PD = VbusHigh_IRQ__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
