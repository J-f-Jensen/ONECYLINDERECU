/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Scheduler.c
\brief      Multi-thread Task scheduler.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Abraham Tezmol
\version    0.2
\date       04/March/2008
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


/** Variable types and common definitions */
#include "typedefs.h"
/** Scheduler function prototypes definitions */
#include "Scheduler.h"
/** Tasks definition */
#include "Tasks.h"
/** Application definitions */
#include "Application Definitions.h"


/* -- Global Variables --------------------------------------------------------*/
UINT8 gu8Scheduler_Status;
UINT8 gu8Scheduler_Counter;
UINT8 gu8Scheduler_Thread_ID;
UINT8 gu8Scheduler_Thread_ID_Backup;
UINT8 u8_10ms_Counter;
UINT8 u8_50ms_Counter;
UINT8 u8_100ms_Counter;

/*******************************************************************************/
/**
* \brief    Scheduler - Periodic Interrup Timer Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnScheduler_Init(void)
{   
    //S12P uses RTI to generate time base for scheduler.
    //Create 500us period
     //Select RTI clock source to be external oscillator
// Not supported in S12T64
//     CPMUCLKS_RTIOSCSEL = 1;

     //Decimal divider
// Not supported in S12T64
//     CPMURTI_RTDEC =1;

     //Divide by 4000, 8MHz/4000=2kHz or 500us
// Not supported in S12T64
//     CPMURTI_RTR = 0b0000011;

//S12T64 - Divide by 2048, 4MHz/2048~2kHz or 512us

RTICTL = 0b00010001;

     //Enable RTI interrupt later in scheduler_start function.
     //CPMUINT_RTIE = 1;  
}

/*******************************************************************************/
/**
* \brief    Scheduler Start - Once time base is armed, start execution of   \n
            Multi-thread Round Robin scheduling scheme.                     \n
            This function requires prior execution of "vfnScheduler_Init"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnScheduler_Start(void)
{
    //Enable RTI interrupt later in scheduler_start function.
    //CPMUINT_RTIE = 1;    Not supported in S12T64
    CRGINT_RTIE = 1;
}

/*******************************************************************************/
/**
* \brief    Multi-thread round robin task Scheduler  (non-preemtive)        \n
            It calls the different tasks based on the status of             \n   
            "gu8Scheduler_Thread_ID". This variable is modified by          \n
            ISR "Scheduler_PIT0_Isr"                                        \n
            List of tasks shall be defined @ "tasks.h" file
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnTask_Scheduler(void)
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  1ms execution thread - used to derive two execution threads:                */
    /*  a) 1ms thread (high priority tasks)                                         */
    /*  b) 100ms thread (lowest priority tasks)                                     */
    /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/   
    if ((gu8Scheduler_Thread_ID == TASKS_1_MS) || (gu8Scheduler_Thread_ID == TASKS_100_MS))
    {
        /* Make a copy of scheduled task ID */
        gu8Scheduler_Thread_ID_Backup = gu8Scheduler_Thread_ID;
        
        EXECUTE_1MS_TASKS();
        
        if (gu8Scheduler_Thread_ID == TASKS_100_MS)
        {
            EXECUTE_100MS_TASKS();
        }
         /* Verify that thread execution took less than 500 us */
        if (gu8Scheduler_Thread_ID_Backup == gu8Scheduler_Thread_ID)
        {
             /* In case execution of all thread took less than 500us */
            gu8Scheduler_Thread_ID = NO_TASK_PENDING;
        }
        else
        {
            gu8Scheduler_Status = TASK_SCHEDULER_OVERLOAD_1MS;
        }
    }
    else
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  2ms execution thread - used to derive two execution threads:                */
        /*  a) 2ms group A thread (high priority tasks)                                 */
        /*  b) 50ms thread (second lowest priority tasks)                               */
        /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if ((gu8Scheduler_Thread_ID == TASKS_2_MS_A) || (gu8Scheduler_Thread_ID == TASKS_50_MS))
        {
            /* Make a copy of scheduled task ID */
            gu8Scheduler_Thread_ID_Backup = gu8Scheduler_Thread_ID;
            
            EXECUTE_2MS_A_TASKS();
            
            if (gu8Scheduler_Thread_ID == TASKS_50_MS)
            {
                EXECUTE_50MS_TASKS();
            }
            /* Verify that thread execution took less than 500 us */
            if (gu8Scheduler_Thread_ID_Backup == gu8Scheduler_Thread_ID)
            {
                 /* In case execution of all thread took less than 500us */
                gu8Scheduler_Thread_ID = NO_TASK_PENDING;
            }
            else
            {
                gu8Scheduler_Status = TASK_SCHEDULER_OVERLOAD_2MS_A;
            }
        }
        else
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group B thread (high priority tasks)                                 */
            /*  b) 10ms thread (medium priority tasks)                                      */
            /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if ((gu8Scheduler_Thread_ID == TASKS_2_MS_B) || (gu8Scheduler_Thread_ID == TASKS_10_MS))
            {
                /* Make a copy of scheduled task ID */
                gu8Scheduler_Thread_ID_Backup = gu8Scheduler_Thread_ID;
                
                EXECUTE_2MS_B_TASKS();
                
                if (gu8Scheduler_Thread_ID == TASKS_10_MS)
                {
                    EXECUTE_10MS_TASKS();
                }
                 /* Verify that thread execution took less than 500 us */
                if (gu8Scheduler_Thread_ID_Backup == gu8Scheduler_Thread_ID)
                {
                    /* In case execution of all thread took less than 500us */
                    gu8Scheduler_Thread_ID = NO_TASK_PENDING;
                }
                else
                {
                    gu8Scheduler_Status = TASK_SCHEDULER_OVERLOAD_2MS_B;
                }
            }
        }
    }        
}

