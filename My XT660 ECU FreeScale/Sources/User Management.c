/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       User Management.c
\brief      User management functions and application task
\author     Freescale Semiconductor
\author     Jesse Beeker
\version    0.3
\date       December 29, 2008
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



/****Files to be included in build.  Modify based on system functionality.****/
/** User Management header file */
#include "User Management.h"
/** MCU definitions */
#include "MCUdefinitions.h"
/** Variable types and common definitions */
#include "typedefs.h"
/** GPIO mapping */
#include "Input_Output.h"
/** Application definitions */
#include "Application Definitions.h"
/** Spark control function prototypes */
#include "Spark_Control.h"
/** Fuel control function prototypes */
#include "Fuel_Control.h"
/** Crank sensing definitions and function prototypes */
#include "Crank_Sensing.h"
//** Relay control function prototypes */
#include "Relays.h"
//O2 Heater function prototypes
#include "O2H.h"
/** TPS function prototypes */
#include "TPS.h"
/** MAP function prototypes */
#include "MAP.h"
/** MIL function prototypes */
#include "MIL.h"
/** ENGSTOP switch function prototypes */
#include "ENGSTOPSW.h"


//User Management Variables
//State machine variables for User Management
unsigned char Current_Appl_State;
unsigned char Last_Appl_State;

//User safety variable
unsigned char SAFETY;

//Engine running variables calculated by the user management
//Engine Load parameter
#ifdef Analog_Data_8
  //Load is from 8 bit data
  unsigned char LOAD;
#else
  //Load is from 10 or 12 bit data
  unsigned int LOAD;
#endif

//Engine speed parameter
unsigned int Engine_Speed;
//Measurement of the fastest engine speed when engine is running
unsigned int Top_Speed=0xffff;

//TPS calibration
//Calibration minimum TPS result for closed throttle
unsigned int CAL_TPS_LOW = 549;
//Calibration maximum TPS result for Wide Open Throttle
unsigned int CAL_TPS_HIGH = 3358;

//TPS range variables
//Minimum TPS result for closed throttle
unsigned int TPS_LOW = 0;
//Maximum TPS result for Wide Open Throttle
unsigned int TPS_HIGH = 0;

//Throttle transient detection
//Flag for large increase in throttle position.
unsigned char TIP_IN=0;
//Flag for large decrease in throttle position.
unsigned char TIP_OUT=0;
//Count for the duration of TIP event
unsigned char TIP_Counter=0;

#ifdef MSTART
//Start up choke fuel modifier
//Counter for the duration of starting fuel modifier event
unsigned char MSTART_Counter = 0;
#endif

//Hard fuel calibration variables
// Fuel adder
unsigned int Fuel_Add=0;
//Fuel subtracter for testing.  Raw timer tics to cut from fuel.
unsigned int Fuel_Cut=0;
//Hard spark calibration variables
//Spark adder for testing. Degrees to make closer to TDC.
unsigned int Spark_Advance=0;
//Spark subtracter for testing. Degrees to make farther from TDC.
unsigned int Spark_Retard=0;


//Spark Timing Modifiers
/*ITdes=ITbase*(1+MIT[AIAT+AECT+Aalt+AAF+Aknock+Astart+AEGR])*/
#ifdef Spark_Data_16_bit
unsigned int SM_IT_DES;   //Desired ignition timing.
unsigned int SM_IT_BASE;  //Base ignition timing from table look up
unsigned int SM_MIT = 0;      //Spark timing modify enable.
unsigned int SM_AIAT = 0;     //Intake air temperature modifier
unsigned int SM_AECT = 0;     //Engine coolant temperature modifier
unsigned int SM_AALT = 0;     //Altiude ignition modifier
unsigned int SM_AAF = 0;      //Air fuel ratio modifier
unsigned int SM_AKNOCK = 0;   //Knock condition modifier
unsigned int SM_START = 0;    //Start condition modifier
unsigned int SM_EGR = 0;      //EGR condition modifier
#else
unsigned char SM_IT_DES;   //Desired ignition timing.
unsigned char SM_IT_BASE;  //Base ignition timing from table look up
unsigned char SM_MIT = 0;      //Spark timing modify enable.
unsigned char SM_AIAT = 0;     //Intake air temperature modifier
unsigned char SM_AECT = 0;     //Engine coolant temperature modifier
unsigned char SM_AALT = 0;     //Altiude ignition modifier
unsigned char SM_AAF = 0;      //Air fuel ratio modifier
unsigned char SM_AKNOCK = 0;   //Knock condition modifier
unsigned char SM_START = 0;    //Start condition modifier
unsigned char SM_EGR = 0;      //EGR condition modifier
#endif

unsigned int u16Spark_Modifier = 1;


