# Clipper2 WASM Development Guide

## Introduction
This guide provides step-by-step instructions for setting up and building the Clipper2 WebAssembly (WASM) module.

## Prerequisites
Before you begin, ensure you have the following prerequisites installed on your system:
- Emscripten: Follow the installation steps detailed [here](https://emscripten.org/docs/getting_started/downloads.html).
  - **Important**: Remember to install any dependencies and source the environment variables as described in the guide.

## Building Clipper2 WASM

### Step 1: Prepare the Environment
Change into the C++ directory:
```bash
cd clipper2/CPP
```

### Step 2: Create a Build Directory
Set up a build directory for out-of-source builds:
```bash
mkdir build
cd build
```

### Step 3: Generate Build Files
Use `emcmake` with `cmake` to generate the necessary build files:
```bash
emcmake cmake ../ \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_CXX_FLAGS_RELEASE="-O3" \
-DCLIPPER2_HI_PRECISION=OFF
```

### Step 4: Build the Library
Compile the library files using `emmake`:
```bash
emmake make
```
This step will create `libClipper2.a` and `libClipper2Z.a` library files.

### Step 5: Compile WebAssembly Module
Return to the root directory and run the WebAssembly compilation script:
```bash
cd ..
sh clipper2-wasm/compile-wasm.sh prod
```

### Completion
After completing these steps, you will find the WASM builds in the `clipper2-wasm/dist` directory.

### Generating typescript files
Append `--embind-emit-tsd ../clipper2z.d.ts` to the ES6 export, manually at the Factory export and the glue-stub functions.
