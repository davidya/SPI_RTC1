/*********************************************************************
 *
 *                 PT_SUB_Main Firmware
 *
 *********************************************************************
 * FileName:        ExecCodeVar.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         BTD Systems Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong  04/03/10    Derived from HTV6
 *					04/15/11    Common include file for both Logcode 
 * 				    and Main.
 ********************************************************************/

/** I N C L U D E S **********************************************************/
#include <p18cxxx.h>
#include "GenericTypeDefs.h" 
#include "ExecCodeVar.h"              

#pragma romdata EXECCODEVAR
rom struct						//Need to sync this with LogCode
{
	char ExecCodeVersion[2];	
	char RecordType;			//NA
	char LogFlashStartSector;	//NA
	Word LogFlashEndSector;	//NA
} EXEC_CODE_VAR_STUB = {
	0xff,0xff,
	0,
	0,
	0
};
