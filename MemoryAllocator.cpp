#include <iostream>
#include <vector>
#include <list>
#include "MemoryAllocator.hpp"

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





	return result;

}

bool MemoryAllocator::FreePageFrames(uint32_t count, std::vector<uint32_t> &page_frames) {

	bool result = false;





	return result;

}

uint32_t MemoryAllocator::get_page_frames_free() const {
	return page_frames_free;
}

std::vector<uint32_t> MemoryAllocator::get_free_list() const {
	return freeList;
}

void MemoryAllocator::print_free_list() {

}

