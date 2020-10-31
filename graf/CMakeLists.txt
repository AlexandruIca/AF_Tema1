add_executable(graf ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(graf PRIVATE cxx_std_14)
copy_file(graf.in graf)
