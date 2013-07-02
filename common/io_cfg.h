/*********************************************************************
 *
 *                 SUB_ADMIN Firmware
 *
 *********************************************************************
 * FileName:        io_cfg.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Micro-Smart Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong      04/15/11    Start
 *
 *						07/01/2013	AJA - RTC
 ********************************************************************/

#ifndef IO_CFG
#define IO_CFG

/** I N C L U D E S *************************************************/

/** T R I S *********************************************************/
#define INPUT_PIN           1
#define OUTPUT_PIN          0

/*** SPI ****************************************************/
#define trisSDO TRISCbits.TRISC7
#define trisSEL TRISBbits.TRISB3
#define trisSCK TRISBbits.TRISB4
#define trisSDI TRISBbits.TRISB5
#define SPI_SEL PORTBbits.RB3

#define SDO LATCbits.LATC7
#define SCK LATBbits.LATB4
	
// Pin directions plus Latches set for default data and clock, no open drain, Analog pins set as digital
#define mSetupMSSP1() trisSCK = INPUT_PIN;trisSDO = OUTPUT_PIN;trisSDI = INPUT_PIN;SDO = 0;SCK = 1;ODCON3bits.SPI1OD = 0;ANCON1bits.PCFG12 = 1;
			
//#define mSetSPI() trisSCK = INPUT_PIN; trisSDO = OUTPUT_PIN; ODCON3 = 0x0; ANCON1bits.PCFG12 = 1;
#define mSetSPI_CS_IN() trisSEL = INPUT_PIN;
#define mSetSPI_CS_OUT() trisSEL = OUTPUT_PIN;

#endif //IO_CFG_H
	