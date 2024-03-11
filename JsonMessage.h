#pragma once

class JsonMessage
{
public:
	static void WriteMarketDataFull();
	static void ReadMarketDataFull();
	static void ReadMarketDataFull(char* buf);
};