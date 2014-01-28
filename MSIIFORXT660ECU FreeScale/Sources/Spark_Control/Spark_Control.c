/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Spark_Control.c
\brief      Single and dual spark control.
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

/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** Crank sensing definitions and function prototypes */
#include "Crank_Sensing.h"
/** Spark control function prototypes */
#include "Spark_Control.h"
/** Timer module initialization prototypes and definitions */
#include "Timers.h"
/** Application definitions */
#include "Application Definitions.h" 

/* Ignition spark pulse variables */
UINT16 u16Current_Spark1_Start = 0;
UINT16 u16Current_Spark1_Dwell = 0; 
UINT16 u16Current_Spark1_Dwell_Tooth = 0;
UINT16 u16Current_Spark1_Dwell_Offset = 0;

extern UINT16 u16Next_Spark1_Start;
extern UINT16 u16Next_Spark1_Dwell;
extern UINT16 u16Next_Spark1_Dwell_Tooth;
extern UINT16 u16Next_Spark1_Dwell_Offset;


#ifdef TWO_CYLINDER
UINT16 u16Current_Spark2_Start = 0; 
UINT16 u16Current_Spark2_Dwell = 0;
UINT16 u16Current_Spark2_Dwell_Tooth = 0;
UINT16 u16Current_Spark2_Dwell_Offset = 0;

extern UINT16 u16Next_Spark2_Start;
extern UINT16 u16Next_Spark2_Dwell;
extern UINT16 u16Next_Spark2_Dwell_Tooth;
extern UINT16 u16Next_Spark2_Dwell_Offset;
#endif

/* Local state of spark control state machines */ 
UINT8 u8Spark1_State = SPARK_CTRL_INACTIVE;
UINT8 u8Spark2_State = SPARK_CTRL_INACTIVE;

/* Overall state for fuel controller */
UINT8 u8Spark_Controller_Mode = OFF;

// Counter for spark events on a cycle by cycle basis
UINT8 u8Spark1_Event_Counter = 0;
#ifdef TWO_CYLINDER
UINT8 u8Spark2_Event_Counter = 0;
#endif

/* Spark map arrays */
extern const UINT16 Spark_Timing_Map[SPARK_RPM_POINTS][SPARK_LOAD_POINTS];
extern UINT16 Spark_Timing_Map_RAM[SPARK_RPM_POINTS][SPARK_LOAD_POINTS];


extern UINT16 Spark_Load_Map_Values[SPARK_LOAD_POINTS];
extern UINT16 Spark_RPM_Map_Values[SPARK_RPM_POINTS];


/* Variables related to crankshaft sensing */
extern u16Current_Tooth_Time;
extern UINT8 u8Teeth_Counter;
extern UINT16 u16Current_Period;
extern UINT16 u16Angle_Clock_rate; 
extern UINT8 u8Crank_State;

/* Spark timing modifiers */
extern unsigned int u16Spark_Modifier;


//Test variables.
extern unsigned int Spark_Advance;
extern unsigned int Spark_Retard;


/*******************************************************************************/
/**
* \brief    Set the spark controller state
* \author   Jaime Orozco 
* \param    u8State: ENABLED/ DISABLED
* \return   void
*/
void vfnSet_Spark_Controller(UINT8 u8State_Request)
{  
    if((u8State_Request == ENABLED) && (u8Spark_Controller_Mode == OFF))
    {
        /* Channel 2 enabled as output compare for spark 1 generation */            
        // Not supported in S12T64 OCPD_OCPD2 = 0;
        TIOS_IOS2 = 1;     
        TCTL2_OM2 = 1;             
        TCTL2_OL2 = 0;      /* Clear on output compare event */          
        CFORC_FOC2 = 1;     /* Force output event */
                      
                      
        #ifdef TWO_CYLINDER
                        
        /*Channel 3 enabled as output compare for spark 2 generation */            
        OCPD_OCPD3 = 0;
        TIOS_IOS3 = 1;     
        TCTL2_OM3 = 1;                    
        TCTL2_OL3 = 0;      /* Clear on output compare event */                
        CFORC_FOC3 = 1;     /* Force output event */         
                  
        #endif            
                 
                 
        /* Update spark controller status */
        u8Spark_Controller_Mode = ON;
        
        /* Start the fuel control states machines */
        u8Spark1_State = READY_TO_SCHEDULE_SPARK;
        u8Spark2_State = READY_TO_SCHEDULE_SPARK;
    }
    
    if((u8State_Request == DISABLED) && (u8Spark_Controller_Mode == ON))
    {    
        /* Update fuel controller status */
        u8Spark_Controller_Mode = OFF;
        
    /* Controller will be effectively disabled when fuel events are scheduled */
    }
}     

