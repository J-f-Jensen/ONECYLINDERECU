/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       SCI.c
\brief      Serial Communication Interface functions
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.1
\date       19/02/2008
*/
/*******************************************************************************/
/*                                                                             */
/* All software, source code, included documentation, and any implied know-how */
/* are property of Freescale Semiconductor and therefore considered            */ 
/* CONFIDENTIAL INFORMATION.                                                   */
/*                                                                             */
/* This confidential information is disclosed FOR DEMONSTRATION PURPOSES ONLY. */
/*                                                                             */
/* All Confidential Information remains the property of Freescale Semiconductor*/
/* and will not be copied or reproduced without the express written permission */
/* of the Discloser, except for copies that are absolutely necessary in order  */
/* to fulfill the Purpose.                                                     */
/*                                                                             */
/* Services performed by FREESCALE in this matter are performed AS IS and      */
/* without any warranty. CUSTOMER retains the final decision relative to the   */
/* total design and functionality of the end product.                          */
/*                                                                             */
/* FREESCALE neither guarantees nor will be held liable by CUSTOMER for the    */
/* success of this project.                                                    */
/*                                                                             */
/* FREESCALE disclaims all warranties, express, implied or statutory including,*/
/* but not limited to, implied warranty of merchantability or fitness for a    */
/* particular purpose on any hardware, software ore advise supplied to the     */
/* project by FREESCALE, and or any product resulting from FREESCALE services. */
/*                                                                             */
/* In no event shall FREESCALE be liable for incidental or consequential       */
/* damages arising out of this agreement. CUSTOMER agrees to hold FREESCALE    */
/* harmless against any and all claims demands or actions by anyone on account */
/* of any damage,or injury, whether commercial, contractual, or tortuous,      */
/* rising directly or indirectly as a result of the advise or assistance       */
/* supplied CUSTOMER in connectionwith product, services or goods supplied     */
/* under this Agreement.                                                       */
/*                                                                             */
/*******************************************************************************/

/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/* SCI routines prototypes */ 
#include "SCI.h"
/** Variable types and common definitions */
#include "typedefs.h"
/** Application definitions */
#include "Application Definitions.h" 
/*******************************************************************************/
/* Global SCI communication status */
UINT8 u8SCI_Comm_Status;
/* Reception array */
UINT8 u8SCI_RxData[SCI_RX_MAX_SIZE];
/* Length of received frame */
UINT8 u8SCI_RxLength;
/* Pointer to current location on Reception array */
UINT8 *pu8SCI_Receive_Data_ptr;
/* Pointer to actual location being read from the input buffer */
UINT8 *pu8SCI_Read_Receive_Data_ptr;
/* Transmision array */
UINT8 u8SCI_TxData[SCI_TX_MAX_SIZE];
/* Length of received frame */
UINT8 u8SCI_TxLength;
/* Pointer to actual location being read from the output buffer */
UINT8 *pu8SCI_Read_Transmit_Data_ptr;


//Not converted for S12P yet
#if HARDWARE == (EMULATOR | PROTOTYPE)

/*******************************************************************************/
/**
* \brief    SCI initialization
* \author   Abraham Tezmol
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   void
*/

void vfnSCI_Init(UINT8 u8SCIPort)
{
    switch(u8SCIPort)
    {
        case (SCI_Port_0):                    
            SCI0BD = SCIBaudRate;
            SCI0CR1 = 0x00;
            SCI0CR2 = 0x2C;
            /*       0b00101100
                       ||||||||____ SendBrakeBit
                       |||||||_____ Receiver Wakeup bit
                       ||||||______ Receiver Enable bit
                       |||||_______ Transmiter Enable Bit
                       ||||________ Idle Line Interrupt Enable Bit
                       |||_________ Receiver full interrupt enable bit
                       ||__________ Transmission complete interrupt enable bit
                       |___________ Transmitter Interrupt Enable Bit
            */
            /* Reset auxiliary variables for input buffer management */
            vfnSER_ClearRx(SCI_Port_0);
            pu8SCI_Read_Transmit_Data_ptr = &u8SCI_TxData[0];
            u8SCI_Comm_Status = SCI_COMM_OK;
            break;
       default:
            u8SCI_Comm_Status = SCI_COMM_PORT_ERROR;
            break;     
    }       
}

