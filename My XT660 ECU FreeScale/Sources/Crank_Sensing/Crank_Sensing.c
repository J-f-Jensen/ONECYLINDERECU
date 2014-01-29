/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       Crank_Sensing.c
\brief      Crankshaft sensing state machine
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     Jaime Orozco
\ThirdParty Omar Hernandez/Rodrigo Ruiz (NACURI)
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

/** Seabreeze Emulator Compilation Options */
#include "Seabreeze_Emulator.h"
/** Crank sensing definitions and function prototypes */
#include "Crank_Sensing.h"
/** Spark control function prototypes */
#include "Spark_Control.h"
/** Fuel control function prototypes */
#include "Fuel_Control.h"
/** ADC definitions and functions */
#include "ADC.h"
/** Timer module definitions */
#include "Timers.h" 
/** Manifold Absolute Pressure function prototypes */
#include "MAP.h"
/** Application definitions */
#include "Application Definitions.h" 

/* Tooth edge related variables */ 
UINT16  u16Current_Tooth_Time = 0; 
UINT16  u16Previous_Tooth_Time = 0;
UINT16  u16Current_Period = 1;
UINT16  u16Previous_Period = 1;

/* Tooth noise variable, counts noise related interrupt for crank state machine */
UINT16 u16Tooth_Noise_Counter = 0;

/* Auxiliar variables for period validation */
UINT32 u32Period0  = 0;
UINT32 u32Period1  = 0;  
    
/* Initial State */    
UINT8 u8Crank_State = TOOTH_INIT; 

UINT8 u8Teeth_Counter = 0;
UINT16 u16Last_Timeout = 0;
UINT8 u8Engine_Rotation_Synchronization_counter = 0; 
UINT16 u16Engine_Position_Degrees = 0x0000;  
UINT16 u16Angle_Clock_rate = 0;  
       
/** Array to store tooth period data for two engine revolutions */
#ifdef FOUR_STROKES
  UINT16 au16Prior_Periods[2 * NUMBER_OF_TEETH_4C];
#else
  UINT16 au16Prior_Periods[2 * NUMBER_OF_TEETH];
#endif

/** Index to store period data */
UINT8 u8Period_Counter = 0;


//Index for looking at the MAP data buffer.
UINT8 u8Buffer_Counter;

/** Buffer used to collect MAP data */
#ifdef MAP
  #ifdef Analog_Data_8
    extern UINT8  MAP_Data_Buffer[MAP_BUFFER_SIZE];
  #else 
    extern UINT16 MAP_Data_Buffer[MAP_BUFFER_SIZE];  
  #endif
#endif


//Flag for indicating a positive test for intake pressure signature.
UINT8 Signature_Valid;


/** Engine speed (RPM) */
extern unsigned int Engine_Speed;
/** Load */
extern unsigned int LOAD;

extern UINT16 u16Current_Spark1_Dwell_Tooth;
extern UINT8 u8Spark1_State;

/** Clears the counter for the number of spark events per cycle*/
extern void vfnSpark1_Counter_Reset();

/** Functions to convert from 2 cycle to 4 cycle process*/
#ifdef FOUR_STROKES
extern void vfnSpark_4C_Convert();
extern void vfnFuel_4C_Convert();
#endif


/*******************************************************************************/

void vfnInit_Crank_Sensing(void)     
{   
    vfnTimerModule_Init(PREESCALER_VALUE);
    
     /* Channel 1 as input capture for crankshaft tooth edge detection */ 
    TIOS_IOS1 = 0;
                              
    /* Channel 5 as output compare for missing tooth interrupt generation */
    TIOS_IOS5 = 1;
    
// Not supported in S12T64
//    OCPD_OCPD5 = 1; /* Channel not connected to output pin */                    
    
    // This is used intead of OCPD_OCPD5 = 1;
    TCTL1_OM5 = 0;
    TCTL1_OL5 = 0;
    
    
    /* Channel 4 as output compare for timeout interrupt */
    TIOS_IOS4 = 1;
     
// Not supported in S12T64
//    OCPD_OCPD4 = 1; /* Channel not connected to output pin */                
    
    // This is used intead of OCPD_OCPD4 = 1; 
    TCTL1_OM4 = 0;
    TCTL1_OL4 = 0;
    
                                                                           
    /* Teeth are detected on falling edge or rising edge depending on  */                                                                       
    /* the system configuration defined in the application header file.*/   
                        
    #ifdef DETECT_ON_RISING_EDGE
    TCTL4 = (TCTL4 & ~(TCTL4_EDG1A_MASK | TCTL4_EDG1B_MASK)) | TCTL4_EDG1A_MASK;
    #else
    #ifdef DETECT_ON_FALLING_EDGE
    TCTL4 = (TCTL4 & ~(TCTL4_EDG1A_MASK | TCTL4_EDG1B_MASK)) | TCTL4_EDG1B_MASK;    
    #endif
    #endif 
                                                               
     
    /* CRANKSHAFT_INTERRUPT = ENABLED;    Enable tooth edge interrupt */ 
    CRANKSHAFT_INTERRUPT(ENABLED);
}


