# Build Options

    - Dynamic linking: `DYN_LINK`
    - Debug build: `BUILD_DEBUG`

## Build steps

    - Build project using below command
    ```sh
        mkdir build
        cd build
        emcmake cmake .. -DDYN_LINK=<ON|OFF> -DBUILD_DEBUG=<ON|OFF>
        cmake --build .
        cd ..
    ```
    - Run http server
    ```sh
        python -m http.server
    ```
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
        - In `wasm-split` args, add `-g`  if `BUILD_DEBUG` was `ON` and
        `--initial-table=650` if `DYN_LINK` was `ON` while building the project

