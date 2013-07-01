/*********************************************************************
 *
 *                PT_SUB_Main Firmware
 *
 *********************************************************************
 * FileName:        main.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         BTD Systems Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong      04/15/2011	SPI Driven
 *						
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
void WritePIC_EE(char adr, byte data);
unsigned char ReadPIC_EE(char ptr);
char ChkSumROM(rom char *Data, int Len);
char ChkSumEE(char Addr, int Len);
void IntHandlerHigh (void);
void IntHandlerLow (void);

/** VARIABLES **************************************************************/
char counter,byteTemp;
volatile far PROG_DATA_PACKET Data;
uint32 CoeffSAddr;
BOOL ExecCodeOK, Measuring;
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

#pragma romdata JUMPTABLE = JUMPTABLEADDR		// The jump table at 0x2100

rom stdFn jump_table[16];							//Actually filled out by ExecCode. Only the position matters.
												//Note this will 0 out the first byte in the table if this project is compiled last !

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
//	if( PIR1bits.SSPIF ) 
//	{
//		Service_SPI();
//	}else{
//		if( !INTCONbits.TMR0IF && !INTCONbits.INT0IF && !INTCONbits.RBIF )		//Make sure non of these is passed through
//		{
//    		_asm goto INT_HIGH_OFFS _endasm
//  	}  		
// 	}   	
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
	
	OpenSPI(SLV_SSOFF, MODE_11, SMPMID);				//Initialize in slave mode with SS pin disabled.
	mSetSPI_CS_IN()	
	
	OSCCONbits.IRCF0 = 1;	//Run the internal oscillator at 8Mhz (if we have no external 8mHz)
	OSCCONbits.IRCF1 = 1;
	OSCCONbits.IRCF2 = 1;
		
	Rtn = SSPBUF;									//Clear BF
 	SSPBUF = 0x00;           						// initiate bus cycle
 	
 	RCONbits.IPEN = 1;								//Enable priority levels on interrupts 
 	INTCONbits.GIEH = 1;							//Enables all high-priority interrupts
 	INTCONbits.TMR0IE = 0;							//Disable TMR0 interrupts
 	INTCONbits.INT0IE = 0;							//Disable INT0 External Interrupts
 	INTCONbits.RBIE = 0;							//Disable RB Port Change Interrupts
 	PIE1bits.SSPIE = 1;								//Master Synchronous Serial Port Interrupt Enable bit
 	IPR1bits.SSPIP = 1;								//Master Synchronous Serial Port Interrupt Priority bit - High Priority
 	
 	Measuring = FALSE;
 	 	
	while(1)
	{
		if( Measuring && ExecCodeOK )
		{
			Status.field.busy = 1;
			(*jump_table[FN_MEASURE])( Data.ADR.Adr32, &Data );	//The subs that dont support the MEASURE command just return
			Measuring = FALSE;
		}
	}	
}//end main


void Service_SPI( void )
{
	char Rtn,i,chk;
	trisSDO = INPUT_PIN;							//Turn off the output in case we receive a broadcast command.

	PIR1bits.SSPIF = 0;      						// Clear interrupt flag
 				
 	//LATBbits.LATB3 = 0; 		
 	CMD.Val = SSPBUF;
	  												
	if( CMD.Val == SUB_MEASURE )//Look for a MEASURE command where no CS is needed.
	{
		if( ExecCodeOK ) Measuring = TRUE;
	}else{
		if(!SPI_SEL )									//We are selected.
		{
			trisSDO = OUTPUT_PIN;
// Sub commands here //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////				
			if( CMD.bits.b7 == 0 && CMD.bits.b6 == 0 && ExecCodeOK && CMD.Val != 0 ) {
				(*jump_table[CMD.Val])( Data.ADR.Adr32, &Data );	//Pass the command straight through
			}else{

// Common commands here - /////////////////////////////////////////////////////////////////////////////////////////////////////				

				while( !SPI_SEL ){}					//Wait until the Master releases the CS line
				SPI_SEL = 1;						//Make sure the outgoing is high
				mSetSPI_CS_OUT()					//Switch the CS around
				
				switch( CMD.Val )
				{
					case SUB_READSTATUS:
						if( ExecCodeOK ) 
						{
							Status.bitmap = (*jump_table[FN_EXECPROCESS])( Data.ADR.Adr32, &Data );
							if( Status.field.busy == 0 ) Measuring = FALSE;
						}else{
							Status.bitmap = 0x3d;
						}	
						SPI_SEL = 0;						//Signal to the Master we are ready
						WriteSPI(Status.bitmap);
						break;
						
					case SUB_GETPGMEM:
						SPI_SEL = 0;						//Signal to the Master we are ready
						Data.ADR.upper = ReadSPI();			//Get the address bytes	
						SPI_SEL = 1;		
						Data.ADR.high = ReadSPI();
						SPI_SEL = 0;
						Data.ADR.low = ReadSPI();
						SPI_SEL = 1;						
						Data.len = ReadSPI();				//How many bytes to read.
				
						if( Data.ADR.upper > 127 )			//If the high bit is set then EEPROM
						{
							Data.ADR.low &= 0b10000000;		//Upper or lower half in top bit
							for( i = 0; i < Data.len; i++ ) Data.data[i] = ReadPIC_EE( Data.ADR.low + i );
						}else{
							if( Data.len > 128 ) Data.len = 128;//Cap it at 128 because of the array
							ReadProgMem();											
						}

						for( i = 0; i < Data.len; i++ )
						{
							SPI_SEL = !SPI_SEL;
							WriteSPI(Data.data[i]);				
						}
						break;
						
					case SUB_PROGRAMEXEC:
						SPI_SEL = 0;						//Signal to the Master we are ready					
						Data.ADR.upper = ReadSPI();			//Get the address bytes
						SPI_SEL = 1;
						Data.ADR.high = ReadSPI();
						SPI_SEL = 0;
						Data.ADR.low = ReadSPI();
				
						for( i = 0; i < 64; i++ )
						{
							SPI_SEL = !SPI_SEL;
							Data.data[i] = ReadSPI();
						}
						
						if( Data.ADR.upper > 127 )			//If the high bit is set then EEPROM
						{
							Data.ADR.low &= 0b11000000;
							for( i = 0; i < 64; i++ ) WritePIC_EE( Data.ADR.low + i, Data.data[i] );
							chk = ChkSumEE(	Data.ADR.low, 64 );
						}else{
							if( Data.ADR.Adr32 >= EXECCODE_STARTADDR )		//Prevent overwrites below
							{
								Data.len = 1;								//Just erase 1 64 byte block
								EraseProgMem();
								Data.len = 64;								//Always 64
								WriteProgMem();
								chk = ChkSumROM( Data.ADR.pAdr, 64 );
							}													
						}
						
						SPI_SEL = !SPI_SEL;
						WriteSPI( chk );						//Send the CheckSum back for verification
						break;
				}			
				mSetSPI_CS_IN()						//Turn the CS around again	
			}						
		}			
	}
	Rtn = SSPBUF;									//Clear BF
 	SSPBUF = 0x00;           						// initiate bus cycle again				         				
}//end Service_SPI

