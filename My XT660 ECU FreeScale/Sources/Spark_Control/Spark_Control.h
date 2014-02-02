/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Spark_Control.h
\brief      Single and dual spark control definitions and function prototypes
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Omar Hernandez/Rodrigo Ruiz (NACURI)
\version    0.3
\date       May/ 2008
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

#include <hidef.h>
/** MCU definitions */
#include "MCUdefinitions.h"
/** Application definitions */
#include "Application Definitions.h"
/** Variable types and common definitions */
#include "typedefs.h"


/* Reference (0 for missing tooth gap, TDC_ANGLE or angle value in degrees */ 
//Two cycle mode
#define SPARK1_REF_ANGLE  TDC_ANGLE 

#ifdef TWO_CYLINDER
//Crankshaft orienation between the two cylinders.
#define SPARK2_REF_ANGLE  TDC_ANGLE + 180
#endif

#ifdef FOUR_STROKES
//Four cycle mode, both cylinders need to be adjusted for four cycle mode.
#define SPARK1_REF_ANGLE_4C  SPARK1_REF_ANGLE + 360 
  #ifdef TWO_CYLINDER
  #define SPARK2_REF_ANGLE_4C  SPARK2_REF_ANGLE - 180
  #endif
#endif

/* Select dwell to be angle or fixed time */
//#define DWELL_ANGLE        130      /* Dwell angle in degrees */
#define DWELL_TIME_MS       8      /* Dwell time in miliseconds */

#define SOLENOID_DELAY_MS   0      /* Solenoid delay in ms */
   

#ifdef  DWELL_TIME_MS
#define DWELL_TIME      DWELL_TIME_MS * 625 /* Dwell time converted to timer cycles */
#endif

#define SOLENOID_DELAY  SOLENOID_DELAY_MS * 625 /* Solenoid delay converted to timer cycles */


/** Timer channel assigned to spark pulse 1 */
#define SPARK_PULSE1_TIMER                  TIMER_CHANNEL_D     
/** Timer channel interrupt enable/disable */      
#define SPARK_PULSE1_INTERRUPT(SELECTOR)    CHANNEL_D_INTERRUPT(SELECTOR)
/* Set output on compare event for timer channel */   
#define SET_SPARK1_ON_NEXT_STATE()          SET_ON_COMPARE_EVENT_D()
#define CLEAR_SPARK1_ON_NEXT_STATE()        CLEAR_ON_COMPARE_EVENT_D()
/** Force compare event */
#define SPARK1_FORCE_EVENT()                CHANNEL_D_FORCE_EVENT()  

#ifdef TWO_CYLINDER
/** Timer channel assigned to spark pulse 2 */
#define SPARK_PULSE2_TIMER                  TIMER_CHANNEL_D     
/** Timer channel interrupt enable/disable */      
#define SPARK_PULSE2_INTERRUPT(SELECTOR)    CHANNEL_D_INTERRUPT(SELECTOR)
/* Actions on compare event for timer channel */ 
#define SET_SPARK2_ON_NEXT_STATE()          SET_ON_COMPARE_EVENT_D()
#define CLEAR_SPARK2_ON_NEXT_STATE()        CLEAR_ON_COMPARE_EVENT_D()
/** Force compare event */
#define SPARK2_FORCE_EVENT()                CHANNEL_D_FORCE_EVENT()  
#endif

/* Definition of spark controller states */
enum
{
SPARK_CTRL_INACTIVE,
READY_TO_SCHEDULE_SPARK,
WAITING_STARTING_CURRENT_FLOW,
WAITING_IGNITION_TIME
};

/* Spark signals definition */
#define SPARK_COIL_1    3
#ifdef TWO_CYLINDER
#define SPARK_COIL_2    4
#endif
/** Function prototypes */

/** Set the spark controller state */
void vfnSet_Spark_Controller(UINT8 u8State_Request);

/** Direct control of signals to spark coils */
void vfnSpark_Direct_Control(UINT8 u8Coil, UINT8 u8Coil_State);

/** Disable timers to allow direct control of spark coils */ 
void vfnDisable_Spark1_Timer(void);
#ifdef TWO_CYLINDER
void vfnDisable_Spark2_Timer(void);
#endif

/** Copy spark timing map from Flash to RAM */
void vfnSpark_Map_CopytoRAM(void);

/** Read spark timing control map from Flash */
UINT16 u16Read_Spark_Map(UINT16 u16RPM_Input, UINT16 u16Load_Input);                  

/** Calculation of spark 1 ignition timing */
void vfnSchedule_Spark1_Pulse(void);

/** Update spark 1 timing variables */
void vfnUpdate_Current_Spark1_Params(void);

//Convert current spark data to a 4 cycle process
#ifdef FOUR_STROKES
void vfnSpark_4C_Convert(void);
#endif
/** Clear the number of spark events that occurred*/
void vfnSpark1_Counter_Reset(void);

#ifdef TWO_CYLINDER
/** Calculation of spark 2 ignition timing */
void vfnSchedule_Spark2_Pulse(void);

/** Update spark 2 timing variables */
void vfnUpdate_Current_Spark2_Params(void);

/** Clear the number of spark events that occurred*/
void vfnSpark2_Counter_Reset(void);

#endif


#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Spark1_Control_Isr(void);

#ifdef TWO_CYLINDER
void interrupt Spark2_Control_Isr(void);
#endif
#pragma CODE_SEG DEFAULT


/** Interpolation by successive aproximation */
UINT16 u16Interpolation(UINT16 u16Input_Data, 
                        UINT16 *au16Data_array, UINT16 u16Size_of_Array);    

/** Interpolation by successive aproximation */
UINT16 u16Rev_Interpolation(UINT16 u16Input_Data, 
                        UINT16 *au16Data_array, UINT16 u16Size_of_Array); 
                         
/*******************************************************************************/