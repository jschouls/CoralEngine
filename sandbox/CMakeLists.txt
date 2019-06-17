set(APP_TARGET_NAME MyApp)

set(APP_HEADER_FILES) # none yet

set(APP_SOURCE_FILES
    source/main.cpp)

add_executable(${APP_TARGET_NAME} WIN32
    ${APP_HEADER_FILES}
    ${APP_SOURCE_FILES}
)

target_include_directories(${APP_TARGET_NAME}
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${APP_TARGET_NAME} 
	PUBLIC
    coral::core
)

set_property(TARGET MyApp PROPERTY CXX_STANDARD 17)

#if(WIN32)
#	set(APP_HEADER_FILES
#		include/platform/windows.h)
#
#	set(APP_SOURCE_FILES
#		source/platform/windows.cpp)
#endif(WIN32)


#target_compile_options(${APP_TARGET_NAME} 
#	PUBLIC "/SUBSYSTEM:CONSOLE"
#	)

#if(WIN32)
#	set_target_properties(${APP_TARGET_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
#	set_target_properties(${APP_TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
#	set_target_properties(${APP_TARGET_NAME} PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
#	set_target_properties(${APP_TARGET_NAME} PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
#	set_target_properties(${APP_TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
#	set_target_properties(${APP_TARGET_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
#
#endif(WIN32)
