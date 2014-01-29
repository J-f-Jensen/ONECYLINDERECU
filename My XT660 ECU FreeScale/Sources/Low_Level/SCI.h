/*******************************************************************************/
/**
\file       SCI.h
\brief      Serial Communication Interface functions
\author     Freescale Semiconductor
\author     Abraham Tezmol and Jens F. Jensen
\version    1
\date       18/01/2014
*/
/*******************************************************************************/
/*
\   Serial communication functions including TX and RX ring buffer 
\   This version only support SCI0
\   Works for one wire communication used as implementended in Yamaha XT660 ECU's
\   To change it to use seperate RX/TX wires see ISR function in SCI.c
*/
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

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/* SCI definition defines */
#define SCIBusClock             BUS_FREQ //BUS_FREQ is defined in CPU.h
#define SCIBaudRate             SCI19200bps
/* Buffer size definition */
#define RxQ_SIZE    16
#define TxQ_SIZE    16


/* SCI Ports Definition for u8SCIPort */
//#define SCI_Port_0              0      // Not used
//#define SCI_Port_1              1      // Not used


/*-- Communication status defines --------------------------------------------*/
#define SCI_COMM_OK                         0
#define SCI_COMM_TX_BUSY                    1
#define SCI_COMM_RX_OVERRUN                 2
#define SCI_COMM_PORT_ERROR                 3
#define SCI_COMM_TX_BUFFER_FULL             4 

/*-- Macros ------------------------------------------------------------------*/
#define SCI38400bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(614400))    //38400 * 16
#define SCI19200bps     (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(307200))    //19200 * 16
#define SCI9600bps      (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(153600))    // 9600 * 16
#define SCI4800bps      (unsigned int)((unsigned long)(SCIBusClock) / (unsigned long)(76800))     // 4800 * 16
/*-- Function Prototypes -----------------------------------------------------*/

/** SCI Initalization */
void vfnSCI_Init(void);

/** SCI Byte read from receive buffer **/
UINT8 u8SCI_ReadRx(void);
/** SCI Data bytes available from receive buffer **/
UINT8 u8SCI_CheckRx(void);
/** Discard any incomming data on SCI receive buffer **/
void vfnSER_ClearRx(void);

/** SCI Byte write to transmit buffer **/
UINT8 u8SCI_WriteTx(UINT8 u8TxDataByte);

/** SCI Low-Level Byte Transmit function **/
void vfnSCI_WriteTx(UINT8 u8TxDataByte);

#pragma CODE_SEG __NEAR_SEG NON_BANKED
/** SCI Low-Level RX/TX function **/
void interrupt SCI0_Isr (void);
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#endif /* __SCI_H */