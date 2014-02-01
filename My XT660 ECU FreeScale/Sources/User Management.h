/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       User Management.h
\brief      User management definitions and function prototypes
\author     Freescale Semiconductor
\author     Jesse Beeker
\version    0.1
\date       December/ 2008
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


/** Application definitions */
#include "Application Definitions.h" 


#define Conv_Period_to_RPM(Period)    (Period +1); 

//User Management Functions
//Default configuration and variable initialization
void User_Management_Init(void);

//User Management task
void User_Management(void);

//User Management State transition functions
void vfnGoto_INIT(void);
void vfnGoto_STOP(void);
void vfnGoto_START(void);
void vfnGoto_RUN(void);
void vfnGoto_OVERRUN(void);

//Malfunction Indicator Lamp functions
void MIL_Init(void);
void MIL_Set(void);
void MIL_Clear(void);

//Fuel pump controller functions
void Fuel_Pump_Controller_Init(void);
void Fuel_Pump_Controller(void);

//Injection and ignition fault functions
unsigned char Get_Injector1_Fault(void);
unsigned char Get_Ignition1_Fault(void);

#ifdef TWO_CYLINDER
unsigned char Get_Injector2_Fault(void);
unsigned char Get_Ignition2_Fault(void);
#endif

//Engine operating paramteters update
void Update_Modifiers(void);

//User input engine operations check
unsigned char Safety_Check(void);

//Engine load calculation
void Load_Calculate(void);

//Engine speed calcuation
void RPM_Calculate(void);



//User Management Definitions
//Define the states of the User Managment Application
#define INIT 0
#define STOP 1
#define START 2
#define RUN 3
#define OVERRUN 4

//Injector and Ignition faults
#define No_Fault 0
#define Vbat_Short 1
#define Open 2
#define Ground_Short 3

/* Signals assigned to relays */
#define FUEL_PUMP   RELAY2

//Timeout for fuel pump to shut off if engine does not start.
//Units are executions of User Management Task which is 10ms.
//Timeout is 3 seconds.
#define FUEL_PUMP_TOUT  300

//Start up strategy fuel modifier values
//Select if starting fuel modifier is to be used.
#define MSTART

#ifdef MSTART
  //Define decay rate (timer tics) for the staring fuel modifier.
  #define MSTART_Decay 25
  
  //Define how many cycles through the User Management application it takes to 
  //apply the decay of MSTART fuel modifier.
  #define MSTART_Decay_Timeout 5
#endif

//Transient fuel detection
//Transient fuel/accelerator pump functionality
  //Define if this is to be used and define TIP values
  //#define TIP_Detection
  //Set the change in ADC counts for TPS value change for a TIP in condition  
  #define TIP_IN_VALUE  50
  //Set the change in ADC counts for TPS value change for a TIP out condition  
  #define TIP_OUT_VALUE  50
  //Set the decay rate of the fuel modifier used for TIP in
  #define TIP_IN_Decay_Timeout 5
  //Set the decay rate of the fuel modifier used for TIP out
  #define TIP_OUT_Decay_Timeout  2
  //Set the decay rate for TIP in, in timer tics
  #define TIP_IN_Decay  50
  //Set the decay rate for TIP out, in timer tics
  #define TIP_OUT_Decay  1000


//ISM control definitions
//Control commands
#define STAY 0 
#define CLOSE 1
#define OPEN 2
//Controller loop time
//Based on User Management Task ever 10ms
//Control time set for 500ms
#define ISM_TOUT 50



/*******************************************************************************/
