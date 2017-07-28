#include "micro_setup.h"
#include "AD7147.h"
#include "spi.h"
#include "uart.h"

void setup_AD7147(unsigned int cdc)
{   
    unsigned int StageBuffer[8];
    unsigned int AD7147Registers[8];
    get_CDC(cdc,0);
    // BANK 2 REGISTERS CONFIGURATION
    // StageBuffer[0] StageX_Connections[6:0] setup
    // StageBuffer[1] StageX_Connections[12:7] setup
    // StageBuffer[2] StageX_AFE_offset Control 
    // StageBuffer[3] StageX_Sensitivity 
    // StageBuffer[4] StageX_Offset_Low Control 
    // StageBuffer[5] StageX_Offset_High Control 
    // StageBuffer[6] StageX_Offset_High_Clamp Control 
    // StageBuffer[7] StageX_Offset_Low_Clamp Control 
    // WriteToAD7147(STAGEX_CONNECTION, 8, StageBuffer, 0);
    
    //===========================
    //= Stage 0 - CIN0 (+) S1
    //===========================
    StageBuffer[0] = 0xFFFE;	//Register 0x80
    StageBuffer[1] = 0x1FFF;	//Register 0x81
    StageBuffer[2] = 0x0000;	//Register 0x82
    StageBuffer[3] = 0x2121;	//Register 0x83
    StageBuffer[4] = 4000;      //Register 0x84	
    StageBuffer[5] = 4000;   	//Register 0x85
    StageBuffer[6] = 4250;      //Register 0x86	
    StageBuffer[7] = 4250;      //Register 0x87
    write_AD7147(STAGE0_CONNECTION, 8, StageBuffer,0);
    
    //===========================
    //= Stage 1 - CIN1 (+) S2
    //===========================
    StageBuffer[0]=0xFFFB;	//Register 0x88
    StageBuffer[1]=0x1FFF;	//Register 0x89
    StageBuffer[2]=0x0100;	//Register 0x8A
    StageBuffer[3]=0x2121;	//Register 0x8B
    StageBuffer[4]=4000;	//Register 0x8C
    StageBuffer[5]=4000;	//Register 0x8D
    StageBuffer[6]=4250;	//Register 0x8E
    StageBuffer[7]=4250;	//Register 0x8F
	write_AD7147(STAGE1_CONNECTION, 8, StageBuffer,0);

    //===========================
    //= Stage 2 - CIN2 (+) S3
    //===========================
    StageBuffer[0]=0xFFEF;	//Register 0x90
    StageBuffer[1]=0x1FFF;	//Register 0x91
    StageBuffer[2]=0x0100;	//Register 0x92
    StageBuffer[3]=0x2121;	//Register 0x93
    StageBuffer[4]=4000;	//Register 0x94
    StageBuffer[5]=4000;	//Register 0x95
    StageBuffer[6]=4250;	//Register 0x96
    StageBuffer[7]=4250;	//Register 0x97
	write_AD7147(STAGE2_CONNECTION, 8, StageBuffer,0);

    //===========================
    //= Stage 3 - CIN3 (+) S4
    //===========================
    StageBuffer[0]=0xFFBF;	//Register 0x98
    StageBuffer[1]=0x1FFF;	//Register 0x99
    StageBuffer[2]=0x0100;	//Register 0x9A
    StageBuffer[3]=0x2121;	//Register 0x9B
    StageBuffer[4]=4000;	//Register 0x9C
    StageBuffer[5]=4000;	//Register 0x9D
    StageBuffer[6]=4250;	//Register 0x9E
    StageBuffer[7]=4250;	//Register 0x9F
    write_AD7147(STAGE3_CONNECTION, 8, StageBuffer,0);

    //===========================
    //= Stage 4 - CIN4 (+) S5
    //===========================
    StageBuffer[0]=0xFEFF;	//Register 0xA0
    StageBuffer[1]=0x1FFF;	//Register 0xA1
    StageBuffer[2]=0x0100;	//Register 0xA2
    StageBuffer[3]=0x2121;	//Register 0xA3
    StageBuffer[4]=4000;	//Register 0xA4
    StageBuffer[5]=4000;	//Register 0xA5
    StageBuffer[6]=4250;	//Register 0xA6
    StageBuffer[7]=4250;	//Register 0xA7
    write_AD7147(STAGE4_CONNECTION, 8, StageBuffer,0);

    //===========================
    //= Stage 5 - CIN5 (+) S6
    //===========================
    StageBuffer[0]=0xFBFF;	//Register 0xA8
    StageBuffer[1]=0x1FFF;	//Register 0xA9
    StageBuffer[2]=0x0100;	//Register 0xAA
    StageBuffer[3]=0x2121;	//Register 0xAB
    StageBuffer[4]=4000;	//Register 0xAC
    StageBuffer[5]=4000;	//Register 0xAD
    StageBuffer[6]=4250;	//Register 0xAE
    StageBuffer[7]=4250;	//Register 0xAF
	write_AD7147(STAGE5_CONNECTION, 8, StageBuffer,0);

	//===========================
    //= Stage 6 - CIN6 (+) S7
    //===========================
    StageBuffer[0]=0xEFFF;	//Register 0xB0
    StageBuffer[1]=0x1FFF;	//Register 0xB1
    StageBuffer[2]=0x0100;	//Register 0xB2
    StageBuffer[3]=0x2121;	//Register 0xB3
    StageBuffer[4]=4000;	//Register 0xB4
    StageBuffer[5]=4000;	//Register 0xB5
    StageBuffer[6]=4250;	//Register 0xB6
    StageBuffer[7]=4250;	//Register 0xB7
    write_AD7147(STAGE6_CONNECTION, 8, StageBuffer,0);

    //===========================
    //= Stage 7 - CIN7 (+) S8
    //===========================
    StageBuffer[0]=0xFFFF;	//Register 0xB8
    StageBuffer[1]=0x1FFE;	//Register 0xB9
    StageBuffer[2]=0x0100;	//Register 0xBA
    StageBuffer[3]=0x2121;	//Register 0xBB
    StageBuffer[4]=4000;	//Register 0xBC
    StageBuffer[5]=4000;  	//Register 0xBD
    StageBuffer[6]=4250;	//Register 0xBE
    StageBuffer[7]=4250;	//Register 0xBF
    write_AD7147(STAGE7_CONNECTION, 8, StageBuffer,0);

    //===========================
    //= Stage 8 - CIN8 (+) S9
    //===========================
    StageBuffer[0]=0xFFFF;	//Register 0xC0
    StageBuffer[1]=0x3FFF;	//Register 0xC1
    StageBuffer[2]=0x0000;	//Register 0xC2
    StageBuffer[3]=0x2626;	//Register 0xC3
    StageBuffer[4]=3000;	//Register 0xC4
    StageBuffer[5]=3000;	//Register 0xC5
    StageBuffer[6]=4000;	//Register 0xC6
    StageBuffer[7]=4000;	//Register 0xC7
    write_AD7147(STAGE8_CONNECTION, 8, StageBuffer,0);

    //===========================
    //= Stage 9 - CIN9 (+) S10
    //===========================
    StageBuffer[0]=0xFFFF;	//Register 0xC8	
    StageBuffer[1]=0x3FFF;	//Register 0xC9
    StageBuffer[2]=0x0000;	//Register 0xCA
    StageBuffer[3]=0x2626;	//Register 0xCB
    StageBuffer[4]=3000;	//Register 0xCC
    StageBuffer[5]=3000;	//Register 0xCD
    StageBuffer[6]=4000;	//Register 0xCE
    StageBuffer[7]=4000;	//Register 0xCF
    write_AD7147(STAGE9_CONNECTION, 8, StageBuffer,0);

    //============================
    //= Stage 10 - CIN10 (+) S11
    //============================
    StageBuffer[0]=0xFFFF;	//Register 0xD0
    StageBuffer[1]=0x3FFF;	//Register 0xD1
    StageBuffer[2]=0x0000;	//Register 0xD2
    StageBuffer[3]=0x2626;	//Register 0xD3
    StageBuffer[4]=3000;	//Register 0xD4
    StageBuffer[5]=3000;	//Register 0xD5
    StageBuffer[6]=4000;	//Register 0xD6
    StageBuffer[7]=4000;	//Register 0xD7
	write_AD7147(STAGE10_CONNECTION, 8, StageBuffer,0);

    //============================
    //= Stage 11 - CIN11 (+) S12
    //============================
    StageBuffer[0]=0xFFFF;	//Register 0xD8
    StageBuffer[1]=0x3FFF;	//Register 0xD9
    StageBuffer[2]=0x0000;	//Register 0xDA
    StageBuffer[3]=0x2626;	//Register 0xDB
    StageBuffer[4]=3000;	//Register 0xDC
    StageBuffer[5]=3000;	//Register 0xDD
    StageBuffer[6]=4000;	//Register 0xDE
    StageBuffer[7]=4000;	//Register 0xDF
	write_AD7147(STAGE11_CONNECTION, 8, StageBuffer,0);

    //--------------------------------------------------------------------------//
    //-------------------------Bank 1 Registers---------------------------------//
    //--------------------------------------------------------------------------//
    //Initialization of the first register bank but not the STAGE_CAL_EN
    AD7147Registers[0] = 0x02B2; 			//Register 0x000
    write_AD7147(PWR_CONTROL, 1, AD7147Registers,0);
    
    unsigned int int_low = read_AD7147_interrupt(STAGE_LOW_LIMIT_INT);
    unsigned int int_high = read_AD7147_interrupt(STAGE_HIGH_LIMIT_INT);
    unsigned int int_complete = read_AD7147_interrupt(STAGE_COMPLETE_LIMIT_INT);
    
    AD7147Registers[2] = 0x3230;			//Register 0x002
    AD7147Registers[3] = 0x0419;			//Register 0x003
    AD7147Registers[4] = 0x0832;			//Register 0x004
    AD7147Registers[5] = 0x0000;            //Register 0x005
    AD7147Registers[6] = 0x0000;            //Register 0x006
    AD7147Registers[7] = 0x0001;            //Register 0x007
    write_AD7147(AMB_COMP_CTRL0, 6, AD7147Registers,2);
    
    //Enable data path for all sequences and enable calibration on 8 stages
    AD7147Registers[1] = 0x00FF;			//Register 0x001
    write_AD7147(STAGE_CAL_EN, 1, AD7147Registers,1);

    AD7147Registers[0] = 0x0200;			//Register 0x000
    write_AD7147(PWR_CONTROL, 1, AD7147Registers,0);
    
    //Read high and low limit interrupt status before to enable the interrupts
	//read_AD7147(STAGE_LOW_LIMIT_INT, 3, AD7147Registers); //Registers 0x08 & 0x09 & 0x0A
    int_low = read_AD7147_interrupt(STAGE_LOW_LIMIT_INT);
    int_high = read_AD7147_interrupt(STAGE_HIGH_LIMIT_INT);
    int_complete = read_AD7147_interrupt(STAGE_COMPLETE_LIMIT_INT);
    get_CDC(cdc,1);
}

