// ReadWriteFlatBuffersFile.cpp: 定義應用程式的進入點。
//

#include "ReadWriteFlatBuffersFile.h"

using namespace std;

#include "FlatBufferesMessage.h"
#include "JsonMessage.h"

#include "CodeBlockTimer.h"
#include "FileLoader.h"

void Test1(int n) {
	CodeBlockTimer cbt;
	for (int i = 0; i < n; ++i) {
		FlatBufferesMessage::Write();
		FlatBufferesMessage::Read();
	}
	cbt.Stop();
}

void Test2(int n) {
	CodeBlockTimer cbt;
	for (int i = 0; i < n; ++i) {
		FlatBufferesMessage::WriteMarketDataFull();
		//FlatBufferesMessage::ReadMarketDataFull();
	}
	cbt.Stop();
}

void Test2_Read(int n) {

	char buf[4096];
	int len = 288;

	FileLoader::ReadFile("market_data_full.dat", buf, len);

	CodeBlockTimer cbt;
	for (int i = 0; i < n; ++i) {
		
		FlatBufferesMessage::ReadMarketDataFull(buf);
	}
	cbt.Stop();
}

void Test3(int n) {
	CodeBlockTimer cbt;
	for (int i = 0; i < n; ++i) {
		FlatBufferesMessage::WriteMarketDataBBO();
		FlatBufferesMessage::ReadMarketDataBBO();
	}
	cbt.Stop();
}

void Test4(int n) {
	CodeBlockTimer cbt;
	for (int i = 0; i < n; ++i) {
		JsonMessage::WriteMarketDataFull();
		//JsonMessage::ReadMarketDataFull();
	}
	cbt.Stop();
}

void Test4_Read(int n) {

	char buf[4096];
	memset(buf, 0, 4096);
	int len = 295;

	FileLoader::ReadFile("example.json", buf, len);

	CodeBlockTimer cbt;
	for (int i = 0; i < n; ++i) {
		
		JsonMessage::ReadMarketDataFull(buf);
	}
	cbt.Stop();
}

int main()
{
	
	int n = 10000;
	Test2(n);
	Test4(n);

	Test2_Read(n);
	Test4_Read(n);
	

	/*
	FlatBufferesMessage::WriteSimpleTable();
	FlatBufferesMessage::ReadSimpleTable();
	*/

	return 0;
}
