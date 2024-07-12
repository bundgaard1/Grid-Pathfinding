project(Pathfinding)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Add the executable
add_executable(Pathfinding src/main.cpp src/Grid.cpp src/Cell.cpp src/UI.cpp) # Add other source files as needed

# Link libraries (if you're using SFML or any other libraries)
target_link_libraries(Pathfinding sfml-graphics)