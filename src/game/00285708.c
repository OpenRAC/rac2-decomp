#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

/* lot10: privately byte-gated bodies. */
extern s32 func_00126470(u8 *, s32, s32, s32, s32, s32, s32, s32);

extern s32 func_0011AEA0(s32);

extern s32 func_00126730(u8 *, u8 *);

extern s32 D_001A72E0[] __attribute__((sda));

extern s32 D_001A7340[] __attribute__((sda));

extern void func_002FC3C0(int);

extern void func_00284000_1(void);

extern void func_00284268(int, int, int, int, int, int);

/* Copies a rectangle of the screen picture into the given buffer. */
void func_00285708(s32 left, s32 top, s32 width, s32 height, u8 *destination) {
    u8 image[112];
    func_00126470(image, (D_001A72E0[0]<<8)>>16, (gScreenWidth[0]<<10)>>16,
                0x30,(short)left,(short)top,(short)width,(short)height);
    FlushCache(0);
    func_00126730(image,destination);
}

typedef struct {
    char reserved[0x8C];
    int first, second;
} Limits_285788;
extern Limits_285788 D_001BAC80;

/* Sets two size limits, using the defaults 64 and 16 when a value is zero. */
void func_00285788(int first, int second) {
    int first_limit = 64;
    int second_limit = 16;
    if (first != 0) first_limit = first;
    if (second != 0) second_limit = second;
    gModalState.first = first_limit;
    gModalState.second = second_limit;
}

extern int D_001A8A5C __attribute__((sda));

/* Returns the current menu mode. */
int func_002857B0(void) {
    return D_001A8A5C;
}
