#ifndef _DEBUG_H_
#define _DEBUG_H_
#ifdef _DEBUG

#ifndef _WIN32
#define OutputDebugString(str)
#endif

#include <assert.h>
#define ASSERT(x) assert(x)

void SetupOpenGLDebugCallback();

#endif
#endif

