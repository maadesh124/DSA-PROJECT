# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyNanaApp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add the subdirectory where Nana is located (this should be the folder where the Nana source code is)
add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/nana)

# Add your source files here
set(SOURCES
    src/check.cpp
    # Add other source files here
)

# Create an executable from the sources
add_executable(MyNanaApp ${SOURCES})

# Link the Nana library with your executable
target_link_libraries(MyNanaApp nana)

# Optionally, you can set additional include directories or flags if needed:
# target_include_directories(MyNanaApp PRIVATE ${Nana_INCLUDE_DIRS})