void write_AD7147(unsigned int RegisterAddress, unsigned int NumberOfRegisters, unsigned int DataBuffer[], unsigned int index)
{
    unsigned int Register_Value = 0;
    unsigned int Data_Value = 0;
	//Write out the Message in two individual 16 bit unsigned int messages
	for (unsigned int i=0; i<NumberOfRegisters; i++)
	{
        Register_Value = ENABLE_WRITE + RegisterAddress + i;
        Data_Value = DataBuffer[index+i];
        //uart_write_32((Register_Values+i),DataBuffer[i]);
        w32_spi(Register_Value,Data_Value);
    }
}

unsigned int read_AD7147(unsigned int RegisterAddress, unsigned int NumberOfRegisters)
{
	unsigned int Register_Values;
    unsigned int DataBuffer[];
    //Sends 16-bit Signal containing Enable Word and Register Address
    Register_Values = ENABLE_READ + RegisterAddress;
	// Write out the control word plus the register Addresses for all available ports
	for (unsigned int i=0; i<NumberOfRegisters; i++)
	{
        DataBuffer[i]=w16_r16_spi(Register_Values+i);
	}  
    return DataBuffer[0];
}

unsigned int read_AD7147_interrupt(unsigned int RegisterAddress)
{
	unsigned int Register_Values = ENABLE_READ + RegisterAddress;
    unsigned int interrupt_clear = w16_r16_spi(Register_Values); 
    //Sends 16-bit Signal containing Enable Word and Register Address
    
    return interrupt_clear;
}

