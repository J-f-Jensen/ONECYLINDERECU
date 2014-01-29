/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
\file       stepper_motor_control.h
\brief      Stepper motor functions header 
\author     Freescale Semiconductor
\author     Luis Olea B20740
\version    0.1
\date       Sept/2008
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


/* macros */

//steps required for each case of rotation
#define DEGREES_360   200
#define DEGREES_180   DEGREES_360/2
#define DEGREES_90    DEGREES_180/2
#define DEGREES_45    DEGREES_90/2
#define DEGREES_22_5  DEGREES_45/2
#define DEGREES_0     0  

//States of the idle speed motor
#define STOPPED      1
#define CLOSING      2
#define OPENING      3

//stepper motor states
#define MOTOR_OFF     0x00
#define TURN_MOTOR_ON 0xFF

/* prototypes */

//Initialization for stepper motor
void vfnISM_Init(void);

//task in charge of motor (scheduler, every 2 ms)
void vfn_ISM_TASK(void);

//tells the motor to go to a certain position p
void vfnSet_ISM_Position(UINT16);


/*******************************************************************************/