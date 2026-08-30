//Copyright (c) 2026 LPTEAM
#ifndef LOG_LIB_HPP
#define LOG_LIB_HPP

#include <android/log.h>

#define LPCRAFT_LOG_TAG "LPCRAFT_LOG"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LPCRAFT_LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LPCRAFT_LOG_TAG, __VA_ARGS__)

#endif
