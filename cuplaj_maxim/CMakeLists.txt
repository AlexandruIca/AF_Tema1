add_executable(cuplaj ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(cuplaj PRIVATE cxx_std_14)
copy_file(cuplaj.in cuplaj)
