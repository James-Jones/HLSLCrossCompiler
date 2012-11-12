#ifndef _DEBUG_H_
#define _DEBUG_H_
#ifdef _DEBUG

#ifndef _WIN32
#define OutputDebugString(str)
#else
#include <windows.h>
#endif

#include <assert.h>
#define ASSERT(x) assert(x)

void SetupOpenGLDebugCallback();

#endif
#endif