/*******************************************************************************/


#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt Crank_State_Machine_Isr(void)
{                         
    //TDC_LED = OFF_STATE; 
    
    //Test code
    #if HARDWARE == EMULATOR
    //Toggle TDC LED every tooth 
    if(TDC_LED ==OFF_STATE){
      TDC_LED =ON_STATE;
    
    }else{
      TDC_LED=OFF_STATE;
    }
    #endif
    
    /* Disable timeout interrupt */
    TIMEOUT_INTERRUPT(DISABLED);       
       
    switch(u8Crank_State)
    {
    	case FIRST_EDGE:
        {
			    /* First Edge Task List : Record time of tooth edge occurrence */
			    u16Previous_Tooth_Time = CRANKSHAFT_TIMER; 

          /* Default value is used for starting conditions where only the first 
          tooth has been detected */        
                
          u32Period1 = (UINT32)(DEFAULT_TIME_CRANKSHAFT_TIMEOUT * CRANKSHAFT_TIMEOUT_PERCENTAGE);
          u32Period1 = u32Period1 / 100;  
            
          /* Set timeout period for next edge */
          u16Last_Timeout = DEFAULT_TIME_CRANKSHAFT_TIMEOUT + (UINT16)(u32Period1);

                                                                    
          #ifdef FOUR_STROKES
          /* Measure MAP, if four-cycle */
          #endif
        
          u8Crank_State = FIRST_PERIOD;   /* Go to next state */ 
			
          break;
        }
                
        
        case FIRST_PERIOD:             
        {   
            /* Calculate and validate that tooth period is within limits */     
            if(u8Calculate_Tooth_Period())
            {                       
                //Store the tooth period to the array.
                vfnTooth_Period_Store();
                
                vfnSet_Period_Timeout();    /* Set period timeout for next edge */ 
                
                #ifdef FOUR_STROKES
                /*  Measure MAP, if four-cycle */
                #endif
                                                                      
                u8Crank_State = TESTING_FOR_GAP;    /* Go to next state */           
            } 
            else
            {   
                /* Return to first edge if period is outside the limits */ 
                vfnGoTo_Crank_FirstEdge();                              
            }            
                                                                                       
            break;       
        }
     
        
        case TESTING_FOR_GAP:
        {            
            // Verify that tooth period is within valid limits and tolerance or it is 
            //the missing tooth.
            if(u8Calculate_Tooth_Period() && u8Valid_Period() || u8Missing_Tooth_Gap())
            {              
                //Store the tooth period to the array.
                vfnTooth_Period_Store();

                /* Validate if period corresponds to missing tooth */                                                                
                if(u8Missing_Tooth_Gap())
                {                                                       
                    u8Teeth_Counter = 0;    /* Start teeth counter */                   
                    
                    if(u8Engine_Rotation_Synchronization_counter < 0xFF)
                    {                        
                        u8Engine_Rotation_Synchronization_counter++; 
                    }                                                                                                                        
                    
                    #ifdef FOUR_STROKES
                    /* First Period Task List : 6 Measure MAP, if four-cycle */
                    #endif
                                         
                    u8Crank_State = VALIDATING_GAP; /* Go to next state */                                                      
                }
                    
                else  /* No mising tooth gap, validate that timeout didn't ocurred */
                {                       
                    if(u16Last_Timeout < u16Current_Period) 
                    {
                        /* Discard if period was longer than timeout */ 
                        vfnGoTo_Crank_FirstEdge();      
                    }
                }
                
                vfnSet_Period_Timeout(); 
            }
                
            else
            {   
                /* Return to first edge state if period is outside the limits */ 
                vfnGoTo_Crank_FirstEdge();             
            }             
                                    
            break;       
        }
        
    
        case VALIDATING_GAP:  
        {                
            /* Verify that tooth period is within valid limits and tolerance */
            if(u8Calculate_Tooth_Period() && u8Tooth_After_Gap())
            {	                  	                          
                //Store the tooth period to the array.
                vfnTooth_Period_Store();

                if(u8Tooth_After_Gap())
                {                                                                                                              
                    //Gap has been verified.
                    //Set tooth counter to 1.
                    u8Teeth_Counter = 1;
                    
                    #ifdef FOUR_STROKES
                    /* First Period Task List : 6 Measure MAP, if four-cycle */
                    #endif                  
                                                                      
                    /* Go to synchronization state */
                    u8Crank_State = SYNCHRONIZED;                                           
                    #if HARDWARE == EMULATOR
                    SYNCH_LED = OFF_STATE;                                                                                                                
                    #endif
                }    
                else 
                {          
                    //Gap was not verified.
                    /* Verify if timeout expired */ 
                    if(u16Last_Timeout < u16Current_Period) 
                    {                                            
                        //Tooth timeout occurred.
                        /* Go to initial state */
                        vfnGoTo_Crank_FirstEdge();
                        break;          
                    } 
                    else 
                    {                                                
                        //Gap validation failed.  Continue testing for gap.
                        u8Crank_State = TESTING_FOR_GAP; 
                        #if HARDWARE == EMULATOR
                        SYNCH_LED = OFF_STATE;                             
                        #endif
                    }                                                                                             
                }
                //Set up new tooth timeout.                                                                                                                                                                                        
                vfnSet_Period_Timeout();                                               
            }
            
            else
            {   
                /* Return to first edge state if period is outside the limits */                                                                                                   
                vfnGoTo_Crank_FirstEdge();               
            }
          
            break;        
        }     
        
    
        case (SYNCHRONIZED):
        {
            /* Verify that tooth period is within valid limits and tolerance */                     
            if(u8Calculate_Tooth_Period() && u8Valid_Period())	                         
            {          
                //Store the tooth period to the array.
                vfnTooth_Period_Store();

                if(u16Last_Timeout < u16Current_Period) 
                {                
                    /* Return to first edge state if timeout expired */                                                                                                   
                    vfnGoTo_Crank_FirstEdge();    
                    break;          
                } 
                else 
                {                                                                                                                                                                                                                                   
                    
                
                //Tooth has been validated.  Determine the activity that takes place on this tooth.
                vfnIncrement_Teeth_Counter();  
                    

                //If this is a four cycle engine, testing must be done to transition to a 4 cycle 
                //synchronized state.
                #ifdef FOUR_STROKES
                
                //MAP data is continously being collected based on application header file definition.
                //Tooth based collection will gather one data point for each tooth provided that the 
                //tooth time is greater than the data collection rate.  
                
                //Reference design will need to manually collect data at each tooth
                #if HARDWARE == REFERENCE
                  #ifdef MAP_TOOTH_BASED
                  //Process MAP data
                  //Use dummy value of 5 as it will come from raw buffer not ADC result
                  vfnMAP_Monitoring(5);
                  #endif
                #endif  
                
                //Once the tooth after the last tooth used for MAP data collection has been reached,
                //the signature for advancing to 4 cycle synchronization can be detected.  
                if(u8Teeth_Counter==MAP_TOOTH_END+1){
                  //Need to add check for when MAP_TOOTH_END is the last tooth on the wheel.
                
                //Once buffer is full, look for signature.
                //Buffer is known to be full on the tooth after the last tooth that is measured.  
                //If this is the revolution and measurements have not been made, signature will fail, so no need to test to 
                //see if the buffer has valid data.  
                
                  //Init Flag to indicate result of signature check.
                  Signature_Valid=0;
            
                 //Init counter for MAP data buffer.
                 u8Buffer_Counter=0; 
                  
                 //Buffer is full.  Need to check for signature.  
                 //Only loop to size of buffer minus 1 as comparison is made between current buffer value and next buffer value.
                 while(u8Buffer_Counter<MAP_BUFFER_SIZE){
                  
                    //Look for a decreasing pressure value throughout the buffer.
                    //Drop must be greater than minimum value defined in application header file.
                    if((MAP_Data_Buffer[u8Buffer_Counter]-MAP_Data_Buffer[u8Buffer_Counter+1])>MAP_SIGNATURE_DROP_MIN){
                    //Signature is decreasing.  Continue looking for signature.
                      Signature_Valid=1;
                      //Increment the index
                      u8Buffer_Counter++;
                    }else{
                      //Signature was not correct.  End signature check by breaking the while loop.
                      u8Buffer_Counter=MAP_BUFFER_SIZE;
                      Signature_Valid=0;
                    }                   
                    
                  }//end while loop.
                  //Look at how the loop ended.
                  if(Signature_Valid==1){
                    //The intake opening signiture has been identified.  Move to four cycle synchronization.
                    
                    vfnGoTo_SYNCHRONIZED_4C();
                  }else{
                    //The intake opening signiture was not identified.  Stay in two cycle mode and continue to look for signature.  
                    u8Crank_State = SYNCHRONIZED; 

                  }
                }
                
                
                #endif

                    
                    
                    /* Angle clock calculation */                    
                    u16Angle_Clock_rate = u16Current_Period / DEGREES_PER_TOOTH;                                  
                    
                    //Schedule missing tooth interrupt.  
                    if(u8Teeth_Counter == NUMBER_OF_TEETH - 2) 
                    {
                        GAP_TIMER = u16Current_Period + CRANKSHAFT_TIMER;
                        GAP_INTERRUPT(ENABLED);       /* Enable missing tooth interrupt */                                                                                                                                                
                    }

                    if(u8Teeth_Counter == 0) 
                    {
                        GAP_INTERRUPT(DISABLED);     /* Disable missing tooth interrupt */
                    }                                                                                                                                                                                                                   


                    //Test for TDC
                    if(u8Teeth_Counter == TDC_TOOTH){
                      //Reset Spark Event Counter.
                      vfnSpark1_Counter_Reset();
                      
                      #ifdef TWO_CYLINDER
                      vfnSpark2_Counter_Reset();
                      #endif
                    }

                    /* Schedule spark events */
                    vfnSchedule_Spark1_Pulse();
                    
                    #ifdef TWO_CYLINDER
                    vfnSchedule_Spark2_Pulse();  
                    #endif  
                       
                    /* Schedule fuel pulse events */                    
                    vfnSchedule_Fuel1_Pulse(); 
                    
                    #ifdef TWO_CYLINDER
                    vfnSchedule_Fuel2_Pulse();
                    #endif                      
                
                    //Test code for misfire issue
                    if(u8Teeth_Counter == u16Current_Spark1_Dwell_Tooth){
                      if(u8Spark1_State == 1){
                        u16Tooth_Noise_Counter ++;

                      
                      }
                        
                    }
                
                }                     
                      
                vfnSet_Period_Timeout();                       
            }
            
            else
            {                                                                                                                             
                /* Return to first edge state if period is outside the limits */                                                                                                   
                vfnGoTo_Crank_FirstEdge();                 
            }
       
            break;       
        }   
        #ifdef FOUR_STROKES
        case (SYNCHRONIZED_4C):
        {
            /* Verify that tooth period is within valid limits and tolerance */                     
            if(u8Calculate_Tooth_Period()) {
              //Check to see if the change in tooth time is beyond mechanical limits.
              if(u8Valid_Period())	                         
              {          
                //Store the tooth period to the array.
                vfnTooth_Period_Store();

                //Make sure the tooth came in before a timeout based on the last tooth period
                //expired.
                if(u16Last_Timeout < u16Current_Period) 
                {                
                    /* Return to first edge state if timeout expired */                                                                                                   
                    vfnGoTo_Crank_FirstEdge();    
                    break;          
                } 
                else 
                {                                                                                                                                                                                                                                   
                                    
                //Tooth has been validated.  Determine the activity that takes place on this tooth.
                                        
                    vfnIncrement_Teeth_Counter();  
                    
                    /* Angle clock calculation */                    
                    u16Angle_Clock_rate = u16Current_Period / DEGREES_PER_TOOTH;                                  
                    
                    //Schedule the missing tooth interupt.  Need to do it 
                    //twice as two revs for 720 degree process=two missing teeth.
                    
                    if(u8Teeth_Counter == NUMBER_OF_TEETH - 2) 
                    {
                        GAP_TIMER = u16Current_Period + u16Current_Tooth_Time;
                        GAP_INTERRUPT(ENABLED);       /* Enable missing tooth interrupt */                                                                                                                                                
                    }else if(u8Teeth_Counter == NUMBER_OF_TEETH_4C - 2) 
                    {
                        GAP_TIMER = u16Current_Period + u16Current_Tooth_Time;
                        GAP_INTERRUPT(ENABLED);       /* Enable missing tooth interrupt */                                                                                                                                                
                    }

                    if(u8Teeth_Counter == 0) 
                    {
                        GAP_INTERRUPT(DISABLED);     /* Disable missing tooth interrupt */
                    }                                                                                                                                                                                                                   

                    //Test for TDC
                    if(u8Teeth_Counter == TDC_TOOTH){
                      //Reset Spark Event Counter.
                      vfnSpark1_Counter_Reset();
                      
                      #ifdef TWO_CYLINDER
                      vfnSpark2_Counter_Reset();
                      #endif
                    }
                    
                    /* Schedule spark events */
                    vfnSchedule_Spark1_Pulse();
                    
                    #ifdef TWO_CYLINDER
                    vfnSchedule_Spark2_Pulse();  
                    #endif  
                       
                    /* Schedule fuel pulse events */                    
                    vfnSchedule_Fuel1_Pulse(); 
                    
                    #ifdef TWO_CYLINDER
                    vfnSchedule_Fuel2_Pulse();
                    #endif  
                    
                }
                      
                vfnSet_Period_Timeout();                
       
              }else
              {
                //Period was not valid.  
                if(u16Current_Period == 0){
                  //Reject as noise given that mechanical limitations
                  //defined in application header file were exceeded.  
                  //Use a counter to determine look at noise through a variable.
                  u16Tooth_Noise_Counter ++;
                }else{
                  //Engine speed is drastically falling period is out of tolerance.
                  /* Return to first edge state if period is outside the limits */                                                                                                   
                  u16Tooth_Noise_Counter ++;
                  vfnGoTo_Crank_FirstEdge();                 
                }
              }
            
            }else
            {     
              //There is a serious issue with the tooth period as it corresponds to operating
              //outside engine speed limits defined in the applicaiton header file.
            
                /* Return to first edge state if period is outside the limits */                                                                                                   
                                  u16Tooth_Noise_Counter ++;
                                  u16Tooth_Noise_Counter ++;

                vfnGoTo_Crank_FirstEdge();                 
            }
       
            break;       
        }   
        #endif
        
    
        default:
        {            
            break;
        }
            
    }               
}
#pragma CODE_SEG DEFAULT


