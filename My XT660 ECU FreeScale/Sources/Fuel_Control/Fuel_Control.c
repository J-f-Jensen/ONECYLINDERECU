/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Fuel_Control.c
\brief      Functions for fuel delivery
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\version    0.2
\date       September/ 2008
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

/** MCU definitions **/
#include "MCUdefinitions.h"
/** Crank sensing definitions and function prototypes */
#include "Crank_Sensing.h"
/** Spark control function prototypes */
#include "Spark_Control.h"
/** Fuel control function prototypes */
#include "Fuel_Control.h"
/** Timer module initialization prototypes and definitions */
#include "Timers.h"
/** Application definitions */
#include "Application Definitions.h" 

#include "Engine Management.h"


/* Fuel pulse 1 variables */
UINT16 u16Current_Fuel1_Start = 0;
UINT16 u16Current_Fuel1_Start_Tooth = 0;
UINT16 u16Current_Fuel1_Start_Offset = 0;
UINT16 u16Current_Fuel1_Pulse = 0;

extern UINT16 u16Next_Fuel1_Start;
extern UINT16 u16Next_Fuel1_Start_Tooth;
extern UINT16 u16Next_Fuel1_Start_Offset;
extern UINT16 u16Next_Fuel1_Pulse;

#ifdef TWO_CYLINDER
/* Fuel pulse 2 variables */
UINT16 u16Current_Fuel2_Start = 0;
UINT16 u16Current_Fuel2_Start_Tooth = 0;
UINT16 u16Current_Fuel2_Start_Offset = 0;
UINT16 u16Current_Fuel2_Pulse = 0;

extern UINT16 u16Next_Fuel2_Start;
extern UINT16 u16Next_Fuel2_Start_Tooth;
extern UINT16 u16Next_Fuel2_Start_Offset;
extern UINT16 u16Next_Fuel2_Pulse;
#endif


/* Local state of fuel control state machines */ 
UINT8 u8Fuel1_Control_State = FUEL_CTRL_INACTIVE;
UINT8 u8Fuel2_Control_State = FUEL_CTRL_INACTIVE;

/* Overall state for fuel controller */
UINT8 u8Fuel_Controller_Mode = OFF;


/* Fuel map arrays */
extern const UINT16 Fuel_Pulse_Angle_Map[FUEL_RPM_POINTS][FUEL_LOAD_POINTS];
extern UINT16 Fuel_Pulse_Angle_Map_RAM[FUEL_RPM_POINTS][FUEL_LOAD_POINTS];

extern const UINT16 Fuel_Pulse_Width_Map[FUEL_RPM_POINTS][FUEL_LOAD_POINTS]; 
extern UINT16 Fuel_Pulse_Width_Map_RAM[FUEL_RPM_POINTS][FUEL_LOAD_POINTS];

extern UINT16 Fuel_Load_Map_Values[FUEL_LOAD_POINTS];
extern UINT16 Fuel_RPM_Map_Values[FUEL_RPM_POINTS];

extern unsigned int u16Fuel_Modifier;

/* Variables related to crankshaft sensing */
extern u16Current_Tooth_Time;
extern UINT8 u8Teeth_Counter;
extern UINT16 u16Current_Period;
extern UINT16 u16Angle_Clock_rate;
extern UINT8 u8Crank_State;

//Test Variables
extern UINT16 Fuel_Add;
extern UINT16 Fuel_Cut;


