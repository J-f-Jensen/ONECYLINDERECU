/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Engine Management.c
\brief      Engine management functions
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\version    0.1
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

/** MCU definitions */
//#include "MCUdefinitions.h"
/** Engine management definitions and function prototypes */
#include "Engine Management.h"
/** Crank sensing definitions and function prototypes */
#include "Crank_Sensing.h"
/** Spark control function prototypes */
#include "Spark_Control.h"
/** Fuel control function prototypes */
#include "Fuel_Control.h"

/** Application definitions */
#include "Application Definitions.h"

/* Fuel injection pulse variables */
UINT16 u16Next_Fuel1_Start = 0;
UINT16 u16Next_Fuel1_Start_Tooth = 0;
UINT16 u16Next_Fuel1_Pulse = 0;
UINT16 u16Next_Fuel1_Start_Offset = 0;

/* Ignition spark pulse variables */
UINT16 u16Next_Spark1_Start = 0;
UINT16 u16Next_Spark1_Dwell = 0;
UINT16 u16Next_Spark1_Dwell_Tooth = 0;
UINT16 u16Next_Spark1_Dwell_Offset = 0;


#ifdef TWO_CYLINDER
/* Fuel injection pulse variables */
UINT16 u16Next_Fuel2_Start = 0;
UINT16 u16Next_Fuel2_Start_Tooth = 0;
UINT16 u16Next_Fuel2_Pulse = 0;
UINT16 u16Next_Fuel2_Start_Offset = 0;

/* Ignition spark pulse variables */
UINT16 u16Next_Spark2_Start = 0;
UINT16 u16Next_Spark2_Dwell = 0;
UINT16 u16Next_Spark2_Dwell_Tooth = 0;
UINT16 u16Next_Spark2_Dwell_Offset = 0;
#endif


/* Fuel pulse auxiliary variables */
UINT16 u16Fuel_Start_Angle = 0;
UINT16 u16Fuel_Start_Tooth = 0;
UINT16 u16Fuel_Pulse_Width = 0;
UINT16 u16Fuel_Angle_Offset = 0;

/* Ignition pulse auxiliary variables */
UINT16 u16Spark_Start_Angle = 0;
UINT16 u16Spark_Dwell_Angle = 0;
UINT16 u16Spark_Dwell = 0;
UINT16 u16Spark_Dwell_Tooth = 0;
UINT16 u16Spark_Dwell_Offset = 0;


/** Engine speed (RPM) */
extern unsigned int Engine_Speed;

/** Load */
//extern unsigned int LOAD;
//Engine Load parameter
#ifdef Analog_Data_8
  //Load is from 8 bit data
  extern unsigned char LOAD;
#else
  //Load is from 10 or 12 bit data
  extern unsigned int LOAD;
#endif


/** Modifier for spark angle */
extern unsigned int u16Spark_Modifier;

/** Modifier for fuel angle */
extern unsigned int u16Fuel_Modifier;


/** State variable from Crankshaft sensing state machine */
extern UINT8 u8Crank_State;
extern UINT16 u16Angle_Clock_rate;


// Fuel adder
extern UINT16 Fuel_Add;
//Fuel subtracter for testing.  Raw timer tics to cut from fuel.
extern UINT16 Fuel_Cut;

//Spark adder for testing. Degrees to make closer to TDC.
extern UINT16 Spark_Advance;
//Spark subtracter for testing. Degrees to make farther from TDC.
extern UINT16 Spark_Retard;


/** Calculates engine position (angle and tooth) to start fuel pulse */
void vfnCalc_Fuel_Start(UINT16 u16RPM, UINT16 u16LOAD, UINT16 u16Ref_Angle);

/** Calculates fuel pulse width */
UINT16 u16Calc_Fuel_Pulse_Width(UINT16 u16RPM, UINT16 u16LOAD);

