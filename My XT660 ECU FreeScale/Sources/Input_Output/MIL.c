/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       MIL.c
\brief      Malfunction Indication Lamp Control
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.1
\date       Jul/ 2008
*/
/*******************************************************************************/

/** Application definitions */
#include "Application Definitions.h"
/** MIL function prototypes */
#include "MIL.h"
/** CPU initialization prototypes and definitions */
#include "Input_Output.h"

/*******************************************************************************/
/**
* \brief    Initializations for MIL
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnMIL_Init(void)
{            
#ifdef MIL
   
   /** Default MIL Off, same as Input_Output.c Digital Outputs Initialization */
   vfnMIL_Off();      

#endif
}

/*******************************************************************************/
/**
* \brief    Puts the MIL in the active state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnMIL_On(void)
{            
#ifdef MIL
   
  //Turn on the MIL connected to VLAMP.  
  VLAMPIN = ON;    

#endif
}

/*******************************************************************************/
/**
* \brief    Puts the MIL in the inactive state
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnMIL_Off(void)
{            
#ifdef MIL
   
  //Turn off the MIL connected to VLAMP
  VLAMPIN = OFF;   

#endif
} 
/*******************************************************************************/