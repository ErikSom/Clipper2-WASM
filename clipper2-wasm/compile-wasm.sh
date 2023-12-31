#!/usr/bin/env bash

# Set default build type to 'dev' if not specified
BUILD_TYPE=${1:-dev}

# Create necessary directories
mkdir -p clipper2-wasm/dist
mkdir -p clipper2-wasm/dist/es
mkdir -p clipper2-wasm/dist/umd

# Common flags
COMMON_FLAGS="-Iclipper2/CPP/Clipper2Lib/include -DUSINGZ --bind -s MODULARIZE=1 -s WASM_BIGINT -s ALLOW_MEMORY_GROWTH=1 -s EXIT_RUNTIME=0"

# Development build flags
DEV_FLAGS="-g3 -s ASSERTIONS=2 --source-map-base http://localhost:11009/ -s DISABLE_EXCEPTION_CATCHING=0 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 -O0"

# Production build flags
PROD_FLAGS="-O3 -s DISABLE_EXCEPTION_CATCHING=1"

# Select flags based on build type
if [ "$BUILD_TYPE" = "dev" ]; then
    FLAGS="$COMMON_FLAGS $DEV_FLAGS"
    echo "Building Development Version"
else
    FLAGS="$COMMON_FLAGS $PROD_FLAGS"
    echo "Building Production Version"
fi

# Web

# build ES6
echo "Building ES6"
em++ $FLAGS -s EXPORT_ES6=1 -s NO_FILESYSTEM=1 -s ENVIRONMENT='web' -s clipper2-wasm/clipper.bindings.cpp clipper2/CPP/build/libClipper2Z.a -o clipper2-wasm/dist/es/clipper2z.js -s EXPORT_NAME="Clipper2Z" --post-js clipper2-wasm/glue-stub-z.js

# build Tools ES6
em++ $FLAGS -Iclipper2/CPP/Utils -s EXPORT_ES6=1 -s ENVIRONMENT='web' -s clipper2-wasm/clipper-tools.bindings.cpp clipper2/CPP/build/libClipper2Zutils.a clipper2/CPP/build/libClipper2Z.a -o clipper2-wasm/dist/es/clipper2z-utils.js -s EXPORT_NAME="Clipper2ZUtils" -s EXPORTED_FUNCTIONS=[FS] --post-js clipper2-wasm/glue-stub-tools-z.js

# build UMD
echo "Building UMD"
em++ $FLAGS -s NO_FILESYSTEM=1 clipper2-wasm/clipper.bindings.cpp clipper2/CPP/build/libClipper2Z.a -o clipper2-wasm/dist/umd/clipper2z.js -s ENVIRONMENT='web' -s EXPORT_NAME="Clipper2ZFactory" --post-js clipper2-wasm/glue-stub-z.js

# build Tools UMD
em++ $FLAGS -Iclipper2/CPP/Utils clipper2-wasm/clipper-tools.bindings.cpp clipper2/CPP/build/libClipper2Zutils.a clipper2/CPP/build/libClipper2Z.a -o clipper2-wasm/dist/umd/clipper2z-utils.js -s ENVIRONMENT='web' -s EXPORT_NAME="Clipper2ZUtilsFactory" -s EXPORTED_FUNCTIONS=[FS] --post-js clipper2-wasm/glue-stub-tools-z.js