//Fuel Pulse Modifiers
/* PWreq=PWbase*(1+MO[Maccel*Mload*Mstart*MECT*MIAT*MbattV* Mbap*Mtrimx])*/
#ifdef Spark_Data_16_bit
unsigned int FM_PWREQ;    //Required fuel pulse width
unsigned int FM_PWBASE;   //Base fuel pulse width from table loop up
unsigned int FM_MO = 0;       //Fuel pulse width modifier enable
unsigned int FM_MACCEL = 0;   //Modifier for fast changes in load
unsigned int FM_MLOAD = 1;    //Modifier for high load condition
unsigned int FM_MSTART = 0;   //Modifier for cold starting condition
unsigned int FM_MECT = 1;     //Modifier for cold running engine condition
unsigned int FM_MIAT = 1;     //Modifier intake temperature
unsigned int FM_MBATV = 1;    //Modifier for varying battery voltage
unsigned int FM_MBAP = 1;     //Modifier for altitude based on barometric pressure
unsigned int FM_MTRIM = 1;    //Modifier for fuel difference between cylinders 1 and 2
#else
unsigned char FM_PWREQ;    //Required fuel pulse width
unsigned char FM_PWBASE;   //Base fuel pulse width from table loop up
unsigned char FM_MO = 0;       //Fuel pulse width modifier enable
unsigned char FM_MACCEL = 1;   //Modifier for fast changes in load
unsigned char FM_MLOAD = 1;    //Modifier for high load condition
unsigned char FM_MSTART = 1;   //Modifier for cold starting condition
unsigned char FM_MECT = 1;     //Modifier for cold running engine condition
unsigned char FM_MIAT = 1;     //Modifier intake temperature
unsigned char FM_MBATV = 1;    //Modifier for varying battery voltage
unsigned char FM_MBAP = 1;     //Modifier for altitude based on barometric pressure
unsigned char FM_MTRIM = 1;    //Modifier for fuel difference between cylinders 1 and 2
#endif

unsigned int u16Fuel_Modifier = 1;


//Calibration Spark Timing Modifiers
/*ITdes=ITbase*(1+MIT[AIAT+AECT+Aalt+AAF+Aknock+Astart+AEGR])*/
#ifdef Spark_Data_16_bit
unsigned int CAL_SM_IT_DES;   //Desired ignition timing.
unsigned int CAL_SM_IT_BASE;  //Base ignition timing from table look up
unsigned int CAL_SM_MIT;      //Spark timing modify enable.
unsigned int CAL_SM_AIAT;     //Intake air temperature modifier
unsigned int CAL_SM_AECT;     //Engine coolant temperature modifier
unsigned int CAL_SM_AALT;     //Altiude ignition modifier
unsigned int CAL_SM_AAF;      //Air fuel ratio modifier
unsigned int CAL_SM_AKNOCK;   //Knock condition modifier
unsigned int CAL_SM_START;    //Start condition modifier
unsigned int CAL_SM_EGR;      //EGR condition modifier
#else
unsigned char CAL_SM_IT_DES;   //Desired ignition timing.
unsigned char CAL_SM_IT_BASE;  //Base ignition timing from table look up
unsigned char CAL_SM_MIT;      //Spark timing modify enable.
unsigned char CAL_SM_AIAT;     //Intake air temperature modifier
unsigned char CAL_SM_AECT;     //Engine coolant temperature modifier
unsigned char CAL_SM_AALT;     //Altiude ignition modifier
unsigned char CAL_SM_AAF;      //Air fuel ratio modifier
unsigned char CAL_SM_AKNOCK;   //Knock condition modifier
unsigned char CAL_SM_START;    //Start condition modifier
unsigned char CAL_SM_EGR;      //EGR condition modifier
#endif

