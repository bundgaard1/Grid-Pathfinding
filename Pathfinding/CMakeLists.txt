project(Pathfinding)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Add the executable
add_executable(Pathfinding src/main.cpp src/Grid.cpp src/Cell.cpp src/UI.cpp src/GridController.cpp src/GridView.cpp src/App.cpp src/DFSSearch.cpp src/AstarSearch.cpp) # Add other source files as needed

# Link libraries (if you're using SFML or any other libraries)
target_link_libraries(Pathfinding sfml-graphics)

# Set the source and destination directories for resources
set(RESOURCE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/Pathfinding/resources")
set(RESOURCE_DEST_DIR "${CMAKE_BINARY_DIR}/resources")

# Copy resources to build directory
file(COPY ${RESOURCE_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})