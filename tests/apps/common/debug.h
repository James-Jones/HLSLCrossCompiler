#ifndef _DEBUG_H_
#define _DEBUG_H_
#ifdef _DEBUG

#ifndef _WIN32
#define DebugString(str)
#else
#include <windows.h>
#define DebugString(str) OutputDebugString(str)
#endif

#include <assert.h>
#define ASSERT(x) assert(x)

void SetupOpenGLDebugCallback();

#else
#define ASSERT(X)
#define DebugString(X)
#endif
#endif