//Calibration Fuel Pulse Modifiers
/* PWreq=PWbase*(1+MO[Maccel*Mload*Mstart*MECT*MIAT*MbattV* Mbap*Mtrimx])*/
#ifdef Spark_Data_16_bit
unsigned int CAL_FM_PWREQ;    //Required fuel pulse width
unsigned int CAL_FM_PWBASE;   //Base fuel pulse width from table loop up
unsigned int CAL_FM_MO;       //Fuel pulse width modifier enable
unsigned int CAL_FM_MACCEL = 625;   //Modifier for fast changes in load
unsigned int CAL_FM_MLOAD;    //Modifier for high load condition
unsigned int CAL_FM_MSTART = 3400;   //Modifier for cold starting condition
//unsigned int CAL_FM_MSTART = 0;   //Modifier for cold starting condition
unsigned int CAL_FM_MECT;     //Modifier for cold running engine condition
unsigned int CAL_FM_MIAT;     //Modifier intake temperature
unsigned int CAL_FM_MBATV;    //Modifier for varying battery voltage
unsigned int CAL_FM_MBAP;     //Modifier for altitude based on barometric pressure
unsigned int CAL_FM_MTRIM;    //Modifier for fuel difference between cylinders 1 and 2
#else
unsigned char CAL_FM_PWREQ;    //Required fuel pulse width
unsigned char CAL_FM_PWBASE;   //Base fuel pulse width from table loop up
unsigned char CAL_FM_MO;       //Fuel pulse width modifier enable
unsigned char CAL_FM_MACCEL;   //Modifier for fast changes in load
unsigned char CAL_FM_MLOAD;    //Modifier for high load condition
unsigned char CAL_FM_MSTART;   //Modifier for cold starting condition
unsigned char CAL_FM_MECT;     //Modifier for cold running engine condition
unsigned char CAL_FM_MIAT;     //Modifier intake temperature
unsigned char CAL_FM_MBATV;    //Modifier for varying battery voltage
unsigned char CAL_FM_MBAP;     //Modifier for altitude based on barometric pressure
unsigned char CAL_FM_MTRIM;    //Modifier for fuel difference between cylinders 1 and 2
#endif

//Engine diagnostic variables
unsigned char Injector1_State;
unsigned char Ignition1_State;
unsigned char Injector1_Fault;
unsigned char Ignition1_Fault;

#ifdef TWO_CYLINDER
unsigned char Injector2_State;
unsigned char Ignition2_State;
unsigned char Injector2_Fault;
unsigned char Ignition2_Fault;
#endif

//Fuel pump key on timeout
UINT16 u16Fuel_Pump_Timeout; 


/****External Variables****/
/* Array to store tooth period data for two engine revolutions */
#ifdef FOUR_STROKES
  extern unsigned int au16Prior_Periods[2 * NUMBER_OF_TEETH_4C];
#else
  extern unsigned int au16Prior_Periods[2 * NUMBER_OF_TEETH];
#endif

//Throttle position senser data
#ifdef Analog_Data_8
extern unsigned char TPS_Filtered;
#else 
extern unsigned short TPS_Filtered;
#endif

//O2 Heater functions
#ifdef O2H
extern void vfnO2H_On();
extern void vfnO2H_Off();
#endif

#ifdef R1
extern void vfnRelayControl();
#endif  

      
/**************************************************************************/


void User_Management_Init()
{
    //Init Safety parameter to unsafe conditon.
    SAFETY=0x55;
    //Init RPM value.
    Engine_Speed = 65535;
    //Init LOAD value.
    LOAD = 0;
    //Load TPS calibration data
    TPS_LOW = CAL_TPS_LOW;
    TPS_HIGH = CAL_TPS_HIGH;
    //Initialize the fuel pump
    Fuel_Pump_Controller_Init();
    
    //Enable the voltage regulator module on the scooter.  
    #if HARDWARE==REFERENCE
      //Connected to O2Heater in Reference Design module.
      vfnO2H_On();
    #endif

    // Application state machine initial state */
    Current_Appl_State = INIT;
    // Calculate spark and fuel modifiers */
    Update_Modifiers();    
}


/**************************************************************************/