/*******************************************************************************/
/**
* \brief    Set the fuel controller state
* \author   Jaime Orozco 
* \param    u8State: ENABLED/ DISABLED
* \return   void
*/
void vfnSet_Fuel_Controller(UINT8 u8State_Request)
{  
    if((u8State_Request == ENABLED) && (u8Fuel_Controller_Mode == OFF))
    {
        /* Channel 6 enabled as output compare for fuel pulse 1 generation */            
        // Not supported in S12T64 OCPD_OCPD0 = 0;
        TIOS_IOS6 = 1;     
        TCTL1_OM6 = 1;  /* Clear on output compare event */  
        TCTL1_OL6 = 0;
        CFORC_FOC6 = 1; /* Force output event */
                      
        #ifdef TWO_CYLINDER
                        
        /*Channel 7 enabled as output compare for fuel pulse 2 generation */            
        //OCPD_OCPD1 = 0;
        TIOS_IOS7 = 1;     
        TCTL1_OM7 = 1;  /* Clear on output compare event */
        TCTL1_OL7 = 0;
        CFORC_FOC7 = 1; /* Force output event */ 
                  
        #endif            
                 
                 
        /* Update fuel controller status */
        u8Fuel_Controller_Mode = ON;
        
        //Initialize fuel controller parameters by getting next event info
        vfnUpdate_Current_Fuel1_Params();        
        #ifdef TWO_CYLINDER
        vfnUpdate_Current_Fuel2_Params();        
        #endif
        
        /* Start the fuel control states machines */
        u8Fuel1_Control_State = FUEL_CTRL_READY;
        u8Fuel2_Control_State = FUEL_CTRL_READY;
    }
    
    if((u8State_Request == DISABLED) && (u8Fuel_Controller_Mode == ON))
    {    
        /* Update fuel controller status */
        u8Fuel_Controller_Mode = OFF;
        
    /* Controller will be effectively disabled when fuel events are scheduled */
    }
}     

/*******************************************************************************/
/**
* \brief    Disable timers to allow direct control of fuel injectors
* \author   Jaime Orozco 
* \param    void
* \return   void
*/ 
void vfnDisable_Fuel1_Timer(void)
{
    /* Interrupt disabled */
    FUEL_PULSE1_INTERRUPT(DISABLED);     
    
    /* Channel 6 disconnected from output compare module */             
    // Not supported in S12T64 OCPD_OCPD0 = 1;
    TCTL1_OM6 = 0;  /* Used instead of OCPD_OCPD0 = 1; */  
    TCTL1_OL6 = 0;  /* Used instead of OCPD_OCPD0 = 1; */
    
    TIOS_IOS6 = 0; 
    
    /* Fuel injector turned off */
    INJIN1 = OFF;
}

#ifdef TWO_CYLINDER
void vfnDisable_Fuel2_Timer(void)
{
    /* Interrupt disabled */
    FUEL_PULSE2_INTERRUPT(DISABLED);     
    
    /* Channel 1 disconnected from output compare module */             
    OCPD_OCPD1 = 1;
    TIOS_IOS1 = 0; 
    
    /* Fuel injector turned off */
    INJIN2 = OFF;
}
#endif
        
/*******************************************************************************/
/**
* \brief    Direct control of signals to fuel injectors
* \author   Jaime Orozco 
* \param    u8Injector: FUEL_INJECTOR_1, FUEL_INJECTOR_2
            u8State: ON/ OFF 
* \return   void
*/

void vfnFuel_Direct_Control(UINT8 u8Injector, UINT8 u8Injector_State)
{                                  
    if((u8Fuel1_Control_State == FUEL_CTRL_INACTIVE) && (u8Injector == FUEL_INJECTOR_1))
    { 
        INJIN1 = u8Injector_State;                
    }
    
    #ifdef TWO_CYLINDER 
    if((u8Fuel2_Control_State == FUEL_CTRL_INACTIVE) && (u8Injector == FUEL_INJECTOR_2))
    {           
        INJIN2 = u8Injector_State;                                             
    }
    #endif   
}

/*******************************************************************************/
/**
* \brief    Read state of control signals to fuel injectors
* \author   Jaime Orozco 
* \param    u8Injector: FUEL_INJECTOR_1, FUEL_INJECTOR_2
* \return   void
*/                                                             

UINT8 vfnFuel_Signal_Status(UINT8 u8Injector)
{
    if(u8Injector == FUEL_INJECTOR_1)
    { 
        return INJ1_STAT;                
    }
    
    #ifdef TWO_CYLINDER 
    if(u8Injector == FUEL_INJECTOR_2)
    {           
        return INJ2_STAT;                                             
    }
    #endif   
}

/*******************************************************************************/
/**
* \brief    Copy fuel pulse map from Flash to RAM
* \author   Jaime Orozco 
* \param    void
* \return   void
*/

