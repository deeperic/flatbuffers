#pragma once

#include "flatbuffers/demo_marketdata_generated.h"


using namespace BOCHK::GlobalMarket::FlatBuffers::demo;

class FlatBufferesMessage
{
public:
	static void Write();//simple msg
	static void Read();//simle msg

	static void WriteMarketDataFull();//no union
	static void ReadMarketDataFull();//no union
	static void ReadMarketDataFull(char* buf);//no union

	static void WriteMarketDataBBO();//union
	static void ReadMarketDataBBO();//union

	static void WriteSimpleTable();
	static void ReadSimpleTable();
};