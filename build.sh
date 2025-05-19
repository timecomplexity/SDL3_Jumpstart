#!/bin/bash

############################################################
# Build variables -- change these to suit your build env   #
############################################################
SDL_INSTALL_PATH="E:/SDL3/install"
GENERATOR="Visual Studio 17 2022"

############################################################
# Usage                                                    #
############################################################
Usage()
{
   # Display Help
   echo "Build this SDL project."
   echo
   echo "Syntax: build.sh [-h|r|s|o|v]"
   echo "options:"
   echo "h     Print this help message."
   echo "r     Build in release configuration. Debug is default if this is not specified."
   echo "s     Compile shaders."
   echo "o     Build with OpenGL."
   echo "v     Build with Vulkan."
   echo
}

############################################################
# Main program                                             #
############################################################
mkdir -p build && cd build

BUILD_CONFIGURATION="Debug"
GRAPHICS_API="SDLPG_OPENGL"

while getopts "hrsov" option; do
   case $option in
      h) # display Help
         Usage
         exit;;
      r) # release configuration
         BUILD_CONFIGURATION="Release";;
      s) # compile shaders
         SHADER_CONFIG="-DCOMPILE_SHADERS=1";;
      o) # build for OpenGL
         GRAPHICS_API="OPENGL";;
      v) # build for vulkan
         GRAPHICS_API="VULKAN";;
     \?) # Invalid option
         echo "Error: Invalid option \"$OPTARG\""
         exit;;
   esac
done

cmake ../ -G "$GENERATOR" -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION -DGRAPHICS_API=$GRAPHICS_API -DCMAKE_PREFIX_PATH=$SDL_INSTALL_PATH ${SHADER_CONFIG}
cmake --build . --config $BUILD_CONFIGURATION
