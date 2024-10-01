#include <stddef.h>
#include <stdbool.h>

#include <sys/mman.h>

#include <os/memory.h>


void *Libary_memory_map(void *start_addr, size_t size, 
		File file, enum MMapProt prot, bool shared) {

	if (prot & MMapProt_Execute && !(prot & MMapProt_Read)) {
		return NULL;
	}

	int protections = 0;
	protections |= (prot & MMapProt_Read) ? PROT_READ : 0;
	protections |= (prot & MMapProt_Write) ? PROT_WRITE : 0;
	protections |= (prot & MMapProt_Execute) ? PROT_EXEC : 0;
	
	int flags = (shared) ? MAP_SHARED : MAP_PRIVATE;

	flags |= (file == LIBARY_FILE_INVALID_HANDLE) ? MAP_ANONYMOUS : 0;

	void *addr = mmap(start_addr, size, protections, flags, file, 0);
	
	return (addr != MAP_FAILED) ? addr : NULL;
}

bool Libary_memory_unmap(void *start_addr, size_t size) {
	return (bool)munmap(start_addr, size);
}

