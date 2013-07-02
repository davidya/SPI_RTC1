/*********************************************************************
 *
 *                RTC_SUB_Main Firmware
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Micro-Smart Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong      04/15/2011	SPI Driven
 *
 *						07/01/2013	AJA - RTC code					
 ********************************************************************/
#ifndef MAIN_C
#define MAIN_C
/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include <spi.h> 
#include <delays.h>
#include "io_cfg.h"
#include "ConfigBits.h"
#include "ExecCodeVar.h"
#include "Main.h"

/** LOCAL PROTOTYPES ******************************************************/ 
BOOL ExecCodePresent();
void IntHandlerHigh (void);
void IntHandlerLow (void);

/** VARIABLES **************************************************************/
char counter,byteTemp;
volatile far PROG_DATA_PACKET Data;
UINT8_VAL CMD;
SUB_STATUS Status;

       
/** V E C T O R  R E M A P P I N G ********************************************/
#pragma code high_vector=0x08
void interrupt_at_high_vector(void)
{
	_asm goto IntHandlerHigh _endasm
}
#pragma code

#pragma code low_vector=0x18
void interrupt_at_low_vector(void)
{
    _asm goto IntHandlerLow _endasm
}

#pragma romdata VER = 0x20
rom char Ver[] = {  MINOR_VERSION, MAJOR_VERSION };

/** D E C L A R A T I O N S **************************************************/
#pragma code


#pragma interrupt IntHandlerHigh
void IntHandlerHigh (void)				//Re-Map here
{
	if( PIR1bits.SSPIF ) 
	{
		Service_SPI();
	}
}

void IntHandlerLow (void)
{
	_asm goto INT_LOW_OFFS _endasm
}
/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           Creates an SPI slave interface
 *
 * Output:          SPI responses
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            The ExeCode section is re-programmable but this Admin section
 * 					is not and should be largely agnostic as to what type of sub
 *					the unit is.
 *					Some subs in the system have no external osc, 
 *					so the FCMEM config bit must be set for these to start.
 *****************************************************************************/
void main(void)
{
	char Rtn;
	
	mSetupMSSP1()
	OpenSPI1(SLV_SSOFF, MODE_11, SMPMID);				//Initialize in slave mode with SS pin disabled.
	mSetSPI_CS_IN()	
	
	
	
	OSCCONbits.IRCF0 = 1;	//Run the internal oscillator at 8Mhz (if we have no external 8mHz)
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF2 = 1;
		
	Rtn = SSP1BUF;									//Clear BF
 	SSP1BUF = 0x00;           						// initiate bus cycle
 	
 	//while(!SSP1STATbits.BF);
 	
 	
 	RCONbits.IPEN = 1;								//Enable priority levels on interrupts 
 	INTCONbits.GIEH = 1;							//Enables all high-priority interrupts
 	INTCONbits.TMR0IE = 0;							//Disable TMR0 interrupts
 	INTCONbits.INT0IE = 0;							//Disable INT0 External Interrupts
 	INTCONbits.RBIE = 0;							//Disable RB Port Change Interrupts
 	PIE1bits.SSPIE = 1;								//Master Synchronous Serial Port Interrupt Enable bit
 	IPR1bits.SSPIP = 1;								//Master Synchronous Serial Port Interrupt Priority bit - High Priority
 	PIR1bits.SSPIF = 0; 							//Master Synchronous Serial Port Interrupt Priority bit - High Priority
 		 	
	while(1)
	{
// Read A/D and see if we need to go to sleep.
	}	
}
//end main


void Service_SPI( void )
{
	char Rtn,i,chk;
	trisSDO = INPUT_PIN;							//Turn off the output in case we receive a broadcast command.

	PIR1bits.SSP1IF = 0;      						// Clear interrupt flag
 				
 	//LATBbits.LATB3 = 0; 		
 	CMD.Val = SSP1BUF;
  												
	if(!SPI_SEL )									//We are selected.
	{
		trisSDO = OUTPUT_PIN;

// Commands here - /////////////////////////////////////////////////////////////////////////////////////////////////////				

		while( !SPI_SEL ){}					//Wait until the Master releases the CS line
		SPI_SEL = 1;						//Make sure the outgoing is high
		mSetSPI_CS_OUT()					//Switch the CS around
		
		switch( CMD.Val )
		{
			case SUB_GETTIME:

				SPI_SEL = 0;						//Signal to the Master we are ready
				break;
				
			case SUB_SETTIME:
				SPI_SEL = 0;						//Signal to the Master we are ready
				
				for( i = 0; i < 64; i++ )
				{
					SPI_SEL = !SPI_SEL;
					Data.data[i] = ReadSPI1();
				}
				break;
		}			
		mSetSPI_CS_IN()						//Turn the CS around again	
	}									

	Rtn = SSP1BUF;									//Clear BF
 	SSP1BUF = 0x00;           						// initiate bus cycle again				         				
}//end Service_SPI



/** EOF main.c *************************************************/
#endif