void User_Management(){

    //Begin ASM
    switch (Current_Appl_State){
      
      case INIT:
        //INIT state
        //Engine is not allowed to run.  Configure to default state.
                          
        //Initialize the MIL
        MIL_Init();
              
        //Go to the STOP state.
        vfnGoto_STOP();      
        break;

      case STOP:
        //STOP state
        //Engine is not allowed to run.
        
        //Run fuel pump controller
        Fuel_Pump_Controller();
            
        //MIL on as engine is not running.
        MIL_Set();

        //Calculate RPM
        RPM_Calculate();
        
        //Test for safety conditions allowing engine to run.
        //Example: Kickstand is up.
        SAFETY=Safety_Check();
        
        if(SAFETY==0){
          //Safety conditions are met.
          //Check to see if the engine is running or stalled.
          //Example: Ignition and engine run switches are on.

          //Engine speed related variables are relative to time between teeth.    
          //Determine if the engine is at a run RPM or a start RPM.
          if(Engine_Speed>Stall_Speed){
            //Engine is rotating slow or not rotating and needs 
            //start up strategy.
            vfnGoto_START();
                    
          }else if(Engine_Speed<Over_Speed){
            //Engine is rotating too fast needs recovery strategy
            //Cut intake so no new "fuel"
            vfnGoto_OVERRUN();
          
          }else{
            //Engine is rotating fast and has already been started. 
            //Keep it going.  Controllers on!
            vfnGoto_RUN();
          }
      
        }else{
          //The engine is not safe to run.  Handle specific cases through
          //error codes of Safety_Check().  

          if(SAFETY==0x55){
            //Handle the unsafe condition here.  
          }
        
        }
      break;

    
      case START:
        //START state
        //Engine is in the process of starting up. 
        
        //Run fuel pump controller
        Fuel_Pump_Controller();

        
        //Run the idle speed controller
        //Idle_Speed_Controller();
        
        //Turn on MIL.  Engine is not running.
        MIL_Set();

        //Calculate RPM
        RPM_Calculate();

        //Test for safety conditions allowing engine to run.
        //Example: Kickstand is up.
        SAFETY=Safety_Check();
        if(SAFETY==0){
          //Safety conditions are met.
          //Check to see if the engine is running or stalled.
          //Example: Ignition and engine run switches are on.
          
          //Engine speed related variables are relative to time between teeth.    
          //Test for engine over rev condition.
          if(Engine_Speed<Over_Speed){
            //The engine is running too fast and needs to slow down.
            vfnGoto_OVERRUN();          
          }
          //Determine if the engine is at a run RPM or a start RPM.
          else if(Engine_Speed<Stall_Speed){
            //Engine is rotating fast enough. 
                vfnGoto_RUN();
                          
          }else{
            //Engine is rotating slow or not rotating and needs
            //the start up strategy.

              //Engine control devices are not active but data for controllers
              //needs to be ready.
            
              /*************************************************************
              The start strategy provides fixed fuel and spark events based
              on RAM variables.  Application
              simply gets the fuel and spark data defined for the start 
              strategy.
              *************************************************************/
              
              //Calculate Load for use in engine management table look up.
              Load_Calculate();

              //Determine modifiers

              //Starting condition.  Activate the start fuel modifier.
              //Simple implementation: Increase fuel pulse by fixed amount.
              //Once engine starts, decay fuel adder.       
              #ifdef MSTART              
              /* Get fuel modifier from calibration table */
              FM_MSTART = CAL_FM_MSTART;
                
              /* Enable fuel modifiers */
              FM_MO = 1;
              #endif
              
              /*************************************************************
              End start up strategy.
              *************************************************************/
          
              //Test for faults on injectors.
              Injector1_Fault=Get_Injector1_Fault();
              if(Injector1_Fault!=No_Fault){
                //There is a problem with injector 1.  Handle here.
              }
              #ifdef TWO_CYLINDER
              Injector2_Fault=Get_Injector2_Fault();              
              if(Injector2_Fault!=No_Fault){
                //There is a problem with injector 2.  Handle here.
              }
              #endif
              
              //Test for faults on ignition.
              Ignition1_Fault=Get_Ignition1_Fault();
              if(Ignition1_Fault!=No_Fault){
                //There is a problem with coil 1.  Handle here.
              }
              #ifdef TWO_CYLINDER
              Ignition2_Fault=Get_Ignition2_Fault();
              if(Ignition2_Fault!=No_Fault){
                //There is a problem with coil 2.  Handle here.
              }
              #endif

          
          }
      
        }else{
          //The engine is not safe to run.  Handle specific cases through
          //error codes of SAFETY.  
          //Stop the engine.
          vfnGoto_STOP();        
        }
      break;
      
      
      case RUN:
        //RUN state
        //Engine is in the normal process of running.

        //Run fuel pump controller
        Fuel_Pump_Controller();

        //Engine is running.  Turn off the MIL.
        MIL_Clear();
         
        //Calculate RPM
        RPM_Calculate();
        //Log the fastest engine speed.
        if(Engine_Speed<Top_Speed){
          Top_Speed=Engine_Speed;
        }
        
        //Test for safety conditions allowing engine to run.
        //Example: Kickstand is up.
        SAFETY=Safety_Check();
        if(SAFETY==0){
          //Safety conditions are met.
          //Check to see if the engine is running or stalled.
          //Example: Ignition and engine run switches are on.
              
          //Test for engine over rev condition.
          if(Engine_Speed<Over_Speed){
            //The engine is running too fast and needs to slow down.
            //Cut "fuel" to slow it down.
            vfnGoto_OVERRUN();                      
          }
          
          //Determine if the engine is at a run RPM or a start RPM.
          else if(Engine_Speed>Stall_Speed){
            //Engine is not rotating fast enough. 
            //Goto the START as the engine is rotating slower than a 
            //run condition.
            vfnGoto_START();
        
          }else{
            //Engine is started and needs engine management strategy
            
              //Engine control devices are active.  
              //Implement engine management strategy.
              /*************************************************************
              Engine Management strategy.
              *************************************************************/
              
              //Simple Engine Management
              
              //Calculate Load for use in engine management table look up.
              Load_Calculate();
              
              //Determine modifiers
              
              //MSTART Handler
              #ifdef MSTART
              if(FM_MSTART > MSTART_Decay)
              {
                //Starting fuel modifier is still active.  
                //Check for timeout to decay modifier.
                if(MSTART_Counter == MSTART_Decay_Timeout)
                {
                  //Timeout has occurred.
                  //Decrease the start fuel modifier.
                  FM_MSTART = FM_MSTART - MSTART_Decay;             
                  //Reset the counter.
                  MSTART_Counter = 0;
                
                }
                else
                {
                  //Increment counter.
                  MSTART_Counter++;                
                  
                  //FM_MSTART = 1;
                }                
              }else{
                //Decay the remaining amount of MSTART
                FM_MSTART = 0;
              
              }
              //End MSTART Handler
              #endif
              /*************************************************************
              End Engine Management strategy.
              *************************************************************/
              
              //Test for faults on injectors.
              Injector1_Fault=Get_Injector1_Fault();
              if(Injector1_Fault!=No_Fault){
                //There is a problem with injector 1.  Handle here.
              }
              #ifdef Two_Cylinder
              Injector2_Fault=Get_Injector2_Fault();              
              if(Injector2_Fault!=No_Fault){
                //There is a problem with injector 2.  Handle here.
              }
              #endif
              
              //Test for faults on ignition.
              Ignition1_Fault=Get_Ignition1_Fault();
              if(Ignition1_Fault!=No_Fault){
                //There is a problem with coil 1.  Handle here.
              }
              #ifdef Two_Cylinder
              Ignition2_Fault=Get_Ignition2_Fault();
              if(Ignition2_Fault!=No_Fault){
                //There is a problem with coil 2.  Handle here.
              }
              #endif
              
            //Stay in the RUN state.
          }
      
        }else{
          //The engine is not safe to run.  Handle specific cases through
          //error codes of SAFETY.  
          //Stop the engine.
          vfnGoto_STOP();        
        }
        
      break;

    
      case OVERRUN:
      //OVERRUN State
      //Engine speed has gone past normal operation.
        
        //Run fuel pump controller
        Fuel_Pump_Controller();

        //Engine is "running" so keep the MIL off.
        MIL_Clear();
        
        //Calculate RPM
        RPM_Calculate();
      
        //Test for safety conditions allowing engine to run.
        //Example: Kickstand is up.
        SAFETY=Safety_Check();
        if(SAFETY==0){
          //Safety conditions are met.
          //Check to see if the engine is running or stalled.
          //Example: Ignition and engine run switches are on.
              
          //Determine if the engine is at a run RPM or a start RPM.
          if(Engine_Speed>Over_Speed_Recovery){
            //Engine is not rotating too fast and system can recover. 
            //Goto the RUN as the engine is rotating slower than an 
            //overrun condition.
            vfnGoto_RUN();
        
          }else{
            //Engine is going too fast and needs special engine management
            //strategy.

           /****************************************************
            Engine Over Rev Strategy
            ****************************************************/
          
            //Cut the fuel to slow down the engine.      
            //This is handled in the state transistion by disabling
            //the fuel controllers.  
            

            /****************************************************
            End Engine Over Rev Strategy
            ****************************************************/

              //Calculate Load for use in engine management table look up.
              Load_Calculate();
              
              //Determine modifiers
              //No modifiers for air engine.  
             
              /*************************************************************
              End Engine Management strategy.
              *************************************************************/
              
              //Test for faults on injectors.
              Injector1_Fault=Get_Injector1_Fault();
              if(Injector1_Fault!=No_Fault){
                //There is a problem with injector 1.  Handle here.
              }
              #ifdef Two_Cylinder
              Injector2_Fault=Get_Injector2_Fault();              
              if(Injector2_Fault!=No_Fault){
                //There is a problem with injector 2.  Handle here.
              }
              #endif
              
              //Test for faults on ignition.
              Ignition1_Fault=Get_Ignition1_Fault();
              if(Ignition1_Fault!=No_Fault){
                //There is a problem with coil 1.  Handle here.
              }
              #ifdef Two_Cylinder
              Ignition2_Fault=Get_Ignition2_Fault();
              if(Ignition2_Fault!=No_Fault){
                //There is a problem with coil 2.  Handle here.
              }
              #endif
              
            /****************************************************
            End Engine Over Rev Strategy
            ****************************************************/
             
            //Stay in the OVERRUN state.
          }
        }else{
          //The engine is not safe to run.  Handle specific cases through
          //error codes of Safety_Check().  
          //Stop the engine.
          vfnGoto_STOP();        
        }
      break;
    
    }//End switch/case
                    
    /* Calculate final spark and final fuel using modifiers */
    Update_Modifiers();     
}

