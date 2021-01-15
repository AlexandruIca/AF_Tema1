add_executable(maxflow ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(maxflow PRIVATE cxx_std_14)
copy_file(maxflow.in maxflow)
