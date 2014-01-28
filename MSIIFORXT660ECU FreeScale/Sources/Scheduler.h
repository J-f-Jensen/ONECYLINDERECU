/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Scheduler.h
\brief      Task scheduler function prototypes
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.1
\date       08/Feb/2008
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

#ifndef SCHEDULER_H        /*prevent duplicated includes*/
#define SCHEDULER_H

/*-- Includes ----------------------------------------------------------------*/
/** System configuration definitions */
#include "Cpu.h"
/** Application definitions */
#include "Application Definitions.h"

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/* Task Scheduler state machine status definitions */
#define NO_TASK_PENDING     0x00
#define TASKS_1_MS          0x01
#define TASKS_2_MS_A        0x02
#define TASKS_2_MS_B        0x03
#define TASKS_10_MS         0x04
#define TASKS_50_MS         0x05
#define TASKS_100_MS        0x06

/* Global Task Scheduler Status definitions */
#define TASK_SCHEDULER_OK               0x00   
#define TASK_SCHEDULER_OVERLOAD_1MS     0x01
#define TASK_SCHEDULER_OVERLOAD_2MS_A   0x02
#define TASK_SCHEDULER_OVERLOAD_2MS_B   0x03

/** Periodic Interrupt Timer definitions */
#define PIT_MICROTIMER_PERIOD   1000000
#define PIT_TARGET_FREQ         2000       


/*-- Macros ------------------------------------------------------------------*/

/** Periodic Interrupt Timer macros */
#define PIT_MICROTIMER_DIV  ((BUS_FREQ/PIT_MICROTIMER_PERIOD)-1)
#define PIT_VALUE           ((PIT_MICROTIMER_PERIOD/PIT_TARGET_FREQ)-1)

/*-- Function Prototypes -----------------------------------------------------*/

/** Sheduler Initalization (arming) */
void vfnScheduler_Init(void);

/** Scheduler kick-off function */
void vfnScheduler_Start(void);

/** Multi-thread round robin task scheduler */
void vfnTask_Scheduler(void);

/** ISR that provides time base to MTRR Task Scheduler - */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
#if HARDWARE == (EMULATOR | PROTOTYPE)
void interrupt Scheduler_PIT0_Isr(void);
#else if HARDWARE == REFERENCE
void interrupt Scheduler_RTI_Isr(void);
#endif
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#endif /* SCHEDULER_H */