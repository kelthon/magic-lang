cmake_minimum_required(VERSION 3.20)
project(magic)

# Sets compiler version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the "include" directory to all targets
include_directories(${CMAKE_SOURCE_DIR}/include)

# Generate a library mg that includes shared source files, excluding main.cpp
file(GLOB SOURCE_FILES "src/*.cpp")
list(FILTER SOURCE_FILES EXCLUDE REGEX "src/main\\.cpp")
add_library(mg ${SOURCE_FILES}) # Add library with the shared logic
target_link_libraries(mg PRIVATE m) # Link the math library (libm) to library mg

# Create the main executable using the remaining source files
add_executable(${PROJECT_NAME} src/main.cpp) # Compile the executable
target_link_libraries(${PROJECT_NAME} PRIVATE mg) # Link the shared library mg to the executable

# Add the "tests" directory and include its CMakeLists.txt to manage test setup
# add_subdirectory(tests)
