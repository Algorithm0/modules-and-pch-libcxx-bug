# Potential Issue with libc++ and C++ Modules and Precompiled Headers

This repository demonstrates a potential issue when using C++ modules and precompiled headers with LLVM's libc++ standard library implementation.

## CMake Configuration Options

#### `USE_PCH`
- **Type**: `ON`/`OFF`
- **Default**: `OFF`
- **Description**: Enables precompiled headers configuration when set to `ON`.

#### `USE_STD_FORMAT`
- **Type**: `ON`/`OFF`
- **Default**: `OFF`
- **Description**: Enables string output using `std::format` for library standard testing.

## Test Results

| Standard Library Implementation | clang 19.1.7 (Fedora) | clang 21.0.0 (git) |
|---------------------------------|-----------------------|--------------------|
| **libstdc++ 14.2.1 (Fedora)**   | OK                    | OK                 |
| **libc++ 19.1.7 (Fedora)**      | Error                 | Error              |
| **libc++ 21.0.0 (git)**         | Error                 | Error              |

## Build Configurations

### Compiler Settings

**clang 19.1.7 (Fedora 19.1.7-3.fc41)**
```bash
COMPILER_CONFIG="-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_COMPILER_CLANG_SCAN_DEP=clang-scan-deps"
```
**clang 21.0.0 (git)**
```bash
COMPILER_CONFIG="-DCMAKE_C_COMPILER=${LLVM_21}/bin/clang -DCMAKE_CXX_COMPILER=${LLVM_21}/bin/clang++ -DCMAKE_CXX_COMPILER_CLANG_SCAN_DEP=${LLVM_21}/bin/clang-scan-deps"
```

###  Standard Library Settings

**libstdc++ 14.2.1 (Fedora 14.2.1-7.fc41)**
```bash
STDLIB_CONFIG=""
```

**libc++ 19.1.7 (Fedora)**
```bash
STDLIB_CONFIG="-DCMAKE_EXE_LINKER_FLAGS_INIT='-stdlib=libc++' -DCMAKE_CXX_FLAGS='-stdlib++-isystem/usr/include/c++/v1'"
```

**libc++ 21.0.0 (git)**
```bash
STDLIB_CONFIG="-DCMAKE_EXE_LINKER_FLAGS_INIT='-stdlib=libc++' \
               -DCMAKE_CXX_FLAGS='-stdlib++-isystem${LLVM_21}/include/c++/v1 -isystem${LLVM_21}/include/x86_64-unknown-linux-gnu/c++/v1' \
               -DCMAKE_CXX_STANDARD_LIBRARIES='-L${LLVM_21}/lib/x86_64-unknown-linux-gnu -lc++ -lc++abi'"
```

### Building the Project
```bash
mkdir build
eval " cmake ${STDLIB_CONFIG} ${COMPILER_CONFIG} -DUSE_PCH=ON -G Ninja -B build"
ninja -C build -v
```

## Additional Observations
The build succeeds in all configurations when precompiled headers are disabled (`-DUSE_PCH=OFF`).\
Commit for LLVM 21 - [148111fdcf0e807fe74274b18fcf65c4cff45d63](https://github.com/llvm/llvm-project/commit/148111fdcf0e807fe74274b18fcf65c4cff45d63)