#ifdef TWO_STROKES
/** Calculates angle for next ignition spark */
UINT16 u16Calc_Spark_Start(UINT16 u16RPM, UINT16 u16LOAD, 
                           UINT16 u16Ref_Angle_2C);
#endif
#ifdef FOUR_STROKES
/** Calculates angle for next ignition spark */
UINT16 u16Calc_Spark_Start(UINT16 u16RPM, UINT16 u16LOAD, 
                           UINT16 u16Ref_Angle_2C);
#endif

/** Calculates dwell time to allow steady current through the ignition coil */
void vfnCalc_Spark_Dwell(UINT16 u16Spark_Start_Angle);


/*******************************************************************************/
/**
* \brief    Resources initialization for engine management
* \author   Jaime Orozco 
* \param    void
* \return   void
*/
void Engine_Management_Init(void)
{                 
    /* Timers initialization for crankshaft sensing */
    vfnInit_Crank_Sensing();

    /* Start crankshaft sensing states machine */
    vfnGoTo_Crank_FirstEdge();        
    
    /* Spark and fuel controllers are initially disabled */
    vfnSet_Fuel_Controller(DISABLED);
    vfnSet_Spark_Controller(DISABLED);
}

/*******************************************************************************/
/**
* \brief    Engine control: calculates the timing for spark and fuel pulses
* \author   Jaime Orozco 
* \param    void
* \return   void
*/
void Engine_Management()
{        
    /* Run fuel injection management */
    vfnFuel1_Start(0, 0);
    vfnFuel1_Pulse(Engine_Speed, LOAD);        
    
    /* Run ignition spark management */
    vfnSpark1_Start(Engine_Speed, LOAD);
    vfnSpark1_Dwell(); 
        
    
#ifdef TWO_CYLINDER 
     
    /* Run fuel injection management */
    vfnFuel2_Start(Engine_Speed, LOAD);
    vfnFuel2_Pulse(Engine_Speed, LOAD);        
    
    /* Run ignition spark management */
    vfnSpark2_Start(Engine_Speed, LOAD);
    vfnSpark2_Dwell();             
#endif
}

/*******************************************************************************/
/**
* \brief    Calculates engine position (angle) to start next fuel pulse
* \author   Jaime Orozco 
* \param    Latest RPM & LOAD data
* \return   void
*/

void vfnFuel1_Start(UINT16 u16RPM, UINT16 u16LOAD)
{              
    /* Calculate angle to start next fuel pulse */     
    vfnCalc_Fuel_Start(u16RPM, u16LOAD, FUEL1_REF_ANGLE);
    
    /* Updates start angle and tooth before it */
    u16Next_Fuel1_Start = u16Fuel_Start_Angle; 
    u16Next_Fuel1_Start_Tooth = u16Fuel_Start_Tooth;
    u16Next_Fuel1_Start_Offset = u16Fuel_Angle_Offset;                                                                    
}

#ifdef TWO_CYLINDER 

void vfnFuel2_Start(UINT16 u16RPM, UINT16 u16LOAD)
{   
    /* Calculate angle to start next fuel pulse */     
    vfnCalc_Fuel_Start(u16RPM, u16LOAD, FUEL2_REF_ANGLE);
    
    /* Updates start angle and tooth before it */
    u16Next_Fuel2_Start = u16Fuel_Start_Angle; 
    u16Next_Fuel2_Start_Tooth = u16Fuel_Start_Tooth; 
    u16Next_Fuel2_Start_Offset = u16Fuel_Angle_Offset;                                                            
}

#endif

/*******************************************************************************/
/**
* \brief    Calculates next fuel pulse width 
* \author   Jaime Orozco 
* \param    Latest RPM & LOAD data
* \return   void
*/

void vfnFuel1_Pulse(UINT16 u16RPM, UINT16 u16LOAD)
{    
    /* Calculate next fuel pulse width */     
    u16Next_Fuel1_Pulse = u16Calc_Fuel_Pulse_Width(u16RPM, u16LOAD);                  
}

#ifdef TWO_CYLINDER