/*******************************************************************************/
/**
* \brief    Function to set the applicatin state machine to INIT state.
* \author   Jesse Beeker 
* \param    void
* \return   void
*/
void vfnGoto_INIT(){

  //Actions for transistion to the INIT state
  //Don't turn on the fuel or spark until safe and over the stall speed.
  vfnSet_Fuel_Controller(DISABLED);
  vfnSet_Spark_Controller(DISABLED);
  //Pulse must be scheduled to put controller in inactive mode
  //for direct control
  vfnSchedule_Spark1_Pulse();

  //Turn off the injector to cylinder 1.
  vfnFuel_Direct_Control(FUEL_INJECTOR_1, OFF);
  //Turn off the ignition coil for cylinder 1.
  vfnSpark_Direct_Control(SPARK_COIL_1, OFF);

  //Store the last state of the application
  Last_Appl_State=Current_Appl_State;
  //Change to the new state.
  Current_Appl_State=INIT;

}

/*******************************************************************************/
/**
* \brief    Function to set the applicatin state machine to STOP state.
* \author   Jesse Beeker 
* \param    void
* \return   void
*/
void vfnGoto_STOP(){

  //Actions for transistion to the STOP state
  //Don't turn on the fuel or spark until safe and over the stall speed.
  vfnSet_Fuel_Controller(DISABLED);
  vfnSet_Spark_Controller(DISABLED);
  //Pulse must be scheduled to put controller in inactive mode
  //for direct control.
  vfnSchedule_Spark1_Pulse();
  vfnSchedule_Fuel1_Pulse();

  //Make sure injector is closed.
  //Turn off the injector to cylinder 1.
  vfnFuel_Direct_Control(FUEL_INJECTOR_1, OFF);
  //Make sure ignition coil is off.
  //Turn off the ignition coil for cylinder 1.
  vfnSpark_Direct_Control(SPARK_COIL_1, OFF);

  //Initialize the fuel pump controller.
  Fuel_Pump_Controller_Init();

  //Store the last state of the application
  Last_Appl_State=Current_Appl_State;
  //Change to the new state.
  Current_Appl_State=STOP;

}