/*******************************************************************************/

void vfnGoTo_Crank_FirstEdge(void)
{         
    #if HARDWARE == EMULATOR
    SYNCH_LED = OFF_STATE;
    TDC_LED = OFF_STATE;        
    #endif
    u8Engine_Rotation_Synchronization_counter = 0; 
    u8Crank_State = FIRST_EDGE;             
    
    /* Clear tooth period historic data */
    #ifdef TWO_STROKES
    for(u8Period_Counter = 0; u8Period_Counter < 2*NUMBER_OF_TEETH; u8Period_Counter++)
    {
        au16Prior_Periods[u8Period_Counter] = 0x0000;                      
    }
    #endif
    #ifdef FOUR_STROKES
    for(u8Period_Counter = 0; u8Period_Counter < 2*NUMBER_OF_TEETH_4C; u8Period_Counter++)
    {
        au16Prior_Periods[u8Period_Counter] = 0x0000;                      
    }
    #endif
    u8Period_Counter = 0;  
}

/*******************************************************************************/
#ifdef FOUR_STROKES
void  vfnGoTo_SYNCHRONIZED_4C(void){
  //Transistion to the 4 cycle sync state.
  
  //Convert the current fuel and spark data to a 720 degree cycle.
  //Change Spark parameters to 720 process                  
  vfnSpark_4C_Convert();
  //Change Fuel parameters to 720 process                  
  vfnFuel_4C_Convert();
  //Turn on Sync LED.  Usefull for timing analysis of state machine latency.                  
  #if HARDWARE == EMULATOR
  SYNCH_LED = ON_STATE;         
  #endif
  //Change to the 4 cycle synchronization state.
  u8Crank_State = SYNCHRONIZED_4C; 
}
#endif
/*******************************************************************************/

