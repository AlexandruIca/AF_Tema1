cmake_minimum_required(VERSION 3.13)

project(AF_Tema1)

macro(copy_file FILE_NAME EXECUTABLE_NAME)
  add_custom_command(
    TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}
            ${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME})
endmacro()

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/x_si_zero/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sortaret/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bfs/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dfs/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ctc/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/graf/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/padure3/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/biconexe/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/bellman-ford/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/flux_maxim/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cuplaj_maxim/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/kruskal/)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/kdtree/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dijkstra/)
