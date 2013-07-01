/*********************************************************************
 *
 *  PL_Main Firmware
 *
 *********************************************************************
 * FileName:        ConfigBits.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Micro-Smart Inc
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * David Armstrong      04/03/10    Start
 * 				    	02/19/13	Convert SPI to I2C
 *						04/25/13	Convert to 46j53
 *						07/01/13	Andrew - use in RTC project
 ********************************************************************/

#ifndef ComfigBits_H
#define ComfigBits_H

//Note: Use the hlpPIC18ConfigSet.html in the MCC18/Doc subfolder for values

//Address 30000/XXXF8h CONFIG1L bits////////////////////////////////////////////////////////////////
#pragma config WDTEN = OFF, PLLDIV = 2, STVREN = ON, CFGPLLEN = OFF, XINST = OFF
//bit 3-1 PLLDIV<2:0>: Oscillator Selection bits
//Divider must be selected to provide a 4 MHz input into the 96 MHz PLL.
//111 = No divide – oscillator used directly (4 MHz input)
//110 = Oscillator divided by 2 (8 MHz input)
//101 = Oscillator divided by 3 (12 MHz input)
//100 = Oscillator divided by 4 (16 MHz input)
//011 = Oscillator divided by 5 (20 MHz input)
//010 = Oscillator divided by 6 (24 MHz input)
//001 = Oscillator divided by 10 (40 MHz input)
//000 = Oscillator divided by 12 (48 MHz input)
//bit 6 XINST: Extended Instruction Set Enable bit
//1 = Instruction set extension and Indexed Addressing mode are enabled
//0 = Instruction set extension and Indexed Addressing mode are disabled
//bit 0 WDTEN: Watchdog Timer Enable bit
//1 = WDT is enabled
//0 = WDT is disabled (control is placed on the SWDTEN bit)
//bit 5 STVREN: Stack Overflow/Underflow Reset Enable bit
//1 = Reset on stack overflow/underflow is enabled
//0 = Reset on stack overflow/underflow is disabled
//bit 4 CFGPLLEN: PLL Enable bit
//1 = 96 MHz PLL is disabled
//0 = 96 MHz PLL is enabled

//Address 30001/XXXF9h CONFIG1H bits////////////////////////////////////////////////////////////////
#pragma config CPUDIV = OSC1, CP0 = OFF	
//bit 7-4 Unimplemented: Program the corresponding Flash Configuration bit to ‘1’
//bit 3 Unimplemented: Maintain as ‘0’
//bit 2 CP0: Code Protection bit
//1 = Program memory is not code-protected
//0 = Program memory is code-protected
//bit 1-0 CPDIV<1:0>: CPU System Clock Selection bits
//11 = No CPU system clock divide
//10 = CPU system clock is divided by 2
//01 = CPU system clock is divided by 3
//00 = CPU system clock is divided by 6

//Address 30002/XXXFAh CONFIG2L bits////////////////////////////////////////////////////////////////
#pragma config OSC = INTOSC, SOSCSEL = DIG, CLKOEC = ON, FCMEN = ON, IESO = ON
//bit 7 IESO: Two-Speed Start-up (Internal/External Oscillator Switchover) Control bit
//1 = Two-Speed Start-up is enabled
//0 = Two-Speed Start-up is disabled
//bit 6 FCMEN: Fail-Safe Clock Monitor Enable bit
//1 = Fail-Safe Clock Monitor is enabled
//0 = Fail-Safe Clock Monitor is disabled
//bit 5 CLKOEC: CLKO Enable Configuration bit
//(Applicable only when the FOSC<2:1> bits are configured for EC or ECPLL mode.)
//1 = CLKO output signal active on the RA6 pin
//0 = CLKO output is disabled
//bit 4-3 SOSCSEL<1:0>: T1OSC/SOSC Power Selection Configuration bits
//11 = High-power T1OSC/SOSC circuit is selected
//10 = Digital (SCLKI) mode is enabled
//01 = Low-power T1OSC/SOSC circuit is selected
//00 = Reserved
//bit 2-0 FOSC<2:0>: Oscillator Selection bits
//111 = ECPLL oscillator with PLL software controlled, CLKO on RA6
//110 = EC oscillator with CLKO on RA6
//101 = HSPLL oscillator with PLL software controlled
//100 = HS oscillator
//011 = INTOSCPLLO, internal oscillator with PLL software controlled, CLKO on RA6, port function on
//RA7
//010 = INTOSCPLL, internal oscillator with PLL software controlled, port function on RA6 and RA7
//001 = INTOSCO internal oscillator block (INTRC/INTOSC) with CLKO on RA6, port function on RA7
//000 = INTOSC internal oscillator block (INTRC/INTOSC), port function on RA6 and RA7

//Address 30003/XXXFBh bits////////////////////////////////////////////////////////////////
#pragma config WDTPS = 32768
//bit 7-4 Unimplemented: Program the corresponding Flash Configuration bit to ‘1’
//bit 3-0 WDTPS<3:0>: Watchdog Timer Postscale Select bits
//1111 = 1:32,768
//1110 = 1:16,384
//1101 = 1:8,192
//1100 = 1:4,096
//1011 = 1:2,048
//1010 = 1:1,024
//1001 = 1:512
//1000 = 1:256
//0111 = 1:128
//0110 = 1:64
//0101 = 1:32
//0100 = 1:16
//0011 = 1:8
//0010 = 1:4
//0001 = 1:2
//0000 = 1:1

