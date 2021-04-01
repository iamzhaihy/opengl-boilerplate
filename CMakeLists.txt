cmake_minimum_required(VERSION 3.0.0)
project(OpenGL-Boilerplate CXX)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG)
    set("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG}" "${CMAKE_BINARY_DIR}")
    set("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG}" "${CMAKE_BINARY_DIR}")
    set("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG}" "${CMAKE_BINARY_DIR}")
endforeach(CONFIG CMAKE_CONFIGURATION_TYPES)

# Library directories
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# Add src folder to the include directories
set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Add OpenGL to project
find_package(OpenGL REQUIRED)
set(LIBRARIES ${OPENGL_LIBRARIES})

# Include GLM for linear algebra
list(APPEND INCLUDE_DIRS "${LIBRARY_DIR}/glm")

# Compile GLFW3 statically
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_INSTALL OFF)
add_subdirectory("${LIBRARY_DIR}/glfw" "glfw")
list(APPEND INCLUDE_DIRS "${LIBRARY_DIR}/glfw/include")
list(APPEND LIBRARIES "glfw" "${GLFW_LIBRARIES}")

if((UNIX AND NOT APPLE) OR WIN32)
    add_subdirectory("${LIBRARY_DIR}/glad" "glad")
    list(APPEND INCLUDE_DIRS "${LIBRARY_DIR}/glad/include")
    list(APPEND LIBRARIES "glad")
endif()

file(GLOB PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
                          "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB PROJECT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

add_executable("${PROJECT_NAME}_bin" ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_include_directories("${PROJECT_NAME}_bin" PRIVATE ${INCLUDE_DIRS})
target_link_libraries("${PROJECT_NAME}_bin" ${LIBRARIES})
