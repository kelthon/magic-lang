# CMake configuration file for setting up and running unit tests

# Include GoogleTest as an external dependency
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip # Source of GoogleTest
  DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)

# For Windows: Ensure GoogleTest uses the same runtime library settings as the parent project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest) # Download and make GoogleTest available for use

# Collect all test source files from the "tests" directory
file(GLOB TEST_FILES "*.cpp") # Automatically find all .cpp files in the "tests" directory

# Create the test executable mg with the collected test files
add_executable("${PROJECT_NAME}_tests" ${TEST_FILES} ${SOURCE_FILES}) # Build the test binary
target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest gtest_main mg) # Link GoogleTest and the shared library mg to the test executable

# Enable testing and register the tests to be run with ctest
enable_testing()
add_test(NAME Tests COMMAND ${PROJECT_NAME}_tests) # Define the test target for ctest
