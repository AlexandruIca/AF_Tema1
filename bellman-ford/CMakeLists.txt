add_executable(bellman-ford ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(bellman-ford PRIVATE cxx_std_14)
copy_file(bellmanford.in bellman-ford)