UINT8 u8Calculate_Tooth_Period(void)
{
    u16Current_Tooth_Time= CRANKSHAFT_TIMER;   /* Store time of tooth edge */

    /* Calculate tooth period based on time difference 
    between current tooth edge and prior tooth edge */
    

    if(u16Previous_Tooth_Time > u16Current_Tooth_Time) /* If timer overflow ocurred */
    {                                                 
        u16Current_Period = (0xFFFF - u16Previous_Tooth_Time) + u16Current_Tooth_Time;        
    } 
    else
    {
        u16Current_Period = u16Current_Tooth_Time - u16Previous_Tooth_Time;
    } 
        
    //test code
    //synchronization issue
    if(u16Current_Period < 700){
      //We have an issue
      #if HARDWARE == EMULATOR
      SYNCH_LED = !SYNCH_LED;
      TDC_LED = OFF;
      #endif
      //PTP_PTP3 = 0;
      _asm{
      NOP;
      NOP;
      NOP;
      NOP;
      NOP;
      NOP;
      NOP;
      NOP;
      NOP;
      NOP;

      }
      #if HARDWARE == EMULATOR
      SYNCH_LED = !SYNCH_LED;
      #endif
    }
    
    /* Validate tooth period against valid limits */            
    //This will have limitations when in any synchronized state.  
    //The problem is that when you get to a missing tooth, the tooth period
    //will change by the gap ratio (double for typical application).  
    //When this happens, the test below uses limits for non-missing tooth
    //periods.  This is only an issue at low RPM.  Function can easily be 
    //modified to remove this test or add special case.  
    if((u16Current_Period < MAX_PERIOD_LIMIT) && (u16Current_Period > MIN_PERIOD_LIMIT))
    {
        /* Tooth period is within range */
        return 1;
    } 
    else
    {
        return 0;
    }
}

