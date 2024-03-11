#include <iomanip>
#include "FlatBufferesMessage.h"
#include "FileLoader.h"

void FlatBufferesMessage::Write() {
	
	flatbuffers::FlatBufferBuilder builder;

	auto from = builder.CreateString("Sally");
	auto to = builder.CreateString("Jerry");
	auto freetext = builder.CreateString("good morning?");
	auto freenumber = 0.123456789;

	auto header = CreateHeader(builder, from, to, 1234);
	auto message = CreateMessage(builder, header, freetext, freenumber);

	builder.Finish(message); 

	FileLoader::WriteFile("demo.dat", (char*)builder.GetBufferPointer(), builder.GetSize());

	//std::cout << "done writing: " << builder.GetSize() << std::endl;

}


void FlatBufferesMessage::Read() {

	char buf[4096];
	int len = 120;

	FileLoader::ReadFile("demo.dat", buf, len);

	auto msg = GetMessage(buf);
	//std::cout << "from: " << msg->header()->from()->c_str()
	//	<< " to: " << msg->header()->to()->c_str()
	//	<< " freetext: " << msg->freetext()->c_str()
	//	<< " freenumber: " << std::setprecision(12) << msg->freenumber()
	//	<< std::endl;


	//std::cout << "done reading" << std::endl;

}


void FlatBufferesMessage::WriteMarketDataFull() {
	flatbuffers::FlatBufferBuilder builder;

	std::string instrument{"EUR/USD"};
	std::string instrument_name{"Euro/US Dollar"};
	auto open = 100;
	auto high = 300;
	auto low = 50;
	auto close = 300;
	auto turnover = 5425264673.23;
	auto traded_volume = 5670000;

	auto marketDataInformation = CreateMarketDataInformationDirect(builder, 
		instrument.c_str(), instrument_name.c_str(),
		open, high, low, close, turnover, traded_volume);

	auto md1 = CreateMarketDataEntry(builder, 100.123, 2000000, 101.789, 4000000);
	auto md2 = CreateMarketDataEntry(builder, 99.123, 3000000, 102.789, 1000000);

	// Create a FlatBuffer's `vector` from the `std::vector`.
	std::vector<flatbuffers::Offset<MarketDataEntry>> market_data_entry_vector;
	market_data_entry_vector.push_back(md1);
	market_data_entry_vector.push_back(md2);
	auto market_data_entries = builder.CreateVector(market_data_entry_vector);

	auto marketDataFull = CreateMarketDataFull(builder, marketDataInformation, market_data_entries);
	builder.Finish(marketDataFull);

	//FileLoader::WriteFile("market_data_full.dat", (char*)builder.GetBufferPointer(), builder.GetSize());

	//std::cout << "done writing: " << builder.GetSize() << std::endl;
}

void FlatBufferesMessage::ReadMarketDataFull() {
	char buf[4096];
	int len = 288;

	FileLoader::ReadFile("market_data_full.dat", buf, len);

	auto msg = ::flatbuffers::GetRoot<BOCHK::GlobalMarket::FlatBuffers::demo::MarketDataFull>(buf);
	//std::cout << "instrument: " << msg->mdi()->instrument()->c_str() << std::endl
	//	<< " name: " << msg->mdi()->insrument_name()->c_str() << std::endl
	//	<< " open: " << msg->mdi()->open() << std::endl
	//	<< " high: " << msg->mdi()->high() << std::endl
	//	<< " low: " << msg->mdi()->low() << std::endl
	//	<< " close: " << msg->mdi()->close() << std::endl
	//	<< " turnover: " << msg->mdi()->turnover() << std::endl
	//	<< " traded_volume: " << msg->mdi()->traded_volume() << std::endl;

	auto md = msg->md(); // A pointer to a `flatbuffers::Vector<>`.
	auto size = msg->md()->size();
	for (int i = 0; i < size; ++i) {
		//std::cout << "bid/ask: " 
		//	<< msg->md()->Get(i)->bid_qty() << " " << msg->md()->Get(i)->bid() << " " 
		//	<< msg->md()->Get(i)->ask() << " " << msg->md()->Get(i)->ask_qty()
		//	<< std::endl;
	}


	//std::cout << "done reading" << std::endl;

}

void FlatBufferesMessage::ReadMarketDataFull(char* buf) {
	auto msg = ::flatbuffers::GetRoot<BOCHK::GlobalMarket::FlatBuffers::demo::MarketDataFull>(buf);
}

void FlatBufferesMessage::WriteMarketDataBBO() {
	flatbuffers::FlatBufferBuilder builder;

	std::string instrument{ "EUR/HKD" };

	//create the market data
	auto marketDataEntry = CreateMarketDataEntry(builder, 10.05, 3000, 12.35, 6000);
	auto bbo = CreateMarketDataBBODirect(builder, instrument.c_str(), marketDataEntry);

	//create the union
	auto mdholder = CreateMarketDataHolder(builder, MarketData::MarketData_MarketDataBBO, bbo.Union());
	builder.Finish(mdholder);

	FileLoader::WriteFile("market_data_holder.dat", (char*)builder.GetBufferPointer(), builder.GetSize());

	//std::cout << "done writing: " << builder.GetSize() << std::endl;
}

void FlatBufferesMessage::ReadMarketDataBBO() {
	char buf[4096];
	int len = 104;

	FileLoader::ReadFile("market_data_holder.dat", buf, len);

	auto msg = ::flatbuffers::GetRoot<BOCHK::GlobalMarket::FlatBuffers::demo::MarketDataHolder>(buf);
	if (msg->md_type() == MarketData::MarketData_MarketDataBBO) {

		auto bbo = msg->md_as_MarketDataBBO();
		//std::cout << "instrument: " << bbo->instrument()->c_str() << std::endl			
		//	<< " bid/ask: " 
		//	<< bbo->md()->bid_qty() << " " << bbo->md()->bid() << " "
		//	<< bbo->md()->ask() << " " << bbo->md()->ask_qty()
		//	<< std::endl;
	}
	else {
		//std::cout << "not bbo" << std::endl;
	}

	//std::cout << "done reading" << std::endl;
}


void FlatBufferesMessage::WriteSimpleTable() {

	flatbuffers::FlatBufferBuilder builder;
	auto message = CreateSimpleTableDirect(builder, "Eric Chan", 18000, 68.8);
	builder.Finish(message);
	auto msg = (char*)builder.GetBufferPointer();

	FileLoader::WriteFile("simple_table.dat", msg, builder.GetSize());


	std::cout << "msg size: " << builder.GetSize() << std::endl;
}

void FlatBufferesMessage::ReadSimpleTable() {

	char buf[4096];
	int len = 56;

	FileLoader::ReadFile("simple_table.dat", buf, len);
	auto msg = ::flatbuffers::GetRoot<BOCHK::GlobalMarket::FlatBuffers::demo::SimpleTable>(buf);

	std::cout << "name: " << msg->name()->c_str() << std::endl
		<< " age: " << msg->age() << std::endl
		<< " weight: " << msg->weight() << std::endl;
}
