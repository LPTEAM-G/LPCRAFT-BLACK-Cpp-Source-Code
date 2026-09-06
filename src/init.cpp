//Copyright (c) 2026 LPTEAM
#include "minecraft_app.hpp"
#include "gles.hpp"
#include "log_lib.hpp"
#include "mod_install.hpp"
#include <cstdio>
#include <jni.h>
#include <cstring>
#include <unistd.h>


extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved)
{
	LOGI("Shared Library liblpteam.so Loaded");
	minecraft_app::init();
	gles::install();
	mod_install();
	
	return JNI_VERSION_1_6;
}
