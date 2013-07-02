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
#define trisSDO TRISBbits.TRISB5
#define trisSEL TRISBbits.TRISB3
//#define SPI_SEL PORTCbits.RC6	//Temporary for Sensor sub on first main board (will move to common
#define SPI_SEL PORTBbits.RB3				
#define mSetSPI_CS_IN() trisSEL = INPUT_PIN;
#define mSetSPI_CS_OUT() trisSEL = OUTPUT_PIN;

#endif //IO_CFG_H
	