/*******************************************************************************/
/**
* \brief    Periodic Interrup Timer Service routine.                            \n
            This interrupt is the core of the task scheduler.                   \n
            It is executed every 500us                                          \n
            It defines 3 basic threads from which other 3 threads are derived:  \n
            a) 1ms thread (basic) ->  100ms thread (derived)                    \n
            b) 2ms A thread (basic)-> 50ms thread (derived)                     \n
            c) 2ms B thread (basic)-> 10ms thread (derived)                     \n
            It partitions core execution time into time slices (500us each one).\n 
            This arrangement assures core will have equal task loading across time.\n   
            For more information on how time slice is assigned to each thread,  \n
            refer to file "S12X Task Scheduler Layout.xls"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt Scheduler_RTI_Isr(void) {
  
    /* Verify that Real Time Interrupt caused the interrupt */
    //if (CPMUFLG_RTIF == 1)
    if (CRGFLG_RTIF == 1)
    {
        /*-- Update scheduler control variable --*/
        gu8Scheduler_Counter++;
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  1ms execution thread - used to derive two execution threads:                */
        /*  a) 1ms thread (highest priority tasks)                                      */
        /*  b) 100ms thread (lowest priority tasks)                                     */
        /*  As any other thread on this scheduling scheme,                              */
        /*  all tasks must be executed in <= 500us                                      */
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if ((gu8Scheduler_Counter & 0x01) == 0x01)
        {
            u8_100ms_Counter++;
            /*-- Allow 100 ms periodic tasks to be executed --*/
            if (u8_100ms_Counter >= 100)
            {    
                gu8Scheduler_Thread_ID = TASKS_100_MS;
                u8_100ms_Counter = 0;
            }
            /*-- Allow 1 ms periodic tasks to be executed --*/
            else
            {
                gu8Scheduler_Thread_ID = TASKS_1_MS;
            }
        }
        else
        { 
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group A thread (high priority tasks)                                 */
            /*  b) 50ms thread (second lowest priority tasks)                               */
            /*  As any other thread on this scheduling scheme,                              */
            /*  all tasks must be executed in <= 500us                                      */
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if ((gu8Scheduler_Counter & 0x02) == 0x02)
            {    
                u8_50ms_Counter++;
                /*-- Allow 50 ms periodic tasks to be executed --*/
                if (u8_50ms_Counter >= 25)
                {
                    gu8Scheduler_Thread_ID = TASKS_50_MS;
                    u8_50ms_Counter = 0;
                }
                /*-- Allow 2 ms group A periodic tasks to be executed --*/
                else
                {
                    gu8Scheduler_Thread_ID = TASKS_2_MS_A;
                }
            }
            else
            { 
                /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                /*  2ms execution thread - used to derive two execution threads:                */
                /*  a) 2ms group B thread (high priority tasks)                                 */
                /*  b) 10ms thread (medium priority tasks)                                      */
                /*  As any other thread on this scheduling scheme,                              */
                /*  all tasks must be executed in <= 500us                                      */
                /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                if ((gu8Scheduler_Counter & 0x03) == 0x00)
                {
                    u8_10ms_Counter++;
                    /*-- Allow 10 ms periodic tasks to be executed --*/
                    if (u8_10ms_Counter >= 5)
                    {
                        gu8Scheduler_Thread_ID = TASKS_10_MS;
                        u8_10ms_Counter = 0;
                    }
                    /*-- Allow 2 ms group B periodic tasks to be executed --*/
                    else
                    {
                        gu8Scheduler_Thread_ID = TASKS_2_MS_B;
                    }
                }
            }
        }
    }
    /* Clear the real time interrupt flag by writing a 1. */
    //CPMUFLG_RTIF = 1; Not supported in S12T64
    CRGFLG_RTIF = 1;
}

#pragma CODE_SEG DEFAULT

/*******************************************************************************/