unsigned int read_sensor(unsigned int sensor)
{	
    unsigned int cdc_sensor = 0;
    if (sensor > 12)
    {
        cdc_sensor = sensor - 12;
    }
    else
    {
        cdc_sensor = sensor;
    }
    unsigned int register1 = ENABLE_READ + 0x00A + cdc_sensor;
    //unsigned int register1 = ENABLE_READ + 0x104;
    sensor_CDC(sensor, 0); //set CS to low (Start Transmitting data)
	unsigned int sensor_value = w16_r16_spi(register1);
    sensor_CDC(sensor, 1); //set CS to high (Stop Transmitting data)
    //This is how we access the ADC Values
	//AD7147Registers[CDC_RESULT_S0] corresponds to ADC Value of Stage 0
    //.....
	//AD7147Registers[CDC_RESULT_S11] corresponds to ADC Value of Stage 11
    
    //return CDC_RESULT[sensor];
    return sensor_value;
}
/*
void read_sensors()
{
    read_AD7147(CDC_RESULT_REGISTER[0], 3, 0);
}
*/
void sensor_CDC(unsigned int sensor, unsigned int state)
{
    //Sensor is the sensor number to be read
    //State: 0 = Transmit Data, 1 = Stop Transmit Data
    if (sensor > 12)
    {
        get_CDC(2,state);
    }
    else
    {
        get_CDC(1,state);
    }
}
void read_sensors()
{
    unsigned int Register_Values[12];
    unsigned int address_low[12];
    unsigned int address_high[12];
    unsigned int enable_word = 0xE400;
    unsigned int blank_low = 0x000;
    unsigned int blank_high = 0x000;
    unsigned int p1, p2, p3, p4;
    unsigned int temp_high, temp_low;
    
    for(unsigned int i=0; i<12; i++)
	{
        //Sends 16-bit Signal containing Enable Word and Register Address
        //Register_Values[i] = enable_word + CDC_RESULT_REGISTER[i];
        Register_Values[i] = enable_word + (0x00B+i);
        address_low[i] = Register_Values[i] & 0xFF;
        address_high[i] = Register_Values[i] >> 8;
	}
    
    CS_CDC1 = 0;   //set CS to low (transmit data)
    for(unsigned int i=0; i<12; i++)
	{   
        temp_high = address_high[i];
        temp_low = address_low[i];
        
        SSPBUF = temp_high;
        while(!SSPSTATbits.BF); // wait to complete 
        p1 = SSPBUF;
        
        SSPBUF = temp_low;  // Command byte (write to pot 0)
        while(!SSPSTATbits.BF); // wait to complete 
        p2 = SSPBUF;
    
        SSPBUF = blank_high;  // Command byte (write to pot 0)
        while(!SSPSTATbits.BF); // wait to complete 
        p3 = SSPBUF;
    
        SSPBUF = blank_low;  // Command byte (write to pot 0)
        while(!SSPSTATbits.BF); // wait to complete 
        p4 = SSPBUF;
        
        //CDC_RESULT[i] = (p3 << 8) + p4;
    }
    CS_CDC1 = 1;   //set CS to low (transmit data)
}

