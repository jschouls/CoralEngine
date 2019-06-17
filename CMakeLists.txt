cmake_minimum_required( VERSION 3.9.1 )


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#option(USE_PYTHON "Include Python")
option(BUILD_SHARED_LIBS "Build shared library" OFF)
option(CORAL_DEVELOP_MODE "Setting the develop mode which gives some extra features." ON)

# Output directory for .lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib/) 
# Output directory for .dll
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib/) 
# Output directory for .exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/dll/)


if( MSVC )
    add_compile_options(/MP)
endif()

project(coral
        LANGUAGES CXX
        VERSION 0.0.1)

		
# Add FlatBuffers directly to our build. This defines the `flatbuffers` target.
set(FLATBUFFERS_SRC_DIR ${CMAKE_SOURCE_DIR}/extern/flatbuffers)
add_subdirectory(${FLATBUFFERS_SRC_DIR}
                 ${CMAKE_CURRENT_BINARY_DIR}/flatbuffers-build
                 EXCLUDE_FROM_ALL)
# Now simply link against flatbuffers as needed to your already declared target.
# The flatbuffers target carry header search path automatically if CMake > 2.8.11.
add_subdirectory(coral_core)
add_subdirectory(sandbox)


set_directory_properties( PROPERTIES 
    VS_STARTUP_PROJECT MyApp
)

configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/coral_core/include/config.h"
)

set_target_properties(coral_core MyApp
						PROPERTIES CXX_STANDARD 17)

