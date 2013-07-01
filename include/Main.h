/*********************************************************************
 *
 *                PL_ADMIN_Main Firmware
 *
 *********************************************************************
 * FileName:        main.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         BTD Systems Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong      04/24/11    Start
 ********************************************************************/

#ifndef MAIN_H
#define MAIN_H

/** I N C L U D E S **********************************************************/
#include "GenericTypeDefs.h" 
//#include "typedefs.h"


#define EECON1_RD       EECON1bits.RD
#define EECON1_WR       EECON1bits.WR

/****** Remapped Vectors ********************
*   _____________________
*   |       RESET       |   0x000000
*   |      LOW_INT      |   0x000008
*   |      HIGH_INT     |   0x000018
*   |       TRAP        |   0x000028
*   |     	 Main       |   0x00002E
*   .                   .
*   .                   .
*   |     USER_RESET    |   0x000800
*   |    USER_LOW_INT   |   0x000808
*   |    USER_HIGH_INT  |   0x000818
*   |      USER_TRAP    |   0x000828
*   |                   |
*   |   Program Memory  |
*   .                   .
*   |___________________|   0x0005FFF / 0x0007FFF
*/

/* Admin Code Version */
#define MINOR_VERSION   7				//Added high on SPI_SEL after master releases.
						  				//6 - Move to RB4 for CS and FCMEM to get subs with no CLK
						  				//7 - Disable INT0 and RB interrupts that were causing update problems
										//Version 4 has FCMEM set to allow start for SUB's with no external clock
#define MAJOR_VERSION   7		  		//Note that only the ExecCode determines the functionality of the sub.

/*
*From ToolSuite.ToolInterface definition
*    Enum BTD_ToolType
*        Qz = 1                  'QuartzController - Pressure/Temperature gauge
*        QzHT                    'Quartz Pressure/Temperature gauge with active cooling system
*        PL                      'Production Logging Tool
*        CIU                     'Cable Interface Unit
*        DepthEncoder
*        SDS = 6                 'Sensor Data Server
*        PL_SUB_ADMIN = 7        'The Admin code in the PL sub
*        PL_PT = 8               'PL sub for Pressure/Temperature
*        PL_RTC                  'PL sub for RTC
*        PL_FSK                  'PL sub for FSK comms
*        PL_SENSOR = 11          'PL sub for Sensors
*		 PL_GAMMA                'PL sub for Gamma control
*		 PL_DENSE = 13           'PL sub for Tuning fork Density
*    End Enum
*/
    
/** S T R U C T U R E S ******************************************************/
typedef union _PROG_DATA_PACKET
{
	struct{
		byte len;
		union
		{
		    rom far char *pAdr;             //Address Pointer
		    uint32 Adr32;
		    struct
		    {
		        byte low;                   //Little-indian order
		        byte high;
		        byte upper;
		        byte top;
		    };
		}ADR;
		byte data[128];
		uint32 WordData;		
	};
} PROG_DATA_PACKET;


/** P U B L I C  P R O T O T Y P E S *****************************************/
void ReadProgMem(void);
void WriteProgMem(void);
void EraseProgMem(void);
void Service_SPI ( void );

/** E X T E R N S ************************************************************/
extern volatile far PROG_DATA_PACKET Prog;

#endif //MAIN_H
