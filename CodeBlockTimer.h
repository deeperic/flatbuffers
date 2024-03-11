#pragma once

#include <iostream>
#include <chrono>


class CodeBlockTimer {
public:	
	void Stop() {		
		// End the timer and calculate the duration
		auto endTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

		// Print the duration
		std::cout << "Execution time: " << duration << " microseconds" << std::endl;
	}

private:
	std::chrono::high_resolution_clock::time_point startTime{ std::chrono::high_resolution_clock::now() };

};