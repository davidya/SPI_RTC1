/*********************************************************************
 *
 *                SUB_ADMIN_Main Firmware
 *
 *********************************************************************
 * FileName:        LogCodeVar.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         BTD Systems Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong      04/15/11
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "GenericTypeDefs.h"                   
#define EXECCODE_STARTADDR 0x2000
#define EXECCODE_ENTRY EXECCODE_STARTADDR + 0x8E
#define INT_HIGH_OFFS EXECCODE_STARTADDR +0x82
#define INT_LOW_OFFS EXECCODE_STARTADDR + 0x88
#define RECORD_TYPE 0								//Just for compatibility with the Qz gauges
#define LOGFLASH_STARTSECTOR 0
#define LOGFLASH_ENDSECTOR 2048

extern rom struct				//Need to sync this with ExecCode
{
	char ExecCodeVersion[2];
	char RecordType;			//NA
	char LogFlashStartSector;	//NA
	char LogFlashEndSector;	    //NA
} EXEC_CODE_VAR;
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

extern rom stdFn jump_table[];
typedef enum
{
	SUB_READSTATUS	    = 0x40,			
	SUB_GETPGMEM  		= 0x80,			
	SUB_PROGRAMEXEC		= 0xc0,			
	SUB_EXECPROCESS   	= 0x01,			//Dont use this. Let the Admin code get the status via the SUB_EXECPROCESS command
	SUB_GETCOEFFSADDR  	= 0x02,
	SUB_MEASURE  	  	= 0x03,			//A broadcast command to all SUB's which support it
	SUB_GETDATA  	  	= 0x04,
	SUB_RESET	  	  	= 0x05,			
	SUB_SENDDATA  	  	= 0x06,			//FSK SUB only. Sends 32 bytes of data.
	SUB_GETTIME	  	  	= 0x07,			//RTC SUB only
	SUB_CLOCKRST  	  	= 0x08,			//RTC SUB only. Has the RTC been powered down ?
	SUB_SETTIME	  	  	= 0x09,			//RTC SUB only.
	SUB_POWER	  	  	= 0x0a,			//GAMMA SUB only.
	SUB_SPARE1	  	  	= 0x0b,
	SUB_SPARE2	  	  	= 0x0c,
	SUB_SPARE3	  	  	= 0x0d,
	SUB_SPARE4	  	  	= 0x0e,
	SUB_SPARE5	  	  	= 0x0f
}SPI_CMD;

/*<code>
 7 6 5 4 3 2 1 0 - Field name
 | | \_________/
 | |      +------- subtype  - The type of sub
 | +-------------- error 	- Sub had error on last operation when set
 +---------------- busy 	- Sub is busy when set
</code>
*/

typedef union
{
    BYTE    bitmap;
    struct
    {
        BYTE subtype:   6;
        BYTE error: 	1;
        BYTE busy: 		1;
    }field;

} SUB_STATUS;

typedef enum
{
	EE_SERIAL_LOW,
	EE_SERIAL_HIGH
}EE_LOCS;

char ExecInit( UINT24 Addr, char * Data );
char ExecProcess( UINT24 Addr, char * Data );
char GetCodeAddr( UINT24 Addr, char * Data );
char GetCoeffsAddr( UINT24 Addr, char * Data );
char Measure( UINT24 Addr, char * Data );
char GetData( UINT24 Addr, char * Data );
char Rst( UINT24 Addr, char * Data );
char SendData( UINT24 Addr, char * Data );
char GetTime( UINT24 Addr, char * Data );
char ClockRst( UINT24 Addr, char * Data );
char SetTime( UINT24 Addr, char * Data );
char Power( UINT24 Addr, char * Data );
char SpareFunc1( UINT24 Addr, char * Data );
char SpareFunc2( UINT24 Addr, char * Data );
char SpareFunc3( UINT24 Addr, char * Data );
char SpareFunc4( UINT24 Addr, char * Data );
char SpareFunc5( UINT24 Addr, char * Data );