void vfnFuel_Map_CopytoRAM(void)
{
UINT8 u8Counter_1 = 0;
UINT8 u8Counter_2 = 0;

   for(u8Counter_1 = 0; u8Counter_1 < FUEL_RPM_POINTS; u8Counter_1++)
   {
      for(u8Counter_2 = 0; u8Counter_2 < FUEL_LOAD_POINTS; u8Counter_2++)
       {    
          Fuel_Pulse_Angle_Map_RAM[u8Counter_2][u8Counter_1] = 
          Fuel_Pulse_Angle_Map[u8Counter_2][u8Counter_1];    
          
          Fuel_Pulse_Width_Map_RAM[u8Counter_2][u8Counter_1] = 
          Fuel_Pulse_Width_Map[u8Counter_2][u8Counter_1];   
       }       
   }
}

/*******************************************************************************/
/**
* \brief    Read fuel pulse angle from control map in Flash
* \author   Jaime Orozco
* \param    void
* \return   void
*/

UINT16 u16Read_Fuel_Pulse_Angle_Map(UINT16 u16RPM_Input,UINT16 u16Load_Input)
{
    static UINT16 u16Load;
    static UINT16 u16RPM;
    
    /* Obtain index of best match for input data within map values */
    u16Load = u16Interpolation(u16Load_Input, Fuel_Load_Map_Values, FUEL_LOAD_POINTS);

    u16RPM = u16Rev_Interpolation(u16RPM_Input, Fuel_RPM_Map_Values, FUEL_RPM_POINTS);
    
    return (Fuel_Pulse_Angle_Map[u16RPM][u16Load]); 
}

/*******************************************************************************/
/**
* \brief    Read fuel pulse width from control map in Flash
* \author   Jaime Orozco
* \param    void
* \return   void
*/

UINT16 u16Read_Fuel_Pulse_Width_Map(UINT16 u16RPM_Input, UINT16 u16Load_Input)
{
    static UINT16 u16Load;
    static UINT16 u16RPM;
    
    /* Obtain index of best match for input data within map values */
    u16Load = u16Interpolation(u16Load_Input, Fuel_Load_Map_Values, FUEL_LOAD_POINTS);

    u16RPM = u16Rev_Interpolation(u16RPM_Input, Fuel_RPM_Map_Values, FUEL_RPM_POINTS);
    
    return (Fuel_Pulse_Width_Map[u16RPM][u16Load]); 
}


   
/*******************************************************************************/
/**
* \brief    Update fuel control variables
* \author   Jaime Orozco 
* \param    void
* \return   void
*/
void vfnUpdate_Current_Fuel1_Params(void)
{  
    u16Current_Fuel1_Start = u16Next_Fuel1_Start;
    u16Current_Fuel1_Pulse = u16Next_Fuel1_Pulse;
    u16Current_Fuel1_Start_Tooth = u16Next_Fuel1_Start_Tooth;  
    u16Current_Fuel1_Start_Offset = u16Next_Fuel1_Start_Offset;
}


#ifdef TWO_CYLINDER   
     
void vfnUpdate_Current_Fuel2_Params(void)
{    
    u16Current_Fuel2_Start = u16Next_Fuel2_Start;
    u16Current_Fuel2_Pulse = u16Next_Fuel2_Pulse;
    u16Current_Fuel2_Start_Tooth = u16Next_Fuel2_Start_Tooth; 
    u16Current_Fuel2_Start_Offset = u16Next_Fuel2_Start_Offset;
}      
        
#endif

/*******************************************************************************/
/**
* \brief    Change the Fuel parameters from a 360 degree process to a 720 degree
*  process.  Called when the crank state machine gets synchronized to the valves. 
* \author   Jesse Beeker 
* \param    void
* \return   void
*/

