# Test repo for wasm

## Prerequisites

- Python: 3.10
- [Poetry](https://python-poetry.org/): 1.8.3
- CMake: 3.29.2
- [emsdk](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended): 3.1.56

## Setup

- Install poetry

  ```sh
  pip install poetry
  ```

- Install dependencies

  ```sh
  poetry install
  ```

## Build

### Build Options

- Dynamic linking: `DYN_LINK`, default is `OFF`
- Debug build: `BUILD_DEBUG`, default is `OFF`
- Split module: `SPLIT_MODULE`, default is `OFF`
- Enable threads: `ENABLE_THREADS`, default is `OFF`

### Build steps

- Build project using below command

  ```sh
  mkdir build
  cd build
  emcmake cmake .. -DDYN_LINK=<ON|OFF> -DBUILD_DEBUG=<ON|OFF> -DSPLIT_MODULE=<ON|OFF> -DENABLE_THREADS=<ON|OFF>
  cmake --build .
  cd ..
  ```

- Run test server

  ```sh
  poetry run server
  ```

- If `SPLIT_MODULE` was `ON`, do below steps:

  - Open browser and collect profile
  - Go to `http://localhost:8000/test.html`
  - Select `Profile run` as run type
  - Click on `Collect profile`. A file named `profile.data` will be downloaded.
  - Do actual split
  - Copy `profile.data` to build directory
  - Run below command to do splitting

    ```sh
    wasm-split --symbolmap --placeholdermap -all --split
    --export-prefix=%test.wasm.orig test.wasm.orig
    --profile=profile.data -o1 test.wasm -o2 test.deferred.wasm -v
    ```

    - Conditional arguments for wasm-split:
      - `-g` if `BUILD_DEBUG` was `ON`
      - `--initial-table=650` if `DYN_LINK` was `ON`
