set(SOURCE_FILES
        Collision.h Collision.cpp
        HigherGround.cpp
        Platforms.h Platforms.cpp
        Player.h Player.cpp
        FilesBank.h FilesBank.cpp
        GameMenu.cpp GameMenu.h 
	Button.cpp Button.h 
	Records.cpp Records.h
)

set(SFML_ROOT ${SFML_DIR})
set(SFML_STATIC_LIBRARIES FALSE)

set(CMAKE_MODULE_PATH "${SFML_DIR}/cmake/Modules")
find_package(SFML REQUIRED COMPONENTS audio graphics window system)

include_directories("${SFML_DIR}/include")
add_executable (${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})