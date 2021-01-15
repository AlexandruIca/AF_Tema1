add_executable(kruskal ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(kruskal PRIVATE cxx_std_14)
copy_file(apm.in kruskal)
