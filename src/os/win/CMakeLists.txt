
target_sources(${PROJECT_NAME} PRIVATE file.c)

target_compile_options(${PROJECT_NAME} PUBLIC /experimental:c11atomics)
# TODO: find a way to not hardcode these
target_link_directories(${PROJECT_NAME} PUBLIC "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/ucrt/x64")   # hardcoded for now
target_link_directories(${PROJECT_NAME} PUBLIC "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64")   # hardcoded for now
target_link_directories(${PROJECT_NAME} PUBLIC "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.38.33130/lib/x64")   # hardcoded for now