void vfnFuel2_Pulse(UINT16 u16RPM, UINT16 u16LOAD)
{       
    /* Calculate next fuel pulse width */     
    u16Next_Fuel2_Pulse = u16Calc_Fuel_Pulse_Width(u16RPM, u16LOAD);         
}

#endif

/*******************************************************************************/
/**
* \brief    Calculates engine position (angle and tooth) to start fuel pulse
* \author   Jaime Orozco/ Jesse Beeker 
* \param    Latest RPM & LOAD data and reference angle
* \return   void
*/

void vfnCalc_Fuel_Start(UINT16 u16RPM, UINT16 u16LOAD, UINT16 u16Ref_Angle)
{    
    /* Get angle to start fuel pulse from control map */     
    u16Fuel_Start_Angle = u16Read_Fuel_Pulse_Angle_Map(u16RPM, u16LOAD);
    
    /* Calculate actual angle using reference relative to missing tooth */
    
    #ifdef TWO_STROKES
    u16Fuel_Start_Angle += u16Ref_Angle;
    
    if(u16Fuel_Start_Angle > 360)
    {        
        //Keep the angle between 0 and 360 as the process is one revolution.
        u16Fuel_Start_Angle -= 360;
    }      
    #endif
    
    #ifdef FOUR_STROKES
    
    if(u8Crank_State==SYNCHRONIZED_4C){
      
      //Compensate for missing tooth not TDC.
      u16Fuel_Start_Angle += u16Ref_Angle + 360;
    
      if(u16Fuel_Start_Angle >= 720)
      {        
        //Keep the angle bgetween 0 and 720 as the process is two revolutions.
        u16Fuel_Start_Angle -= 720;
      } 
    
    }
    else
    {
      //Compensate for missing tooth not TDC.
      u16Fuel_Start_Angle += u16Ref_Angle;

      if(u16Fuel_Start_Angle >= 360)
      {        
        //Keep the angle between 0 and 360 as the process is one revolution.
        u16Fuel_Start_Angle -= 360;
      }          
    }
    #endif
    
                                
    /* Calculate tooth before fuel pulse event */                                
    u16Fuel_Start_Tooth = (u16Fuel_Start_Angle / DEGREES_PER_TOOTH);

    /* Calculate angle error to properly estimate the pulse start */
    u16Fuel_Angle_Offset = u16Fuel_Start_Angle - 
                          (u16Fuel_Start_Tooth * DEGREES_PER_TOOTH);             
    
    
    if(!u16Fuel_Start_Tooth)
    {
        if(u8Crank_State==SYNCHRONIZED_4C){          
          /* Adjust if calculated tooth is zero- synchronized to 4 stroke */
          u16Fuel_Start_Tooth = NUMBER_OF_TEETH_4C;            
        }
        else
        {
          /* Adjust if calculated tooth is zero- not synchronized to 4 stroke */
          u16Fuel_Start_Tooth = NUMBER_OF_TEETH;            
        }    
    }
    
    
    if(!u16Fuel_Angle_Offset)    
    {
        /* If there is not angle error, go back another tooth */
        u16Fuel_Start_Tooth --; 
        
            if(!u16Fuel_Start_Tooth){
              
              if(u8Crank_State==SYNCHRONIZED_4C){          
                /* Adjust if calculated tooth is zero- synchronized to 4 stroke */
                u16Fuel_Start_Tooth = NUMBER_OF_TEETH_4C;            
              }
              else
              {
                /* Adjust if calculated tooth is zero- not synchronized to 4 stroke */
                u16Fuel_Start_Tooth = NUMBER_OF_TEETH;            
              }
            }
        /* Time to start pulse is 1 period */    
        u16Fuel_Angle_Offset = DEGREES_PER_TOOTH;     
    } 
    
    /* Decrement to match teeth numbering scheme (0 to NUMBER_OF:TEETH -1)*/
    u16Fuel_Start_Tooth --;                                                                                                                                           
}

