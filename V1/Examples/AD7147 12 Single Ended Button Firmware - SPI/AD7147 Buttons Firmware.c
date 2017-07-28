//#pragma OPTIMIZE (9)
/****************************************************************************/
/*																			*/
/* AD7147 Standard Buttons Software											*/
/* --------------------------												*/
/* Date: 07/06/2007															*/
/* Author: ADI																*/
/*																			*/
/* Descripton:																*/
/* -----------																*/
/* This firmware configures the AD7147 to respond to 12 buttons.			*/
/* Every time a button is touched, a bit is set in the High Limit Interrupt */
/* Status register. The AD7147 fires an interrupt only when a button is 	*/
/* touched or when we lift off.												*/
/****************************************************************************/
/* Sensor Buttons: ButtonStatus												*/
/* ======================================									*/
/*																			*/
/*	bit: 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0								*/
/*       			  |  | | | | | | | | | | |-	Stage 0 - CIN 0				*/
/*       			  |  | | | | | | | | | |---	Stage 1 - CIN 1				*/
/*       			  |  | | | | | | | | |----- Stage 2 - CIN 2				*/
/*       			  |  | | | | | | | |-------	Stage 3 - CIN 3				*/
/*       			  |  | | | | | | |---------	Stage 4 - CIN 4				*/
/*       			  |  | | | | | |-----------	Stage 5 - CIN 5				*/
/*       			  |  | | | | |-------------	Stage 6 - CIN 6				*/
/*       			  |  | | | |---------------	Stage 7 - CIN 7				*/
/*       			  |  | | |-----------------	Stage 8 - CIN 8				*/
/*       			  |  | |------------------- Stage 9 - CIN 9				*/
/*       			  |  |---------------------	Stage 10 - CIN 10			*/
/*       			  |------------------------	Stage 11 - CIN 11			*/
/*       				   													*/
/****************************************************************************/


#include <ADUC841.H>
#include <intrins.h>
#include "AD7147regMap.h"
#include "General Definitions.h"
#include "SPI.h"
#include "Single Ended Button Config.h"

//---------------------------------
//Function prototypes
//---------------------------------
static int ServiceAD7147Isr(void);
static void ForceCalibration(void);
static WORD DecodeButtons(const WORD HighLimitStatusRegister);
//---------------------------------
//Button Status Variable
//---------------------------------
WORD ButtonStatus;

//---------------------------------
//void AD7147_Isr() interrupt 0
//---------------------------------
//---------------------------------
//Interrupt service routine that is executed when the INT0 pin goes low.
//--------------------------------------------------------------------------------
/********************************************************************************************/
/*//////////////////////////////////////////////////////////////////////////////////////////*/
// This function declaration is specific to the ADuC841 and needs to be changed for another //
// host processor. The interrupt vector number may be different 		   					//
/*//////////////////////////////////////////////////////////////////////////////////////////*/
/********************************************************************************************/
static void AD7147_Isr() interrupt 0
{
	EX0=0;
	ServiceAD7147Isr();
	EX0=1;
	return;
}

void main (void)
{
	//---------------------------
	//Device initialisation
	//---------------------------
	/********************************************************************************************/
	/*//////////////////////////////////////////////////////////////////////////////////////////*/
	// Specific to the ADuC841, this section configures the ADuC841 pins as input or as output. //
 	// This needs to be changed for another host processor 		   							  	//
	/*//////////////////////////////////////////////////////////////////////////////////////////*/
	/********************************************************************************************/
	DOUT=1;				//Set the DOUT pin
	CLK=1;				//Set the CLK pin
	ADUC841_INT0=1;		//Makes sure that the INT0 pin on the ADuC841 is be an input.
	
	/********************************************************************************/
	/*//////////////////////////////////////////////////////////////////////////////*/
	// Specific to the ADuC841, this line can be removed for another host processor //
	/*//////////////////////////////////////////////////////////////////////////////*/
	/********************************************************************************/	
	CFG841 |= 1;	//Enable the extended internal RAM		
	
	//-----------------
	//Configure Device
	//-----------------
	ConfigAD7147();	
	
	//Initialise Status Variable
	//--------------------
	ButtonStatus=0;

	/*******************************************************************************************/
	/*/////////////////////////////////////////////////////////////////////////////////////////*/
	// Enable interrupt after software initialisation. This section cannot be placed anywhere  //
	// else. These instructions must be changed for another host processor.					   //
	/*/////////////////////////////////////////////////////////////////////////////////////////*/
	/*******************************************************************************************/
	IT0=0x1;			//INT0 interrupt is negative edged triggered
	EX0=1;				//Enable external interrupt "0" //AD7147 interrupt
	EA=1;				//Enable all interrupts
	
	while(1)
	{	
		//Access our Status Register Here 
		/****************************************************************************/
		/* Sensor Buttons: ButtonStatus												*/
		/* ======================================									*/
		/*																			*/
		/*	bit: 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0								*/
		/*       			  |  | | | | | | | | | | |-	Stage 0 - CIN 0				*/
		/*       			  |  | | | | | | | | | |---	Stage 1 - CIN 1				*/
		/*       			  |  | | | | | | | | |----- Stage 2 - CIN 2				*/
		/*       			  |  | | | | | | | |-------	Stage 3 - CIN 3				*/
		/*       			  |  | | | | | | |---------	Stage 4 - CIN 4				*/
		/*       			  |  | | | | | |-----------	Stage 5 - CIN 5				*/
		/*       			  |  | | | | |-------------	Stage 6 - CIN 6				*/
		/*       			  |  | | | |---------------	Stage 7 - CIN 7				*/
		/*       			  |  | | |-----------------	Stage 8 - CIN 8				*/
		/*       			  |  | |------------------- Stage 9 - CIN 9				*/
		/*       			  |  |---------------------	Stage 10 - CIN 10			*/
		/*       			  |------------------------	Stage 11 - CIN 11			*/
		/*       				   													*/
		/****************************************************************************/	
	}
}


	
//---------------------------------
//Function  definitions 
//---------------------------------

