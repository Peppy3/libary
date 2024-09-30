#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>

#define WIN32_LEAN_AND_MEAN // only include commonly used headers by default
#include <Windows.h>

#include <os/file.h>

File File_open(const char *path, enum FileOpenFlags flags) {
	assert(path != NULL);

	DWORD desired_access = 0;
	DWORD creation_disposition = 0;

	// read write perms
	desired_access = (flags & FileOpenFlags_WRITE) ? GENERIC_WRITE : GENERIC_READ;
	desired_access = (flags & FileOpenFlags_RDWR) ? GENERIC_WRITE|GENERIC_READ : desired_access;

	// what to do if the file does or doesn't exist
	creation_disposition |= (flags & FileOpenFlags_TRUNCATE) ? TRUNCATE_EXISTING : 0;
	creation_disposition |= (flags & FileOpenFlags_CREATE) ? CREATE_NEW : 0;

	return (intptr_t)CreateFileA(path, desired_access, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, creation_disposition, FILE_ATTRIBUTE_NORMAL, NULL);
}

bool File_close(File file) {
	return CloseHandle(file) == 0;
}

intmax_t File_read(File file, size_t size, const void *buff) {
	DWORD bytes_read = 0;
	if(ReadFile(file, buff, size, &bytes_read, NULL)) {
		return bytes_read;
	};
	return -1;
}

intmax_t File_write(File file, size_t size, void *buff) {
	DWORD bytes_written = 0;
	if (WriteFile((HANDLE)file, buff, size, &bytes_written, NULL)) {
		return bytes_written;
	};
	return -1;
}


File File_get_stdin(void) { return GetStdHandle(STD_INPUT_HANDLE); }
File File_get_stdout(void) { return GetStdHandle(STD_OUTPUT_HANDLE); }
File File_get_stderr(void) { return GetStdHandle(STD_ERROR_HANDLE); }


