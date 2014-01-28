/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       PWM.c
\brief      Pulse Width Modulator functions.
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory. RTAC Americas
\author     Jaime Orozco
\version    0.1
\date       25/02/2008
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

/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** S12X derivative information */
#include __S12X_DERIVATIVE
/** Variable types and common definitions */
#include "typedefs.h"
/** PWM definitions */
#include "PWM.h"

#include "User Management.h"


static UINT16 u16Crank_Speed;
UINT8 u8Duty_High;
UINT8 u8Duty_Low;
    
extern unsigned int LOAD;


/*******************************************************************************/
/**
* \brief    PWM Module initialization
* \author   B05114
* \param    void
* \return   void
*/
void vfnPWM_Init(void)
{    
    PWME_PWME3 = 0;     /* PWM channel disabled */
   
    PWMPOL_PPOL3 = PWM_POL_LOW;     /* Polarity selection */
    
    PWMCLK_PCLK3 = 0;               /* Clock B is the clock source */
    
    PWMPRCLK_PCKB = PWM_PRESCALER;  /* Clock B prescaler */   

    PWMCAE_CAE3 = PWM_CENTER_ALIGN; /* Outputs alignment */
    
    PWMCTL_CON23 = 1;
    
    PWMPER2 = 0x0F;         /* PWM period */   
    PWMPER3 = PWM_PERIOD; 
    
    PWMDTY2 = 0;    /* Initial duty cycle */
    PWMDTY3 = 0;
    
    PWME_PWME3 = 1; /* PWM channel enabled */    
}


/*******************************************************************************/
/**
* \brief    PWM Duty Cyle definition 
* \author   B05114
* \param    u8PWM_DutyCycle
* \return   void
*/
void vfnSet_PWM_Duty_Cycle(UINT16 u16PWM_DutyCycle) 
{                 
    u8Duty_High = u16PWM_DutyCycle >> 8;
    u8Duty_Low = u16PWM_DutyCycle & 0xFF;
    
    PWMDTY2 = u8Duty_High;
    PWMDTY3 = u8Duty_Low;    /* Load desired duty cycle */    
}

/*******************************************************************************/
/**
* \brief    PWM Duty Cyle definition 
* \author   B05114
* \param    u8PWM_DutyCycle
* \return   void
*/
void vfn_Update_Crank_Speed(void)
{       
    if(!Safety_Check())
    {        
        u16Crank_Speed = LOAD >> 1;               
        vfnSet_PWM_Duty_Cycle(u16Crank_Speed);
    }
}

/*******************************************************************************/
/**
* \brief    Stop the crank motor
* \author   B05114
* \param    void
* \return   void
*/
void vfn_Stop_Crank_Motor(void)
{              
    vfnSet_PWM_Duty_Cycle(0);   /* Null PWM duty cycle */
}

/*******************************************************************************/