/*******************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
\file       stepper_motor_control.c
\brief      Stepper Motor functions
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

/** Common defines and macros */
#include <hidef.h>
/** Variable types and common definitions */
#include "typedefs.h"
/** MCU definitions */
#include "MCUdefinitions.h"
/** Input Output definitions */
#include "Input_Output.h"
/** function prototypes */
#include "Idle_Speed_Control.h"
/** Application definitions */
#include "Application Definitions.h" 

//local variables
#ifdef ISM
UINT8  u8ISM_State;
UINT8  u8_motor_state;
UINT8  u8_last_motor_state;
UINT16 u16Current_ISM_Position;
UINT16 u16_direction;
UINT16 u16Commanded_ISM_Position;

/*******************************************************************************/
/**
* \brief    Initialization for the idle speed stepper motor
* \author   Jesse Beeker
* \param    void
* \return   void
*/
void vfnISM_Init(){
  //Set the ISM control signals to a default state and initialize 
  //the controller.  Run this function on every key on cycle.  
  
  //Set control signals to initialized motor position of state 1
  SIN_P = 0;
  COS_P = 0;
  SIN_N = 0;
  COS_N = 1;
  //Set motor control state to match signals of state 1.
  u8_motor_state = MOTOR_OFF;
  //Set the ISM control state to stopped.
  u8ISM_State = STOPPED;
  //Set the last motor state to first position.
  u8_last_motor_state = 0x01;
  //Init the current position to zero
  u16Current_ISM_Position = 0;
  //Init the desired position match current position
  u16Commanded_ISM_Position = 0;
  
}

/*******************************************************************************/
/**
* \brief    Stepping forward state machine
* \author   Luis Olea / B20740
* \param    void
* \return   void
*/
void vfn_Half_Step_Forward(void){    
    
    switch(u8_motor_state)
    {
        /*motor off*/
        case MOTOR_OFF:
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 0;
          break;
        
        //turn on motor
        case TURN_MOTOR_ON:
          //Motor needs to begin moving.  
          //Restore position state.
          u8_motor_state = u8_last_motor_state;
          //Save the last state to prevent incrementing position on this iteration.
          u8_last_motor_state = TURN_MOTOR_ON;
          break;
        
        //first stage
        case 0x01:
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 1;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //second stage
        case 0x02:
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 1;
          COS_N = 1;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //third stage
        case 0x03:
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 1;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //fourth stage        
        case 0x04:
          SIN_P = 0;
          COS_P = 1;
          SIN_N = 1;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //fifth stage
        case 0x05:
          SIN_P = 0;
          COS_P = 1;
          SIN_N = 0;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        //sixth stage
        case 0x06:
          SIN_P = 1;
          COS_P = 1;
          SIN_N = 0;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        //seventh stage
        case 0x07:
          SIN_P = 1;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        //eigth stage
        case 0x08:
          SIN_P = 1;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 1;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state = 0x01;
          break;
        
        default:
          break;
    }
    //Increment position if the motor was not just turned on.
    if((u8_last_motor_state !=TURN_MOTOR_ON)&&(u8ISM_State != STOPPED)){
      
      #if ISM_OPEN==CCW
      u16Current_ISM_Position++;
      #else if ISM_OPEN==CW
      u16Current_ISM_Position--;
      #endif
    
      //Test to see if this is the commanded position
      if(u16Current_ISM_Position==u16Commanded_ISM_Position)
      {
        //Set a flag to indicate that the motor has reached the desired position
        u8ISM_State = STOPPED;
        //Store the position of the stopped motor.
        u8_last_motor_state = u8_motor_state;
        //Set a flag to open up the motor coils next time through.
        //Prevents damage to the stepper motor
        u8_motor_state = MOTOR_OFF;
      }else{
        //Set a flag to indicate that the ISM is opening the bypass air
        #if ISM_OPEN==CCW
        u8ISM_State = OPENING;
        #else if ISM_OPEN==CW
        u8ISM_State = CLOSING;
        #endif
      }
    }else{
      //Motor was just turned on.
    
    
    }
}
/*******************************************************************************/
/**
* \brief    Stepping backward state machine
* \author   B20740
* \param    void
* \return   void
*/
void vfn_Half_Step_Backward(void){
    
    switch(u8_motor_state)
    {
        /*motor off*/
        case MOTOR_OFF:
          //Open up all coils to prevent overheating damage.
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 0;
          break;
        
        //turn on motor
        case TURN_MOTOR_ON:
          //Motor needs to begin moving.  
          //Restore position state.
          u8_motor_state = u8_last_motor_state;
          //Save the last state to prevent incrementing position on this iteration.
          u8_last_motor_state = TURN_MOTOR_ON;
          break;
        
        //first stage
        case 0x01:
          SIN_P = 1;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 1;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //second stage
        case 0x02:
          SIN_P = 1;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //third stage
        case 0x03:
          SIN_P = 1;
          COS_P = 1;
          SIN_N = 0;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //fourth stage
        case 0x04:
          SIN_P = 0;
          COS_P = 1;
          SIN_N = 0;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //fifth stage
        case 0x05:
          SIN_P = 0;
          COS_P = 1;
          SIN_N = 1;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
        break;
        
        //sixth stage
        case 0x06:
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 1;
          COS_N = 0;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //seventh stage
        case 0x07:
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 1;
          COS_N = 1;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state++;
          break;
        
        //eigth stage
        case 0x08:
          SIN_P = 0;
          COS_P = 0;
          SIN_N = 0;
          COS_N = 1;
          u8_last_motor_state = u8_motor_state;
          u8_motor_state = 0x01;
          break;
        
        default:
          break;
    }
    //Decrement position if the motor was not just turned on.
    if((u8_last_motor_state != TURN_MOTOR_ON)&&(u8ISM_State != STOPPED)){
      #if ISM_CLOSE==CW
      u16Current_ISM_Position--;
      #else if ISM_CLOSE==CCW
      u16Current_ISM_Position++;
      #endif
      
    
      //Test to see if this is the commanded position
      if(u16Current_ISM_Position==u16Commanded_ISM_Position)
      {
        //Set a flag to indicate that the motor has reached the desired position
        u8ISM_State = STOPPED;
        //Store the position of the stopped motor.
        u8_last_motor_state = u8_motor_state;
        //Set a flag to open up the motor coils next time through.
        //Prevents damage to the stepper motor
        u8_motor_state = MOTOR_OFF;
        
      }else{
        //Set a flag to indicate that the ISM is closing the bypass air
       #if ISM_CLOSE==CW
       u8ISM_State = CLOSING;
       #else if ISM_CLOSE==CCW
       u8ISM_State = OPENING;
       #endif
       
      }
    }else{
      //Motor was just turned on.
    
    }
}

