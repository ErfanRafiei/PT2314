#include "PT2314.h"
#include "main.h"
#include "i2c.h"

uint8_t PT_data[6];
uint8_t PT_Error=0;

const uint8_t eq_Value[] = 
{
	0,		// -14
	0,		// -13
	1,		// -12
	1,		// -11
	2,		// -10
	2,		// -9
	3,		// -8
	3,		// -7
	4,		// -6
	4,		// -5
	5,		// -4
	5,		// -3
	6,		// -2
	6,		// -1
	7,		// 0
	14,		// 1
	14,		// 2
	13,		// 3
	13,		// 4
	12,		// 5
	12,		// 6
	11,		// 7
	11,		// 8
	10,		// 9
	10,		// 10
	9,		// 11
	9,		// 12
	8,		// 13
	8,		// 14
	
};


void PT_Volume(uint8_t Volume)  //Keep Volume Value in 0-63 range
{
	if(Volume<64)
	{
	  PT_data[0]=63-Volume;
	}
	else 
	{
		PT_Error=1;
	}
}


//Use "Right_Speaker" or "Left_Speaker"
//Use "Mute_OFF" or "Mute_ON"
//Keep Attenuator Value in 0-30 range
void PT_Attenuators(uint8_t Select_Speaker,uint8_t Attenuator,uint8_t Mute)
{
	if(Select_Speaker)
	{
		if(Mute)
		{			
					PT_data[2]=0xff; //SpkR ATT

		}
		else
		{
			if(Attenuator<0x1f)
			{
				PT_data[2]=Attenuator|0xe0; //SpkR ATT

			}
			else
			{
				PT_Error=1;
			}
		}
	}
	
	else
	{
		if(Mute)
		{			
					PT_data[1]=0xdf; //SpkL ATT

		}
		else
		{
			if(Attenuator<0x1f)
			{
				PT_data[1]=Attenuator|0xc0; //SpkL ATT

			}
			else
			{
				PT_Error=1;
			}
		}
	}
	
}
//Use PT_CH_1 . . . PT_CH_4
void PT_Select_Channel(uint8_t Select_Channel)
{
	switch(Select_Channel)
	{
		case 0:
			PT_data[3]|=0x40;
		  PT_data[3]&=~((1<<0)|(1<<1));

		break;
		case 1:
			PT_data[3]|=0x41;
		  PT_data[3]&=~(1<<1);

		break;
		case 2:
			PT_data[3]|=0x42;
		  PT_data[3]&=~(1<<0);

		break;
		case 3:
			PT_data[3]|=0x43;

		break;
		
		
	}
	
	
}

//Use "Loadness_OFF" or "Loadness_ON"
void PT_Loadness(uint8_t Loadness)
{
	if(Loadness)
	{
		PT_data[3]|=0x40;
		PT_data[3]&=~(1<<2);

	}
	else
	{
		PT_data[3]|=0x40;
		PT_data[3]|=(1<<2);

	}
}

//Use Gain_0db or Gain_3_75db or Gain_7_5db or Gain_11_25db
void PT_Set_Gain(uint8_t Set_Gain)
{
	switch(Set_Gain)
	{
		case 0:
			PT_data[3]|=0x58;

		break;
		case 1:
			PT_data[3]|=0x50;
		  PT_data[3]&=~(1<<3);

		break;
		case 2:
			PT_data[3]|=0x48;
		  PT_data[3]&=~(1<<4);
	
		break;
		case 3:
			PT_data[3]|=0x40;
		  PT_data[3]&=~((1<<3)|(1<<4));

		break;
		
		
	}
	
}
//Keep Base Value in 0-28 range -14...0...14
//Keep Treble Value in 0-28 range -14...0...14
void PT_Set_Base_Treble(uint8_t Base,uint8_t Treble)
{
	PT_data[4]=eq_Value[Base];
	PT_data[5]=eq_Value[Treble];
	PT_data[4]|=0x60; //Base
	PT_data[5]|=0x70; //Trible

}


void PT_Update_Data(void)
{	
	//if you want to transmit with interrupt change function name to HAL_I2C_Master_Transmit_IT and remove PT2314_Timeout
	if(HAL_I2C_Master_Transmit(_PT2314_I2C_Typedef,_PT2314_Add,PT_data,sizeof(PT_data),_PT2314_Timeout)!=HAL_OK)
	{
		PT_Error=1;
	}
}