/*******************************************************************************/
/**
* \brief    Disable timers to allow direct control of spark coils
* \author   Jaime Orozco 
* \param    void
* \return   void
*/ 
void vfnDisable_Spark1_Timer(void)
{
    /* Interrupt disabled */
    SPARK_PULSE1_INTERRUPT(DISABLED);     
    
    /* Channel 2 disconnected from output compare module */             
    // Not supported in S12T64 OCPD_OCPD2 = 1;
    TCTL2_OM2 = 0;  /* Used instead of OCPD_OCPD2 = 1; */                  
    TCTL2_OL2 = 0;  /* Used instead of OCPD_OCPD2 = 1; */ 
    TIOS_IOS2 = 0; 
       
    /* Spark coil 1 turned off */
    IGNIN1 = OFF;
}

#ifdef TWO_CYLINDER
void vfnDisable_Spark2_Timer(void)
{
    /* Interrupt disabled */
    SPARK_PULSE2_INTERRUPT(DISABLED);     
    
    /* Channel 3 disconnected from output compare module */             
    OCPD_OCPD3 = 1;
    TIOS_IOS3 = 0; 
    
    /* Spark coil 2 turned off */
    IGNIN2 = OFF;
}
#endif

/*******************************************************************************/
/**
* \brief    Direct control of signals to spark coils
* \author   Jaime Orozco 
* \param    u8Injector: SPARK_COIL_1, SPARK_COIL_2
            u8State: ON/ OFF 
* \return   void
*/
void vfnSpark_Direct_Control(UINT8 u8Coil, UINT8 u8Coil_State)
{
    if((u8Spark1_State == SPARK_CTRL_INACTIVE) && (u8Coil == SPARK_COIL_1))
    {                   
        IGNIN1 = u8Coil_State;    
    }
    
    #ifdef TWO_CYLINDER          
    if((u8Spark2_State == SPARK_CTRL_INACTIVE) && (u8Coil == SPARK_COIL_2)) 
    {                       
        IGNIN2 = u8Coil_State;                                  
    }
    #endif
}

/*******************************************************************************/
/**
* \brief    Copies Spark timing map from Flash to RAM
* \author   OH 
* \param    Void
* \return   Void
*/

void vfnSpark_Map_CopytoRAM(void)
{
UINT8 u8Counter_1 = 0;
UINT8 u8Counter_2 = 0;

   for(u8Counter_1 = 0; u8Counter_1 < SPARK_RPM_POINTS; u8Counter_1++)
   {
      for(u8Counter_2 = 0; u8Counter_2 < SPARK_LOAD_POINTS; u8Counter_2++)
       {    
          Spark_Timing_Map_RAM[u8Counter_2][u8Counter_1] = 
          Spark_Timing_Map[u8Counter_2][u8Counter_1];    
       }
   }
}

/*******************************************************************************/
/**
* \brief    Read spark timing control map from Flash
* \author   OH
* \param    void
* \return   void
*/
UINT16 u16Read_Spark_Map(UINT16 u16RPM_Input, UINT16 u16Load_Input)
{
    static UINT16 u16Load;
    static UINT16 u16RPM;
    static unsigned int temp;
    /* Obtain index of best match for input data within map values */
    u16Load = u16Interpolation(u16Load_Input, Spark_Load_Map_Values, SPARK_LOAD_POINTS);

    u16RPM = u16Rev_Interpolation(u16RPM_Input, Spark_RPM_Map_Values, SPARK_RPM_POINTS);
    
    
    temp =  Spark_Timing_Map[u16RPM][u16Load];
    return (Spark_Timing_Map[u16RPM][u16Load]); 
}


