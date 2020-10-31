add_executable(x_si_zero ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_features(x_si_zero PRIVATE cxx_std_14)
copy_file(xsizero.in x_si_zero)
