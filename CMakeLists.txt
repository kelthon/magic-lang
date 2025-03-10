cmake_minimum_required(VERSION 3.20)
project(magic)

include_directories(include)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}  PRIVATE m)