/*******************************************************************************/
/**
* \brief    Update spark timing variables
* \author   Jaime Orozco 
* \param    void
* \return   void
*/
void vfnUpdate_Current_Spark1_Params(void)
{  
    u16Current_Spark1_Start = u16Next_Spark1_Start; 
    u16Current_Spark1_Dwell = u16Next_Spark1_Dwell;
    u16Current_Spark1_Dwell_Tooth = u16Next_Spark1_Dwell_Tooth; 
    u16Current_Spark1_Dwell_Offset = u16Next_Spark1_Dwell_Offset;
}


#ifdef TWO_CYLINDER   
     
void vfnUpdate_Current_Spark2_Params(void)
{    
    u16Current_Spark2_Start = u16Next_Spark2_Start; 
    u16Current_Spark2_Dwell = u16Next_Spark2_Dwell;
    u16Current_Spark2_Dwell_Tooth = u16Next_Spark2_Dwell_Tooth;
    u16Current_Spark2_Dwell_Offset = u16Next_Spark2_Dwell_Offset;
}      
        
#endif


/*******************************************************************************/
/**
* \brief    Change the Spark parameters from a 360 degree process to a 720 degree
*  process.  Called when the crank state machine gets synchronized to the valves. 
* \author   Jesse Beeker 
* \param    void
* \return   void
*/

#ifdef FOUR_STROKES
void vfnSpark_4C_Convert(void){

//Convert cylinder 1
//Change Current_Spark1 Parameters to 4 cycle
//If the Spark1 reference angle for 4 cycle sync is on the second revolution,
//then we need to add a revolution the current Spark1 parameters.
  if(SPARK1_REF_ANGLE_4C>=360){
    //Spark1 occurs on the second revolution.
    //Change the angle for the start of the spark.
    u16Current_Spark1_Start=u16Current_Spark1_Start+360;
    //Change the angle for the dwell.
    u16Current_Spark1_Dwell=u16Current_Spark1_Dwell+360;
    //Change the tooth that is before dwell starts.
    u16Current_Spark1_Dwell_Tooth=u16Current_Spark1_Dwell_Tooth+NUMBER_OF_TEETH;
                      
    //The values were already tested against zero cases, so no need to test again.    
  }

#ifdef TWO_CYLINDER
//Convert cylinder 2
//Change Current_Spark2 Parameters to 4 cycle
//If the Spark2 reference angle for 4 cycle sync is on the second revolution,
//then we need to add a revolution the current Spark2 parameters.
  if(SPARK2_REF_ANGLE_4C>=360){
    //Spark2 occurs on the second revolution.
    //Change the angle for the start of the spark.
    u16Current_Spark2_Start=u16Current_Spark2_Start+360;
    //Change the angle for the dwell.
    u16Current_Spark2_Dwell=u16Current_Spark2_Dwell+360;
    //Change the tooth that is before dwell starts.
    u16Current_Spark2_Dwell_Tooth=u16Current_Spark2_Dwell_Tooth+NUMBER_OF_TEETH;
                      
    //The values were already tested against zero cases, so no need to test again.    
  }
#endif


}

#endif

/*******************************************************************************/

void vfnSpark1_Counter_Reset(){
  //Clear the number of spark events that occurred.
  u8Spark1_Event_Counter = 0;

}

/*******************************************************************************/
#ifdef TWO_CYLINDER
void vfnSpark2_Counter_Reset(){
  //Clear the number of spark events that occurred.
  u8Spark2_Event_Counter = 0;

}
#endif

/*******************************************************************************/

