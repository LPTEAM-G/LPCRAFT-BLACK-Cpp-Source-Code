cmake_minimum_required(VERSION 3.15)
project(lpteam LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(NDK_HOME "/opt/android-ndk-aide")
set(GNUSTL_INC "${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/include")
set(GNUSTL_INC_ABI "${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include")
set(GNUSTL_LIB "${NDK_HOME}/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a")
set(ANDROIDEABI_INC "${NDK_HOME}/sysroot/usr/include/arm-linux-androideabi/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${CMAKE_SYSROOT} -isystem ${SYSROOT_INC} -isystem ${GNUSTL_INC} -isystem ${GNUSTL_INC_ABI} -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${CMAKE_SYSROOT} -isystem ${SYSROOT_INC} -isystem ${GNUSTL_INC} -isystem ${GNUSTL_INC_ABI} -march=armv7-a -mfpu=vfpv3-d16 -mfloat-abi=softfp")

#[[static library - MShook]]
file(GLOB_RECURSE MSHOOK_SOURCES
	"lib/Substrate/*.c"
	"lib/Substrate/*.cpp"
	"lib/Substrate/*.cc"
)
add_library(
	mshook STATIC
	${MSHOOK_SOURCES}
)

target_include_directories(
	mshook PUBLIC
	"lib"
	${ANDROIDEABI_INC}
)

#[[The shared library we need to generate]]
file(GLOB_RECURSE LPTEAM_SOURCES
	"src/*.c"
	"src/*.cpp"
	"src/*.cc"
)
add_library(
	lpteam SHARED
	${LPTEAM_SOURCES}
)

target_include_directories(
	lpteam PRIVATE
	"lib"
	"src"
	${ANDROIDEABI_INC}
)

set_target_properties(
	lpteam PROPERTIES
	POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(
	lpteam PRIVATE
	EGL
	log
	gnustl_shared
	mshook
)

target_link_directories(
	lpteam PRIVATE
	${GNUSTL_LIB}
)

target_link_options(lpteam PRIVATE
	--sysroot=${CMAKE_SYSROOT}
	-march=armv7-a
)

set_target_properties(lpteam PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
	OUTPUT_NAME "lpteam"
)

message(STATUS "Output: liblpteam.so will be in ${CMAKE_SOURCE_DIR}/out")
