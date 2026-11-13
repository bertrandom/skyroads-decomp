/* Hand written implementations of the decompiled program's runtime, BIOS,
 * DOS, hardware and rasteriser routines.
 *
 * The Ghidra decompilation frequently got the number/order of arguments
 * wrong (custom 16-bit calling conventions, register arguments, self
 * modifying code).  Declarations therefore use old-style empty parameter
 * lists: callers may pass any arguments and the callee picks out what it
 * needs. */
#ifndef SKYROADS_RUNTIME_H
#define SKYROADS_RUNTIME_H

#include "compat.h"

/* video / renderer */
void     FUN_1000_0000();
void     FUN_1000_0ed0();
uint16_t FUN_1000_2cce();
void     FUN_1000_2d1f();
void     FUN_1000_34ae();
void     FUN_1000_39d4();
void     FUN_1000_3a22();
void     FUN_1000_3a3f();
void     FUN_1000_3a96();
void     FUN_1000_3b9d();
void     FUN_1000_3c03();
void     FUN_1000_3c52();
void     FUN_1000_3c9a();
void     FUN_1000_3cb1();
void     FUN_1000_3d18();
void     FUN_1000_3d9e();
void     FUN_1000_3e0f();
uint32_t FUN_1000_3e4c();
void     FUN_1000_3e8a();

/* input / timers */
uint8_t  FUN_1000_0672();
void     FUN_1000_068b();
void     FUN_1000_06a4();
int16_t  FUN_1000_06b9();
uint8_t  FUN_1000_6151();
uint32_t FUN_1000_6168();
void     FUN_1000_61e4();
uint16_t FUN_1000_5fcc();
uint16_t FUN_1000_5feb();

/* sound */
uint8_t  FUN_1000_5892();
void     FUN_1000_5919();
void     FUN_1000_59cf();
uint16_t FUN_1000_5a98();
uint32_t FUN_1000_5b39();

/* DOS / BIOS */
void     FUN_1000_00bb();
void     FUN_1000_03c2();
uint16_t FUN_1000_5bdb();
uint16_t FUN_1000_5bf8();
uint16_t FUN_1000_5c36();
void     FUN_1000_5c59();
uint16_t FUN_1000_5c6a();
uint16_t FUN_1000_5c77();
void     FUN_1000_5c82();
void     FUN_1000_5c96();
int16_t  FUN_1000_5ca6();
void     FUN_1000_5f7d();
int16_t  FUN_1000_60ab();
void     FUN_1000_609f();
void     FUN_1000_60e9();
int32_t  FUN_1000_5e5a();
void     FUN_1000_6001();
void     FUN_1000_601d();
uint16_t FUN_1000_6027();
uint16_t FUN_1000_603b();
void     FUN_1000_6053();
void     FUN_1000_4331();
void     FUN_1000_4485();
void     FUN_1000_4b43();

/* buffered reader / LZS */
void     FUN_1000_630f();
void     FUN_1000_6326();
void     FUN_1000_633d();
void     FUN_1000_6350();
void     FUN_1000_6364();
void     FUN_1000_63a3();
void     FUN_1000_63bf();
void     FUN_1000_63d3();
void     FUN_1000_63f0();
void     FUN_1000_6420();
void     FUN_1000_644a();
uint8_t  FUN_1000_6490();
void     FUN_1000_3f91();
void     FUN_1000_3fe2();
void     FUN_1000_4084();
uint16_t FUN_1000_5614();
void     FUN_1000_57c4();
void     FUN_1000_6499();
int16_t  FUN_1000_64ab();
void     FUN_1000_64ff();
uint16_t FUN_1000_6576();
void     FUN_1000_6595();
void     FUN_1000_65e0();
void     FUN_1000_661f();
void     FUN_1000_6645();
void     FUN_1000_6679();
uint32_t FUN_1000_669c();
void     FUN_1000_66e6();

/* C runtime / formatting */
void     FUN_1000_5cd1();
void     FUN_1000_5ce3();
void     FUN_1000_5d07();
uintptr_t FUN_1000_5d1b();
void     FUN_1000_5d33();
int32_t  FUN_1000_5d4c();
uint16_t FUN_1000_5d80();
uint32_t FUN_1000_5d8c();
uint32_t FUN_1000_5dee();
void     FUN_1000_5ef6();
void     FUN_1000_5f0c();
void     FUN_1000_5f52();
void     FUN_1000_5fb5();
void     FUN_1000_5fd4();

#endif
