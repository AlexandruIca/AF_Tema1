add_executable(bfs ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(bfs PRIVATE cxx_std_14)
copy_file(bfs.in bfs)