#ifdef FOUR_STROKES
void vfnFuel_4C_Convert(void){

//Convert cylinder 1
                    //Change Current_Fuel1 Parameters to 4 cycle
                    //If the Fuel1 reference angle for 4 cycle sync is on the second revolution,
                    //then we need to add a revolution the current Fuel1 parameters.
                    if(FUEL1_REF_ANGLE_4C>=360){
                      //Fuel1 occurs on the second revolution.
                      //Change the angle for the start of the fuel pulse.
                      u16Current_Fuel1_Start=u16Current_Fuel1_Start+360;
                      //Change the tooth that is before fuel pulse starts.
                      u16Current_Fuel1_Start_Tooth=u16Current_Fuel1_Start_Tooth+NUMBER_OF_TEETH;
                      
                      //The fuel pulse length is still the same no changes.  
                      //u16Current_Fuel1_Pulse = u16Current_Fuel1_Pulse;

                      
                      //The values were already tested against zero cases, so no need to test again.    
                    }

#ifdef TWO_CYLINDER
//Convert cylinder 2
                    //Change Current_Fuel2 Parameters to 4 cycle
                    //If the Fuel2 reference angle for 4 cycle sync is on the second revolution,
                    //then we need to add a revolution the current Fuel2 parameters.
                    if(FUEL2_REF_ANGLE_4C>=360){
                      //Fuel2 occurs on the second revolution.
                      //Change the angle for the start of the fuel pulse.
                      u16Current_Fuel2_Start=u16Current_Fuel2_Start+360;
                      //Change the tooth that is before fuel pulse starts.
                      u16Current_Fuel2_Start_Tooth=u16Current_Fuel2_Start_Tooth+NUMBER_OF_TEETH;
                      
                      //The fuel pulse length is still the same no changes.  
                      //u16Current_Fuel2_Pulse = u16Current_Fuel2_Pulse;

                      
                      //The values were already tested against zero cases, so no need to test again.    
                    }
#endif


}
#endif

  
/*******************************************************************************/
/**
* \brief    Set time to start fuel pulses 
* \author   Jaime Orozco 
* \param    void
* \return   void
*/

void vfnSchedule_Fuel1_Pulse(void)
{
    UINT32 u32Start1;    /* Auxiliary variable */   
                
    /* Verify if fuel controller is active */
    if(u8Fuel_Controller_Mode == ON)
    {              
        /* Update current fuel control values */
        vfnUpdate_Current_Fuel1_Params();
                            
        /* Validate if tooth before fuel pulse 1 has ocurred */           
        if(u8Teeth_Counter == u16Current_Fuel1_Start_Tooth)
        {                       
            /* Compensate start of pulse using angle clock rate */
            u16Current_Fuel1_Start_Offset = 
            u16Current_Fuel1_Start_Offset * u16Angle_Clock_rate;
             
            /* Calculate value to be loaded on compare register */                     
            u32Start1 = u16Current_Tooth_Time + u16Current_Fuel1_Start_Offset;
                           
            if(u32Start1 > 0xFFFF)
            {
                u32Start1 = u32Start1 - 0xFFFF;
            }
            
            SET_FUEL1_ON_NEXT_STATE();  /* Set output pin on next compare event */ 
            
            /* Load value corresponding to fuel pulse start */
            FUEL_PULSE1_TIMER = (UINT16)u32Start1;  
                   
            FUEL_PULSE1_INTERRUPT(ENABLED);     /* Fuel pulse 1 interrupt enabled */
            
            u8Fuel1_Control_State = FUEL_PULSE_SCHEDULED;
        } 
    } 
    
    else
    {
        /* Disable fuel controller if it is not already inactive */
        if(u8Fuel1_Control_State != FUEL_CTRL_INACTIVE)
        {   
            vfnDisable_Fuel1_Timer();             
            u8Fuel1_Control_State = FUEL_CTRL_INACTIVE;                                 
        }    
    }
}


#ifdef TWO_CYLINDER

void vfnSchedule_Fuel2_Pulse(void)
{
    UINT32 u32Start2;    /* Auxiliary variable */   
                    
    /* Verify if fuel controller is active */
    if(u8Fuel_Controller_Mode == ON)
    {          
        /* Update current fuel control values */
        vfnUpdate_Current_Fuel2_Params();
        
        /* Validate if tooth before fuel pulse 2 has ocurred */            
        if(u8Teeth_Counter == u16Current_Fuel2_Start_Tooth)
        {                       
            /* Compensate start of pulse using angle clock rate */
            u16Current_Fuel2_Start_Offset = u16Current_Fuel2_Start_Offset * u16Angle_Clock_rate;
                          
            /* Calculate value to be loaded on compare register */                       
            u32Start2 = u16Current_Tooth_Time + u16Current_Fuel2_Start_Offset;
                   
            if(u32Start2 > 0xFFFF)
            {
                u32Start2 = u32Start2 - 0xFFFF;
            }
            
            SET_FUEL2_ON_NEXT_STATE();  /* Set output pin on next compare event */ 
            
            /* Load value corresponding to fuel pulse start */
            FUEL_PULSE2_TIMER = (UINT16)u32Start2;  
                   
            FUEL_PULSE2_INTERRUPT(ENABLED);     /* Fuel pulse 1 interrupt enabled */
            
            u8Fuel2_Control_State = FUEL_PULSE_SCHEDULED;
        } 
    }
    
    else
    {
        /* Disable fuel controller if it is not already inactive */
        if(u8Fuel2_Control_State != FUEL_CTRL_INACTIVE)
        {   
            vfnDisable_Fuel2_Timer();
            
            u8Fuel2_Control_State = FUEL_CTRL_INACTIVE;                 
        }    
    }
}

