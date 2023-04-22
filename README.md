# SDL2 Jumpstart

Easy starting point for playing around with SDL2 and Vulkan, frankenstein'd from other projects.

## Dependencies

`CMake` is our build tool of choice. Need to install at least version 3.26.

Download and build [SDL2](https://github.com/libsdl-org/SDL) which we will be using as our cross-platform window and input system. I cloned the latest release branch of SDL, changed into the root directory and ran the following (For Visual Studio 2022 on Windows). This will put all of the libraries into one place cleanly.

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

Set up Vulkan using the installation process described [here](https://vulkan-tutorial.com/Development_environment#page_Windows).

No need to install GLFW or GLM as we are using SDL2 and GLM is included as a submodule. We are using SDL2 instead of GLFW.

## Building

For the final step, there is also a provided `build.sh` script which only needs the named variables updated at the top of the script to match your generator and custom SDL2 install path.

```
git clone --recurse-submodules https://github.com/timecomplexity/Learning-Vulkan.git
cd Learning-Vulkan

# Setup a shadow build
mkdir build && cd build

# Run CMake, replacing with appropriate values for your setup
cmake ../ -G <DesiredGenerator> -DCMAKE_BUILD_TYPE=<DesiredBuildConfiguration> -DCMAKE_PREFIX_PATH=<CustomSDLInstallLocation>
cmake --build . --config <DesiredBuildConfiguration>

# Example for Visual Studio 2022 and a custom install location for SDL2 in Release mode
cmake ../ -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="E:/SDL/install"
cmake --build . --config Release
```