void vfnSchedule_Spark1_Pulse(void)
{
    UINT32 u32Spark1;    /* Auxiliary variable */ 

    //Get the latest spark event data
    vfnUpdate_Current_Spark1_Params();   

    /* Verify if spark controller is active */
    if(u8Spark_Controller_Mode == ON)
    {               
        if(u8Spark1_State == READY_TO_SCHEDULE_SPARK) 
        {                             
            if(u8Teeth_Counter == u16Current_Spark1_Dwell_Tooth - 1)
            { 
                //Make sure we have not already done the maximum spark events for this cycle.
                //Prevents multiple sparks for slow moving engine
                if(u8Spark1_Event_Counter < SPARK_EVENTS_NUM){
                
                  /* Compensate start of pulse using angle clock rate */
                  u16Current_Spark1_Dwell_Offset = 
                  u16Current_Spark1_Dwell_Offset * u16Angle_Clock_rate;                
             
                  /* Calculate value to be loaded on compare register */                     
                  u32Spark1 = u16Current_Tooth_Time + u16Current_Spark1_Dwell_Offset;

                  /* Compensate for overflow */
                  if(u32Spark1 > 0xFFFF)
                  {
                    //Check to make sure this time has not already happened within a minimum timer tic window.  
                    if(u32Spark1 < (UINT32)TIMER_COUNTER + 2){
                      //This time is in the past and event needs to be scheduled now.
                      u32Spark1 = (UINT32)TIMER_COUNTER + 2;
                    }else{
                      //Spark event time will be in the future after next overflow.
                      u32Spark1 = u32Spark1 - 0xFFFF;
                    }
                  
                  }else{
                    //Check to make sure the event is in the future.
                    if((UINT16)u32Spark1 < TIMER_COUNTER + 2){
                      //This time is past and the event needs to be scheduled now.
                      u32Spark1 = (UINT32)TIMER_COUNTER + 2;
                    }
                  }
             
                  SET_SPARK1_ON_NEXT_STATE();  /* Set output pin on next compare event */                

                  /* Load compare value */             
                  SPARK_PULSE1_TIMER = (UINT16)u32Spark1;
                
                  SPARK_PULSE1_INTERRUPT(ENABLED);
                
                  u8Spark1_State = WAITING_STARTING_CURRENT_FLOW;                             
                }
                
            }else if((u8Teeth_Counter == u16Current_Spark1_Dwell_Tooth)){
              //We missed the correct time to start the dwell due to tooth processing latencies.
              //Start the dwell now to avoid missing a spark event.
                             
                //Make sure we have not already done the maximum spark events for this cycle.
                //Prevents multiple sparks for slow moving engine
                if(u8Spark1_Event_Counter < SPARK_EVENTS_NUM){
                                  
                  /* Calculate value to be loaded on compare register */
                  //We want the current clock value plus a some timer tics to make sure it is in the future.                     
                  u32Spark1 = TIMER_COUNTER + 2;
        
                  /* Compensate for overflow */
                  if(u32Spark1 > 0xFFFF)
                  {
                      u32Spark1 = u32Spark1 - 0xFFFF;
                  }
             
                  SET_SPARK1_ON_NEXT_STATE();  /* Set output pin on next compare event */
                 
                  /* Load compare value */             
                  SPARK_PULSE1_TIMER = (UINT16)u32Spark1;
                
                  SPARK_PULSE1_INTERRUPT(ENABLED);
                
                  u8Spark1_State = WAITING_STARTING_CURRENT_FLOW;                             
                }
            }
            
        }
    }
        
    else 
    {
        /* Disable spark controller if it is not already inactive */
        if(u8Spark1_State != SPARK_CTRL_INACTIVE)
        {   
            vfnDisable_Spark1_Timer();             
            u8Spark1_State = SPARK_CTRL_INACTIVE;                                 
        }            
    }        
}


/*******************************************************************************/

#ifdef TWO_CYLINDER

