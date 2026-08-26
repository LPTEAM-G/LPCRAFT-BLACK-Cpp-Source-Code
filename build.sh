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

# 公共 CMake 参数（不含生成 compile_commands 的选项）
CMAKE_COMMON_ARGS=(
	# 只能放Debian
	# 如果写Android的话CMake会自作主张找不存在的东西
	# 关键是就算我传递了工具链参数它也不听
	# 如果填Generic, 那就无法生成so文件了, 只能生成静态库文件
	# 所以只能这样子, 但就算写Debian
	# 它生成的v7a的so文件仍然可以被安卓系统加载
	# 这是幸运的
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
        
        echo "CMake 初始化完成 (Release 模式)"
        echo "编译器: $CC"
        ;;
        
    --b)
        if [ ! -f "$BUILD_DIR/Makefile" ]; then
            echo "错误: 请先运行 $0 --init 初始化"
            exit 1
        fi
        cd "$BUILD_DIR"
        make -j"$(nproc)" lpteam
        echo ""
        echo "构建完成"
        if [ -f "../out/liblpteam.so" ]; then
            ls -lh "../out/liblpteam.so"
            file "../out/liblpteam.so"
        else
            echo "错误: out/liblpteam.so 未生成"
            exit 1
        fi
        ;;
        
    --command)
    echo "正在重新配置 CMake 以更新 GLOB..."
    cd "$BUILD_DIR"
    CC="$CC" CXX="$CXX" cmake .. \
        "${CMAKE_COMMON_ARGS[@]}" \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cd - > /dev/null
    ln -sf "$BUILD_DIR/$COMPILE_COMMANDS" "$COMPILE_COMMANDS"
    echo "已链接并更新 $COMPILE_COMMANDS"
    ;;
        
    --clean)
        rm -rf "$BUILD_DIR" out
        echo "已清理"
        ;;
        
    --help)
        echo "用法: ./build.sh [选项]"
        echo "  --init     初始化 CMake（清空重建）"
        echo "  --b        构建 liblpteam.so"
        echo "  --command  生成并链接 compile_commands.json（若不存在则自动生成）"
        echo "  --clean    清理构建输出"
        ;;
        
    *)
        echo "未知选项，请使用 --help 查看帮助"
        exit 1
        ;;
esac