//ServiceAD7147Isr();
//-----------------------------------------------------------------
// Function called by the AD7147 ISR. Anything that must be 
// executed during the ISR needs to be done here
//-----------------------------------------------------------------
static int ServiceAD7147Isr(void)
{
	//Read thresholds and proximity registers
	ReadFromAD7147(STAGE_LOW_LIMIT_INT, 2, AD7147Registers, STAGE_LOW_LIMIT_INT);	

	//Recover from errors if needed
	if (((AD7147Registers[STAGE_LOW_LIMIT_INT] & POWER_UP_INTERRUPT) != 0x0000) && 
		((AD7147Registers[STAGE_HIGH_LIMIT_INT] & POWER_UP_INTERRUPT) == 0x0000))
	{
		ForceCalibration();		
	}
	else
		ButtonStatus=DecodeButtons(AD7147Registers[STAGE_HIGH_LIMIT_INT]);		
}

//ForceCalibration();
//-----------------------------------------------------------------
// Function called by ServiceAD7147Isr when there is a touch on 
// power up or when there is a problem with the calibration.
//-----------------------------------------------------------------
static void ForceCalibration(void)
{
	ReadFromAD7147(AMB_COMP_CTRL0, 1, AD7147Registers, AMB_COMP_CTRL0);
	AD7147Registers[AMB_COMP_CTRL0] |= 0x4000;
	WriteToAD7147(AMB_COMP_CTRL0, 1, AD7147Registers, AMB_COMP_CTRL0);
}

//DecodeButtons()
//-----------------------------------------------------------------
// Function called by ServiceAD7147Isr. This function retrieves the
// button being set based on the High Limit Status Register.
//-----------------------------------------------------------------
static WORD DecodeButtons(const WORD HighLimitStatusRegister)
{
	WORD ButtonStatusValue=0;
	
	if ((HighLimitStatusRegister & 0x0001) == 0x0001)
		ButtonStatusValue |= 0x0001;
	
	if ((HighLimitStatusRegister & 0x0002) == 0x0002)
		ButtonStatusValue |= 0x0002;
	
	if ((HighLimitStatusRegister & 0x0004) == 0x0004)
		ButtonStatusValue |= 0x0004;
	
	if ((HighLimitStatusRegister & 0x0008) == 0x0008)
		ButtonStatusValue |= 0x0008;

	if ((HighLimitStatusRegister & 0x0010) == 0x0010)
		ButtonStatusValue |= 0x0010;

	if ((HighLimitStatusRegister & 0x0020) == 0x0020)
		ButtonStatusValue |= 0x0020;

	if ((HighLimitStatusRegister & 0x0040) == 0x0040)
		ButtonStatusValue |= 0x0040;

	if ((HighLimitStatusRegister & 0x0080) == 0x0080)
		ButtonStatusValue |= 0x0080;

	if ((HighLimitStatusRegister & 0x0100) == 0x0100)
		ButtonStatusValue |= 0x0100;

	if ((HighLimitStatusRegister & 0x0200) == 0x0200)
		ButtonStatusValue |= 0x0200;

	if ((HighLimitStatusRegister & 0x0400) == 0x0400)
		ButtonStatusValue |= 0x0400;

	if ((HighLimitStatusRegister & 0x0800) == 0x0800)
		ButtonStatusValue |= 0x0800;
	
	return (ButtonStatusValue);
}