void vfnSchedule_Spark2_Pulse(void)
{
    UINT32 u32Spark2;    /* Auxiliary variable */ 

    //Get the latest spark event data
    vfnUpdate_Current_Spark2_Params();   

    /* Verify if spark controller is active */
    if(u8Spark_Controller_Mode == ON)
    {               
        if(u8Spark2_State == READY_TO_SCHEDULE_SPARK) 
        {                             
            if(u8Teeth_Counter == u16Current_Spark2_Dwell_Tooth - 1)
            { 
                //Make sure we have not already done the maximum spark events for this cycle.
                //Prevents multiple sparks for slow moving engine
                if(u8Spark2_Event_Counter < SPARK_EVENTS_NUM){
                
                  /* Compensate start of pulse using angle clock rate */
                  u16Current_Spark2_Dwell_Offset = 
                  u16Current_Spark2_Dwell_Offset * u16Angle_Clock_rate;                
             
                  /* Calculate value to be loaded on compare register */                     
                  u32Spark2 = u16Current_Tooth_Time + u16Current_Spark2_Dwell_Offset;

                  /* Compensate for overflow */
                  if(u32Spark2 > 0xFFFF)
                  {
                    //Check to make sure this time has not already happened within a minimum timer tic window.  
                    if(u32Spark2 < (UINT32)TIMER_COUNTER + 2){
                      //This time is in the past and event needs to be scheduled now.
                      u32Spark2 = (UINT32)TIMER_COUNTER + 2;
                    }else{
                      //Spark event time will be in the future after next overflow.
                      u32Spark2 = u32Spark2 - 0xFFFF;
                    }
                  
                  }else{
                    //Check to make sure the event is in the future.
                    if((UINT16)u32Spark2 < TIMER_COUNTER + 2){
                      //This time is past and the event needs to be scheduled now.
                      u32Spark2 = (UINT32)TIMER_COUNTER + 2;
                    }
                  }
             
                  SET_SPARK2_ON_NEXT_STATE();  /* Set output pin on next compare event */                

                  /* Load compare value */             
                  SPARK_PULSE2_TIMER = (UINT16)u32Spark2;
                
                  SPARK_PULSE2_INTERRUPT(ENABLED);
                
                  u8Spark2_State = WAITING_STARTING_CURRENT_FLOW;                             
                }
                
            }else if((u8Teeth_Counter == u16Current_Spark2_Dwell_Tooth)){
              //We missed the correct time to start the dwell due to tooth processing latencies.
              //Start the dwell now to avoid missing a spark event.
                             
                //Make sure we have not already done the maximum spark events for this cycle.
                //Prevents multiple sparks for slow moving engine
                if(u8Spark2_Event_Counter < SPARK_EVENTS_NUM){
                                  
                  /* Calculate value to be loaded on compare register */
                  //We want the current clock value plus a some timer tics to make sure it is in the future.                     
                  u32Spark2 = TIMER_COUNTER + 2;
        
                  /* Compensate for overflow */
                  if(u32Spark2 > 0xFFFF)
                  {
                      u32Spark2 = u32Spark2 - 0xFFFF;
                  }
             
                  SET_SPARK2_ON_NEXT_STATE();  /* Set output pin on next compare event */
                 
                  /* Load compare value */             
                  SPARK_PULSE2_TIMER = (UINT16)u32Spark2;
                
                  SPARK_PULSE2_INTERRUPT(ENABLED);
                
                  u8Spark2_State = WAITING_STARTING_CURRENT_FLOW;                             
                }
            }
            
        }
    }
        
    else 
    {
        /* Disable spark controller if it is not already inactive */
        if(u8Spark2_State != SPARK_CTRL_INACTIVE)
        {   
            vfnDisable_Spark2_Timer();             
            u8Spark2_State = SPARK_CTRL_INACTIVE;                                 
        }            
    }        
}

#endif

