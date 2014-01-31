/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Fuel_Control.h
\brief      Fuel delivery definitions and function prototypes
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\version    0.2
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

/** Timer channel assigned to fuel pulse 1 */
#define FUEL_PULSE1_TIMER                  TIMER_CHANNEL_G     
/** Timer channel interrupt enable/disable */      
#define FUEL_PULSE1_INTERRUPT(SELECTOR)    CHANNEL_G_INTERRUPT(SELECTOR)
/* Set output on compare event for timer channel */   
#define SET_FUEL1_ON_NEXT_STATE()          SET_ON_COMPARE_EVENT_G()
#define CLEAR_FUEL1_ON_NEXT_STATE()        CLEAR_ON_COMPARE_EVENT_G()
/** Force compare event */
#define FUEL1_FORCE_EVENT()                CHANNEL_G_FORCE_EVENT()  

/** Timer channel assigned to fuel pulse 2 */
#define FUEL_PULSE2_TIMER                  TIMER_CHANNEL_H    
/** Timer channel interrupt enable/disable */      
#define FUEL_PULSE2_INTERRUPT(SELECTOR)    CHANNEL_H_INTERRUPT(SELECTOR)
/* Actions on compare event for timer channel */ 
#define SET_FUEL2_ON_NEXT_STATE()          SET_ON_COMPARE_EVENT_H()
#define CLEAR_FUEL2_ON_NEXT_STATE()        CLEAR_ON_COMPARE_EVENT_H()
/** Force compare event */
#define FUEL2_FORCE_EVENT()                CHANNEL_H_FORCE_EVENT()


/* Definition of fuel controller states */
enum
{
FUEL_CTRL_INACTIVE,
FUEL_CTRL_READY,
FUEL_PULSE_SCHEDULED,
FUEL_PULSE_ON
};

/* Fuel injectors definition */

#define FUEL_INJECTOR_1     1
#define FUEL_INJECTOR_2     2


/* Macros to read status of fuel control signals */
#define FUEL_INJECTOR1_STATUS   INJ1_STAT
#define FUEL_INJECTOR2_STATUS   INJ2_STAT


/* Function prototypes */

/** Enable/ disable the fuel controller */
void vfnSet_Fuel_Controller(UINT8 u8State_Request);

/** Direct control of signals to fuel injectors if controller is disabled */
void vfnFuel_Direct_Control(UINT8 u8Injector, UINT8 u8Injector_State);

/** Disable timers to allow direct control of fuel injectors */ 
void vfnDisable_Fuel1_Timer(void);
void vfnDisable_Fuel2_Timer(void);

/** Read state of control signals to fuel injectors */
UINT8 vfnFuel_Signal_Status(UINT8 u8Injector);

/** Copy fuel pulse map from Flash to RAM */
void vfnFuel_Map_CopytoRAM(void);

/** Read data from fuel pulse angle map */
UINT16 u16Read_Fuel_Pulse_Angle_Map(UINT16 u16RPM_Value, UINT16 u16Load_Value);

/** Read data from fuel pulse width map */
UINT16 u16Read_Fuel_Pulse_Width_Map(UINT16 u16RPM_Value, UINT16 u16Load_Value);


/** Set time to start fuel pulse */
void vfnSchedule_Fuel1_Pulse(void);

/** Update current values for fuel control */
void vfnUpdate_Current_Fuel1_Params(void);

//Convert current fuel data to a 4 cycle process
#ifdef FOUR_STROKES
void vfnFuel_4C_Convert(void);
#endif



#ifdef TWO_CYLINDER

/** Set time to start fuel pulse */
void vfnSchedule_Fuel2_Pulse(void);

/** Update current values for fuel control */
void vfnUpdate_Current_Fuel2_Params(void);

#endif


#pragma CODE_SEG __NEAR_SEG NON_BANKED

/** Fuel pulse 1 ISR */
void interrupt Fuel1_Control_Isr(void);

/** Fuel pulse 2 ISR */
void interrupt Fuel2_Control_Isr(void);

#pragma CODE_SEG DEFAULT

/*******************************************************************************/


