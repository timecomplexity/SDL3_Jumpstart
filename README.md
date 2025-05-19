# SDL3 Jumpstart

Easy starting point for playing around with SDL3 and Vulkan, frankenstein'd from other projects.

## Dependencies

`CMake` is our build tool of choice. Need to install at least version 3.26.

Download and build [SDL3](https://github.com/libsdl-org/SDL) which we will be using as our cross-platform window and input system. I cloned the latest release branch of SDL, changed into the root directory and ran the following (For Visual Studio 2022 on Windows). This will put all of the libraries into one place cleanly.

```
# Builds and installs Debug libraries
cmake -S . -B build/debug -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug --target install --config Debug

# Builds and installs Release libraries
cmake -S . -B build/release -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX=./install -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --target install --config Release
```

We are using C++17. The following compilers are verified to work:

- Visual Studio 2019
- Visual Studio 2022
- GCC 8
- GCC 12



## Setup

### Vulkan

If using Vulkan, set up Vulkan using the installation process described [here](https://vulkan-tutorial.com/Development_environment#page_Windows).

### OpenGL

Build GLEW so we can use OpenGL. GLEW will be pulled down in the include/vendor directory. From the vendor directory:

(Note that it's probably best to reference the documentation on the repo for GLEW if these steps don't work.)

If you're on Linux, from the vendor directory:
```
cd glew/build
cmake ./cmake
make -j4
```

On Windows, go into the build directory (`include/vendor/glew/build`) and open up the project in visual studio. This should be the `vc15` project. Open the.sln file and compile each project for both Debug and Release x64. These files will appear under the bin directory in the glew project.

No need to install GLM which is included as a submodule.

## Building

For the final step, there is also a provided `build.sh` script which only needs the named variables updated at the top of the script to match your generator and custom SDL3 install path.

In order to build shaders, when invoking CMake you will need to supply the argument `-DCOMPILE_SHADERS=1`.

```
git clone --recurse-submodules https://github.com/timecomplexity/SDL3_Jumpstart.git
cd SDL3_Jumpstart

# Setup a shadow build
mkdir build && cd build

# Run CMake, replacing with appropriate values for your setup
cmake ../ -G <DesiredGenerator> -DCMAKE_BUILD_TYPE=<DesiredBuildConfiguration> -DCMAKE_PREFIX_PATH=<CustomSDLInstallLocation>
cmake --build . --config <DesiredBuildConfiguration>

# Example for Visual Studio 2022 and a custom install location for SDL3 in Release mode
cmake ../ -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="E:/SDL/install"
cmake --build . --config Release
```