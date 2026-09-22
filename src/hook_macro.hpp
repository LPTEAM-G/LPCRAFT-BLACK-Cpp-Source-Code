//Copyright (c) 2026 LPTEAM
#pragma once

#include <Substrate/SubstrateHook.h>

#define MSHook(target, replace, orig) \
MSHookFunction((void*)(target), (void*)(replace), (void**)(&(orig)))
