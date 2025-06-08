# Minimum from sPDNgin.
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(TINS25)

add_executable(game WIN32)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/res)
add_dependencies(game assets)

set(WANT_COLOR OFF)
set(WANT_MEMFILE OFF)
set(WANT_PHYSFS OFF)
set(WANT_NATIVE_DIALOG OFF)
set(WANT_VIDEO OFF)
set(WANT_IMAGE_JPG OFF)
set(WANT_IMAGE_PNG OFF)
set(WANT_IMAGE_FREEIMAGE OFF)
set(WANT_IMAGE_WEBP OFF)
set(WANT_ACODEC ON)
set(WANT_FLAC OFF)
set(WANT_VORBIS OFF)
set(WANT_OPUS OFF)
set(WANT_DUMB OFF)
set(WANT_OPENMPT OFF)
set(WANT_MP3 OFF)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/vendor/sPDNgin)

target_link_libraries(game PRIVATE pdn)

target_precompile_headers(game PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/game.h)

target_sources(
	game PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/src/local.c
	${CMAKE_CURRENT_LIST_DIR}/src/render.c
	${CMAKE_CURRENT_LIST_DIR}/src/tilemap_patched.c
	${CMAKE_CURRENT_LIST_DIR}/src/util.c
	${CMAKE_CURRENT_LIST_DIR}/src/update.c

	${CMAKE_CURRENT_LIST_DIR}/include/game.h)

target_include_directories(game PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
