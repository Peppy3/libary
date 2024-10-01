#include <stdbool.h>

#include <test.h>

#include <os/memory.h>

bool os_memory_mmap_private(void *state) {
	const size_t map_size = 4096;
	
	void *mapping = Libary_memory_map(NULL, map_size, 
			MMapProt_Read | MMapProt_Write, false);

	if (mapping == NULL) {
		return false;
	}

	// we can loose one page if it fails ig
	bool unmap_error = Libary_memory_unmap(mapping, map_size);
	return !unmap_error;
}

bool os_memory(void *state) {
	
	Test_run_test(os_memory_mmap_private, NULL);

	return true;
}

