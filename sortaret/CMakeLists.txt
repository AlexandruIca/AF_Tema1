add_executable(sortaret ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(sortaret PRIVATE cxx_std_14)
copy_file(sortaret.in sortaret)
