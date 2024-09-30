
if (UNIX AND NOT APPLE)
	add_subdirectory(os/linux)
elseif (WIN32)
	add_subdirectory(os/win)
endif ()

target_sources(${PROJECT_NAME} PRIVATE arena.c ring_buff.c test.c)


