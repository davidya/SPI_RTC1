/*********************************************************************
 *
 *  PT_SUB_Main Firmware
 *
 *********************************************************************
 * FileName:        ConfigBits.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         BTD Systems Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong      04/15/10    Start
 ********************************************************************/

#ifndef ComfigBits_H
#define ComfigBits_H

//Address 30000 bits////////////////////////////////////////////////////////////////
#pragma config PLLDIV = 2, CPUDIV = OSC1_PLL2, USBDIV = 2
//PLLDIV = 1 No divide (4 MHz input)
//PLLDIV = 2 Divide by 2 (8 MHz input)
//PLLDIV = 3 Divide by 3 (12 MHz input)
//PLLDIV = 4 Divide by 4 (16 MHz input)
//PLLDIV = 5 Divide by 5 (20 MHz input)
//PLLDIV = 6 Divide by 6 (24 MHz input)
//PLLDIV = 10 Divide by 10 (40 MHz input)
//PLLDIV = 12 Divide by 12 (48 MHz input)

//CPUDIV = OSC1_PLL2 [OSC1/OSC2 Src: /1][96 MHz PLL Src: /2]
//CPUDIV = OSC2_PLL3 [OSC1/OSC2 Src: /2][96 MHz PLL Src: /3]
//CPUDIV = OSC3_PLL4 [OSC1/OSC2 Src: /3][96 MHz PLL Src: /4]
//CPUDIV = OSC4_PLL6 [OSC1/OSC2 Src: /4][96 MHz PLL Src: /6]

//USBDIV = 1 USB Clock source from OSC1/OSC2
//USBDIV = 2 USB Clock source from 96 MHz PLL/2

//Address 30001 bits////////////////////////////////////////////////////////////////
#pragma config FOSC = ECPLLIO_EC, FCMEN = ON, IESO = OFF	
//FOSC = XT_XT XT oscillator, XT used by USB
//FOSC = XTPLL_XT XT oscillator, PLL enabled, XT used by USB
//FOSC = ECIO_EC External clock, port function on RA6, EC used by
//USB
//FOSC = EC_EC External clock, CLKOUT on RA6, EC used by USB
//FOSC = ECPLLIO_EC External clock, PLL enabled, port function on RA6,
//EC used by USB
//FOSC = ECPLL_EC External clock, PLL enabled, CLKOUT on RA6, EC
//used by USB
//FOSC = INTOSCIO_EC Internal oscillator, port function on RA6, EC used by
//USB
//FOSC = INTOSC_EC Internal oscillator, CLKOUT on RA6, EC used by
//USB
//FOSC = INTOSC_XT Internal oscillator, XT used by USB
//FOSC = INTOSC_HS Internal oscillator, HS used by USB
//FOSC = HS HS oscillator, HS used by USB
//FOSC = HSPLL_HS HS oscillator, PLL enabled, HS used by USB

//FCMEM = OFF Fail-Safe Clock Monitor disabled  

//IESO = OFF Oscillator Switchover mode disabled

//Address 30002 bits////////////////////////////////////////////////////////////////
#pragma config PWRT = ON, BOR = ON, BORV = 3, VREGEN = ON
//PWRT = OFF PWRT disabled  
//Brown-out Reset enabled in hardware only and disabled in Sleep mode (SBOREN is disabled) 
//USB voltage regulator enabled  

//Address 30003 bits////////////////////////////////////////////////////////////////
#pragma config WDT = OFF, WDTPS = 32768
// HW Disabled - SW Controlled  
// 1:32768 

//Address 30005 bits////////////////////////////////////////////////////////////////
#pragma config CCP2MX = ON, PBADEN = OFF, LPT1OSC = OFF, MCLRE = ON
// CCP2 input/output is multiplexed with RC1  
// PORTB<4:0> pins are configured as digital I/O on Reset  
//   Low-Power Timer 1 Oscillator Enable bit:
//     LPT1OSC = OFF        Timer1 configured for higher power operation
//     LPT1OSC = ON         Timer1 configured for low-power operation
// MCLR pin enabled; RE3 input pin disabled  

//Address 30006 bits////////////////////////////////////////////////////////////////
#pragma config STVREN = ON, LVP = OFF, ICPRT = OFF, XINST = OFF, DEBUG = OFF
// Stack full/underflow will cause Reset  
// Single-Supply ICSP disabled  
// ICPORT disabled  
// Instruction set extension and Indexed Addressing mode disabled (Legacy mode)

//Address 30008 bits////////////////////////////////////////////////////////////////
#pragma config CP0 = OFF,CP1 = OFF, CP2 = OFF, CP3 = OFF           
//Block 0-3 code-protected

//Address 30009 bits////////////////////////////////////////////////////////////////
#pragma config CPD = OFF, CPB = OFF            
//Boot block (000000-0007FFh) code-protected
// Data EEPROM not code-protected 

//Address 3000A bits////////////////////////////////////////////////////////////////
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF			
//Write Protection bit Block 0:
//WRT0 = ON            Block 0 (000800-001FFFh) write-protected
//WRT0 = OFF           Block 0 (000800-001FFFh) not write-protected
//Write Protection bit Block 1:
//WRT1 = ON            Block 1 (002000-003FFFh) write-protected
//WRT1 = OFF           Block 1 (002000-003FFFh) not write-protected
//Write Protection bit Block 2:
//WRT2 = ON            Block 2 (004000-005FFFh) write-protected
//WRT2 = OFF           Block 2 (004000-005FFFh) not write-protected
//Write Protection bit Block 3:
//WRT3 = ON            Block 3 (006000-007FFFh) write-protected
//WRT3 = OFF           Block 3 (006000-007FFFh) not write-protected

//Address 3000B bits////////////////////////////////////////////////////////////////
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF		
//WRTC = ON            Configuration registers (300000-3000FFh) write-protected
//WRTC = OFF           Configuration registers (300000-3000FFh) not write-protected
//Data EEPROM Write Protection bit:
//WRTD = ON            Data EEPROM write-protected
//WRTD = OFF           Data EEPROM not write-protected

//Address 3000C bits////////////////////////////////////////////////////////////////
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
//Table Read Protection bit Block 0:
//EBTR0 = ON           Block 0 (000800-001FFFh) protected from table reads executed in other blocks
//EBTR0 = OFF          Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
//Table Read Protection bit Block 1:
//EBTR1 = ON           Block 1 (002000-003FFFh) protected from table reads executed in other blocks
//EBTR1 = OFF          Block 1 (002000-003FFFh) not protected from table reads executed in other blocks
//Table Read Protection bit Block 2:
//EBTR2 = ON           Block 2 (004000-005FFFh) protected from table reads executed in other blocks
//EBTR2 = OFF          Block 2 (004000-005FFFh) not protected from table reads executed in other blocks
//Table Read Protection bit Block 3:
//EBTR3 = ON           Block 3 (006000-007FFFh) protected from table reads executed in other blocks
//EBTR3 = OFF          Block 3 (006000-007FFFh) not protected from table reads executed in other blocks

//Address 3000D bits////////////////////////////////////////////////////////////////
#pragma config EBTRB = OFF		
//Boot Block Table Read Protection:
//EBTRB = ON           Boot block (000000-0007FFh) protected from table reads executed in other blocks
//EBTRB = OFF          Boot block (000000-0007FFh) not protected from table reads executed in other blocks

#endif