#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include "MemoryAllocator.hpp"

// the private member vars need to be given vals

MemoryAllocator::MemoryAllocator(int numPageFrames) {
	
	page_frames_total = numPageFrames;
	int memSize = numPageFrames * page_frames_size;
	memory.reserve(memSize);
	memory.resize(memSize);
	freeList.reserve(memSize);
	freeList.resize(memSize);

	

}

bool MemoryAllocator::AllocatePageFrames(uint32_t count, std::vector<uint32_t> &page_frames) {

	bool result = false;

	if (get_page_frames_free() <= count) { //
		result = false;
	} else {
		
		uint32_t index = get_memory().size();
		uint32_t v32 = 0x0; //

		for (uint32_t i = 0; i < count; ++i) {
			
			page_frames.push_back(get_free_list().at(i));
			memcpy(&memory[index + i], &v32, sizeof(uint32_t));
			get_free_list().pop_back();

		}

		page_frames_total = get_free_list().size() + get_allocated_page_frames().size();
		page_frames_free = get_free_list().size();

		if (get_free_list().size() == 0) {
			free_list_head = 0xFFFFFFFF;
		} else {
			free_list_head = get_free_list().front();
		}

	}

	return result;

}

bool MemoryAllocator::FreePageFrames(uint32_t count, std::vector<uint32_t> &page_frames) {

	std::cout << "FreePageFrames called\n";

	bool result = false;

	std::cout << "0\n";

	if (count <= page_frames.size()) {
	
		result = true;

		std::cout << "1\n";

		uint32_t index = get_memory().size() - 1;
		uint32_t v32 = 0x0; //

		std::cout << "2\n";

		for (uint32_t i = 0; i < count; ++i) {
		

			freeList.push_back(page_frames.back());
			std::cout << "3\n";

			std::cout << v32  << "\n";
			std::cout << "3.1\n";
			std::cout << index - i << " ***\n";
			std::cout << "3.2\n";
			std::cout << get_memory().at(index - i) << "\n";

			std::cout << "3.3\n";

			memcpy(&v32, &get_memory().at(index - i), sizeof(uint32_t)); //
			std::cout << "4\n";
			
			page_frames.pop_back();
			std::cout << "5\n";
		}

		std::cout << "6\n";
		page_frames_total = get_free_list().size() + get_allocated_page_frames().size();
		std::cout << "7\n";
		page_frames_free = get_free_list().size();
		std::cout << "8\n";
		if (get_free_list().size() == 0) {
			free_list_head = 0xFFFFFFFF;
			std::cout << "9\n";
		} else {
			free_list_head = get_free_list().front();
			std::cout << "get_free_list().size() != 0\n";
		}

	} else {
		result = false;
		std::cout << "count >= page_frames.size()\n";
	}

	return result;

}

uint32_t MemoryAllocator::get_page_frames_free() const {
	return page_frames_free;
}

std::vector<uint32_t> MemoryAllocator::get_free_list() const {
	return freeList;
}

std::vector<uint8_t> MemoryAllocator::get_memory() const {
	return memory;
}

std::vector<uint32_t> MemoryAllocator::get_allocated_page_frames() const {
	return allocatedPageFrames;
}

void MemoryAllocator::print_free_list() {

	//std::cout << get_free_list().size() << " ###\n";

	for (int i = 0; i < (get_page_frames_free() - 1); ++i) {
		std::cout << std::hex << get_free_list().at(i) << " ";
	}

	std::cout << std::hex << get_free_list().back() << "\n";


}

