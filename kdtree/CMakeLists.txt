add_executable(kdtree ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(kdtree PRIVATE cxx_std_14)
copy_file(kdtree.in kdtree)
