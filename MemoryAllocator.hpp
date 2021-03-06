#ifndef MEMORY_ALLOCATOR_HPP
#define MEMORY_ALLOCATOR_HPP

#include <vector>
#include <fstream>

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




	/**
	* get_free_list - accesses the free list
	*/
	std::vector<uint32_t> get_free_list() const;

	/**
	* print_free_list - prints the free list
	*/
	void print_free_list(); // params?

private:

	std::vector<uint8_t> memory;
	std::vector<uint32_t> freeList; // page frames // vector or list type?
	std::vector<uint32_t> allocatedPageFrames; // addresses of currently alloacted page frames
	uint32_t page_frames_size = 0x10000; //
	uint32_t page_frames_total;
	uint32_t page_frames_free;
	uint32_t free_list_head;
	//std::ifstream iF;

};

#endif // !1

