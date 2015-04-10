#pragma once

typedef int RESULT;
typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
#ifndef _UINT8
typedef unsigned char uint8;
#define _UINT8
#endif

#ifndef _UINT16
typedef unsigned short uint16;
#define _UINT16
#endif

#ifndef ___UINT32
typedef unsigned int uint32;
#define ___UINT32
#endif

typedef unsigned long long uint64;

typedef enum _Enum_Result_ {
    RESULT_OK = 0x0,
    RESULT_FALSE = 0x1,
    RESULT_FAIL = 0x80000000,
    RESULT_CANCEL
} EnumResult;

#define RESULT_FAIL_INTERFACE_BASE 0x80010000

#define RESULT_TO_STRING(r) \
    ((r) == RESULT_OK)                                  ? "no error"                            : \
    ((r) == RESULT_FALSE)                               ? "unexpected result"                   : \
    ((r) == RESULT_FAIL)                                ? "general failure"                     : \
    ((r) == RESULT_CANCEL)                              ? "operation cancelled"                 : \
    "Unknown Result"

#include <stdio.h>
#include <string.h>

namespace benchmark
{
    inline bool Succeeded(RESULT result){return result>= 0;}
    inline bool Failed(RESULT result){return result< 0;}
    inline void ThrowFailed(RESULT result){if (Failed(result)) throw( result);}
}
