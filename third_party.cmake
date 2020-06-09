include(ExternalProject)

ExternalProject_Add(SDL2-project

  GIT_REPOSITORY    https://github.com/SDL-mirror/SDL.git
  GIT_TAG           release-2.0.12

  SOURCE_DIR        ${CMAKE_BINARY_DIR}/third_party/SDL2
  INSTALL_COMMAND   sudo make install -j9
  CMAKE_ARGS        -D                  -D                  -D                  -D
                    -D
                    -D
)
ExternalProject_Get_Property(SDL2-project BINARY_DIR)
ExternalProject_Get_Property(SDL2-project SOURCE_DIR)

file(MAKE_DIRECTORY ${BINARY_DIR})

add_library(SDL2 SHARED IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
  IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}SDL2${CMAKE_SHARED_LIBRARY_SUFFIX}
)

ExternalProject_Add(skia-project

  GIT_REPOSITORY    https://github.com/google/skia.git
  GIT_TAG           origin/chrome/m84

  SOURCE_DIR        third_party/skia/
  PATCH_COMMAND     python tools/git-sync-deps && bin/gn gen out/config && cp ${CMAKE_SOURCE_DIR}/skia.args out/config/args.gn
  UPDATE_COMMAND    ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     /usr/bin/ninja-build -C out/config
  INSTALL_COMMAND   sudo cp libskia.so /usr/local/lib/
)
ExternalProject_Get_Property(skia-project BINARY_DIR)
ExternalProject_Get_Property(skia-project SOURCE_DIR)

file(MAKE_DIRECTORY ${BINARY_DIR})

add_library(skia SHARED IMPORTED GLOBAL)
set_target_properties(skia PROPERTIES
  IMPORTED_LOCATION ${BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}skia${CMAKE_SHARED_LIBRARY_SUFFIX}
  INTERFACE_INCLUDE_DIRECTORIES ${SOURCE_DIR})
