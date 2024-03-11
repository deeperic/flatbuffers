#pragma once

#include <iostream>
#include <fstream>
#include <string_view>

class FileLoader {
public:
	static void ReadFile(std::string_view filename, char* p, int len) {
		std::ifstream rf(std::string(filename), std::ios::in | std::ios::binary);
		rf.read((char*)p, len);
		rf.close();
	}

	static void WriteFile(std::string_view filename, char* p, int len) {

		//std::cout << "Write file: " << len << std::endl;

		std::ofstream wf(std::string(filename), std::ios::out | std::ios::binary);
		wf.write((char*)p, len);
		wf.close();

	}
};



