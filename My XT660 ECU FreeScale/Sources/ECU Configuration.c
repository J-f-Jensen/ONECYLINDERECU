/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       ECU COnfiguration.c
\brief      Engine control unit hardware configuration
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\version    0.1
\date       November/ 2008
*/
/*******************************************************************************/
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

/** CPU definitions */
#include "Cpu.h"
/** Scheduler function prototypes definitions */
#include "Scheduler.h"
/** SCI functions and definitions */
#include "SCI.h"
/** SPI definitions and functions prototypes */
#include "SPI.h"
/** ADC definitions and functions */
#include "ADC.h"
/** Input Output macros and definitions */
#include "Input_Output.h"
/** Relays definitions and functions prototypes */
#include "Relays.h"  

/** ECU configuration function prototypes */
#include "ECU Configuration.h" 
/** Software and hardware configuration */
#include "Application Definitions.h"


/*******************************************************************************/
/**
* \brief    Initialization of the ECU hardware resources
* \author   Jaime Orozco
* \param    void
* \return   void
*/

void vfnECU_Init(void)
{
    /* PLL initialization, Bus Clock @ 32MHz */
    vfnClock_Init(); 
    /* Other CPU initalization parameters */
    vfnCpu_init();                       
    /* Perform initialization of Multi-thread round robin Task Scheduler */
    vfnScheduler_Init();
    /* Perform SPI Initialization */
    //vfnSPI_Init();
    /* Perform SCI Initialization */
    vfnSCI_Init();
    /* Perform I/O configuration and Initialization */
    vfnInputs_Outputs_Init();
    /* Perform ADC initialization */
    vfnADC_Init();    
        
    /* Relays initialization */
    vfnRelays_Initialization();     
}

/*******************************************************************************/