/*******************************************************************************/

UINT8 u8Valid_Period(void)
{
    //Return variable
    UINT8 u8Period_Valid = 0;
    
    /* Calculate previous period plus tolerance */
      //u16Period_Mod = u16Previous_Period + (u16Previous_Period * POS_PERIOD_PERCENTAGE)/100;
    
    u32Period0 = u16Previous_Period; 
    u32Period0 = u32Period0 + (u32Period0 * POS_PERIOD_PERCENTAGE)/100;
    
    /* Calculate previous period minus tolerance */
    u32Period1 = u16Previous_Period;
    u32Period1 = u32Period1 - (u32Period1 * NEG_PERIOD_PERCENTAGE)/100;                  
    
    /* Compare current period against previous period +/- tolerance */
    //Compare against negative tolerance
    if(u16Current_Period < u32Period1){
      //Tooth came in faster than mechanical limitation defined in the 
      //application header file.
      //Reject this tooth as noise by restoring previous tooth time
      u16Current_Period = 0;
      u8Period_Valid = 0;
    }else {
      //Test against a slowing engine for positive tolerance
      if(u16Current_Period > u32Period0)
      {
        //Engine is slowing and out of synchronization tolerance.
        u8Period_Valid = 0;   
    
      }else{
        //Tooth is in tolerance.  
        //Period is valid and ready to be processed.
        u8Period_Valid = 1;
      
      }
    
    }
    
    return(u8Period_Valid);
}

