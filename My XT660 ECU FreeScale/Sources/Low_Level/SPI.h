/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       SPI.h
\brief      Serial Peripheral Interface definitions and function prototypes.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory. RTAC Americas.
\author     Jaime Orozco.
\version    0.1
\date       25/02/2008
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

#ifndef __SPI_H        /* Prevent duplicated includes */
#define __SPI_H

/*-- Includes ----------------------------------------------------------------*/

/** Variable types and common definitions */
#include "typedefs.h"
/** CPU common definitions */
#include "CPU.h"
/** Application definitions */
#include "Application Definitions.h"

/*-- Defines -----------------------------------------------------------------*/

/* SPI baud rate = Bus_clock /  Baud_rate_divider  */    
/* Baud rate divider = (SPPR+1)*2^(SPR+1) */  
/* For SPI baud rate = 1MHz and Bus Clock = 40 MHz, baud rate divider = 40 */
#define SPI_SPPR   4       
#define SPI_SPR    2       

/*-- Communication status defines --------------------------------------------*/
#define SPI_COMM_READY      0
#define SPI_COMM_TX_BUSY    1
#define SPI_COMM_RX_OK      2   

/*-- Function Prototypes -----------------------------------------------------*/

//Not converted for S12P yet
#if HARDWARE == (EMULATOR | PROTOTYPE)

/** SPI Initalization */
void vfnSPI_Init(void);

/** 16 bit transmission through SPI, data is received simultaneously */
UINT8 u8SPI_Transfer(UINT16 u16SPI_data);

/** Retrieve 16 bit data received through SPI */
UINT16 u16SPI_Read_Data(void);

/** SPI test function to illustrate SPI low level routines usage 
this must be replaced by actual SPI tasks */
void vfnSPI_test(void);

#endif
/*******************************************************************************/

#endif /* __SPI_H */