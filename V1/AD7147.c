#include "micro_setup.h"
#include "AD7147.h"
#include "spi.h"
#include "uart.h"

void setup_AD7147(unsigned int *DataBuffer, unsigned int cdc)
{   
    unsigned int StageBuffer[8] = {0};
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
    StageBuffer[0] = 0x3FFE;	//Register 0x80
    StageBuffer[1] = 0x1FFF;	//Register 0x81
    StageBuffer[2] = 0x0100;	//Register 0x82
    StageBuffer[3] = 0x2121;	//Register 0x83
    StageBuffer[4] = 500;       //Register 0x84	
    StageBuffer[5] = 500;   	//Register 0x85
    StageBuffer[6] = 600;       //Register 0x86	
    StageBuffer[7] = 600;       //Register 0x87
    write_AD7147(STAGE0_CONNECTION, 8, StageBuffer, 0, cdc);
    
    //===========================
    //= Stage 1 - CIN1 (+) S2
    //===========================
    StageBuffer[0]=0x3FFB;      //Register 0x88
    StageBuffer[1]=0x1FFF;      //Register 0x89
    StageBuffer[2]=0x0100;      //Register 0x8A
    StageBuffer[3]=0x2121;      //Register 0x8B
    StageBuffer[4]=500;         //Register 0x8C
    StageBuffer[5]=500;         //Register 0x8D
    StageBuffer[6]=600;         //Register 0x8E
    StageBuffer[7]=600;         //Register 0x8F
	write_AD7147(STAGE1_CONNECTION, 8, StageBuffer, 0, cdc);

    //===========================
    //= Stage 2 - CIN2 (+) S3
    //===========================
    StageBuffer[0]=0x3FEF;	//Register 0x90
    StageBuffer[1]=0x1FFF;	//Register 0x91
    StageBuffer[2]=0x0100;	//Register 0x92
    StageBuffer[3]=0x2121;	//Register 0x93
    StageBuffer[4]=500;     //Register 0x94
    StageBuffer[5]=500;     //Register 0x95
    StageBuffer[6]=600;     //Register 0x96
    StageBuffer[7]=600;     //Register 0x97
	write_AD7147(STAGE2_CONNECTION, 8, StageBuffer, 0, cdc);

    //===========================
    //= Stage 3 - CIN3 (+) S4
    //===========================
    StageBuffer[0]=0x3FBF;	//Register 0x98
    StageBuffer[1]=0x1FFF;	//Register 0x99
    StageBuffer[2]=0x0100;	//Register 0x9A
    StageBuffer[3]=0x2121;	//Register 0x9B
    StageBuffer[4]=500; 	//Register 0x9C
    StageBuffer[5]=500;     //Register 0x9D
    StageBuffer[6]=600;     //Register 0x9E
    StageBuffer[7]=600;     //Register 0x9F
    write_AD7147(STAGE3_CONNECTION, 8, StageBuffer, 0, cdc);

    //===========================
    //= Stage 4 - CIN4 (+) S5
    //===========================
    StageBuffer[0]=0x3EFF;	//Register 0xA0
    StageBuffer[1]=0x1FFF;	//Register 0xA1
    StageBuffer[2]=0x0100;	//Register 0xA2
    StageBuffer[3]=0x2121;	//Register 0xA3
    StageBuffer[4]=500;	//Register 0xA4
    StageBuffer[5]=500;	//Register 0xA5
    StageBuffer[6]=600;	//Register 0xA6
    StageBuffer[7]=600;	//Register 0xA7
    write_AD7147(STAGE4_CONNECTION, 8, StageBuffer,0, cdc);

    //===========================
    //= Stage 5 - CIN5 (+) S6
    //===========================
    StageBuffer[0]=0x3BFF;	//Register 0xA8
    StageBuffer[1]=0x1FFF;	//Register 0xA9
    StageBuffer[2]=0x0100;	//Register 0xAA
    StageBuffer[3]=0x2121;	//Register 0xAB
    StageBuffer[4]=500;	//Register 0xAC
    StageBuffer[5]=500;	//Register 0xAD
    StageBuffer[6]=600;	//Register 0xAE
    StageBuffer[7]=600;	//Register 0xAF
	write_AD7147(STAGE5_CONNECTION, 8, StageBuffer,0, cdc);

	//===========================
    //= Stage 6 - CIN6 (+) S7
    //===========================
    StageBuffer[0]=0x3FFF;	//Register 0xB0
    StageBuffer[1]=0xDFFF;	//Register 0xB1
    StageBuffer[2]=0x0100;	//Register 0xB2
    StageBuffer[3]=0x2121;	//Register 0xB3
    StageBuffer[4]=500;     //Register 0xB4
    StageBuffer[5]=500;     //Register 0xB5
    StageBuffer[6]=600;     //Register 0xB6
    StageBuffer[7]=600;     //Register 0xB7
    write_AD7147(STAGE6_CONNECTION, 8, StageBuffer, 0, cdc);

    //===========================
    //= Stage 7 - CIN7 (+) S8
    //===========================
    StageBuffer[0]=0x3FFF;	//Register 0xB8
    StageBuffer[1]=0xDFFF;	//Register 0xB9
    StageBuffer[2]=0x0100;	//Register 0xBA
    StageBuffer[3]=0x2121;	//Register 0xBB
    StageBuffer[4]=500;     //Register 0xBC
    StageBuffer[5]=500;  	//Register 0xBD
    StageBuffer[6]=600;     //Register 0xBE
    StageBuffer[7]=600;     //Register 0xBF
    write_AD7147(STAGE7_CONNECTION, 8, StageBuffer, 0, cdc);

    //===========================
    //= Stage 8 - CIN8 (+) S9
    //===========================
    StageBuffer[0]=0x3FFF;	//Register 0xC0
    StageBuffer[1]=0xDFFF;	//Register 0xC1
    StageBuffer[2]=0x0100;	//Register 0xC2
    StageBuffer[3]=0x2121;	//Register 0xC3
    StageBuffer[4]=500; 	//Register 0xC4
    StageBuffer[5]=500;     //Register 0xC5
    StageBuffer[6]=600;     //Register 0xC6
    StageBuffer[7]=600;     //Register 0xC7
    write_AD7147(STAGE8_CONNECTION, 8, StageBuffer, 0, cdc);

    //===========================
    //= Stage 9 - CIN9 (+) S10
    //===========================
    StageBuffer[0]=0x3FFF;	//Register 0xC8	
    StageBuffer[1]=0xDFFF;	//Register 0xC9
    StageBuffer[2]=0x0000;	//Register 0xCA
    StageBuffer[3]=0x2626;	//Register 0xCB
    StageBuffer[4]=4000; 	//Register 0xCC
    StageBuffer[5]=2500;     //Register 0xCD
    StageBuffer[6]=4000;     //Register 0xCE
    StageBuffer[7]=600;     //Register 0xCF
    write_AD7147(STAGE9_CONNECTION, 8, StageBuffer, 0, cdc);

    //============================
    //= Stage 10 - CIN10 (+) S11
    //============================
    StageBuffer[0]=0x3FFF;	//Register 0xD0
    StageBuffer[1]=0xDFFF;	//Register 0xD1
    StageBuffer[2]=0x0100;	//Register 0xD2
    StageBuffer[3]=0x2121;	//Register 0xD3
    StageBuffer[4]=500;     //Register 0xD4
    StageBuffer[5]=500;     //Register 0xD5
    StageBuffer[6]=600;     //Register 0xD6
    StageBuffer[7]=600;     //Register 0xD7
	write_AD7147(STAGE10_CONNECTION, 8, StageBuffer, 0, cdc);

    //============================
    //= Stage 11 - CIN11 (+) S12
    //============================
    StageBuffer[0]=0x3FFF;	//Register 0xD8
    StageBuffer[1]=0xDFFF;	//Register 0xD9
    StageBuffer[2]=0x0100;	//Register 0xDA
    StageBuffer[3]=0x2121;	//Register 0xDB
    StageBuffer[4]=500; 	//Register 0xDC
    StageBuffer[5]=500;     //Register 0xDD
    StageBuffer[6]=600;     //Register 0xDE
    StageBuffer[7]=600;     //Register 0xDF
	write_AD7147(STAGE11_CONNECTION, 8, StageBuffer, 0, cdc);

    //--------------------------------------------------------------------------//
    //-------------------------Bank 1 Registers---------------------------------//
    //--------------------------------------------------------------------------//
    //Initialization of the first register bank but not the STAGE_CAL_EN
    //  10  [1:0] Power Mode, 00 = Full Power Mode, 10 = low power mode
    //  00  [3:2] LP_CONV_DELAY, 00 = 200 ms, low power conversion delay
    //  0101 [7:4] SEQUENCE_STAGE_NUM, 0101 = 6 conversion stages in sequence
    //  00  [9:8]  DECIMATION, 10 decimate by 64
    //  0   [10]    SW_RESET, 0 = Do not reset registers to default values
    //  0   [11]    Interrupt polarity control, 0 = active low
    //  0   [12]    Ext_Source, 0 = Enable excitation source to CINx pins
    //  0   [13]    UNUSED, set to 0
    //  00  [15:14] CDC Bias Current control, 00 = normal operation
    StageBuffer[0] = 0x0052; 			//Register 0x000 PWR_CONTROL
    write_AD7147(PWR_CONTROL, 1, StageBuffer, 0, cdc);
    
    //Read Interrupt Status to enable the Interrupts
    read_AD7147(DataBuffer, STAGE_LOW_LIMIT_INT, 3, cdc); //Registers 0x08 & 0x09 & 0x0A
    
    //  0000 [3:0]   Fast Filter Skip Control, 0000 = no sequence of results is skip
    //  0011 [7:4]   FP_PROXIMITY_CNT, Calibration disable period in full power
    //  0010 [11:8]  LP_PROXIMITY_CNT, Calibration disable period in low power mode
    //  11   [13:12] PWR_DOWN_TIMEOUT, 11 = 2.00 x (FP_PROXIMITY_CNT)
    //  0    [14]    FORCED_CAL, forced calibration control, 0 = normal operation
    //  0    [15]    CONV_RESET, (self-clearing), 0 = normal operation
    StageBuffer[2] = 0x3230;			//Register 0x002 AMB_COMP_CTRL0
    
    //  0001 1001   [7:0]    PROXIMITY_RECAL_LVL, 0000 = no sequence of results is skip
    //  001000      [13:8]   PROXIMITY_DETECTION_RATE, proximity detection rate, the value is multiplied by 16 to determine actual detection rate
    //  00          [15:14]  SLOW_FILTER_UPDATE_LVL, Slow Filter Update Level
    StageBuffer[3] = 0x0819;			//Register 0x003 AMB_COMP_CTRL1
    
    //  00 0011 0010 [9:0]   FP_PROXIMITY_RECAL, Full power mode proximity recalibration time control
    //  0000 10      [15:10] LP_PROXIMITY_RECAL, Low power mode proximity recalibration time control
    StageBuffer[4] = 0x0832;			//Register 0x004 AMB_COMP_CTRL2
    
    //  0  [0] STAGE0, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [1] STAGE1, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [2] STAGE2, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [3] STAGE3, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [4] STAGE4, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [5] STAGE5, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [6] STAGE6, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [7] STAGE7, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [8] STAGE8, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [9] STAGE9, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [10] STAGE10, Low interrupt enable, 0 = Interrupt source disabled
    //  0  [11] STAGE11, Low interrupt enable, 0 = Interrupt source disabled
    //  00 [13:12] GPIO_SETUP, 00 = disable GPIO pin 
    //  00 [15:14] GPIO_INPUT_CONFIG, 00 = Triggered on negative level
    StageBuffer[5] = 0x0000;            //Register 0x005 STAGE_LOW_INT_ENABLE
    
    //  0  [0] STAGE0, High interrupt enable, 0 = Interrupt source disabled
    //  0  [1] STAGE1, High interrupt enable, 0 = Interrupt source disabled
    //  0  [2] STAGE2, High interrupt enable, 0 = Interrupt source disabled
    //  0  [3] STAGE3, High interrupt enable, 0 = Interrupt source disabled
    //  0  [4] STAGE4, High interrupt enable, 0 = Interrupt source disabled
    //  0  [5] STAGE5, High interrupt enable, 0 = Interrupt source disabled
    //  0  [6] STAGE6, High interrupt enable, 0 = Interrupt source disabled
    //  0  [7] STAGE7, High interrupt enable, 0 = Interrupt source disabled
    //  0  [8] STAGE8, High interrupt enable, 0 = Interrupt source disabled
    //  0  [9] STAGE9, High interrupt enable, 0 = Interrupt source disabled
    //  0  [10] STAGE10, High interrupt enable, 0 = Interrupt source disabled
    //  0  [11] STAGE11, High interrupt enable, 0 = Interrupt source disabled
    //  0000 [15:12] UNUSED, Set to 0 
    StageBuffer[6] = 0x0000;            //Register 0x006 STAGE_HIGH_INT_ENABLE
    
    //  0  [0] STAGE0, Completion Interrupt enable, 0 = Interrupt source disabled
    //  0  [1] STAGE1, Completion Interrupt enable, 0 = Interrupt source disabled
    //  0  [2] STAGE2, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [3] STAGE3, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [4] STAGE4, Completion interrupt enable, 0 = Interrupt source disabled
    //  1  [5] STAGE5, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [6] STAGE6, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [7] STAGE7, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [8] STAGE8, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [9] STAGE9, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [10] STAGE10, Completion interrupt enable, 0 = Interrupt source disabled
    //  0  [11] STAGE11, Completion interrupt enable, 1 = Interrupt source enabled
    //  0  [12] GPIO_INT_ENABLE, Interrupt control when GPIO input pin changes level, 0 = disabled
    //  000 [15:13] UNUSED, Set to 0 
    StageBuffer[7] = 0x0020;            //Register 0x007 - STAGE_COMPLETE_INT_ENABLE
    write_AD7147(AMB_COMP_CTRL0, 6, StageBuffer, 2, cdc);
    
    //Enable data path for all sequences and enable calibration on 4 stages
    
    //  1  [0] STAGE0_CAL_EN, STAGE0 Calibration enable, 1 = Calibration Enabled
    //  1  [1] STAGE1_CAL_EN, Completion Interrupt enable, 1 = Calibration Enabled
    //  1  [2] STAGE2_CAL_EN, Completion Interrupt enable, 1 = Calibration Enabled
    //  1  [3] STAGE3_CAL_EN, Completion Interrupt enable, 1 = Calibration Enabled
    //  1  [4] STAGE4_CAL_EN, Completion Interrupt enable, 1 = Calibration Disabled
    //  1  [5] STAGE5_CAL_EN, Completion Interrupt enable, 0 = Calibration Disabled
    //  0  [6] STAGE6_CAL_EN, Completion Interrupt enable, 0 = Calibration Disabled
    //  0  [7] STAGE7_CAL_EN, Completion Interrupt enable, 0 = Calibration Disabled
    //  0  [8] STAGE8_CAL_EN, Completion Interrupt enable, 0 = Calibration Disabled
    //  0  [9] STAGE9_CAL_EN, Completion Interrupt enable, 0 = Calibration Disabled
    //  0  [10] STAGE10_CAL_EN, Completion Interrupt enable, 0 = Calibration Disabled
    //  0  [11] STAGE11_CAL_EN, Completion Interrupt enable, 0 = Calibration Disabled
    //  00 [13:12] AVG_FP_SKIP, Full Power mode skip control, 00 = skip 3 samples
    //  00 [15:14] AVG_LP_SKIP, Low Power mode skip control, 00 = use all samples
    StageBuffer[1] = 0x003F;			//Register 0x001
    write_AD7147(STAGE_CAL_EN, 1, StageBuffer, 1, cdc);
    
    //Set the "Force Calibration Bit" 
    //  0000 [3:0]   Fast Filter Skip Control, 0000 = no sequence of results is skip
    //  0000 [7:4]   FP_PROXIMITY_CNT, Calibration disable period in full power
    //  0000 [11:8]  LP_PROXIMITY_CNT, Calibration disable period in low power mode
    //  00   [13:12] PWR_DOWN_TIMEOUT, 11 = 2.00 x (FP_PROXIMITY_CNT)
    //  1    [14]    FORCED_CAL, forced calibration control, 1 = force all conversion stages to recalibrate
    //  0    [15]    CONV_RESET, (self-clearing), 0 = normal operation
    StageBuffer[2] = 0x4000;            //Register 0x002
    write_AD7147(AMB_COMP_CTRL0, 1, StageBuffer, 2, cdc);
    
    //Read high and low limit interrupt status before to enable the interrupts
    read_AD7147(DataBuffer, STAGE_LOW_LIMIT_INT, 3, cdc); //Registers 0x08 & 0x09 & 0x0A
    
}

