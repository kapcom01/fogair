#!/bin/bash

mkdir -p build/webassembly
docker run -v .:/src emscripten/emsdk emcc -o build/webassembly/index.html source/game.c source/map.c -Os -Wall raylib-5.5_webassembly/lib/libraylib.a -I. -Iassets -Iraylib-5.5_webassembly/include -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 -s EXPORTED_RUNTIME_METHODS=['HEAPF32','requestFullscreen'] --shell-file minshell.html -DPLATFORM_WEB
