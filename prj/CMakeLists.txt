set(
        SOURCE_FILES
        Collision.h Collision.cpp
        HigherGround.cpp
        Platforms.h Platforms.cpp
        Player.h Player.cpp
        FilesBank.h FilesBank.cpp
        GameMenu.cpp GameMenu.h 
	Button.cpp Button.h 
	Records.cpp Records.h
)

set(SFML_ROOT ${CMAKE_SOURCE_DIR}/libs/SFML_VS)
set(SFML_STATIC_LIBRARIES FALSE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libs/SFML_VS/cmake/Modules")
find_package(SFML REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	add_executable (${PROJECT_NAME} ${SOURCE_FILES})
	target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()
