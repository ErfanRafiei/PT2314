#ifndef PT2314_H_
#define PT2314_H_
#endif

#include <stdint.h>
#include "i2c.h"

// Keep I2C Clock lower than 100Khz
// After set any parameter use "PT_Update_Data" to send your config in chip
#define _PT2314_Add 0x88
#define _PT2314_Timeout 10
#define _PT2314_I2C_Typedef &hi2c1 // <<---Set your I2C_HandleTypeDef

#define Right_Speaker  1
#define Left_Speaker   0

#define Mute_ON   1
#define Mute_OFF  0

#define Loadness_ON   1
#define Loadness_OFF  0

#define PT_CH_1  0
#define PT_CH_2  1
#define PT_CH_3  2
#define PT_CH_4  3

#define Gain_0db      0
#define Gain_3_75db   1
#define Gain_7_5db    2
#define Gain_11_25db  3

void PT_Volume(uint8_t Volume);
void PT_Attenuators(uint8_t Select_Speaker,uint8_t Attenuator,uint8_t Mute);
void PT_Select_Channel(uint8_t Select_Channel);
void PT_Loadness(uint8_t Loadness);
void PT_Set_Gain(uint8_t Set_Gain);
void PT_Set_Base_Treble(uint8_t Base,uint8_t Treble);
void PT_Update_Data(void);



