/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       SCI.h
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

#ifndef __SCI_H        /*prevent duplicated includes*/
#define __SCI_H

/*-- Includes ----------------------------------------------------------------*/
/** Application definitions */
#include "Application Definitions.h"

/** Variable types and common definitions */
#include "typedefs.h"
/** CPU common definitions */
#include "CPU.h"
 /** Application definitions */
#include "Application Definitions.h" 

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/* SCI definition defines */
#define SCIBusClock             BUS_FREQ
#define SCIBaudRate             SCI19200bps
#define SCI_RX_MAX_SIZE         16
#define SCI_TX_MAX_SIZE         32

/* SCI Ports Definition for u8SCIPort */
#define SCI_Port_0              0
#define SCI_Port_1              1


/*-- Communication status defines --------------------------------------------*/
#define SCI_COMM_OK                         0
#define SCI_COMM_TX_BUSY                    1
#define SCI_COMM_RX_OVERRUN                 2
#define SCI_COMM_PORT_ERROR                 3

/*-- Macros ------------------------------------------------------------------*/
#define SCI38400bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(614400))    //38400 * 16
#define SCI19200bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(307200))    //19200 * 16
#define SCI9600bps      (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(153600))    // 9600 * 16
#define SCI4800bps      (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(76800))     // 4800 * 16
/*-- Function Prototypes -----------------------------------------------------*/

#if HARDWARE == (EMULATOR | PROTOTYPE)
//Not converted to S12P
/** SCI Initalization */
void vfnSCI_Init(UINT8 u8SCIPort);
/** SCI Low-Level Byte Transmit function **/
void vfnSCI_WriteTx(UINT8 u8SCIPort, UINT8 u8TxDataByte);
/** SCI Byte read from receive buffer **/
UINT8 u8SCI_ReadRx(UINT8 u8SCIPort);
/** SCI Data bytes available from receive buffer **/
UINT8 u8SCI_CheckRx(UINT8 u8SCIPort);
/** Discard any incomming data on SCI receive buffer **/
void vfnSER_ClearRx(UINT8 u8SCIPort);

void vfn_SCI_Rx_Tasks(void);
void vfn_SCI_Tx_Tasks(void);
#endif

#pragma CODE_SEG __NEAR_SEG NON_BANKED
/** SCI Low-Level Byte Receive function **/
void interrupt SCI_Receive_Isr (void);
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#endif /* __SCI_H */