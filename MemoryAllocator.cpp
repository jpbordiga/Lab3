#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include "MemoryAllocator.hpp"

MemoryAllocator::MemoryAllocator(int numPageFrames) {
	
	uint32_t page_frames_total = (uint32_t) numPageFrames;
	uint32_t page_frames_free =  numPageFrames;
	uint32_t free_list_head = 0x00000000; // 0x00000000 or 0xFFFFFFFF?
	uint32_t memSize = numPageFrames * page_frames_size;
	
	memory.reserve(memSize);
	memory.resize(memSize);

	memcpy(&memory[0], &page_frames_total, sizeof(uint32_t));
	memcpy(&memory[4], &page_frames_free, sizeof(uint32_t));
	memcpy(&memory[8], &free_list_head, sizeof(uint32_t));

	for (int i = 1; i < numPageFrames; ++i) {
	
		uint32_t v32 = i * page_frames_size;
		memcpy(&memory[i * page_frames_size], &v32, sizeof(uint32_t));

	}

	

	


	

}

bool MemoryAllocator::AllocatePageFrames(uint32_t count, std::vector<uint32_t> &page_frames) {

	bool result = false; 

	if (get_page_frames_free() <= count) { //
		result = false;
	} else {
		
		uint32_t index = page_frames_size;
		uint32_t v32 = 0x0;

		for (uint32_t i = 0; i < count; ++i) {
			
			memcpy(&v32, &memory[(index * count) - (index * i)], sizeof(uint32_t));
			page_frames.push_back(v32); //

		}

		set_page_frames_free(get_page_frames_free() - count);

		if (get_page_frames_free() == 0) {
			set_free_list_head(0xFFFFFFFF);
		} else {
			//free_list_head = get_free_list().front();
		}

	}
	
	return result;

}

bool MemoryAllocator::FreePageFrames(uint32_t count, std::vector<uint32_t> &page_frames) {

	bool result = false;

	if (count <= page_frames.size()) {
	
		result = true;

		uint32_t index = page_frames_size;
		uint32_t v32 = 0x0;

		for (uint32_t i = 1; i < count; ++i) {
		
			memcpy(&memory[(index * count) - (index * (i + 1))], &page_frames.back(), sizeof(uint32_t));
			page_frames.pop_back();

		}

		set_page_frames_free(get_page_frames_free() + count);

		if (get_page_frames_free() == 0) {
			set_free_list_head(0xFFFFFFFF);
		}
		else {
			//
		}

	} else {
		result = false;
	}

	return result;

}

uint32_t MemoryAllocator::get_page_frames_free() const {
	
	uint32_t result = 0x0;
	memcpy(&result, &get_memory().at(4), sizeof(uint32_t));
	return result;

}

void MemoryAllocator::set_page_frames_free(uint32_t f) const {
	memcpy(&get_memory()[4], &f, sizeof(uint32_t));
}

std::vector<uint8_t> MemoryAllocator::get_memory() const {
	return memory;
}

uint32_t MemoryAllocator::get_free_list_head() const {

	uint32_t result = 0x0;
	memcpy(&result, &get_memory().at(8), sizeof(uint32_t));
	return result;

}

void MemoryAllocator::set_free_list_head(uint32_t f) const {
	memcpy(&get_memory()[8], &f, sizeof(uint32_t));
}

uint32_t MemoryAllocator::get_page_frames_total() const {

	uint32_t result = 0x0;
	memcpy(&result, &get_memory().at(0), sizeof(uint32_t));
	return result;

}

void MemoryAllocator::print_free_list() {

	for (uint32_t i = 0; i < get_page_frames_free(); ++i) {
		std::cout << std::hex << get_memory().at((page_frames_size * i) - (page_frames_size * (i))) << " ";
	}

	std::cout << "\n";

	//std::cout << std::hex << get_memory().at(page_frames_size) << "\n";


}

