#include <stddef.h>
#include <stdbool.h>

#define WIN32_LEAN_AND_MEAN // only include commonly used headers by default
#include <Windows.h>

#include <os/memory.h>


void *Libary_map_file(void *start_addr, size_t size, 
		File file, enum MMapProt prot, bool shared) {

	if (prot & MMapProt_Execute && !(prot & MMapProt_Read)) {
		return NULL;
	}

	ULONG protection = 0;

	switch (prot) {
	case MMapProt_Read:
		protection = PAGE_READONLY;
		break;
	case MMapProt_Read | MMapProt_Write:
		protection = PAGE_READWRITE;
		break;
	case MMapProt_Execute | MMapProt_Read:
		protection = PAGE_EXECUTE_READ;
		break;
	case MMapProt_Execute | MMapProt_Read | MMapProt_Write:
		protection = PAGE_EXECUTE_READWRITE;
		break;
	default:
		return NULL;
	}

	DWORD max_size_low = 0, max_size_high = 0;

	max_size_low = size & 0xFFFFFFFF;
	max_size_high = (size >> 32) & 0xFFFFFFFF;
	
	HANDLE file_mapping_object = CreateFileMappingA((HANDLE)file, NULL, protection, max_size_high, max_size_low, NULL);

	if (file_mapping_object == NULL) return NULL;

	DWORD access = 0;
	access |= (prot & MMapProt_Read) ? FILE_MAP_READ : 0;
	access |= (prot & MMapProt_Write) ? FILE_MAP_WRITE : 0;
	access |= (prot & MMapProt_Execute) ? FILE_MAP_EXECUTE : 0;
	return MapViewOfFile(file_mapping_object, access, 0, 0, size);
	
}

bool Libary_unmap_file(void *start_addr, size_t size) {
	// we have to call FlushViewOfFile because the modified pages are written "lazily" to disk
	if (!FlushViewOfFile(start_addr, size)) {
		return true; // unable to flush file to disk
	};
	return !UnmapViewOfFile(start_addr);
}

void* Libary_map_memory(void* start_addr, size_t size,
	enum MMapProt prot, bool shared) {

	if (prot & MMapProt_Execute && !(prot & MMapProt_Read)) {
		return NULL;
	}

	ULONG protection = 0;

	switch (prot) {
	case MMapProt_Read:
		protection = PAGE_READONLY;
		break;
	case MMapProt_Read | MMapProt_Write:
		protection = PAGE_READWRITE;
		break;
	case MMapProt_Execute | MMapProt_Read:
		protection = PAGE_EXECUTE_READ;
		break;
	case MMapProt_Execute | MMapProt_Read | MMapProt_Write:
		protection = PAGE_EXECUTE_READWRITE;
		break;
	default:
		return NULL;
	}

	return VirtualAlloc(start_addr, size, MEM_RESERVE | MEM_COMMIT, protection);
}

bool Libary_unmap_memory(void* start_addr, size_t size) {
	return !VirtualFree(start_addr, 0, MEM_RELEASE);
}