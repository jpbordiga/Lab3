#include <iostream>
#include <vector>
#include <list>
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
		
		for (int i = 0; i < count; ++i) {
			//page_frames.push_back(); // addresses?
		}

	}

	page_frames_total = get_free_list().size() + get_allocated_page_frames().size();
	page_frames_free = get_free_list().size();
	free_list_head = get_free_list().front();

	return result;

}

bool MemoryAllocator::FreePageFrames(uint32_t count, std::vector<uint32_t> &page_frames) {

	bool result = false;

	if (count <= page_frames.size()) {
	
		result = true;

		for (int i = 0; i < count; ++i) {
		
			freeList.push_back(page_frames.back());
			page_frames.pop_back();

		}

		page_frames_total = get_free_list().size() + get_allocated_page_frames().size();
		page_frames_free = get_free_list().size();
		free_list_head = get_free_list().front();

	} else {
		result = false;
	}

	return result;

}

uint32_t MemoryAllocator::get_page_frames_free() const {
	return page_frames_free;
}

std::vector<uint32_t> MemoryAllocator::get_free_list() const {
	return freeList;
}

std::vector<uint32_t> MemoryAllocator::get_allocated_page_frames() const {
	return allocatedPageFrames;
}

void MemoryAllocator::print_free_list() {

	std::cout << "#2\n";

	for (int i = 0; i < (get_page_frames_free() - 1); ++i) {
		std::cout << std::hex << get_free_list().at(i) << " ";
	}

	std::cout << std::hex << get_free_list().back() << "\n";


}

