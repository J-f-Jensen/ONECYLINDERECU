/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       typedefs.h
\brief      Variable types and common macros
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco/Abraham Tezmol
\version    0.2
\date       14/Feb/2008
\warning   
* History:
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

#ifndef TYPEDEFS_H        /*prevent duplicated includes*/
#define TYPEDEFS_H

/*-- Includes ----------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/
typedef unsigned char   UINT8;  /*unsigned 8 bit definition */
typedef unsigned short  UINT16; /*unsigned 16 bit definition*/
typedef unsigned long   UINT32; /*unsigned 32 bit definition*/
typedef signed char     INT8;   /*signed 8 bit definition */
typedef short           INT16;  /*signed 16 bit definition*/
typedef long int        INT32;  /*signed 32 bit definition*/

/*-- Defines -----------------------------------------------------------------*/
/* Common Bit masks */

/* The following two lines were modified for S12XS compatibility */
#define ENABLE_INTERRUPTS()  {__asm CLI;}        /*interrupts enabled        */
#define DISABLE_INTERRUPTS() {__asm SEI;}        /*interrupts disabled       */

/* Uncomment these two lines if used with any other S12X derivative but S12XS */
//#define ENABLE_INTERRUPTS()  {__asm CLI; XGMCTL_XGIE = 1;}        /*interrupts enabled        */
//#define DISABLE_INTERRUPTS() {__asm SEI; XGMCTL_XGIE = 0;}        /*interrupts disabled       */

#define XIRQ_ENABLE()        {asm andcc #0xBF;}  /*XIRQ enabled              */
#define WAIT()               {asm wait;}         /*enter wait mode           */
#define STOP_ENABLE()        {asm andcc #0x7F;}  /*stop mode enabled         */
#define STOP_MODE()          {asm stop;}         /*enter stop mode           */
#define NOP()                {asm nop;}          /*enter NOP asm instruction */

/* Common Constants */
#define ON          1
#define OFF         0
#define TRUE        1
#define FALSE       0
#define PASS        0u
#define FAIL        1u
#define SET         1u
#define CLEAR       0u
#define ENABLED     1
#define DISABLED    0

/*-- Macros ------------------------------------------------------------------*/

/*-- Function Prototypes -----------------------------------------------------*/

#endif /* TYPEDEFS_H */