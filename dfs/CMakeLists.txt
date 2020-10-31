add_executable(dfs ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(dfs PRIVATE cxx_std_14)
copy_file(dfs.in dfs)
