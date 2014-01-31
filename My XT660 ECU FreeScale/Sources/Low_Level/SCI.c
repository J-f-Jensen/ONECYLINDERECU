/*******************************************************************************/
/**
\file       SCI.c
\brief      Serial Communication Interface functions
\author     FreeScale and Jens F. Jensen
\version    1
\date       18/01/2014
*/
/*******************************************************************************/
/**                                                                             
\   Serial communication functions including TX and RX ring buffer 
\   This version only support SCI0
\   Works for one wire communication used as implementended in Yamaha XT660 ECU's
\   Easy to change for normal serial communication. Removed whats described in ISR function
\  Circular buffer functions are defined in cbuf.h 
*/                                                                             
/*******************************************************************************/

/** MCU definitions */
#include "MCUdefinitions.h"


/* SCI routines prototypes */ 
#include "SCI.h"
/** Variable types and common definitions */
#include "typedefs.h"
/** Application definitions */
#include "Application Definitions.h"
/** Circular buffer **/
#include "cbuf.h"
 
/*******************************************************************************/
/* Global SCI communication status */
UINT8 u8SCI_Comm_Status;
   
volatile struct {
 UINT8     m_getIdx;
 UINT8     m_putIdx;
 UINT8     m_entry[ RxQ_SIZE ];
} RxQ;

volatile struct {
 UINT8     m_getIdx;
 UINT8     m_putIdx;
 UINT8     m_entry[ TxQ_SIZE ];
} TxQ;

/* Internal SCI tmp only used in ISR!! */
UINT8 SCI_ISR_tmp0 = 1;
UINT8 SCI_ISR_tmp1 = 1;

//SCI_tmp0 = 0;
//SCI_tmp0 = 0;

/*******************************************************************************/
/**
* \brief    SCI initialization
* \author   Abraham Tezmol
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   void
*/

void vfnSCI_Init()
{
    /** Init bufers **/
    CBUF_Init(RxQ);
    CBUF_Init(TxQ);      
    
    /* Init SCI port 0 */                
    SCI0BD = SCIBaudRate;
    SCI0CR1 = 0x00;
    SCI0CR2 = 0x2C;
    //SCI0CR2 = 0x0C; /** Recive interupt disabled **/
    /*       0b00101100
               ||||||||____ SendBrakeBit
               |||||||_____ Receiver Wakeup bit
               ||||||______ Receiver Enable bit
               |||||_______ Transmiter Enable Bit
               ||||________ Idle Line Interrupt Enable Bit
               |||_________ Receiver full interrupt enable bit
               ||__________ Transmission complete interrupt enable bit
               |___________ Transmitter Interrupt Enable Bit
    */
    
    /* Reset auxiliary variables for input buffer management */
    CBUF_Init(RxQ);
           
    u8SCI_Comm_Status = SCI_COMM_OK;
}

/*******************************************************************************/
/**
* \brief    Read 1 data byte from input buffer. 
* \author   Abraham Tezmol
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   UINT8 - read byte from input buffer.
*/
UINT8 u8SCI_ReadRx()
{       
   return(CBUF_Pop( RxQ ));
}

/*******************************************************************************/
/**
* \brief    SCI Tramsmit Function
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
            UINT8 u8TxDataByte - Data byte to be transmitted
* \return   UINT8 - result
*/

UINT8 u8SCI_WriteTx(UINT8 u8TxDataByte) {
  if (CBUF_IsFull(TxQ) != TRUE) {
    /* put char in buffer */
    CBUF_Push(TxQ, u8TxDataByte);
   
    /* Enable TX interupt */
	  if (SCI0CR2_SCTIE == 0) {
	   SCI0CR2_SCTIE = 1;
	   /* and disable RX interupt */
	   SCI0CR2_RIE = 0;
	  }
    
    return SCI_COMM_OK;
  }
  else
  {
    return SCI_COMM_TX_BUFFER_FULL;
  }
}

/*******************************************************************************/
/**
* \brief    SCI Low-Level Tramsmit Function 
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
            UINT8 u8TxDataByte - Data byte to be transmitted
* \return   void
*/

void vfnSCI_WriteTx(UINT8 u8TxDataByte)
{
    /* Check if SCI0 TX buffer is full */
    if (SCI0SR1_TDRE == 1)
    {
        /* Send data */
        SCI0DRL = (UINT8)u8TxDataByte;
    }
    else
    {
        u8SCI_Comm_Status = SCI_COMM_TX_BUSY;
    }    
}  
 

/*******************************************************************************/
/**
* \brief    Poll for new data flag on SCI input buffer
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   UINT8 - Number of bytes in the reception buffer
*/
UINT8 u8SCI_CheckRx()
{
  return(CBUF_Len(RxQ));
}

/*******************************************************************************/
/**
* \brief    Discard any incomming data on SCI receive buffer
* \param    UINT8 u8SCIPort - Port number
            0 -> SCI channel 0
* \return   void
*/
void vfnSER_ClearRx()
{   
  CBUF_Init(RxQ);
}


/*******************************************************************************/
/**
* \brief    ISR, handle recive and transmit interupt
* \param    void
* \return   void
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt SCI0_Isr(void)
{
  
  /* Data in receive register interupt */
  if (SCI0SR1_RDRF == 1) {
      /* Check Overrun Flag  */
      if (SCI0SR1_OR == CLEAR)
      {
          /* Read SCI RX data */
          SCI_ISR_tmp0 = SCI0DRL;
          /* Check if it is echo back */
          if (SCI_ISR_tmp1 > 0) {
            /* Echo back - not used */              
            --SCI_ISR_tmp1;
          } else {
            /* Add data to recive buffer */
            CBUF_Push(RxQ, SCI_ISR_tmp0);
          }
      }
      else
      {
          u8SCI_Comm_Status = SCI_COMM_RX_OVERRUN;
      }
  }
  
	/* Transmit buffer empty interupt */
	if (SCI0SR1_TDRE == 1) {
	
	    if (CBUF_IsEmpty(TxQ) != 1) {  
        /* Remark next line out if you do not use a one wire setup */
        ++SCI_ISR_tmp1;	      
	      
	      /* Send next char in TX buffer */
        SCI0DRL = CBUF_Pop(TxQ);
      }
      else
      {
	      /* When buffer is empty disable TX interupt */
	      SCI0CR2_SCTIE = 0;	      
	      /* and enable RX interupt */
	      SCI0CR2_RIE = 1;
      }
	}   
}
#pragma CODE_SEG DEFAULT
