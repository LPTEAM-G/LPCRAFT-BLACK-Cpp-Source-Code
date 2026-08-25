#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <Substrate/SubstrateHook.h>
#include <xHook/xhook.h>

#define MSHook(target, replace, orig) \
MSHookFunction((void*)(target), (void*)(replace), (void**)&(orig))

#define LIBNAME_REGEX "libminecraftpe.so"

#define XHook(replace, orig, symbol) \
xhook_register(LIBNAME_REGEX, symbol, (void*)(replace), (void**)&(orig))

#endif
