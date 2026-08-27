#!/bin/bash

set -e

BUILD_DIR=".build"
COMPILE_COMMANDS="compile_commands.json"

NDK_HOME="/opt/android-ndk-aide"
TOOLCHAIN="${NDK_HOME}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-arm64"
SYSROOT="${NDK_HOME}/platforms/android-21/arch-arm"
SYSROOT_INC="${NDK_HOME}/sysroot/usr/include"
GNUSTL_INC="${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/include"
GNUSTL_INC_ABI="${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include"
GNUSTL_LIB="${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a"
CC="${TOOLCHAIN}/bin/arm-linux-androideabi-gcc"
CXX="${TOOLCHAIN}/bin/arm-linux-androideabi-g++"

# Public CMake parameters
CMAKE_COMMON_ARGS=(
	# CMake cross-compilation parameters targeting Android.
	# We set CMAKE_SYSTEM_NAME to "Debian" as a workaround:
	#   - "Android" causes CMake to ignore the provided toolchain and search for
	#     incompatible defaults, even when toolchain arguments are explicitly passed.
	#   - "Generic" only permits static library builds, not shared objects (.so).
	# Although the system is named "Debian", the generated .so files are still
	# loadable on Android (tested for armeabi-v7a). All other settings enforce
	# proper cross-compilation with the given sysroot and GNU STL paths.
	-DCMAKE_SYSTEM_NAME=Debian
	-DCMAKE_C_COMPILER="$CC"
	-DCMAKE_CXX_COMPILER="$CXX"
	-DCMAKE_SYSROOT="$SYSROOT"
	-DSYSROOT_INC="$SYSROOT_INC"
	-DGNUSTL_INC="$GNUSTL_INC"
	-DGNUSTL_INC_ABI="$GNUSTL_INC_ABI"
	-DGNUSTL_LIB="$GNUSTL_LIB"
	-DCMAKE_CROSSCOMPILING=TRUE
	-DCMAKE_BUILD_TYPE=Release
	-DCMAKE_FIND_ROOT_PATH="$SYSROOT"
	-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER
	-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY
	-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY
)

case "$1" in
	--init)
		rm -rf "$BUILD_DIR"
		mkdir -p "$BUILD_DIR"
		cd "$BUILD_DIR"
		
		CC="$CC" \
		CXX="$CXX" \
		cmake .. \
			"${CMAKE_COMMON_ARGS[@]}" \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
		
		echo -e "\033[0;32;1mCMake initialization complete (Release mode)\033[0m"
		echo -e "\033[0;32;1mCompiler\033[0m: \033[0;36;1m$CC\033[0m"
		;;
		
	--b)
		if [ ! -f "$BUILD_DIR/Makefile" ]; then
			echo -e "\033[0;31;1mError\033[0m: Please run $0 --init first."
			exit 1
		fi
		cd "$BUILD_DIR"
		make -j"$(nproc)" lpteam
		echo ""
		echo -e "\033[0;32;1mBuild complete.\033[0m"
		if [ -f "../out/liblpteam.so" ]; then
			ls -lh "../out/liblpteam.so"
			file "../out/liblpteam.so"
		else
			echo -e "\033[0;31;1mError\033[0m: out/liblpteam.so not generated."
			exit 1
		fi
		;;
		
	--command)
	echo "Generating and linking $COMPILE_COMMANDS..."
	cd "$BUILD_DIR"
	CC="$CC" CXX="$CXX" cmake .. \
		"${CMAKE_COMMON_ARGS[@]}" \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cd - > /dev/null
	ln -sf "$BUILD_DIR/$COMPILE_COMMANDS" "$COMPILE_COMMANDS"
	echo -e "\033[0;32;1mGenerated and linked $COMPILE_COMMANDS and updated GLOB_RECURSE.\033[0m"
	;;
		
	--clean)
		rm -rf "$BUILD_DIR" out
		rm -rf "$COMPILE_COMMANDS"
		echo -e "\033[0;32;1mCleaned up.\033[0m"
		;;
		
	--help)
		echo "Usage: ./build.sh [options]"
		echo "  --init      Initialize CMake (clean rebuild)"
		echo "  --b         Build liblpteam.so"
		echo "  --command   Generate and symlink compile_commands.json (auto-generated if missing)"
		echo "  --clean     Clean build outputs"
		;;
		
	*)
		echo -e "\033[0;31;1mUnknown option. Please use --help for help.\033[0m"
		exit 1
		;;
esac