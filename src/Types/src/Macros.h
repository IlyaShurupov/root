#pragma once

#include <limits.h>
#include <float.h>
#include "Memory/Mem.h"

// #if _WIN32 || _WIN64
// #if _WIN64
#define ENVIRONMENT64
// #else
// #define ENVIRONMENT32
// #endif
// #endif

#define NAME(v) #v
#define ABS(val) val > 0 ? val : -val
#define CLAMP(val, min, max) if (val > max) { val = max; } else if (val < min) {val = min;}
#define OFFSET(first, offset) (*((&first) + offset))
#define INRANGE(val, bd1, bd2) ((val) >= (bd1) && (val) <= (bd2))
#define DOIF(action, cond) if ((cond)) { action; }
#define IF(cond, action) if ((cond)) { action; }
#define SWAP(val1, val2, type) type tmp; tmp = val1; val1 = val2; val2 = tmp

// Types
typedef char					int1;
typedef unsigned char			uint1;
typedef short					int2;
typedef unsigned short			uint2;
typedef int						int4;
typedef unsigned int			uint4;
#ifdef ENVIRONMENT64
typedef long					int8;
typedef unsigned long			uint8;
typedef int8                    aligned;
#define ALIGNED_MAX LONG_MAX
#define ALIGNED_MIN LONG_MIN
#else
typedef int4                    aligned;
typedef long long				int8;
typedef unsigned long long		uint8;
#define ALIGNED_MAX LLONG_MAX
#define ALIGNED_MIN LLONG_MIN
#endif

// Coustom types
typedef int SCR_INT;
#define SCR_UINT_MAX USHRT_MAX

// Consts
#define MATH_EPSILON 0.0000001
#define MATH_Pi float(3.1415926535897932384626433832795)
#define MATH_SQRT2 1.4142135623730950488016887242
#define MATH_E 2.7182818284590452353602874714

int FltToInt(float f);
float IntToFlt(aligned i);
uint8 next_pow_of_2(uint8 v);
int hash_string(const char* bytes);