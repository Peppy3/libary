#include <stddef.h>
#include <stdbool.h>

#include <sys/mman.h>

#include <os/memory.h>


void *Libary_map_file(void *start_addr, size_t size,
		File file, enum MMapProt prot, bool shared) {

	if (prot & MMapProt_Execute && !(prot & MMapProt_Read)) {
		return NULL;
	}

	int protections = 0;
	protections |= (prot & MMapProt_Read) ? PROT_READ : 0;
	protections |= (prot & MMapProt_Write) ? PROT_WRITE : 0;
	protections |= (prot & MMapProt_Execute) ? PROT_EXEC : 0;
	
	int flags = (shared) ? MAP_SHARED : MAP_PRIVATE;

	void *addr = mmap(start_addr, size, protections, flags, file, 0);
	
	return (addr != MAP_FAILED) ? addr : NULL;
}

bool Libary_unmap_file(void *start_addr, size_t size) {
	return (bool)munmap(start_addr, size);
}

void* Libary_map_memory(void* start_addr, size_t size,
	enum MMapProt prot, bool shared) {

	if (prot & MMapProt_Execute && !(prot & MMapProt_Read)) {
		return NULL;
	}

	int protections = 0;
	protections |= (prot & MMapProt_Read) ? PROT_READ : 0;
	protections |= (prot & MMapProt_Write) ? PROT_WRITE : 0;
	protections |= (prot & MMapProt_Execute) ? PROT_EXEC : 0;
	
	int flags = MAP_ANONYMOUS;
	flags |= (shared) ? MAP_SHARED : MAP_PRIVATE;

	// file is -1 for compatibility reasons
	void *addr = mmap(start_addr, size, protections, flags, -1, 0);
	
	return (addr != MAP_FAILED) ? addr : NULL;
}

bool Libary_unmap_memory(void* start_addr, size_t size) {
	return (bool)munmap(start_addr, size);
}
