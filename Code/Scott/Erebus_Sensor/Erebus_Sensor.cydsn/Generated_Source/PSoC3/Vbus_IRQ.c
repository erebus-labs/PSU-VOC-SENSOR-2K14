/*******************************************************************************
* File Name: Vbus_IRQ.c  
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
#include <Vbus_IRQ.h>

#if !defined(Vbus_IRQ__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START Vbus_IRQ_intc` */
    #include "USBUART.h"
    #include "Blink_Timer.h"
    #include "Vbus.h"
/* `#END` */


/*******************************************************************************
* Function Name: Vbus_IRQ_Start
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
void Vbus_IRQ_Start(void) 
{
    /* For all we know the interrupt is active. */
    Vbus_IRQ_Disable();

    /* Set the ISR to point to the Vbus_IRQ Interrupt. */
    Vbus_IRQ_SetVector(&Vbus_IRQ_Interrupt);

    /* Set the priority. */
    Vbus_IRQ_SetPriority((uint8)Vbus_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Vbus_IRQ_Enable();
}


/*******************************************************************************
* Function Name: Vbus_IRQ_StartEx
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
void Vbus_IRQ_StartEx(cyisraddress address) 
{
    /* For all we know the interrupt is active. */
    Vbus_IRQ_Disable();

    /* Set the ISR to point to the Vbus_IRQ Interrupt. */
    Vbus_IRQ_SetVector(address);

    /* Set the priority. */
    Vbus_IRQ_SetPriority((uint8)Vbus_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    Vbus_IRQ_Enable();
}


/*******************************************************************************
* Function Name: Vbus_IRQ_Stop
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
void Vbus_IRQ_Stop(void) 
{
    /* Disable this interrupt. */
    Vbus_IRQ_Disable();
}


/*******************************************************************************
* Function Name: Vbus_IRQ_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for Vbus_IRQ.
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
CY_ISR(Vbus_IRQ_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START Vbus_IRQ_Interrupt` */
    while(1){
        
        char8 *parity[] = { "None", "Odd", "Even", "Mark", "Space" };
        char8 *stop[] = { "1", "1.5", "2" };


        uint16 count;
        uint8 buffer[BUFFER_LEN];
        char8 lineStr[20];
        uint8 state;
        
        /* Enable Global Interrupts */
        CyGlobalIntEnable;                        

        /* Start USBFS Operation with 3V operation */
        USBUART_1_Start(0u, USBUART_1_3V_OPERATION);

        /* Start LCD */
        LCD_Start();
        LCD_PrintString("USB-UART example");
        
        /* Wait for Device to enumerate */
        while(!USBUART_1_GetConfiguration());

        /* Enumeration is done, enable OUT endpoint for receive data from Host */
        USBUART_1_CDC_Init();

        /* Main Loop: */
        for(;;)
        {
            if(USBUART_1_DataIsReady() != 0u)               /* Check for input data from PC */
            {   
                count = USBUART_1_GetAll(buffer);           /* Read received data and re-enable OUT endpoint */
                if(count != 0u)
                {
                    while(USBUART_1_CDCIsReady() == 0u);    /* Wait till component is ready to send more data to the PC */ 
                    USBUART_1_PutData(buffer, count);       /* Send data back to PC */
                }
            }  
            
            state = USBUART_1_IsLineChanged();              /* Check for Line settings changed */
            if(state != 0u)
            {  
                if(state & USBUART_1_LINE_CODING_CHANGED)   /* Show new settings */
                {
                    sprintf(lineStr,"BR:%4ld,DB:%d",USBUART_1_GetDTERate(),(uint16)USBUART_1_GetDataBits());
                    LCD_Position(0u, 0u);
                    LCD_PrintString("                    ");
                    LCD_Position(0u, 0u);
                    LCD_PrintString(lineStr);
                    sprintf(lineStr,"SB:%s,Parity:%s", stop[(uint16)USBUART_1_GetCharFormat()], \
                                                         parity[(uint16)USBUART_1_GetParityType()]);
                    LCD_Position(1u, 0u);
                    LCD_PrintString("                    ");
                    LCD_Position(1u, 0u);
                    LCD_PrintString(lineStr);
                }
                if(state & USBUART_1_LINE_CONTROL_CHANGED)  /* Show new settings */
                {   
                    state = USBUART_1_GetLineControl();
                    sprintf(lineStr,"DTR:%s,RTS:%s",  (state & USBUART_1_LINE_CONTROL_DTR) ? "ON" : "OFF", \
                                                        (state & USBUART_1_LINE_CONTROL_RTS) ? "ON" : "OFF");
                    LCD_Position(1u, 0u);
                    LCD_PrintString("                    ");
                    LCD_Position(1u, 0u);
                    LCD_PrintString(lineStr);
                
                }
            }
        }   
    }


    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (Vbus_IRQ__ES2_PATCH ))      
            Vbus_IRQ_ISR_PATCH();
        #endif /* CYDEV_CHIP_REVISION_USED */
    #endif /* (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */
}


/*******************************************************************************
* Function Name: Vbus_IRQ_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling Vbus_IRQ_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use Vbus_IRQ_StartEx instead.
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void Vbus_IRQ_SetVector(cyisraddress address) 
{
    CY_SET_REG16(Vbus_IRQ_INTC_VECTOR, (uint16) address);
}


/*******************************************************************************
* Function Name: Vbus_IRQ_GetVector
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
cyisraddress Vbus_IRQ_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(Vbus_IRQ_INTC_VECTOR);
}


/*******************************************************************************
* Function Name: Vbus_IRQ_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. Note calling Vbus_IRQ_Start
*   or Vbus_IRQ_StartEx will override any effect this method would 
*   have had. This method should only be called after Vbus_IRQ_Start or 
*   Vbus_IRQ_StartEx has been called. To set the initial
*   priority for the component use the cydwr file in the tool.
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
* Return:
*   None
*
*******************************************************************************/
void Vbus_IRQ_SetPriority(uint8 priority) 
{
    *Vbus_IRQ_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: Vbus_IRQ_GetPriority
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
uint8 Vbus_IRQ_GetPriority(void) 
{
    uint8 priority;


    priority = *Vbus_IRQ_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: Vbus_IRQ_Enable
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
void Vbus_IRQ_Enable(void) 
{
    /* Enable the general interrupt. */
    *Vbus_IRQ_INTC_SET_EN = Vbus_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: Vbus_IRQ_GetState
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
uint8 Vbus_IRQ_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return ((*Vbus_IRQ_INTC_SET_EN & (uint8)Vbus_IRQ__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: Vbus_IRQ_Disable
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
void Vbus_IRQ_Disable(void) 
{
    /* Disable the general interrupt. */
    *Vbus_IRQ_INTC_CLR_EN = Vbus_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: Vbus_IRQ_SetPending
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
void Vbus_IRQ_SetPending(void) 
{
    *Vbus_IRQ_INTC_SET_PD = Vbus_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: Vbus_IRQ_ClearPending
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
void Vbus_IRQ_ClearPending(void) 
{
    *Vbus_IRQ_INTC_CLR_PD = Vbus_IRQ__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
