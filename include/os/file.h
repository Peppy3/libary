#ifndef LIBARY_FILE_H
#define LIBARY_FILE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Unbuffered file
#ifndef __LIBARY_FILE_DEFINED
#define __LIBARY_FILE_DEFINED
typedef intptr_t File;
#define LIBARY_FILE_INVALID_HANDLE (-1)
#endif

// NOTE: if it is doable, add async flag
enum FileOpenFlags {
	FileOpenFlags_READ = 0x00, // read access
	FileOpenFlags_WRITE = 0x01, // write access
	FileOpenFlags_RDWR = 0x02, // read and write access
	FileOpenFlags_CREATE = 0x04, // create file 
	FileOpenFlags_TRUNCATE = 0x08, // trucates the file
};

/*
 * Opens a file. It must be opened for either reading, writing, or both.
 * If FileOpenFlags_CREATE flag is set, it creates the file if it does not already exsist.
 * If the FileOpenFlags_TRUNCATE is set, the file will be truncated if it already exsists.
 * returns -1 on error
 */
File File_open(const char *path, enum FileOpenFlags flags);

// returns true on error
bool File_close(File file);

// reads and writes a buffer of a set size to the file
// they either return the size read or written or -1 if an error occured
intmax_t File_read(File file, size_t size, void *buff);
intmax_t File_write(File file, size_t size, const void *buff);

// returns the size of the file in bytes
size_t File_size(File file);

File File_get_stdin(void);
File File_get_stdout(void);
File File_get_stderr(void);

#endif /* LIBARY_FILE_H */

