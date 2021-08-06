#pragma once

#define MEM_DEBUG

#include <cstddef>

#ifdef MEM_DEBUG

void* operator new (size_t size, const char* file, int line);
void operator delete (void* p);
void operator delete (void* p, const char* file, int line);
#define new new (__FILE__, __LINE__)

#endif

//bool init_mem_debug();
