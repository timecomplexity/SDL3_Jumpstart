mkdir -p build && cd build

SDL_INSTALL_PATH="E:/SDL/install"
GENERATOR="Visual Studio 17 2022"

if [[ "$1" == "r" || "$1" == "release" ]]; then
    BUILD_CONFIGURATION="Release"
else
    BUILD_CONFIGURATION="Debug"
fi


cmake ../ -G "$GENERATOR" -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION -DCMAKE_PREFIX_PATH=$SDL_INSTALL_PATH
cmake --build . --config $BUILD_CONFIGURATION
