#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include "MemoryAllocator.hpp"

int main() {
	
	std::string fileName = "allocator1.txt";

	std::ifstream iF;

	iF.open(fileName);

	if (iF.fail()) {
		std::cout << fileName << "\n";
		throw std::runtime_error("ERROR: file not found: " + fileName);
	} else {
		
		uint32_t totalPageFrames = 0;
		uint32_t command;
		uint32_t count; // number of page frames to alloc or dealloc
		std::string currentLine;
		std::getline(iF, currentLine);
		std::istringstream sstream(currentLine, std::ios::in);

		sstream >> totalPageFrames;

		MemoryAllocator *mA = new MemoryAllocator(totalPageFrames);
		
		while (std::getline(iF, currentLine)) {

			std::istringstream sstream(currentLine, std::ios::in);
		
			sstream >> command;
			sstream >> count; 

			if (command == 0) { //

				//std::cout << "0\n";
				std::vector<uint32_t> freeListTemp = mA->get_free_list();
				mA->FreePageFrames(count, freeListTemp);

			} else if (command == 1) {

				//std::cout << "1\n";
				std::vector<uint32_t> freeListTemp = mA->get_free_list();
				mA->AllocatePageFrames(count, freeListTemp);

			} else if (command == 2) {
				//std::cout << "2\n";
				mA->print_free_list();
			}
		
		}

	}
	
	




	return 0;
}