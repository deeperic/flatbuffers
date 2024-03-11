#include "JsonMessage.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

#include "FileLoader.h"

using namespace rapidjson;

rapidjson::Document CreateBidAsk1() {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value bidValue;
    bidValue.SetDouble(50.1234);
    document.AddMember("bid", bidValue, document.GetAllocator());

    rapidjson::Value bidQtyValue;
    bidQtyValue.SetInt(600000);
    document.AddMember("bid_qty", bidQtyValue, document.GetAllocator());


    rapidjson::Value askValue;
    askValue.SetDouble(52.1234);
    document.AddMember("ask", askValue, document.GetAllocator());

    rapidjson::Value askQtyValue;
    askQtyValue.SetInt(800000);
    document.AddMember("ask_qty", askQtyValue, document.GetAllocator());

    return document;
}


rapidjson::Document CreateBidAsk2() {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value bidValue;
    bidValue.SetDouble(49.1234);
    document.AddMember("bid", bidValue, document.GetAllocator());

    rapidjson::Value bidQtyValue;
    bidQtyValue.SetInt(900000);
    document.AddMember("bid_qty", bidQtyValue, document.GetAllocator());


    rapidjson::Value askValue;
    askValue.SetDouble(55.1234);
    document.AddMember("ask", askValue, document.GetAllocator());

    rapidjson::Value askQtyValue;
    askQtyValue.SetInt(1600000);
    document.AddMember("ask_qty", askQtyValue, document.GetAllocator());

    return document;
}

void JsonMessage::WriteMarketDataFull() {
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Value instValue;
    instValue.SetString("EUR/USD");
    document.AddMember("instrument", instValue, document.GetAllocator());

    rapidjson::Value instNameValue;
    instNameValue.SetString("Euro/US Dollar");
    document.AddMember("instrument_name", instNameValue, document.GetAllocator());

    rapidjson::Value openValue;
    openValue.SetInt(100);
    document.AddMember("open", openValue, document.GetAllocator());

    rapidjson::Value highValue;
    highValue.SetInt(300);
    document.AddMember("high", highValue, document.GetAllocator());

    rapidjson::Value lowValue;
    lowValue.SetInt(50);
    document.AddMember("low", lowValue, document.GetAllocator());

    rapidjson::Value closeValue;
    closeValue.SetInt(300);
    document.AddMember("close", closeValue, document.GetAllocator());

    rapidjson::Value turnoverValue;
    turnoverValue.SetDouble(5425264673.23);
    document.AddMember("turnover", turnoverValue, document.GetAllocator());

    rapidjson::Value tradedVolumeValue;
    tradedVolumeValue.SetInt(5670000);
    document.AddMember("traded_volume", tradedVolumeValue, document.GetAllocator());

    rapidjson::Value marketDataValues(rapidjson::kArrayType);

    //first bid/ask
    rapidjson::Value document2Value(rapidjson::kObjectType);
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value document2Copy(CreateBidAsk1(), allocator);
    marketDataValues.PushBack(document2Copy, allocator);

    //second bid/ask
    rapidjson::Value document2Value2(rapidjson::kObjectType);
    rapidjson::Value document2Copy2(CreateBidAsk2(), allocator);
    marketDataValues.PushBack(document2Copy2, allocator);        

    document.AddMember("marketdata", marketDataValues, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::string jsonString = buffer.GetString();
    //std::cout << jsonString << std::endl;

    //FileLoader::WriteFile("example.json", (char*)jsonString.c_str(), jsonString.size());
}

void JsonMessage::ReadMarketDataFull() {

    char buf[4096];
    memset(buf, 0, 4096);
    int len = 295;

    FileLoader::ReadFile("example.json", buf, len);

    Document d;
    d.Parse(buf);

    if (d.HasMember("instrument") && d["instrument"].IsString()) {
        std::string instrument = d["instrument"].GetString();
        //std::cout << "instrument: " << instrument << std::endl;
    }
    else {
        //std::cout << "not found:" << std::endl;
    }

}


void JsonMessage::ReadMarketDataFull(char* buf) {    
    Document d;
    d.Parse(buf);

    if (d.HasMember("instrument") && d["instrument"].IsString()) {
        std::string instrument = d["instrument"].GetString();
        //std::cout << "instrument: " << instrument << std::endl;
    }
    else {
        //std::cout << "not found:" << std::endl;
    }

}