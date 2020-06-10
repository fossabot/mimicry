set(SDL_STATIC OFF)
set(SDL_SHARED ON)
set(SDL_AUDIO OFF)
option(VIDEO_VIVANTE ON)
option(VIDEO_WAYLAND ON)
option(WAYLAND_SHARED ON)
add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_subdirectory(skia/out/cmake EXCLUDE_FROM_ALL)
