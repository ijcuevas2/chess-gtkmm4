#!/bin/bash
# use a clean Homebrew environment (optional)
LIBPREFIX="/opt/homebrew"
export PATH="$LIBPREFIX/bin:/usr/bin:/bin:/usr/sbin:/sbin"

# keg-only libraries
export PKG_CONFIG_PATH="$LIBPREFIX/opt/icu4c/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$LIBPREFIX/opt/libsoup@2/lib/pkgconfig"

# prevent picking up libxslt and libxml2 from the (wrong) SDK
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$LIBPREFIX/opt/libxslt/lib/pkgconfig"
export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$LIBPREFIX/opt/libxml2/lib/pkgconfig"

# where to install
PREFIX="$PWD/install-prefix"

# Get the SDK path
SDK_PATH=$(xcrun --show-sdk-path)

mkdir -p build
cd build

# -G Ninja \
# ninja
# ninja install

cmake -G Ninja \
    -DCMAKE_OSX_SYSROOT="$SDK_PATH" \
    -DCMAKE_SHARED_LINKER_FLAGS="-L$LIBPREFIX/lib" \
    -DCMAKE_EXE_LINKER_FLAGS="-L$LIBPREFIX/lib" \
    -DCMAKE_INSTALL_PREFIX=$PREFIX \
    -DCMAKE_C_COMPILER_LAUNCHER=ccache \
    -DCMAKE_CXX_COMPILER_LAUNCHER=ccache \
    -DWITH_DBUS=OFF \
    ..

ninja && ./run_tests && ./chess