#endif

/*******************************************************************************/
/**
* \brief    Timer channel interrupt service routine 
* \author   Jaime Orozco 
* \param    void
* \return   void
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt Fuel1_Control_Isr(void)
{ 
    UINT32 u32Width1;    /* Auxiliary variable */

    switch(u8Fuel1_Control_State)
    {        
        case FUEL_PULSE_SCHEDULED:
        {
            /* Signal INJIN1 is ON at this moment */
           
            /* Add pulse width to previous comparisson value */
            u32Width1 = FUEL_PULSE1_TIMER + u16Current_Fuel1_Pulse;  
            
            if(u32Width1 > 0xFFFF)
            {
                u32Width1 = u32Width1 - 0xFFFF;
            }
            
            /* Clear output pin on next compare event */  
            CLEAR_FUEL1_ON_NEXT_STATE();     
                    
            /* Load value corresponding to calculated fuel pulse width */
            FUEL_PULSE1_TIMER = (UINT16)u32Width1;
            
            /* Fuel pulse 1 interrupt enabled */           
            FUEL_PULSE1_INTERRUPT(ENABLED);     
            
            u8Fuel1_Control_State = FUEL_PULSE_ON;   /* Update state */ 
            
            break;            
        }
        
        case FUEL_PULSE_ON:
        {
            /* Signal INJIN1 is OFF at this moment */
            
            FUEL_PULSE1_INTERRUPT(DISABLED);  /* Disable interrupt */
          
            /* Update current fuel control values. 
            Redundant as done on each tooth.*/
            vfnUpdate_Current_Fuel1_Params();
        
            u8Fuel1_Control_State = FUEL_CTRL_READY;  /* Go to initial state */ 
            
            break;                      
        }
        
        default:
        {        
            break;
        }
    }
    return ;          
}


void interrupt Fuel2_Control_Isr(void)
{         
#ifdef TWO_CYLINDER

    UINT32 u32Width2;    /* Auxiliary variable */
    
    switch(u8Fuel2_Control_State)
    {        
        case FUEL_PULSE_SCHEDULED:
        {
            /* Signal INJIN2 is ON at this moment */
           
            /* Add pulse width to previous comparisson value */
            u32Width2 = FUEL_PULSE2_TIMER + u16Current_Fuel2_Pulse;  
            
            if(u32Width2 > 0xFFFF)
            {
                u32Width2 = u32Width2 - 0xFFFF;
            }
            
            /* Clear output pin on next compare event */     
            CLEAR_FUEL2_ON_NEXT_STATE();    
                                    
            /* Load value corresponding to calculated fuel pulse width */
            FUEL_PULSE2_TIMER = (UINT16)u32Width2;
            
            /* Fuel pulse 2 interrupt enabled */           
            FUEL_PULSE2_INTERRUPT(ENABLED);     
            
            u8Fuel2_Control_State = FUEL_PULSE_ON;   /* Update state */ 
            
            break;            
        }
        
        case FUEL_PULSE_ON:
        {
            /* Signal INJIN2 is OFF at this moment */
            
            FUEL_PULSE2_INTERRUPT(DISABLED);  /* Disable interrupt */
            
            /* Update current fuel control values 
            Redundant as done on each tooth. */
            vfnUpdate_Current_Fuel2_Params();
                   
            u8Fuel2_Control_State = FUEL_CTRL_READY;  /* Go to initial state */ 
            
            break;                      
        }
        
        default:
        {        
            break;
        }
    }
    return ;  
    
#endif        
}
 

#pragma CODE_SEG DEFAULT

/*******************************************************************************/
