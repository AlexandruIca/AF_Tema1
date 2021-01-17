add_executable(dijkstra ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(dijkstra PRIVATE cxx_std_14)
copy_file(dijkstra.in dijkstra)