/*******************************************************************************/
/**
* \brief    Read 1 data byte from input buffer. 
* \author   Abraham Tezmol
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   UINT8 - read byte from input buffer.
*/
UINT8 u8SCI_ReadRx(UINT8 u8SCIPort)
{       
    switch(u8SCIPort)
    {
        case (SCI_Port_0):
        	u8SCI_RxLength--;
            return(*pu8SCI_Read_Receive_Data_ptr++);
            break;
        default:
            u8SCI_Comm_Status = SCI_COMM_PORT_ERROR;
            return (0); 
            break;
    }            
}

/*******************************************************************************/
/**
* \brief    SCI Low-Level Tramsmit Function
* \author   Abraham Tezmol
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
            UINT8 u8TxDataByte - Data byte to be transmitted
* \return   void
*/
void vfnSCI_WriteTx(UINT8 u8SCIPort, UINT8 u8TxDataByte)
{
    switch(u8SCIPort)
    {
        case (SCI_Port_0):
            if (SCI0SR1_TDRE == 1)
            {
                SCI0DRL = (UINT8)u8TxDataByte;
            }
            else
            {
                u8SCI_Comm_Status = SCI_COMM_TX_BUSY;
            }    
            break;
        default:
            u8SCI_Comm_Status = SCI_COMM_PORT_ERROR;
            break;    
    }
}   

/*******************************************************************************/
/**
* \brief    Poll for new data flag on SCI input buffer
* \author   Abraham Tezmol
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   UINT8 - Number of bytes in the reception buffer
*/
UINT8 u8SCI_CheckRx(UINT8 u8SCIPort)
{
    switch(u8SCIPort)
    {
        case (SCI_Port_0):
            return(u8SCI_RxLength);
            break;
        default:
            u8SCI_Comm_Status = SCI_COMM_PORT_ERROR;
            return (0); 
            break;    
    }            
}

/*******************************************************************************/
/**
* \brief    Discard any incomming data on SCI receive buffer
* \author   Abraham Tezmol
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   void
*/
void vfnSER_ClearRx(UINT8 u8SCIPort)
{   
    switch(u8SCIPort)
    {
        case (SCI_Port_0):
            pu8SCI_Receive_Data_ptr = &u8SCI_RxData[0];
            pu8SCI_Read_Receive_Data_ptr = pu8SCI_Receive_Data_ptr;
            u8SCI_RxLength = 0;
            break;
        default:
            u8SCI_Comm_Status = SCI_COMM_PORT_ERROR;
            break;
    }    
}

/*******************************************************************************/
/**
* \brief    ISR, read byte into input data buffer
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt SCI_Receive_Isr(void)
{
	if (SCI0SR1_RDRF == 1)
    {
        if (SCI0SR1_OR == CLEAR)
        {
            *pu8SCI_Receive_Data_ptr = SCI0DRL;		/* Copy data from input buffer */
            u8SCI_RxLength++;					    /* Update input data bytes counter */
            pu8SCI_Receive_Data_ptr++;              /* Update input buffer pointer */
        }
        else
        {
            u8SCI_Comm_Status = SCI_COMM_RX_OVERRUN;
        }
    }
}
#pragma CODE_SEG DEFAULT


/*******************************************************************************/
/**
* \brief    Read incomming data on SCI receive buffer
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfn_SCI_Rx_Tasks (void)
{    
//    UINT8 u8DataIndex;
    UINT8 u8DataBytes;
    static UINT8 u8_Iterarion_ctr = 0;
    
    u8_Iterarion_ctr++;
  
    if (u8_Iterarion_ctr >= 5)
    {    
        DISABLE_INTERRUPTS();
        
        /* Receive test data */
        u8DataBytes = u8SCI_CheckRx(SCI_Port_0);
        if (u8DataBytes != 0)
        {
//            for (u8DataIndex=0; u8DataIndex<u8DataBytes; u8DataIndex++)
//            {
//            		u8SCI_TxData[u8DataIndex] = u8SCI_ReadRx(0);
//          	}
//          	u8SCI_TxLength = u8DataBytes;       
        }
        vfnSER_ClearRx(SCI_Port_0);
        
        ENABLE_INTERRUPTS();
        u8_Iterarion_ctr = 0;
    }
}

/*******************************************************************************/
/**
* \brief    Transmit data on SCI Transmit buffer
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfn_SCI_Tx_Tasks (void)
{   
    
    if (u8SCI_TxLength != 0)
    {
       vfnSCI_WriteTx(SCI_Port_0, *pu8SCI_Read_Transmit_Data_ptr );
       u8SCI_TxLength--;
       pu8SCI_Read_Transmit_Data_ptr++;
    }
    else
    {
        pu8SCI_Read_Transmit_Data_ptr = &u8SCI_TxData[0];
    }
    
}
/*******************************************************************************/
#endif