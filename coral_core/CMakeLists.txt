#coral core
project(coral_core)


set(CORE_HEADER_FILES
	include/config.h
	include/application.h
	include/window.h
	include/entity.h
	include/scenegraph.h
	include/transform.h

	include/resources/resourcemanager.h
	include/resources/asset.h
	
	#platform
	include/platform/windows_platform.h
	
	)

set(CORE_SOURCE_FILES
	source/config.cpp
	source/application.cpp
	source/entity.cpp

	source/resources/resourcemanager.cpp
	source/resources/asset.cpp

	source/platform/windows_platform.cpp
	)




add_library(${PROJECT_NAME} 
	${CORE_HEADER_FILES}
	${CORE_SOURCE_FILES}
)
add_library(coral::core ALIAS ${PROJECT_NAME})

target_link_libraries(coral_core PRIVATE flatbuffers)

#  Includes
target_include_directories(${PROJECT_NAME}
	PRIVATE
	PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_SOURCE_DIR}/extern
)

# Compiler options
target_compile_options(${PROJECT_NAME}
	PRIVATE 
		-W3)
if(CORAL_DEVELOP_MODE)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE
			CORAL_DEVELOP_MODE)
endif()
		
if(BUILD_SHARED_LIBS)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE
			CORAL_DLL_EXPORT)
endif()

