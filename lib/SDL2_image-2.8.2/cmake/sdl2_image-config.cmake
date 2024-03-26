# SDL2_image CMake configuration file:
# This file is meant to be placed in a cmake subfolder of SDL2_image-devel-2.x.y-mingw

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(sdl2_image_config_path "${CMAKE_CURRENT_LIST_DIR}/../i686-w64-mingw32/lib/cmake/SDL2_image/sdl2_image-config.cmake")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(sdl2_image_config_path "${CMAKE_CURRENT_LIST_DIR}/../x86_64-w64-mingw32/lib/cmake/SDL2_image/sdl2_image-config.cmake")
else("${CMAKE_SIZEOF_VOID_P}" STREQUAL "")
    set(SDL2_image_FOUND FALSE)
    return()
endif()

if(NOT EXISTS "${sdl2_image_config_path}")
    message(WARNING "${sdl2_image_config_path} does not exist: MinGW development package is corrupted")
    set(SDL2_image_FOUND FALSE)
    return()
endif()

include("${sdl2_image_config_path}")