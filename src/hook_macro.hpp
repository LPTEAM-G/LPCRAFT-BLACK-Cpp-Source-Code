#ifndef HOOK_MACRO_HPP
#define HOOK_MACRO_HPP

#include <Substrate/SubstrateHook.h>

#define MSHook(target, replace, orig) \
MSHookFunction((void*)(target), (void*)(replace), (void**)(&(orig)))

#endif