/*******************************************************************************/
/**
* \brief    Function to set the applicatin state machine to START state.
* \author   Jesse Beeker 
* \param    void
* \return   void
*/
void vfnGoto_START(){

  //Actions for transistion to the START state
  //Turn on the fuel and spark.
  vfnSet_Fuel_Controller(ENABLED);
  vfnSet_Spark_Controller(ENABLED);

  //Initialize the fuel pump controller.
  Fuel_Pump_Controller_Init();

  //Store the last state of the application
  Last_Appl_State=Current_Appl_State;
  //Change to the new state.
  Current_Appl_State=START;

}

/*******************************************************************************/
/**
* \brief    Function to set the applicatin state machine to RUN state.
* \author   Jesse Beeker 
* \param    void
* \return   void
*/
void vfnGoto_RUN(){

  //Actions for transistion to the RUN state
  vfnSet_Fuel_Controller(ENABLED);
  vfnSet_Spark_Controller(ENABLED);

  //Store the last state of the application
  Last_Appl_State=Current_Appl_State;
  //Change to the new state.
  Current_Appl_State=RUN;

}

/*******************************************************************************/
/**
* \brief    Function to set the applicatin state machine to OVERRUN state. 
* \author   Jesse Beeker 
* \param    void
* \return   void
*/
void vfnGoto_OVERRUN(){

  //Actions for transistion to the OVERRUN state
  vfnSet_Fuel_Controller(DISABLED);

  //Initialize the fuel pump controller.
  Fuel_Pump_Controller_Init();

  //Store the last state of the application
  Last_Appl_State=Current_Appl_State;
  //Change to the new state.
  Current_Appl_State=OVERRUN;

}


/*******************************************************************************/
/**
* \brief    Initialzation of the fuel pump controller 
* \author   Jesse Beeker 
* \param    void
* \return   void
*/
void Fuel_Pump_Controller_Init(void){
  //Turn off the fuel pump.
    vfnRelayControl(FUEL_PUMP, OFF);
  //Configure the timeout value.
  u16Fuel_Pump_Timeout = FUEL_PUMP_TOUT;        
}


