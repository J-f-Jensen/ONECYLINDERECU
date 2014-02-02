/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Tasks.h
\brief      Tasks to be assigned to each execution thread of Task scheduler.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.1
\date       10/Feb/2008
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

#ifndef __TASKS
#define __TASKS

/*-- Includes ----------------------------------------------------------------*/

/** MCU definitions */
#include "MCUdefinitions.h"
/** Serial Communication definitions */
#include "SCI.h"
/** SPI definitions and function prototypes */
#include "SPI.h"
/** ADC definitions and function prototypes */
#include "ADC.h"
/** Emulator Test function prototypes */
//JAOV #include "Emulator_Test.h"
/** Macros for GPIO handling */
#include "GPIO_macros.h"
/** Crank sensing definitions and function prototypes */
#include "Crank_Sensing.h"
/** Idle speed stepper motor control function prototypes */
#include "Idle_Speed_Control.h"
/** PWM for crank motor function prototypes */
//#include "PWM.h"

#include "User Management.h"
#include "Data Management.h"
#include "Engine Management.h"



/*-- Types Definitions -------------------------------------------------------*/
extern UINT8 gu8Index;

extern INT8 ai8TempBuffer[4];

/*-- Defines -----------------------------------------------------------------*/
/*-- Macros ------------------------------------------------------------------*/

/* List of tasks to be executed @ 1ms */
#define EXECUTE_1MS_TASKS()     \
{                               \
    Engine_Management();        \
    Data_Management();          \
}
/* List of tasks to be executed @ 2ms, first group */
#define EXECUTE_2MS_A_TASKS()   \
{                               \
                                \
}
/* List of tasks to be executed @ 2ms, second group */
#define EXECUTE_2MS_B_TASKS()   \
{                               \
                                \
}
/* List of tasks to be executed @ 10ms */
#define EXECUTE_10MS_TASKS()    \
{                               \
    User_Management();          \
}
/* List of tasks to be executed @ 50ms */
#define EXECUTE_50MS_TASKS()    \
    {;}
//{                               \
//    vfn_Update_Crank_Speed();   \ //PWM control used in demo
//}
/* List of tasks to be executed @ 100ms */
#ifdef __EMULATOR_HARDWARE_FIRMWARE
    #define EXECUTE_100MS_TASKS()   \
    {;}
#else
    #define EXECUTE_100MS_TASKS()   \
    {;}
#endif

/*============================================================================*/
#endif /*__TASKS */
