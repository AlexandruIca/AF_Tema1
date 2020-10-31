add_executable(ctc ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(ctc PRIVATE cxx_std_14)
copy_file(ctc.in ctc)
