cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME HigherGround)

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W1")
set(CMAKE_CXX_STANDARD 17)


find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if (DOXYGEN_FOUND)

	set(DOXYGEN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
	
    message("Doxygen build started")
	
	add_custom_target(
		docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc
	)

endif()

include_directories(prj)

#set(CMAKE_INSTALL_PREFIX .)


if (WIN32)
	install (FILES 
	${SFML_DIR}/bin/openal32.dll
	${SFML_DIR}/bin/sfml-audio-2.dll
	${SFML_DIR}/bin/sfml-graphics-2.dll
	${SFML_DIR}/bin/sfml-system-2.dll
	${SFML_DIR}/bin/sfml-window-2.dll 
	${SFML_DIR}/bin/sfml-audio-d-2.dll
	${SFML_DIR}/bin/sfml-graphics-d-2.dll
	${SFML_DIR}/bin/sfml-system-d-2.dll
	${SFML_DIR}/bin/sfml-window-d-2.dll 
	DESTINATION .
)
elseif (UNIX)
	install (FILES 
	${SFML_DIR}/bin/libsfml-audio.so.2.4.2
	${SFML_DIR}/bin/libsfml-graphics.so.2.4.2
	${SFML_DIR}/bin/libsfml-system.so.2.4.2
	${SFML_DIR}/bin/libsfml-window.so.2.4.2
	${SFML_DIR}/bin/libsfml-audio-d.so.2.4.2
	${SFML_DIR}/bin/libsfml-graphics-d.so.2.4.2
	${SFML_DIR}/bin/libsfml-system-d.so.2.4.2
	${SFML_DIR}/bin/libsfml-window-d.so.2.4.2
	DESTINATION .
)
else ()
	message (FATAL_ERROR "An unknown system")
endif ()
	

install(DIRECTORY ${CMAKE_SOURCE_DIR}/src DESTINATION .)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/doc DESTINATION ${PROJECT_BINARY_DIR})

add_subdirectory(prj)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