char ChkSumROM(rom char *Data, int Len)
{
	BYTE tm;
	tm = 0;
	while(Len)
	{
		tm += *Data;	//Just add modulo 256
		*Data++;
		Len--;		
	}

	tm ^= 0xff;
	tm++;					

	return tm;
}

char ChkSumEE(char Addr, int Len)
{
	BYTE tm;
	tm = 0;
	while(Len)
	{
		tm += ReadPIC_EE( Addr );	//Just add modulo 256
		Addr++;
		Len--;		
	}

	tm ^= 0xff;
	tm++;					

	return tm;
}

BOOL ExecCodePresent()
{
	char Subtype;
	Data.ADR.Adr32 = JUMPTABLEADDR;	
	for ( counter = 0; counter < sizeof(jump_table); counter+=3 )
    {
	    //If any of the lines has 0xffffff we know there is a problem.
	    //Doing it this way because the compiler can put 0 in the first byte of the jump table.
       	if( (*((Data.ADR.pAdr) + counter) == 0xff) && (*((Data.ADR.pAdr) + counter + 1) == 0xff) && (*((Data.ADR.pAdr) + counter + 2) == 0xff) ) return FALSE;
    }
    Data.ADR.Adr32 = EXECCODE_STARTADDR + 1;
    Subtype = *Data.ADR.pAdr;
    if ( (Subtype < 8) || (Subtype > 13) ) return FALSE;		//Need to have a valid sub identity in the MS byte of the version.
	return TRUE;
}

//Just run these function as they are because they work. Stucture holding the data goes all the way back
//to the PICDEM software but it works fine so leave alone.

void StartWrite(void)
{
    /*
     * A write command can be prematurely terminated by MCLR or WDT reset
     */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1_WR = 1;
}//end StartWrite

void ReadProgMem( void ) 
{
    for (counter = 0; counter < Data.len; counter++)
    {
        //2 separate inst prevents compiler from using RAM stack  
        byteTemp = *((Data.ADR.pAdr)+counter);
        Data.data[counter] = byteTemp;
    }//end for
    
    TBLPTRU = 0x00;         // forces upper byte back to 0x00
                            // optional fix is to set large code model
}//end ReadProgMem

void WriteProgMem(void) //TESTED: Passed
{
    Data.ADR.low &= 0b11100000;  //Force 32-byte boundary - DYA 01/18/06
    EECON1 = 0b10000100;        //Setup writes: EEPGD=1,WREN=1

    //LEN = # of byte to write

    for (counter = 0; counter < (Data.len); counter++)
    {
        *((Data.ADR.pAdr)+counter) = \
        Data.data[counter];
        if ((counter & 0b00001111) == 0b00001111)
        {
            StartWrite();
        }//end if
    }//end for
}//end WriteProgMem

void EraseProgMem(void) //TESTED: Passed
{
    //The most significant 16 bits of the address pointer points to the block
    //being erased. Bits5:0 are ignored. (In hardware).

    //LEN = # of 64-byte block to erase
    EECON1 = 0b10010100;     //Setup writes: EEPGD=1,FREE=1,WREN=1
    for(counter=0; counter < Data.len; counter++)
    {
        *(Data.ADR.pAdr+(((int)counter) << 6));  //Load TBLPTR
        StartWrite();
    }//end for
    TBLPTRU = 0;            // forces upper byte back to 0x00
    
                            // optional fix is to set large code model
                            // (for USER ID 0x20 0x00 0x00)
}//end EraseProgMem

void WritePIC_EE( char adr, byte data )
{

    EEADR = adr;
    EEDATA = data;
    EECON1 = 0b00000100;    //Setup writes: EEPGD=0,WREN=1
    EECON2 = 0x55;
   	EECON2 = 0xAA;
   	EECON1bits.WR = 1;
   	
    while(EECON1bits.WR);       //Wait till WR bit is clear
}

unsigned char ReadPIC_EE( char ptr )
{
	EECON1 = 0x00;
    EEADR = ptr;
    EECON1bits.RD = 1;
    return EEDATA;
}	

/** EOF main.c *************************************************/
#endif
