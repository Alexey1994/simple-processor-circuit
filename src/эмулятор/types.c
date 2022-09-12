#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED


typedef unsigned char          Byte;
typedef unsigned char          Bit8;
typedef unsigned short int     Bit16;
typedef unsigned long int      Bit32;
typedef unsigned long long int Bit64;

typedef unsigned char          Number8;
typedef unsigned short int     Number16;
typedef unsigned long int      Number32;
typedef unsigned long long int Number64;
typedef Number64               Number;

typedef char                   Integer_Number8;
typedef short int              Integer_Number16;
typedef long int               Integer_Number32;
typedef long long int          Integer_Number64;
typedef Integer_Number64       Integer_Number;

typedef float                  Rational_Number32;
typedef double                 Rational_Number64;
typedef Rational_Number64      Rational_Number;

typedef Number                 Boolean;


#define stdcall      __attribute__((__stdcall__))
#define cdecl        __attribute__((__cdecl__))
#define import       __attribute__((dllimport)) __attribute__((__stdcall__))
#define import_cdecl __attribute__((dllimport)) __attribute__((__cdecl__))
#define export       __attribute__((dllexport)) __attribute__((__stdcall__))
#define export_cdecl __attribute__((dllexport)) __attribute__((__cdecl__))


#pragma pack(push, 1) //no align for structs


//#include <log.c>
#define print(...) printf(__VA_ARGS__)


#endif//TYPES_INCLUDED