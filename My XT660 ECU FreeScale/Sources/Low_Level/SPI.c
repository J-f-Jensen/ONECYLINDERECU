/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       SPI.c
\brief      Serial Peripheral Interface functions
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory. RTAC Americas
\author     Jaime Orozco
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

/** MCU definitions */
#include "MCUdefinitions.h"


/** SPI definitions and function prototypes */ 
#include "SPI.h"
/** Variable types and common definitions */
#include "typedefs.h"
/** Application definitions */
#include "Application Definitions.h" 

/** SPI module status */
static UINT8 u8SPI_Status;

//Not converted for S12P yet
#if HARDWARE == (EMULATOR | PROTOTYPE)

/*******************************************************************************/
/**
* \brief    SPI 0 module initializing in Master mode
* \author   B05114
* \param    void
* \return   void
*/
void vfnSPI_Init(void)
{  
    SPI0CR1 = 0x04;     /* SPI module disabled */                    
    SPI0CR2 = 0x00;
    
    MODRR_MODRR4 = 1;   /* SPI module connected to port M (PM2 to PM5) */
    
    (void)SPI0SR;       /* Read the status register and */
    (void)SPI0DR;       /* read the data register to clear the status flags */
    
    SPI0CR1_MSTR = 1;   /* SPI in Master mode */                                                                             
    
    SPI0BR_SPPR = SPI_SPPR;     /* Load baud rate divider */
    SPI0BR_SPR = SPI_SPR;    
    
    SPI0CR2_MODFEN = 1; /* Slave select output pin used by SPI module */  
    SPI0CR1_SSOE = 1;   
          
    SPI0CR1_CPOL = 0;   /* Clock idle state is low */
    SPI0CR1_CPHA = 1;   /* Data sampling at falling edges */
    
    SPI0CR2_XFRW = 1;   /* 16 bit data transfer */          
    
    SPI0CR1_SPE = 1;    /* SPI module enabled */
    
    u8SPI_Status = SPI_COMM_READY;
}


/*******************************************************************************/
/**
* \brief    16 bit transmission through SPI, data is received simultaneously 
* \author   B05114
* \param    u16SPI_data: 16 bit data to be sent
* \return   u8SPI_Status: Communication status as defined in SPI.h
*/

UINT8 u8SPI_Transfer(UINT16 u16SPI_data)
{
    if(u8SPI_Status != SPI_COMM_TX_BUSY)  /* If no transfer is in progress */
    {
      if(SPI0SR_SPTEF)              /* verify if SPI data register is empty */ 
        {
            SPI0DR = u16SPI_data;   /* Load byte in data transmission register */ 
            u8SPI_Status = SPI_COMM_TX_BUSY;    /* SPI transfer in progress */ 
        }      
    }
    
    
    if(u8SPI_Status == SPI_COMM_TX_BUSY)    /* If SPI transfer was in progress, */
    {
        if(SPI0SR_SPIF)                     /* verify if it has been completed */
        {
            u8SPI_Status = SPI_COMM_RX_OK;  /* New received data available */
        }
    }  
    
    return u8SPI_Status;    /* Return the status of the SPI transfer */             
}

/*******************************************************************************/
/**
* \brief    Retrieve 16 bit data received through SPI
* \author   B05114
* \param    void
* \return   16 bit value in SPI data register
*/

UINT16 u16SPI_Read_Data(void)
{
    UINT16 u16SPI_RxData = 0;
    
    if(u8SPI_Status == SPI_COMM_RX_OK)  /* If new data has been received */
    {
        u16SPI_RxData = SPI0DR;          /* Read SPI data register */
        u8SPI_Status = SPI_COMM_READY;  /* Update SPI status */        
    }
    
    return u16SPI_RxData;        
}


/*******************************************************************************/
/**
* \brief    SPI test function. 
* \         This illustrates SPI low level routines usage 
* \         and must be replaced by actual SPI tasks
* \author   B05114
* \param    void
* \return   void
*/
void vfnSPI_test(void)
{
    static UINT16  u16Dummy_Data = 0;     /* Dummy data for SPI testing */
    UINT16 u16ReadValue;
    
    if(u8SPI_Transfer(u16Dummy_Data) == SPI_COMM_RX_OK)
    {                                       /* If new data is available */
        u16ReadValue = u16SPI_Read_Data();  /* read SPI data register */
        
        u16Dummy_Data ++;           /* Increment dummy variable */           
    }      
}

/*******************************************************************************/

#endif