#ifndef LIBARY_OS_MEMORY
#define LIBARY_OS_MEMORY

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef __LIBARY_FILE_DEFINED
#define __LIBARY_FILE_DEFINED
typedef intptr_t File;
#define LIBARY_FILE_INVALID_HANDLE (-1)
#endif

enum MMapProt {
	MMapProt_Read = 0x01,
	MMapProt_Write = 0x02,
	MMapProt_Execute = 0x04,
};

// start_addr: NULL or a request to the start of the memory region (the request may not be fulfilled
// size: size size of the object being mapped
// file: LIBARY_FILE_INVALID_HANDLE or a handle to a file object
// prot: what memory protections the memory mapping should have (this should not be set to write and execute)
// shared: if the memory map is shared or private
//
// returns NULL if not able to map the memory region
void *Libary_memory_map(void *start_addr, size_t size, 
		File file, enum MMapProt prot, bool shared);


// start_addr: address to the start of the memory region
// size: the size of the memory region
//
// returns true if unable to unmap the memory region
bool Libary_memory_unmap(void *start_addr, size_t size);

#endif /* LIBARY_OS_MEMORY */

