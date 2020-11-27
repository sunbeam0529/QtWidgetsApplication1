#pragma once
#include "QtWidgetsApplication1.h"

typedef union
{
	uint8_t BYTE[8];
	struct Data
	{
		uint8_t ReverseByte1;
		uint8_t BackLight;
		uint8_t ReverseByte3;
		uint8_t ReverseByte4;
		uint8_t ReverseByte5;
		uint8_t ReverseByte6;
		uint8_t ReverseByte7;
		uint8_t ReverseByte8;
	};
}MSG_0A_TYPE;

typedef struct
{
	uint8_t BYTE[8];
}MSG_10_TYPE;

typedef struct
{
	uint8_t BYTE[8];
	
}MSG_11_TYPE;

typedef union
{
	uint8_t BYTE[8];
	struct 
	{
		//byte1
		uint8_t Key_RES:2;
		uint8_t Key_SET:2;
		uint8_t Key_DIST:2;
		uint8_t Key_LIM:2;
		//byte2
		uint8_t Key_SpeedPlus:2;
		uint8_t Key_SpeedReduce:2;
		uint8_t Key_ACC:2;
		uint8_t ReverseByte2:1;
		uint8_t LIN_err:1;
		//byte3
		uint8_t SpeedSlider;
		//reverse
		uint8_t ReverseByte4;
		uint8_t ReverseByte5;
		uint8_t ReverseByte6;
		uint8_t ReverseByte7;
		uint8_t ReverseByte8;
	}Data;
}MSG_19_TYPE;

typedef union
{
	uint8_t BYTE[8];
	struct
	{
		//byte1
		uint8_t Key_SeekPlus : 2;
		uint8_t Key_SeekReduce: 2;
		uint8_t Key_VolPlus : 2;
		uint8_t Key_VolReduce : 2;
		//byte2
		uint8_t Key_OK : 2;
		uint8_t Key_Speech : 2;
		uint8_t Key_Menu : 2;
		uint8_t ReverseByte2 : 1;
		uint8_t LIN_err : 1;
		//byte3
		uint8_t VolSlider;
		//reverse
		uint8_t ReverseByte4;
		uint8_t ReverseByte5;
		uint8_t ReverseByte6;
		uint8_t ReverseByte7;
		uint8_t ReverseByte8;
	}Data;
}MSG_1A_TYPE;