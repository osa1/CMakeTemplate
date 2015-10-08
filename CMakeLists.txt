cmake_minimum_required(VERSION 2.8)
project(Main CXX)

include(ExternalProject)

################################################################################
# SDL2 settings

set(sdl_DIR "SDL2")
set(sdl_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${sdl_DIR}")
set(sdl_INSTALL_DIR "${sdl_PREFIX}/build")
set(sdl_CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${sdl_INSTALL_DIR}
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS})

ExternalProject_Add(sdl
    PREFIX ${sdl_PREFIX}
    URL https://www.libsdl.org/release/SDL2-2.0.3.tar.gz
    CMAKE_ARGS ${sdl_CMAKE_ARGS}
    )

include_directories("${sdl_INSTALL_DIR}/include")
# This line is needed for SDL2_ttf:
include_directories("${sdl_INSTALL_DIR}/include/SDL2")
link_directories("${sdl_INSTALL_DIR}/lib")

################################################################################
# SDL2_ttf settings

set(sdl_ttf_DIR "SDL2_ttf")
set(sdl_ttf_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${sdl_ttf_DIR}")
set(sdl_ttf_INSTALL_DIR "${sdl_ttf_PREFIX}/build")

ExternalProject_Add(sdl_ttf
    DEPENDS sdl
    PREFIX ${sdl_ttf_PREFIX}
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
    CONFIGURE_COMMAND
        ${sdl_ttf_PREFIX}/src/sdl_ttf/configure
            --prefix=${sdl_ttf_INSTALL_DIR}
            --with-sdl-prefix=${sdl_INSTALL_DIR}
    BUILD_COMMAND ${MAKE}
    )

include_directories("${sdl_ttf_INSTALL_DIR}/include")
link_directories("${sdl_ttf_INSTALL_DIR}/lib64")
link_directories("${sdl_ttf_INSTALL_DIR}/lib")

################################################################################
# SDL2_image settings

set(sdl_image_DIR "SDL2_image")
set(sdl_image_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${sdl_image_DIR}")
set(sdl_image_INSTALL_DIR "${sdl_image_PREFIX}/build")

ExternalProject_Add(sdl_image
    DEPENDS sdl
    PREFIX ${sdl_image_PREFIX}
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.0.tar.gz
    CONFIGURE_COMMAND
        ${sdl_image_PREFIX}/src/sdl_image/configure
            --prefix=${sdl_image_INSTALL_DIR}
            --with-sdl-prefix=${sdl_INSTALL_DIR}
    BUILD_COMMAND ${MAKE}
    )

include_directories("${sdl_image_INSTALL_DIR}/include")
link_directories("${sdl_image_INSTALL_DIR}/lib64")
link_directories("${sdl_image_INSTALL_DIR}/lib")

################################################################################
# GLEW settings

set(glew_DIR "GLEW")
set(glew_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/${glew_DIR}")
set(glew_INSTALL_DIR "${glew_PREFIX}/build")

ExternalProject_Add(glew
    PREFIX ${glew_PREFIX}
    URL https://github.com/nigels-com/glew/archive/glew-1.13.0.tar.gz
    CONFIGURE_COMMAND cp -r ${glew_PREFIX}/src/glew/. . && make extensions
    BUILD_COMMAND GLEW_PREFIX=${glew_INSTALL_DIR} GLEW_DEST=${glew_INSTALL_DIR} make
    INSTALL_COMMAND GLEW_PREFIX=${glew_INSTALL_DIR} GLEW_DEST=${glew_INSTALL_DIR} make install
    )

include_directories("${glew_INSTALL_DIR}/include")
link_directories("${glew_INSTALL_DIR}/lib64")

################################################################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

add_executable(main main.cpp)

target_link_libraries(main SDL2 SDL2_ttf SDL2_image GLEW)

add_dependencies(main sdl sdl_ttf sdl_image glew)