/*******************************************************************************/

void vfnTooth_Period_Store(void){

  /* Tooth period data is stored for two engine revolutions */
    
  #ifdef TWO_STROKES    
  if(u8Period_Counter == 2 * NUMBER_OF_TEETH) 
  {                                                          
    u8Period_Counter=0;
  }
  #endif
    
  #ifdef FOUR_STROKES
  if(u8Period_Counter == 2 * NUMBER_OF_TEETH_4C) 
  {                                                          
    u8Period_Counter=0;
  }    
  #endif
  //Store to buffer
  au16Prior_Periods[u8Period_Counter] = u16Current_Period;
  u8Period_Counter++;   

}

/*******************************************************************************/

void vfnSet_Period_Timeout(void)
{
    /* Load current period */              
    u32Period1 = u16Current_Period;

    /* Calculate period tolerance */
    u32Period1 = (u32Period1 * CRANKSHAFT_TIMEOUT_PERCENTAGE);
    u32Period1 = u32Period1 / 100; 
      
    /* Set timeout period for next edge */                    
    u16Last_Timeout = u16Current_Period + (UINT16)(u32Period1); 
              
    /* Overwrite previous period and edge time */       
    u16Previous_Period = u16Current_Period;  
    u16Previous_Tooth_Time = u16Current_Tooth_Time; 
    
    /* Calculate timeout */
    u32Period1 = CRANKSHAFT_TIMER + (u16Last_Timeout << 2);
    
    if(u32Period1 > 0xFFFF)
    { 
        u32Period1 -= 0xFFFF;
    }
    
    /* Load timeout in timer and enable interrupt */
    TIMEOUT_TIMER = (UINT16)u32Period1;        
    //TIMEOUT_INTERRUPT(ENABLED);      
}

