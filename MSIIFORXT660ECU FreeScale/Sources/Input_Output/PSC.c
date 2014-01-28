/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       PSC.c
\brief      Power Supply Control
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jul/ 2008
*/
/*******************************************************************************/

/** Application definitions */
#include "Application Definitions.h"
/** PSC function prototypes */
#include "PSC.h"
/** CPU initialization prototypes and definitions */
#include "Input_Output.h"

/*******************************************************************************/
/**
* \brief    Initializations for PSC
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnPSC_Init(void)
{            
#ifdef PSC
   
   /** Default PSC Off, same as Input_Output.c Digital Outputs Initialization ?? */
   vfnPSC_Off();      

#endif
}

/*******************************************************************************/
/**
* \brief    Puts the PSC in the active state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnPSC_On(void)
{            
#ifdef PSC
   
  //Turn on the PSC connected to ????.  
  // ???? = ON;    

#endif
}

/*******************************************************************************/
/**
* \brief    Puts the PSC in the inactive state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnPSC_Off(void)
{            
#ifdef PSC
   
  //Turn off the PSC connected to ???
  // ???? = OFF;   

#endif
} 
/*******************************************************************************/