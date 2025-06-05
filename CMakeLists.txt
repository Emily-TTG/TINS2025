# Minimum from sPDNgin.
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(TINS25)

add_executable(game WIN32)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/res)
add_dependencies(game assets)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/sPDNgin)

target_link_libraries(game PRIVATE pdn)

target_sources(
	game PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/src/local.c)