/*******************************************************************************/
/**
* \brief    Set desired position of stepper motor
* \author   Jesse Beeker
* \param    u16Commanded_ISM_Position is the position in steps
* \return   void
*/
void vfnSet_ISM_Position(UINT16 u16Position_Input){
    //Use u16Commanded_Position to set the position for the ISM.
    u16Commanded_ISM_Position = u16Position_Input;
    //Test to see if the motor is commanded to open the idle bypass air
    if(u16Commanded_ISM_Position > u16Current_ISM_Position)
    {
      //Test to see if motor was not already going the desired direction
      if(u8ISM_State != OPENING){
        //ISM was not opening.  Test if it was stopped.
        if(u8ISM_State == STOPPED){
          //ISM was stopped and now needs to open.  Change the state of the 
          //low level state machine to go to the last active position.
          u8_motor_state = TURN_MOTOR_ON;
        }
        //Idle speed motor needs to change direction
        u8ISM_State = OPENING;
      }
    } 
    //Test to see if the motor is commanded to close the idle bypass air
    else if(u16Commanded_ISM_Position < u16Current_ISM_Position)
    {
      //Test to see if motor was not already going the desired direction
      if(u8ISM_State != CLOSING){
        //ISM was not closing.  Test if it was stopped.
        if(u8ISM_State == STOPPED){
          //ISM was stopped and now needs to close.  Change the state of the 
          //low level state machine to go to the last active position.
          u8_motor_state = TURN_MOTOR_ON;
        }
        //Idle speed motor needs to change direction
        u8ISM_State = CLOSING;
      }
    }else{
      //The motor is in the commanded position.
      //Set ISM state to stopped
      u8ISM_State = STOPPED;
    }
}

/*******************************************************************************/
/**
* \brief    Go to wanted position of stepper motor
* \author   B20740
* \param    void
* \return   void
*/
void vfn_ISM_TASK(void){
     
     
     if(u8ISM_State != STOPPED)
     {              
        if(u8ISM_State==OPENING)
        {        
            #if ISM_OPEN==CCW
            vfn_Half_Step_Forward();
            #else if ISM_OPEN==CW
            vfn_Half_Step_Backward();
            #endif
        }
        else if(u8ISM_State==CLOSING)
        {        
            #if ISM_CLOSE==CW
            vfn_Half_Step_Backward();
            #else if ISM_CLOSE==CCW
            vfn_Half_Step_Forward();
            #endif
        } 
     }else{
      //Make a function call to any step function to keep motor shut off
      vfn_Half_Step_Backward();     
     }
}

#endif
/*******************************************************************************/