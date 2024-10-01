# code to find subdirectories of a folder taken from
# https://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

target_sources(${PROJECT_NAME} PRIVATE file.c "memory.c")

target_compile_options(${PROJECT_NAME} PUBLIC /experimental:c11atomics)

# get the location of the windows SDK from registry
cmake_host_system_information(RESULT WINAPI_DIR QUERY WINDOWS_REGISTRY "HKLM/SOFTWARE/Microsoft/Windows Kits/Installed Roots" VALUE "KitsRoot10")
cmake_host_system_information(RESULT WINAPI_SDKS QUERY WINDOWS_REGISTRY "HKLM/SOFTWARE/Microsoft/Windows Kits/Installed Roots" SUBKEYS)
list(GET WINAPI_SDKS -1 WINAPI_CHOSEN_SDK)

target_link_directories(${PROJECT_NAME} PUBLIC "${WINAPI_DIR}/Lib/${WINAPI_CHOSEN_SDK}/ucrt/x64")
target_link_directories(${PROJECT_NAME} PUBLIC "${WINAPI_DIR}/Lib/${WINAPI_CHOSEN_SDK}/um/x64")

# locate vswhere
find_program(vswhere_tool 
    NAMES vswhere 
    PATHS "$ENV{ProgramFiles\(x86\)}/Microsoft Visual Studio/Installer")
if (NOT ${vswhere})
  message(FATAL_ERROR "Could not locate vswhere.exe")
endif()

# use vswhere to get visual studio's install dir
execute_process(COMMAND ${vswhere_tool} -property installationPath OUTPUT_VARIABLE VS_INSTALL_DIR)

# strip trailing newline and replace backslash with forwardslash
string(STRIP ${VS_INSTALL_DIR} VS_INSTALL_DIR)
string(REPLACE "\\" "/" VS_INSTALL_DIR ${VS_INSTALL_DIR})

# get a list of all installed MSVC versions and pick the newest
SUBDIRLIST(MSVC_INSTALL_DIR "${VS_INSTALL_DIR}/VC/Tools/MSVC")
list(GET MSVC_INSTALL_DIR -1 MSVC_VER)

target_link_directories(${PROJECT_NAME} PUBLIC "${VS_INSTALL_DIR}/VC/Tools/MSVC/${MSVC_VER}/lib/x64")