add_executable(biconex ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(biconex PRIVATE cxx_std_14)
copy_file(biconex.in biconex)