/*******************************************************************************/
/**
* \brief    Fuel pump controller. Must be called periodically for timeout 
*\          functionality based on user management timing.  
* \author   Jesse Beeker 
* \param    void
* \return   void
*/
void Fuel_Pump_Controller(void){
  //Should the fuel pump be on?
  if(Current_Appl_State == RUN){
    //Fuel pump should be on. No questions asked
    /* Fuel pump turned on */
    vfnRelayControl(FUEL_PUMP, ON);
  }else if((Current_Appl_State==START)||(Current_Appl_State==OVERRUN)){
      //The engine is on but not spraying fuel.
       //Manage the time it is turned on.
    if(u16Fuel_Pump_Timeout >= 1){
      //If timeout has not occurred, turn on fuel pump.
      vfnRelayControl(FUEL_PUMP, ON);
      /* Decrease the timeout counter */
      u16Fuel_Pump_Timeout --;
    }else{
      //Check for timeout to turn off the fuel pump. 
      if(u16Fuel_Pump_Timeout==0){
        /*Timeout expired. Turn off the fuel pump */
        vfnRelayControl(FUEL_PUMP, OFF); 
      }
    }
  }else{
    //Fuel pump is to be turned off.
    vfnRelayControl(FUEL_PUMP, OFF); 
  }
                                   
}

/**************************************************************************/

void Update_Modifiers()
{       
    /*ITdes = ITbase * (1 + MIT[AIAT+AECT+Aalt+AAF+Aknock+Astart+AEGR])  */
    u16Spark_Modifier = 1 + SM_MIT * (SM_AIAT + SM_AECT + SM_AALT + SM_AAF + 
                                      SM_AKNOCK + SM_START + SM_EGR);
                                      
    /* PWreq = PWbase * (1 + MO[Maccel*Mload*Mstart*MECT*MIAT*MbattV* Mbap*Mtrimx])  */
    //u16Fuel_Modifier = 1 + FM_MO * (FM_MACCEL * FM_MLOAD * FM_MSTART * FM_MECT *
    //                                FM_MIAT * FM_MBATV * FM_MBAP * FM_MTRIM);                                                                      
    u16Fuel_Modifier = (FM_MO* (FM_MSTART+FM_MACCEL));
}

/*******************************************************************************/

void MIL_Init(){  
  //Default with the MIL on.
  MIL_Set();
}


void MIL_Set(){
  //Turn on the MIL connected to VLAMP.  
  //VLAMPIN = ON;
  //MIL seems to be connected to the head light. Do not turn on.
    VLAMPIN = OFF;

}


void MIL_Clear(){
  //Turn off the MIL connected to VLAMP
  VLAMPIN = OFF;
}

/*******************************************************************************/

unsigned char Get_Injector1_Fault()
{
  return(0);
}
unsigned char Get_Ignition1_Fault()
{
  return(0);
}
unsigned char Get_Injector2_Fault()
{
  return(0);
}
unsigned char Get_Ignition2_Fault()
{
  return(0);
}

/*******************************************************************************/

unsigned char Safety_Check()
{
//Test the signals that indicate that the user is safe to run the engine.
//Returns a value of zero if all conditions are met and the user is safe.

  //Return variable indicating that all safety conditions have been met.
  UINT8 SAFE=0;
             
  return(SAFE);
}


/*******************************************************************************/

void RPM_Calculate()
{
//This function takes the raw tooth period measurements and updates the Engine Speed
//value needed for Engine Management application.  Engine Speed is in timer tics.

   //Variable for summation of all stored tooth periods.
   unsigned long TOOTH_SUM;
   
   //Variable for summation loop.
   unsigned char LOOP_COUNT;
   
   //Variable for number of valid data entries.
   unsigned char DATA_COUNT;
   
   UINT16 Test_Value = 0;   // JAOV

   //Engine_Speed is in timer ticks per revolution and is an average value over the last 
   //two revolutions.
   
   //Calculate average.
   //Probably should transfer the buffer contents to a temp buffer to avoid a change in 
   //data while calculating.
   
   //Init running sum.
   TOOTH_SUM=0;
   //Set the loop iterations. Include index of zero.
   #ifdef TWO_STROKES
   LOOP_COUNT=2*NUMBER_OF_TEETH-1;
   #endif
   #ifdef FOUR_STROKES
   LOOP_COUNT=2*NUMBER_OF_TEETH_4C-1;
   #endif
   //Initialize the number of valid data entries.
   DATA_COUNT=0;
   //Loop over tooth timing array
   while(LOOP_COUNT>0){
      //Test the data for this index.
      if(au16Prior_Periods[LOOP_COUNT]!=0){
        //Data is valid for this index.
        //Sum each value
        TOOTH_SUM = TOOTH_SUM + au16Prior_Periods[LOOP_COUNT-1];
        //Increment the number of valid data entries.
        DATA_COUNT++;
      }
      //Go to the next index.
      LOOP_COUNT--;
   }
   
   //Divide by the number of valid data entries to get the average.
   //Update the engine speed value.  
   //This is 32 bit math.  Need to optimize for an 8/16 bit solution. 
   if(DATA_COUNT){    
        Engine_Speed = TOOTH_SUM/DATA_COUNT;
//        Test_Value = Conv_Period_to_RPM(Engine_Speed);
   }
   else
   {
        Engine_Speed = 0xFFFF; 
   }    
}