//Address 30004 bits////////////////////////////////////////////////////////////////
#pragma config DSWDTOSC = T1OSCREF, RTCOSC = INTOSCREF, DSBOREN = OFF, DSWDTEN = OFF, DSWDTPS = G2
//bit 7-4 DSWDTPS<3:0>: Deep Sleep Watchdog Timer Postscale Select bits(1)
//The DSWDT prescaler is 32. This creates an approximate base time unit of 1 ms.
//1111 = 1:2,147,483,648 (25.7 days) - G2
//1110 = 1:536,870,912 (6.4 days) - M536
//1101 = 1:134,217,728 (38.5 hours) - M134
//1100 = 1:33,554,432 (9.6 hours) - M33
//1011 = 1:8,388,608 (2.4 hours) - M8
//1010 = 1:2,097,152 (36 minutes) - M2
//1001 = 1:524,288 (9 minutes) - K524
//1000 = 1:131,072 (135 seconds) - K131
//0111 = 1:32,768 (34 seconds) - K32
//0110 = 1:8,192 (8.5 seconds) - 8192
//0101 = 1:2,048 (2.1 seconds)
//0100 = 1:512 (528 ms)
//0011 = 1:128 (132 ms)
//0010 = 1:32 (33 ms)
//0001 = 1:8 (8.3 ms)
//0000 = 1:2 (2.1 ms)
//bit 3 DSWDTEN: Deep Sleep Watchdog Timer Enable bit(1)
//1 = DSWDT is enabled
//0 = DSWDT is disabled
//bit 2 DSBOREN: “F” Device Deep Sleep BOR Enable bit, “LF” Device VDD BOR Enable bit
//For “F” Devices:
//1 = VDD sensing BOR is enabled in Deep Sleep
//0 = VDD sensing BOR circuit is always disabled
//For “LF” Devices:
//1 = VDD sensing BOR circuit is always enabled
//0 = VDD sensing BOR circuit is always disabled
//bit 1 RTCOSC: RTCC Reference Clock Select bit
//1 = RTCC uses T1OSC/T1CKI as reference clock
//0 = RTCC uses INTRC as the reference clock
//bit 0 DSWDTOSC: DSWDT Reference Clock Select bit(1)
//1 = DSWDT uses INTRC as the reference clock
//0 = DSWDT uses T1OSC/T1CKI as reference clock

//Address 30005 bits////////////////////////////////////////////////////////////////
#pragma config IOL1WAY = ON, ADCSEL = BIT12, MSSP7B_EN = MSK7
//bit 7-4 Unimplemented: Program the corresponding Flash Configuration bit to ‘1’
//bit 3 MSSPMSK: MSSP 7-Bit Address Masking Mode Enable bit
//1 = 7-Bit Address Masking mode is enabled
//0 = 5-Bit Address Masking mode is enabled
//bit 2 Unimplemented: Read as ‘0’
//bit 1 ADCSEL: A/D Converter Mode
//1 = 10-bit conversion mode is enabled
//0 = 12-bit conversion mode is enabled
//bit 0 IOL1WAY: IOLOCK One-Way Set Enable bit
//1 = IOLOCK bit (PPSCON<0>) can be set once, provided the unlock sequence has been completed.
//Once set, the Peripheral Pin Select registers cannot be written to a second time.
//0 = IOLOCK bit (PPSCON<0>) can be set and cleared as needed, provided the unlock sequence has
//been completed

//Address 30006 bits////////////////////////////////////////////////////////////////
#pragma config WPCFG = OFF
//bit 7 WPCFG: Write/Erase Protect Configuration Region Select bit (valid when WPDIS = 0)
//1 = Configuration Words page is not erase/write-protected unless WPEND and WPFP<5:0> settings
//include the Configuration Words page(1)
//0 = Configuration Words page is erase/write-protected, regardless of WPEND and WPFP<5:0>(1)
//bit 6-0 WPFP<6:0>: Write/Erase Protect Page Start/End Location bits
//Used with WPEND bit to define which pages in Flash will be write/erase protected.

//Address 30007 bits////////////////////////////////////////////////////////////////
#pragma config LS48MHZ = SYS48X8, WPEND = PAGE_0         
//bit 7-4 Unimplemented: Program the corresponding Flash Configuration bit to ‘1’
//bit 3 LS48MHZ: Low-Speed USB Clock Selection
//1 = 48-MHz system clock is expected; divide-by-8 generates low-speed USB clock
//0 = 24-MHz system clock is expected; divide-by-4 generates low-speed USB clock
//bit 2 Unimplemented: Read as ‘0’
//bit 1 WPEND: Write-Protect Disable bit
//1 = Flash pages, WPFP<6:0> to (Configuration Words page), are write/erase protected
//0 = Flash pages 0 to WPFP<6:0> are write/erase-protected
//bit 0 WPDIS: Write-Protect Disable bit
//1 = WPFP<5:0>, WPEND and WPCFG bits are ignored; all Flash memory may be erased or written
//0 = WPFP<5:0>, WPEND and WPCFG bits enabled; erase/write-protect is active for the selected
//region(s)



#endif