unsigned int get_ID(unsigned int cdc)
{
    get_CDC(cdc,0);
    unsigned int result = (w16_r16_spi(ENABLE_READ + DEV_ID) & 0b1111111111110000) >> 4;
    get_CDC(cdc,1);
    return result;
}

void switch_LED(unsigned int cdc, unsigned int state)
{
 get_CDC(cdc,0);
 if (state==1)
 {
     unsigned int message = 0b0010000000000000;
     w32_spi((ENABLE_WRITE + STAGE_LOW_INT_EN),message);
 }
 else
 {
     unsigned int message = 0b0011000000000000;
     w32_spi((ENABLE_WRITE + STAGE_LOW_INT_EN),message);
 }
 delay_ms(10);
 get_CDC(cdc,1);
}
void blink_LED(unsigned int cdc)
{
    get_CDC(cdc,0);
    unsigned int message = 0b0010000000000000;
    w32_spi((ENABLE_WRITE + STAGE_LOW_INT_EN),message);
    delay_ms(10);
    get_CDC(cdc,1);
    delay_ms(1000);
    get_CDC(cdc,0);
    unsigned int message = 0b0011000000000000;
    w32_spi((ENABLE_WRITE + STAGE_LOW_INT_EN),message);
    delay_ms(10);
    get_CDC(cdc,1);
}
void get_CDC(unsigned int cdc, unsigned int state)
{
    if (state == 1)
    {
            CS_CDC1 = 1;   //set CS to high (stop transmit data)
            CS_CDC2 = 1;    //set CS to high (stop transmit data)
    }
    else
    {
        if (cdc == 1)
        {
            CS_CDC1 = 0;   //set CS to low (transmit data)
            CS_CDC2 = 1;   //Keep CS of CDC 2 High 
        }
        else
        {
            CS_CDC2 = 0;    //set CS to low (transmit data)
            CS_CDC1 = 1;    //Keep CS of CDC 1 High 
        }
    }
}
/*
static int ServiceAD7147Isr(void)
{	
    unsigned int POWER_UP_INTERRUPT = 0x01FF;
    unsigned int InterruptCounterForThresholdIntMode;
    unsigned int NUMBER_OF_INTS_BEFORE_THRES_INT_MODE;
	//Read thresholds registers
	read_AD7147(STAGE_LOW_LIMIT_INT, 3, AD7147Registers);
    //=======================
	// Change interrupt mode
    //=======================
	if (((AD7147Registers[STAGE_HIGH_LIMIT_INT] & POWER_UP_INTERRUPT) != 0x0000) || ((AD7147Registers[STAGE_LOW_LIMIT_INT] & POWER_UP_INTERRUPT) != 0x0000))
	{
        //Configure AD7147 in EOC interrupt mode
		if (AD7147Registers[STAGE_COMPLETE_INT_EN] == 0x0000)
		{
			AD7147Registers[STAGE_LOW_INT_EN] &= 0xF000;
			AD7147Registers[STAGE_HIGH_INT_EN] &= 0xF000;
			AD7147Registers[STAGE_COMPLETE_INT_EN] = 0x0001;
			write_AD7147(STAGE_LOW_INT_EN, 3, AD7147Registers);
		}
	//	InterruptCounterForThresholdIntMode = NUMBER_OF_INTS_BEFORE_THRES_INT_MODE;
	}
	else
	{
		//Configure AD7147 in threshold interrupt driven mode
		if (InterruptCounterForThresholdIntMode > 0)
		{
            InterruptCounterForThresholdIntMode--;
        }
			
        if (AD7147Registers[STAGE_HIGH_INT_EN] == 0x0000 && InterruptCounterForThresholdIntMode == 0)
		{
			AD7147Registers[STAGE_LOW_INT_EN] |= POWER_UP_INTERRUPT;
			AD7147Registers[STAGE_HIGH_INT_EN] |= 0x00FF;
			AD7147Registers[STAGE_COMPLETE_INT_EN] = 0x0000;
			write_AD7147(STAGE_LOW_INT_EN, 3, AD7147Registers);
		}
	}
}

static void ForceCalibration(void)
{
	read_AD7147(AMB_COMP_CTRL0, 1, AD7147Registers);
	AD7147Registers[AMB_COMP_CTRL0] |= 0x4000;//Set "forced cal" bit
	write_AD7147(AMB_COMP_CTRL0, 1, AD7147Registers);
}*/