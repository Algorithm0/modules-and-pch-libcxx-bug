# Is there a problem with libc++?

This repository contains an example of a problem with using C++ modules
and precompiled headers when using LLVM libc++.

## Available CMake custom flags
#### USE_PCH
Pass this flag with a value of `ON` to enable precompiled headers configuration.
Not used by default.

#### USE_STD_FORMAT
Pass this flag with a value of `ON` to enable string output using `std::format`.
Used for testing the library standard. Not used by default.

## Tests performed

|                                 stdlib                                  | clang version 19.1.7 (Fedora 19.1.7-3.fc41) | clang version 21.0.0git (148111fdcf0e807fe74274b18fcf65c4cff45d63) |
|:-----------------------------------------------------------------------:|:-------------------------------------------:|:------------------------------------------------------------------:|
|                   **libstdc++-14.2.1-7.fc41.x86_64**                    |                     OK                      |                                 OK                                 |
|            **libc++ version 19.1.7 (Fedora 19.1.7-3.fc41)**             |                    Error                    |                               Error                                |
| **libc++ version 21.0.0git (148111fdcf0e807fe74274b18fcf65c4cff45d63)** |                    Error                    |                               Error                                |

## Configurations used
**clang version 19.1.7 (Fedora 19.1.7-3.fc41)**
~~~bash
COMPILER_CONFIG="-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_COMPILER_CLANG_SCAN_DEP=clang-scan-deps"
~~~
**clang version 21.0.0git (148111fdcf0e807fe74274b18fcf65c4cff45d63)**
~~~bash
COMPILER_CONFIG="-DCMAKE_C_COMPILER=${LLVM_21}/bin/clang -DCMAKE_CXX_COMPILER=${LLVM_21}/bin/clang++ -DCMAKE_CXX_COMPILER_CLANG_SCAN_DEP=${LLVM_21}/bin/clang-scan-deps"
~~~
**libstdc++-14.2.1-7.fc41.x86_64**
~~~bash
STDLIB_CONFIG=""
~~~
**libc++ version 19.1.7 (Fedora 19.1.7-3.fc41)**
~~~bash
STDLIB_CONFIG="-DCMAKE_EXE_LINKER_FLAGS_INIT='-stdlib=libc++' -DCMAKE_CXX_FLAGS='-stdlib++-isystem/usr/include/c++/v1'"
~~~
**libc++ version 21.0.0git (148111fdcf0e807fe74274b18fcf65c4cff45d63)**
~~~bash
STDLIB_CONFIG="-DCMAKE_EXE_LINKER_FLAGS_INIT='-stdlib=libc++' \
               -DCMAKE_CXX_FLAGS='-stdlib++-isystem${LLVM_21}/include/c++/v1 -isystem${LLVM_21}/include/x86_64-unknown-linux-gnu/c++/v1' \
               -DCMAKE_CXX_STANDARD_LIBRARIES='-L${LLVM_21}/lib/x86_64-unknown-linux-gnu -lc++ -lc++abi'"
~~~

### Run build
~~~bash
mkdir build
eval " cmake ${STDLIB_CONFIG} ${COMPILER_CONFIG} -DUSE_PCH=ON -G Ninja -B build"
ninja -C build -v
~~~

### Additional information
Interestingly, when disabling the use of precompiled headers, any configuration is followed by a successful build.