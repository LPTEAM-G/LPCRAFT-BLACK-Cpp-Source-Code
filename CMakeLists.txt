cmake_minimum_required(VERSION 3.15)
project(lpteam LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(NDK_HOME "/opt/android-ndk-aide")
set(GNUSTL_INC "${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/include")
set(GNUSTL_INC_ABI "${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include")
set(GNUSTL_LIB "${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a")

if(NOT CMAKE_SYSROOT)
    set(CMAKE_SYSROOT "${NDK_HOME}/platforms/android-21/arch-arm")
endif()
if(NOT SYSROOT_INC)
    set(SYSROOT_INC "${NDK_HOME}/sysroot/usr/include")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${CMAKE_SYSROOT} -isystem ${SYSROOT_INC} -isystem ${GNUSTL_INC} -isystem ${GNUSTL_INC_ABI} -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${CMAKE_SYSROOT} -isystem ${SYSROOT_INC} -isystem ${GNUSTL_INC} -isystem ${GNUSTL_INC_ABI} -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp")

file(GLOB_RECURSE LPTEAM_SOURCES
    # Hook逻辑主体
    "src/*.c"
    "src/*.cpp"
    "src/*.cc"
    # MSHook
    "lib/Substrate/*.c"
    "lib/Substrate/*.cpp"
    "lib/Substrate/*.cc"
    # XHook
    "lib/xHook/*.c"
    "lib/xHook/*.cpp"
    "lib/xHook/*.cc"
)
add_library(lpteam SHARED ${LPTEAM_SOURCES})
target_include_directories(lpteam PRIVATE "lib" "src")
set_target_properties(lpteam PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(lpteam
    log
    gnustl_shared
)

target_link_directories(lpteam PRIVATE ${GNUSTL_LIB})

target_link_options(lpteam PRIVATE
    --sysroot=${CMAKE_SYSROOT}
    -march=armv7-a
)

set_target_properties(lpteam PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
    OUTPUT_NAME "lpteam"          # 生成 liblpteam.so
)

message(STATUS "Output: liblpteam.so will be in ${CMAKE_SOURCE_DIR}/out")