/*******************************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Spark1_Control_Isr(void)
{
  UINT16 u16Temp = 0;
  UINT32 u32Width_Spark1 = 0;

  if(u8Spark1_State == WAITING_IGNITION_TIME) 
  {  
   /* Ingition signal IGNIN1 is OFF at this moment */       
   
   //Spark event has occurred.  Increase event count.
   u8Spark1_Event_Counter ++;
   
   //Disable output compare interrupt.
   SPARK_PULSE1_INTERRUPT(DISABLED); 
   
   /* Update current spark control values 
   Redundant as done on each tooth.*/
    vfnUpdate_Current_Spark1_Params();   
   
   u8Spark1_State = READY_TO_SCHEDULE_SPARK;                
  }


  if(u8Spark1_State == WAITING_STARTING_CURRENT_FLOW) 
  {     
     /* Ingition signal IGNIN1 is ON at this moment */
                                                    
    #ifdef DWELL_ANGLE
        u32Width_Spark1 = (u16Angle_Clock_rate * DWELL_ANGLE) +
                          SOLENOID_DELAY + SPARK_PULSE1_TIMER;          
    #else        
    #ifdef DWELL_TIME
        u32Width_Spark1 = DWELL_TIME + SPARK_PULSE1_TIMER; 
    #endif
    #endif  
    
    /* Compensate for overflow */
    if(u32Width_Spark1 > 0xFFFF)
    {
        u32Width_Spark1 = u32Width_Spark1 - 0xFFFF;
    }
    
    SPARK_PULSE1_TIMER = (UINT16)u32Width_Spark1;
    
    /* Clear output pin on next compare event */  
    CLEAR_SPARK1_ON_NEXT_STATE(); 
    
    u8Spark1_State = WAITING_IGNITION_TIME;            
  }
   
    return ;          
}
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Spark2_Control_Isr(void)
{
#ifdef TWO_CYLINDER

  UINT16 u16Temp = 0;
  UINT32 u32Width_Spark2 = 0;
  
  if(u8Spark2_State == WAITING_IGNITION_TIME) 
  {
   /* Ingition signal IGNIN2 is OFF at this moment */   

   //Spark event has occurred.  Increase event count.
   u8Spark2_Event_Counter ++;
   
   SPARK_PULSE2_INTERRUPT(DISABLED);
   
   /* Update current spark control values 
   Redundant as it is done on each tooth.*/
    vfnUpdate_Current_Spark2_Params();  
      
   u8Spark2_State = READY_TO_SCHEDULE_SPARK;       
  }


  if(u8Spark2_State == WAITING_STARTING_CURRENT_FLOW) 
  {                                      
    #ifdef DWELL_ANGLE
        u32Width_Spark2 = (u16Angle_Clock_rate * DWELL_ANGLE) +
                          SOLENOID_DELAY + SPARK_PULSE2_TIMER;         
    #else    
    #ifdef DWELL_TIME
        u32Width_Spark2 = DWELL_TIME + SPARK_PULSE2_TIMER; 
    #endif
    #endif 
    
    /* Compensate for overflow */
    if(u32Width_Spark2 > 0xFFFF)
    {
        u32Width_Spark2 = u32Width_Spark2 - 0xFFFF;
    } 
    
    SPARK_PULSE2_TIMER = (UINT16)u32Width_Spark2; 
    
    /* Clear output pin on next compare event */  
    CLEAR_SPARK2_ON_NEXT_STATE();
    
    u8Spark2_State = WAITING_IGNITION_TIME;        
  }

    return ;    
#endif      
}
#pragma CODE_SEG DEFAULT


