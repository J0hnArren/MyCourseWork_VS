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

set(SFML_ROOT ${CMAKE_SOURCE_DIR}/libs/SFML-2.4.2)
set(SFML_STATIC_LIBRARIES FALSE)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/libs/SFML-2.4.2/cmake/Modules")
find_package(SFML REQUIRED COMPONENTS audio graphics window system)

include_directories(${SFML_INCLUDE_DIR})
add_executable (${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})