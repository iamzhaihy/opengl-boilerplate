cmake_minimum_required(VERSION 3.0.0)
project(OpenGL-Boilerplate CXX)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Library directories
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# Compilation flags: adapt to your needs
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR} )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR} )
endif()

# Add src folder to the include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add OpenGL to project
find_package(OpenGL REQUIRED)
set(LIBRARIES ${OPENGL_LIBRARIES})

# Include GLM for linear algebra
include_directories("${LIBRARY_DIR}/glm")

# Compile GLFW3 statically
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_INSTALL OFF)
add_subdirectory("${LIBRARY_DIR}/glfw" "glfw")
include_directories("${LIBRARY_DIR}/glfw/include")
list(APPEND LIBRARIES "glfw" ${GLFW_LIBRARIES})

if((UNIX AND NOT APPLE) OR WIN32)
    option(GLEW_INSTALL OFF)
    add_subdirectory("${LIBRARY_DIR}/glad" "glad")
    include_directories("${LIBRARY_DIR}/glad/include")
    list(APPEND LIBRARIES "glad")
endif()

file(GLOB PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
                          "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB PROJECT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable(${PROJECT_NAME}_bin ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_link_libraries(${PROJECT_NAME}_bin ${LIBRARIES})
