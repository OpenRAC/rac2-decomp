/* func_US2_0034DBD8, the USA v2.00 copy of func_0034CE98: the same C. */

extern unsigned long long func_00347EA0(unsigned long long);

typedef int s32;

typedef unsigned char u8;

typedef float f32;

extern void func_00348068(unsigned char *owner, float *records);

extern int func_00348128(unsigned char *);

#ifndef RAC2_T_S_F49AFCBFE
#define RAC2_T_S_F49AFCBFE
#endif

/* Measured partial layouts; original type and game roles are unknown. */
/* func_0034CA68: owner ABI/declaration review retained. */
extern int func_002A9588(int, int, int, int, int);
/* func_00345490 is built from 00345358-init.c. */

/* func_00345F70 is built from 00345358-layout-g8.c. */

/* func_003462A8 is built from 00345358-descriptor-g8.c for small-data access. */

/* func_003463C8 and func_003464D0 are built from 00345358-g8.c for small-data access. */

/* The two menu labels at +0x2E8 and +0x330: shown according to the flags of the highlighted
   grid entry, and placed relative to the owner's position record. */
typedef struct { int x; int y; } MenuLabelOffset;
typedef struct { short a, b, c, id, e; } MenuGridEntry;
extern MenuGridEntry D_00259F58[];
extern MenuLabelOffset ref_003472B8_00;
extern void func_00335E68(void *, int);

/* func_00347468 is built from 00345358-selection-g8.c. */

unsigned long long func_00347EA0(unsigned long long value);

/* func_00347F80 is built from 00345358-wrap.c. */

void func_00348068(u8 *a0,f32 *a1);

/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
s32 func_00348128(u8 *a0);

/* Measured target: byte-identical across all 27 levels. */
/* func_00348138 is built from 00345358-menu.c. */

/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
/* Forwards one shared global pointer plus a fixed byte offset, together with five distinct fixed offsets of the first object, into the same callee five times, reading one distinct word of the second object each call. */
/* stores the count in a field, then loops count times calling one helper on each successive 72-byte slot and passing the result to a second helper. */
/* func_003486A8 is built from 00345358-children.c. */

/* func_003489E8 is built from 00345358-list-g8.c. */

/* func_00349190 is built from 00345358-input-g8.c. */

/* Measured target: byte-identical across all 27 levels. */
/* Zeroes six word fields of an object, reads back the first one as a float, calls a helper twice with that float (then with 1.0f) over five float arguments, sets two more int fields, and calls a second helper with two float arguments. */
/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
/* Store an indexed four-component parameter row and its float weight */
/* Measured target: byte-identical across all 27 levels. */
/* func_00349680 is built with float min/max in 00345358-interpolation.c. */

/* Initialises a record of four 1.0 floats, one zero, one small constant and four zero words, then runs the same four-argument setup four times with two selector flags swept over 0 and 1. */
/* Store four float components in a selected row of a parameter group */
/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
/* Replace the value at offset 0x04 and, when it changes while the bound debug byte is zero, retain the previous value and set the two counters to 180 and 300; original game role is unknown. */
typedef struct { float values[3]; } StageFloatTable;
typedef struct { int values[3]; } StageIntTable;
extern const StageFloatTable D_001AE628, D_001AE638;
extern const StageIntTable D_001AE648, D_001AE658;
/* func_0034A808 is in 0034A808.c. */

/* func_0034AA30 is built from 0034AA30.c. */

/* Stores an argument at +1012; if the word at +1024 is zero it returns, else it clears +1024, sets +12 to 1 and calls one callee four times on this+468/604/740/876 with argument 1. */
extern int func_002A9588(int, int, int, int, int);

extern void func_00335E68(void *, int);
/* Measured target: byte-identical across all 27 levels. */
void func_US2_0034DBD8(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x2dc) = a1; }