/*******************************************************************************/

void Load_Calculate()
{
//This function calulates the engine load parameter that is fed into the engine 
//management used for table look up.  Load can be calculated in various ways 
//using the sensor inputs.  For AlphaN, the throttle position determines load.

#ifdef AlphaN
#ifdef TIP_Detection
/********************************************/
/*  Throttle position transient detection   */
/********************************************/
  //Update with case statements in future-JB 6/2/08
  //Test to see if throttle transient TIP has been previously detected.
  //Case 1: Not currently in a TIP condition.
  if((TIP_IN==0)&&(TIP_OUT==0)){   
    //Test for new transient condition for TIP IN
    //If the last load value (based on TPS only) was smaller by 
    //the defined value, then we are in a tip in condition.
    if(TPS_Filtered >= (LOAD + TIP_IN_VALUE)){
      //TIP IN condition has occurred
      TIP_IN=1;
      //Clear TIP OUT as they cannot be simultaneous
      TIP_OUT=0;
      //Load the calibrated fuel modifier value for TIP IN condition.
      FM_MACCEL=CAL_FM_MACCEL;
      //Reset the TIP counter as this is a new TIP event.
      TIP_Counter=0;
    }
    //Test for new transient condition for TIP OUT
    //If the last load value (based on TPS only) was larger by 
    //the defined value, then we are in a tip in condition.
    else if(TPS_Filtered <= (LOAD-TIP_OUT_VALUE)){
      //TIP OUT condition has occurred
      TIP_OUT=1;
      //Clear TIP IN as they cannot be simultaneous.
      TIP_IN=0;
      //Load the calibrated fuel modifier value for TIP OUT condition.
      FM_MACCEL=CAL_FM_MACCEL;
      //Reset the TIP counter as this is a new TIP event.
      TIP_Counter=0;
    }
    //No TIP condition is present.
    else{
      //Clear the TIP fuel modifier.
      FM_MACCEL=0;
      //Clear all TIP conditions.
      TIP_IN=0;
      TIP_OUT=0;
      //Clear all TIP condition counter
      TIP_Counter=0;
    }
  }
  //Test for actively in a TIP IN condition
  //Case 2: Currnetly in a TIP IN condition.
  else if(TIP_IN==1){
    //Test for new transient condition.
    if(TPS_Filtered >= (LOAD + TIP_IN_VALUE)){
      //TIP IN condition has occurred
      TIP_IN=1;
      //Clear TIP OUT as they cannot be simultaneous
      TIP_OUT=0;
      //Load the calibrated fuel modifier value for TIP IN condition.
      FM_MACCEL=CAL_FM_MACCEL;
      //Reset the TIP counter as this is a new TIP event.
      TIP_Counter=0;
    }
    //Test for timeout to modify the TIP IN fuel modifer
    else if(TIP_Counter==TIP_IN_Decay_Timeout){
      //Test to see how large the TIP modifier is
      if(FM_MACCEL >= TIP_IN_Decay){
        //Adjust the TIP IN fuel modifier based on the defined decay rate.
        FM_MACCEL=FM_MACCEL-TIP_IN_Decay;
      }else{    
        //Remove remaining fuel modifier.
        FM_MACCEL = 0;
        //Remove TIP in condition
        TIP_IN = 0;
      }
      //Clear the counter.
      TIP_Counter=0;  

    }else{
        //Increment the TIP_Counter
        TIP_Counter++; 
    }

  //Test for actively in a TIP OUT condition
  //Case 3: Currently in a TIP OUT condition.
  }else if(TIP_OUT==1){
    
    //Test for timeout to modify the TIP OUT fuel modifer
    if(TIP_Counter==TIP_OUT_Decay_Timeout){
      //Test to see how large the TIP modifier is
      if(FM_MACCEL >= TIP_OUT_Decay){
        //Adjust the TIP OUT fuel modifier based on the defined decay rate.
        FM_MACCEL=FM_MACCEL-TIP_OUT_Decay;
      }else{    
        //Remove remaining fuel modifier.
        FM_MACCEL = 0;
        //Remove TIP in condition
        TIP_OUT = 0;
      }
      //Clear the counter.
      TIP_Counter=0;  

    }else{
        //Increment the TIP_Counter
        TIP_Counter++; 
    }
  }
 
  //Inclusive structure.  Should be optimized out as all cases covered previously.
  else{
    //Error case.
    //Clear conditions
    TIP_IN = 0;
    TIP_OUT = 0;
  
  }
/************************************************/
/*  END Throttle position transient detection   */
/************************************************/  
#endif


  //AlphaN Load calculation.
 
  //Update the Load value with the latest throttle position.
  LOAD = TPS_Filtered;
  
#endif

}

/*******************************************************************************/