/*******************************************************************************/
/**
* \brief    Calculates fuel pulse width
* \author   Jaime Orozco 
* \param    Latest RPM & LOAD data
* \return   Pulse width (UINT16)
*/

UINT16 u16Calc_Fuel_Pulse_Width(UINT16 u16RPM, UINT16 u16LOAD)
{      
    /* Get fuel pulse width from control map */     
    u16Fuel_Pulse_Width = u16Read_Fuel_Pulse_Width_Map(u16RPM, u16LOAD);          
    
    /* Apply system fuel adders */
    u16Fuel_Pulse_Width = u16Fuel_Pulse_Width + u16Fuel_Modifier;  
    
    //We need more control during delvopment
    u16Fuel_Pulse_Width = u16Fuel_Pulse_Width + Fuel_Add - Fuel_Cut;
    
    #ifdef FOUR_STROKES
    if(u8Crank_State != SYNCHRONIZED_4C){  
      /* Divide by two to run in two stroke mode */ 
      u16Fuel_Pulse_Width = u16Fuel_Pulse_Width >> 1;                                   
    }
    #endif

    return  u16Fuel_Pulse_Width;    
}


/*******************************************************************************/
/**
* \brief    Determines angle to fire the spark plug,  
* \author   Jaime Orozco/ Jesse Beeker 
* \param    Latest RPM & latest LOAD data
* \return   Void
*/

void vfnSpark1_Start(UINT16 u16RPM, UINT16 u16LOAD)
{                     
    /* Calculate spark event angle */  
    
//    #ifdef TWO_STROKES            
    u16Next_Spark1_Start = u16Calc_Spark_Start(u16RPM, u16LOAD, SPARK1_REF_ANGLE);    
//    #endif
    
//    #ifdef FOUR_STROKES    
//    u16Next_Spark1_Start = u16Calc_Spark_Start(u16RPM, u16LOAD, 
//                                               SPARK1_REF_ANGLE, SPARK1_REF_ANGLE_4C); 
//    #endif                 
}

#ifdef TWO_CYLINDER

void vfnSpark2_Start(UINT16 u16RPM, UINT16 u16LOAD)
{
    /* Calculate spark event angle */ 
    //#ifdef TWO_STROKES  
    u16Next_Spark2_Start = u16Calc_Spark_Start(u16RPM, u16LOAD, SPARK2_REF_ANGLE);  
    //#endif   
    
    //#ifdef FOUR_STROKES  
    //u16Next_Spark2_Start = u16Calc_Spark_Start(u16RPM, u16LOAD, 
   //                                            SPARK2_REF_ANGLE, SPARK2_REF_ANGLE_4C);  
    //#endif                                                                 
}

#endif 

/*******************************************************************************/
/**
* \brief    Requirement 16 - schedules the start of the time to allow steady 
            state current through the primary ignition coil(dwell time)
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnSpark1_Dwell(void)
{            
    vfnCalc_Spark_Dwell(u16Next_Spark1_Start);    
    u16Next_Spark1_Start = u16Spark_Start_Angle;           
    u16Next_Spark1_Dwell = u16Spark_Dwell;
    u16Next_Spark1_Dwell_Tooth = u16Spark_Dwell_Tooth; 
    u16Next_Spark1_Dwell_Offset = u16Spark_Dwell_Offset;
}

#ifdef TWO_CYLINDER

void vfnSpark2_Dwell(void)
{
    vfnCalc_Spark_Dwell(u16Next_Spark2_Start);  
    
    u16Next_Spark2_Start = u16Spark_Start_Angle;   
    u16Next_Spark2_Dwell = u16Spark_Dwell;
    u16Next_Spark2_Dwell_Tooth = u16Spark_Dwell_Tooth;  
    u16Next_Spark2_Dwell_Offset = u16Spark_Dwell_Offset;        
}

#endif

/*******************************************************************************/
/**
* \brief    Calculates angle for next spark start.  
* \author   Jaime Orozco/ Jesse Beeker 
* \param    Latest RPM & latest LOAD data and reference angle
* \return   Void
*/

