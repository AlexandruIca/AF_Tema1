add_executable(padure ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(padure PRIVATE cxx_std_14)
copy_file(padure.in padure)
