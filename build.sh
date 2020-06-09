cd externals/skia
python2 tools/git-sync-deps
bin/gn gen out/cmake --ide=json --json-ide-script=../../gn/gn_to_cmake.py --args='
      skia_use_egl = true
      skia_enable_gpu = false
      skia_use_freetype = false
      skia_use_zlib = false
      skia_use_angle = false
      skia_use_expat = false
      skia_use_icu = false
      skia_use_libpng = false
      skia_use_libwebp = false
      skia_use_lua = false
      skia_use_opencl = false
      skia_use_piex = false
      skia_use_zlib = false
      skia_use_metal = false
      skia_enable_flutter_defines = false
      skia_enable_fontmgr_empty = false
      skia_enable_pdf = false
      skia_enable_vulkan_debug_layers = false
      skia_enable_tools = false
      skia_use_icu = false
      skia_use_sfntly = false
      is_debug = false
      is_official_build = true
      is_component_build = true
      '
cd ../../build
cmake ../
cmake --build .