//#ifdef TWO_STROKES   
UINT16 u16Calc_Spark_Start(UINT16 u16RPM, UINT16 u16LOAD, UINT16 u16Ref_Angle_2C)
//#endif

//#ifdef FOUR_STROKES   
//UINT16 u16Calc_Spark_Start(UINT16 u16RPM, UINT16 u16LOAD, 
//                           UINT16 u16Ref_Angle_2C, UINT16 u16Ref_Angle_4C)
//#endif                           
{         
    
    /* Get spark event angle from control map */     
    u16Spark_Start_Angle = u16Read_Spark_Map(u16RPM, u16LOAD); 
    
    /* Calculate actual angle using reference relative to missing tooth */
        
    //Two cycle mode
    #ifdef TWO_STROKES
    //Test to see if angle will under flow when we compensate for the 
    //reference angle of TDC.
    if((u16Ref_Angle_2C >= u16Spark_Start_Angle){
      //The reference angle is greater than the loop up value.
      //Simply subtract the look up angle from the reference angle.
      u16Spark_Start_Angle = u16Ref_Angle_2C - u16Spark_Start_Angle;
    }else{
      //Angle needs to be resolved to prevent underflow value.
      //First find the angle for the event based on 360 process.
      //Conversion from before TDC to after TDC.
      //u16Spark_Start_Angle = 360 - u16Spark_Start_Angle;
      //Now compensate for the reference angle of TDC.
      //u16Spark_Start_Angle = u16Spark_Start_Angle - u16Ref_Angle_2C;
    
      //Combine into one statement to avoid intermediate values.
      u16Spark_Start_Angle = 360 - u16Spark_Start_Angle - u16Ref_Angle_2C;
    }
    #endif
    
    //Four cycle mode, requires two cycle and four cycle depending on sync state
    #ifdef FOUR_STROKES
    if(u8Crank_State == SYNCHRONIZED_4C){
      //Four cycle synchronized, use 720 degree process

      //Test to see if angle will under flow when we compensate for the 
      //reference angle of TDC.
      if(u16Ref_Angle_2C >= u16Spark_Start_Angle){
        //The reference angle is greater than the loop up value.
        //Simply subtract the look up angle from the reference angle.
        //Add 360 to compensate for Tooth zero starting at intake process.
        u16Spark_Start_Angle = u16Ref_Angle_2C +360 - u16Spark_Start_Angle;
      }else{
        //Angle needs to be resolved to prevent underflow value.
        //First find the angle for the event based on 720 process.
        //Conversion from before TDC to after TDC.
        //u16Spark_Start_Angle = 720 - u16Spark_Start_Angle;
        //Now compensate for the reference angle of TDC.
        //u16Spark_Start_Angle = u16Spark_Start_Angle - u16Ref_Angle_2C;
    
        //Combine into one statement to avoid intermediate values.
        //Angle should always be greater than 360 as long as look up 
        //table value and TDC_ANGLE are bound by a 360 value.  
        u16Spark_Start_Angle = 720 - u16Spark_Start_Angle - u16Ref_Angle_2C;
      }

    }
    //Not synchronized to 4 cycle process.  Use 2 cycle value.  
    else
    {
      //Test to see if angle will under flow when we compensate for the 
      //reference angle of TDC.
      if(u16Ref_Angle_2C >= u16Spark_Start_Angle){
        //The reference angle is greater than the loop up value.
        //Simply subtract the look up angle from the reference angle.
        u16Spark_Start_Angle = u16Ref_Angle_2C - u16Spark_Start_Angle;
      }else{
        //Angle needs to be resolved to prevent underflow value.
        //First find the angle for the event based on 360 process.
        //Conversion from before TDC to after TDC.
        //u16Spark_Start_Angle = 360 - u16Spark_Start_Angle;
        //Now compensate for the reference angle of TDC.
        //u16Spark_Start_Angle = u16Spark_Start_Angle - u16Ref_Angle_2C;
    
        //Combine into one statement to avoid intermediate values.
        u16Spark_Start_Angle = 360 - u16Spark_Start_Angle - u16Ref_Angle_2C;
      }
    
    }
    
    
    #endif
    
    /* Apply defined adders */
    //u16Spark_Start_Angle = u16Spark_Start_Angle * u16Spark_Modifier;                                            
    
    //Test need more control.
    u16Spark_Start_Angle = u16Spark_Start_Angle + Spark_Advance - Spark_Retard;
    //be carefule as you could create over/underflow using these hard modifiers!
                   
    return  u16Spark_Start_Angle;                                              
}

/*******************************************************************************/
/**
* \brief    Dwell time to allow steady current through the ignition coil
* \author   Jaime Orozco 
* \param    Void
* \return   Void
*/

void vfnCalc_Spark_Dwell(UINT16 u16Spark_Start_Angle)
{                       
    #ifdef DWELL_TIME
        /* Dwell time converted from time to angle */
        u16Spark_Dwell_Angle = DWELL_TIME / u16Angle_Clock_rate;
    #else
    
    #ifdef DWELL_ANGLE
       u16Spark_Dwell_Angle = DWELL_ANGLE;
       
       /* Add solenoid delay to dwell angle */
        u16Spark_Dwell_Angle = u16Spark_Dwell_Angle + (SOLENOID_DELAY / u16Angle_Clock_rate);        
    #endif
    #endif 
                    
    /* Calculate starting point (angle and previous tooth) of pulse for primary coil */
    if(u16Spark_Dwell_Angle >= u16Spark_Start_Angle)
    {    
        //This should never be the case as it means the dwell time is greater than the time
        //for a revolution.  If this case executes, dwell time needs to be changed or 
        //actively managed through RPM based lookup.  
        u16Spark_Start_Angle = 360 - (u16Spark_Dwell_Angle - u16Spark_Start_Angle);
    }
    
    else
    {            
        //Calculate the starting angle for the dwell event.
        u16Spark_Start_Angle = u16Spark_Start_Angle - u16Spark_Dwell_Angle;
    }
            
    //Calculate the tooth that corresponds to the start of the dwell event.   
    u16Spark_Dwell_Tooth = u16Spark_Start_Angle / DEGREES_PER_TOOTH;
           
      
    /* Calculate angle error to properly estimate the pulse start */
    u16Spark_Dwell_Offset = u16Spark_Start_Angle - 
                    (u16Spark_Dwell_Tooth * DEGREES_PER_TOOTH);
                    
                    
    if(!u16Spark_Dwell_Tooth)
    {
        if(u8Crank_State==SYNCHRONIZED_4C){          
          /* Adjust if calculated tooth is zero- synchronized to 4 stroke */
          u16Spark_Dwell_Tooth = NUMBER_OF_TEETH_4C;            
        }else{
          /* Adjust if calculated tooth is zero- not synchronized to 4 stroke */
          u16Spark_Dwell_Tooth = NUMBER_OF_TEETH;            
        }
    
    }        
      
    /* If error is 0, go back another tooth and dwell is a full tooth period */        
    if(!u16Spark_Dwell_Offset)    
    {
        u16Spark_Dwell_Tooth --; 
        
            if(!u16Spark_Dwell_Tooth){
              if(u8Crank_State==SYNCHRONIZED_4C){          
                /* Adjust if calculated tooth is zero- synchronized to 4 stroke */
                u16Spark_Dwell_Tooth = NUMBER_OF_TEETH_4C;            
              }
              else
              {
              /* Adjust if calculated tooth is zero- not synchronized to 4 stroke */
                u16Spark_Dwell_Tooth = NUMBER_OF_TEETH;            
              }
            }
        u16Spark_Dwell = DEGREES_PER_TOOTH;     
    }               
}

/*******************************************************************************/