/*******************************************************************************/
/**
* \brief    Interpolation by successive aproximation
* \author   Jaime Orozco
* \param    u16Input_Data: Data to be searched (approximated) within array  \
            au16Data_array: Array with points defined for control map       \
            u16Size_of_Array: Size of points array    
* \return   u16Index: Index of best match for u16Input_Data 
*/
UINT16 u16Interpolation(UINT16 u16Input_Data, 
                        UINT16 *au16Data_array, UINT16 u16Size_of_Array)
{   
    UINT16 u16Index;    /* Index of data to be tested */    
    UINT16 u16Limit;    /* Range limit */
    UINT16 u16Offset;   /* Offset to define next range */
    
    /* Set the first searched index to the middle position within array */
    u16Index = u16Size_of_Array >> 1;    
    
    /* Initial range limit is the last index of the data array */
    u16Limit = u16Size_of_Array - 1;
    
    /* Next range will be approximately half of current range */
    //Use plus 1 to accomodate for non binary array sizes.  
    u16Offset = (u16Size_of_Array >> 1);
    //Must maintain an range of at least 1 to go through interpolation
    if(u16Offset == 0){
      //Set offset to 1 to go through interpolation at least once.
      u16Offset = 1;  
    }
    //If there is only one element in the array, no need to search.  
    if(u16Size_of_Array == 1){
      //Break the search loop before it happens.
      u16Offset = 0;
    }
    
    /* Successive aproximation is used to locate the closest match to Input_Data */ 

    /* Repeat while range limit is higher than current index */
    while(u16Offset>0)     
    {     
        //Limit of array search resolution has not been reached.
        /* Compare input data against a given value within array */
        if(u16Input_Data < au16Data_array[u16Index])
        {                    
            //Input data is less than this array index.
            //Reduce the array index by the offset
            //Prevent array indexing overrun.
            //Make sure that you get a smaller number when you subtract.
            //Unsigned math handles below zero case.  
            
            if(u16Index < (u16Index - u16Offset)){
              //The offset would result in a negative index.  
              //Set it to first element of the array.
              //Even if it is not the correct value it will naturally correct.
              u16Index = 0;  
            }else{
              //Index is valid use it.
              u16Index = u16Index - u16Offset;
            }
        } 
        else if(u16Input_Data > au16Data_array[u16Index])
        {
            //Input data is greater than this array index.
            /* Go to higher portion of array */     
            //Increase the array index by the offset
            //Prevent array indexing overrun.
            //Make sure it is less than the size of the array and
            //the addition makes it a larger number.
            if(((u16Index + u16Offset) > u16Limit)&&(u16Index < (u16Index + u16Offset))){
              //The offset would result in an out of bounds index.  
              //Set it to last element of the array.
              //Even if it is not the correct value it will naturally correct.
              u16Index = u16Limit;  
            }else{
              //Index is valid use it.
              u16Index = u16Index + u16Offset;
            }
        }else{
          //They are equal.  Use this index.
          //End the procedure by breaking the while loop.
          u16Offset = 0;  
        
        }
        
        
        
        //Reduce the size of the array index offset to half.
        if(u16Offset <=1){
          //The offset was 1 and this was the last iteration.
          //Break while loop.
          u16Offset = 0;
        }else if(u16Offset ==3){
          //Special case needed to create an offset of 2.
          u16Offset = 2;
        }else if(u16Offset == 2){
          //Special case for offset of 2 to allow loop to break.
          u16Offset = 1;
        }else{
          
          //Just shift to create a divide by 2.
          u16Offset = (u16Offset >>1)+1;
        }
    }

    /**************************Interpolation process*************************/
    //Basic
    //Force the index to the closest value.
    //Real application should do a more complex algorithm.
    //This is just an example that will work.  
    /************************************************************************/
    
    //Now the index is narrowed down to within 1 index step.
    //Need to findout which two indices it is between.
    
    if(au16Data_array[u16Index] < u16Input_Data){
      //The value is between the current index value and the next higher index.
    
      //Determine which value it is closer to by looking at the differences from 
      //the input data.
      //Make sure we are not at the end of the array
      if(u16Index==u16Limit){
        //This is the end of the array.  Input data is greater than last element.
        //Use the last element.
        u16Index = u16Limit;
      
      }else if((au16Data_array[u16Index+1] - u16Input_Data)<(u16Input_Data-au16Data_array[u16Index])){
        //The next value higher in the array is closer.
        u16Index = u16Index++;
      
      }else{
        //The current array value is closer.  
        u16Index = u16Index;
      }
    
    
    }else if(au16Data_array[u16Index] > u16Input_Data){
      //The value is between the current index value and the next lower index.
      
      //Determine which value it is closer to by looking at the differences from 
      //the input data.
      //Make sure that this is not the first element in the array.
      if(u16Index == 0){
        //The input data is less than the first element of the array.  
        //Use the first element of the array.
        u16Index = 0;
      
      }else if((u16Input_Data-au16Data_array[u16Index-1])<(au16Data_array[u16Index] - u16Input_Data)){
        //The next value lower in the array is closer.
        u16Index = u16Index--;
      
      }else{
        //The current array value is closer.  
        u16Index = u16Index;
      }
    
    }else{
      //Data falls right on the index.  Rare event.
      //No adjustment is needed.  This is the index we want to use.  
      u16Index = u16Index;
    }

    /* Return position of value closest to input data */
    return (u16Index);                                                 
}