void write_AD7147(unsigned int RegisterStartAddress, unsigned int NumberOfRegisters, unsigned int *OutputBuffer, unsigned int index, unsigned int cdc)
{
    get_CDC(cdc,0);
    unsigned int Register_Value = ENABLE_WRITE + RegisterStartAddress;
    unsigned int Data_Value = 0;
	for (unsigned int i=0; i<NumberOfRegisters; i++)
	{
        Data_Value = OutputBuffer[index+i];
        w32_spi(Register_Value+i,Data_Value);
    }
    get_CDC(cdc,1);
}

void read_AD7147(unsigned int *DataBuffer, unsigned int RegisterStartAddress, unsigned int NumberOfRegisters, unsigned int cdc)
{
    get_CDC(cdc,0);
    unsigned int Register_Values = ENABLE_READ + RegisterStartAddress;
	for (unsigned int i=0; i<NumberOfRegisters; i++)
	{
        DataBuffer[i]=w16_r16_spi(Register_Values+i);
	}
    get_CDC(cdc,1);
}

void read_sensor(unsigned int *sensor_values, unsigned int sensor)
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
    sensor_CDC(sensor, 0); //set CS to low (Start Transmitting data)
	sensor_values[sensor-1] = w16_r16_spi(register1);
    sensor_CDC(sensor, 1); //set CS to high (Stop Transmitting data)
}

void read_sensors(unsigned int *sensor_values, unsigned int *avail_sensors, unsigned int num_cdc)
{
    get_CDC(num_cdc,0);
    for(unsigned int i = 0; i<12; i++)
    {
        if(avail_sensors[i] == 1)
        {
            sensor_values[i] = w16_r16_spi(ENABLE_READ + 0x00B+ i);
        }
    }
    get_CDC(num_cdc,1);
}

void read_cdc1(unsigned int *sensor_values)
{
    get_CDC(1,0);
    sensor_values[0] = w16_r16_spi(ENABLE_READ + 0x00B);
    for(unsigned int i = 1; i<6; i++)
    {
        sensor_values[i] = r16_spi();
    }
    get_CDC(1,1);
}

void read_cdc2(unsigned int *sensor_values)
{
    get_CDC(2,0);
    sensor_values[12] = w16_r16_spi(ENABLE_READ + 0x00B);
    for(unsigned int i = 13; i<17; i++)
    {
        sensor_values[i] = r16_spi();
    }
    get_CDC(2,1);
}

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