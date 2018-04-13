#ifndef MEMORY_ALLOCATOR_HPP
#define MEMORY_ALLOCATOR_HPP

#include <vector>

class MemoryAllocator {

public:

	/**
	* Constructor - build free list
	*
	* @param int number of page frames
	*/
	MemoryAllocator(int numPageFrames);

	// Other constructors, assignment, disallow copy/move
	MemoryAllocator(const MemoryAllocator &orig) = delete;
	MemoryAllocator(MemoryAllocator &&orig) = delete;
	MemoryAllocator operator=(const MemoryAllocator &orig) = delete;
	MemoryAllocator operator=(MemoryAllocator &&orig) = delete;

	/**
	* Destructor - default
	*/
	virtual ~MemoryAllocator() {

		//

	}

	/**
	* AllocatePageFrames - allocates specified number of page frames.
	*
	* @param count			uint32_t number of page frames
	* @param page_frames    std::vector<uint32_t> memory
	* @return				true if the page frames are successfully allocated, false if otherwise
	*/
	bool AllocatePageFrames(uint32_t count, std::vector<uint32_t> &page_frames);

	/**
	* FreePageFrames - deallocates specified number of page frames.
	*
	* @param count			uint32_t number of page frames
	* @param page_frames    std::vector<uint32_t> memory
	* @return				true if count <= page_frames.size(), otherwise returns false without freeing any page frames
	*/
	bool FreePageFrames(uint32_t count, std::vector<uint32_t> &page_frames);

	/**
	* get_page_frames_free - returns uint32_t number of free page frames
	*
	* @return	uint32_t of free page frames
	*/
	uint32_t get_page_frames_free() const;

private:

	std::vector<uint8_t> memory;
	uint32_t page_frames_total;
	uint32_t page_frames_free;
	uint32_t free_list_head;

};

#endif // !1