/*******************************************************************************/
/**
* \brief    Interpolation by successive aproximation-Reverse
* \author   Jaime Orozco
* \param    u16Input_Data: Data to be searched (approximated) within array  \
            au16Data_array: Array with points defined for control map,      \
            u16Size_of_Array: Size of points array    
* \return   u16Index: Index of best match for u16Input_Data 
*/
UINT16 u16Rev_Interpolation(UINT16 u16Input_Data, 
                        UINT16 *au16Data_array, UINT16 u16Size_of_Array)
{   
    UINT16 u16Index;    /* Index of data to be tested */    
    UINT16 u16Limit;    /* Range limit */
    UINT16 u16Offset;   /* Offset to define next range */
    

    /* Middle position within array */
    u16Index = u16Size_of_Array >> 1;    
    
    /* Initial range limit is the higher extreme of data array */
    u16Limit = u16Size_of_Array - 1;
    
    /* Next range will be approximately half of current range */
    //Use plus 1 to accomodate for non binary array sizes.  
    u16Offset = (u16Size_of_Array >> 1);
    //Must maintain an range of at least 1 to go through interpolation
    if(u16Offset == 0){
      //Set offset to 1 to go through interpolation at least once.
      u16Offset = 1;  
    }
    //If there is only one element in the array, no need to search.  
    if(u16Size_of_Array == 1){
      //Break the search loop before it happens.
      u16Offset = 0;
    }
    
    /* Successive aproximation is used to locate the closest match to Input_Data */ 
    /***********************Reverse Algorithm***********************/
    /* Repeat while range limit is higher than current index */
    while(u16Offset>0)     
    {     
        //Limit of array search resolution has not been reached.
        /* Compare input data against a given value within array */
        if(u16Input_Data < au16Data_array[u16Index])
        {                    
            //Input data is less than this array index.
            //Increase the array index by the offset
            //Prevent array indexing overrun.
            //Make sure it is less than the size of the array and
            //the addition makes it a larger number.
            if(((u16Index + u16Offset) > u16Limit)&&(u16Index < (u16Index + u16Offset))){
              //The offset would result in an out of bounds index.  
              //Set it to last element of the array.
              //Even if it is not the correct value it will naturally correct.
              u16Index = u16Limit;  
            }else{
              //Index is valid use it.
              u16Index = u16Index + u16Offset;
            }

        } 
        else if(u16Input_Data > au16Data_array[u16Index])
        {
            //Input data is greater than this array index.
            //Decrease the array index by the offset
            //Prevent array indexing overrun.
            //Make sure that you get a smaller number when you subtract.
            //Unsigned math handles below zero case.  
            
            if(u16Index < (u16Index - u16Offset)){
              //The offset would result in a negative index.  
              //Set it to first element of the array.
              //Even if it is not the correct value it will naturally correct.
              u16Index = 0;  
            }else{
              //Index is valid use it.
              u16Index = u16Index - u16Offset;
            }
        }else{
          //They are equal.  Use this index.
          //End the procedure by breaking the while loop.
          u16Offset = 0;  
        
        }
        
        //Reduce the size of the array index offset to half.
        if(u16Offset <=1){
          //The offset was 1 and this was the last iteration.
          //Break while loop.
          u16Offset = 0;
        }else if(u16Offset ==3){
          //Special case needed to create an offset of 2.
          u16Offset = 2;
        }else if(u16Offset == 2){
          //Special case for offset of 2 to allow loop to break.
          u16Offset = 1;
        }else{
          
          //Just shift to create a divide by 2.
          u16Offset = (u16Offset >>1)+1;
        }
        
    }

    /**************************Interpolation process*************************/
    //Basic
    //Force the index to the closest value.
    //Real application should do a more complex algorithm.
    //This is just an example that will work.  
    /************************************************************************/
    
    //Now the index is narrowed down to within 1 index step.
    //Need to findout which two indices it is between.
    
    if(au16Data_array[u16Index] < u16Input_Data){
      //The value is between the current index value and the next higher index.
    
      //Determine which value it is closer to by looking at the differences from 
      //the input data.
            //Make sure we are not at the end of the array
      if(u16Index==u16Limit){
        //This is the end of the array.  Input data is greater than last element.
        //Use the last element.
        u16Index == u16Limit;
      
      }else if((au16Data_array[u16Index+1] - u16Input_Data)<(u16Input_Data-au16Data_array[u16Index])){
        //The next value higher in the array is closer.
        u16Index = u16Index++;
      
      }else{
        //The current array value is closer.  
        u16Index = u16Index;
      }
    
    
    }else if(au16Data_array[u16Index] > u16Input_Data){
      //The value is between the current index value and the next lower index.
      
      //Determine which value it is closer to by looking at the differences from 
      //the input data.
            //Make sure that this is not the first element in the array.
      if(u16Index == 0){
        //The input data is less than the first element of the array.  
        //Use the first element of the array.
        u16Index = 0;
      
      }else if((u16Input_Data-au16Data_array[u16Index-1])<(au16Data_array[u16Index] - u16Input_Data)){
        //The next value lower in the array is closer.
        u16Index = u16Index--;
      
      }else{
        //The current array value is closer.  
        u16Index = u16Index;
      }
    
    
    }else{
      //Data falls right on the index.  Rare event.
      //No adjustment is needed.  This is the index we want to use.  
      u16Index = u16Index;
    }
    
    /* Next range will be approximately half of current range */
    /* Return position of value closest to input data */
    return (u16Index);                                                 
}

/*******************************************************************************/