/*******************************************************************************/

UINT8 u8Missing_Tooth_Gap(void)
{
    /* Determine if a possible missing tooth gap has been found 
    using Min Gap_Ratio and Max Gap Ratio values */  
           
    u32Period0  = u16Previous_Period;
    u32Period1  = u16Current_Period;
    
    /* u32Period1 is "multiplied" by 16 to allow better resolution */
    u32Period0  = (u32Period1 << 4) / u32Period0; 
          
    if((u32Period0 > MIN_GAP_RATIO) && (u32Period0 < MAX_GAP_RATIO)) 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************/

UINT8 u8Tooth_After_Gap(void)
{
    /* Determine if tooth after gap has been detected using
    Min Gap_Ratio and Max Gap Ratio values */  
    
    u32Period0 = u16Previous_Period;
    u32Period1 = u16Current_Period;
                
    /* u32Period0 is "multiplied" by 16 to allow better resolution */
    u32Period0  = (u32Period0 << 4) / u32Period1; 
                   
    if((u32Period0 > MIN_GAP_RATIO) && (u32Period0 < MAX_GAP_RATIO)) 
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************/

void vfnIncrement_Teeth_Counter(void)
{
    #ifdef TWO_STROKES
    if(u8Teeth_Counter == NUMBER_OF_TEETH - 1) 
    {
          //This was the last tooth.  Reset to starting tooth.  
        u8Teeth_Counter = 0;
    }
    else 
    {  
        u8Teeth_Counter++;                                                       
    }  
    #endif

    #ifdef FOUR_STROKES
    //Increment the tooth counter based on if the application is synchronized to 
    //the valves.
    if(u8Crank_State==SYNCHRONIZED_4C){
      //Increment based on two rotations of the engine for the four cycle process.
      if(u8Teeth_Counter == NUMBER_OF_TEETH_4C - 1) 
      {
          //This was the last tooth.  Reset to starting tooth.  
          u8Teeth_Counter = 0;
      }
      else 
      {  
          u8Teeth_Counter++;                                                       
      }
        
    }else{
      //Engine is not sychronized to the valve and continue in two cyle mode.
      if(u8Teeth_Counter == NUMBER_OF_TEETH - 1) 
      {
          //This was the last tooth.  Reset to starting tooth.  
          u8Teeth_Counter = 0;
      }
      else 
      {  
          u8Teeth_Counter++;                                                       
      }  
    
    }
                
    #endif

}

/*******************************************************************************/
                                
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt Crank_Missing_Tooth_Isr(void)
{    
    //TDC_LED = ON_STATE;
    
    TIMEOUT_INTERRUPT(DISABLED);
                 
    u16Current_Tooth_Time = u16Previous_Tooth_Time + u16Previous_Period; 

    if(u16Previous_Tooth_Time > u16Current_Tooth_Time)
    {     
        /* Adjustement if timer overflow ocurred */                                    
        u16Current_Period = (0xFFFF - u16Previous_Tooth_Time) + u16Current_Tooth_Time;
    } 
    else
    {
        u16Current_Period = u16Current_Tooth_Time - u16Previous_Tooth_Time;
    }                

    vfnSet_Period_Timeout();    /* Next period timeout */
    
    /* Angle clock calculation */
    u16Angle_Clock_rate = u16Current_Period / DEGREES_PER_TOOTH;
        
    GAP_INTERRUPT(DISABLED);  

    u8Teeth_Counter++;
          
    /* Schedule spark events */                
    vfnSchedule_Spark1_Pulse();
    
    #ifdef TWO_CYLINDER
    vfnSchedule_Spark2_Pulse();
    #endif
    
    /* Schedule fuel pulse events */
    vfnSchedule_Fuel1_Pulse();
    
    #ifdef TWO_CYLINDER
    vfnSchedule_Fuel2_Pulse();
    #endif
        
    return ;    
}


void interrupt Crank_Timeout_Isr(void)
{    
    /* Go to first edge state */
    vfnGoTo_Crank_FirstEdge();
    
    return;
}


#pragma CODE_SEG DEFAULT

/*******************************************************************************/
