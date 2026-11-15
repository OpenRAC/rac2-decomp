#include "include_asm.h"

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

/* Builds an image transfer from the four rectangle values and sends it to the buffer a4. */
void func_00285708(s32 a0, s32 a1, s32 a2, s32 a3, u8 *a4) {
    u8 image[112];
    func_00126470(image, (D_001A72E0[0]<<8)>>16, (D_001A7340[0]<<10)>>16,
                0x30,(short)a0,(short)a1,(short)a2,(short)a3);
    func_0011AEA0(0);
    func_00126730(image,a4);
}

typedef struct {
    char reserved[0x8C];
    int first, second;
} Limits_285788;
extern Limits_285788 D_001BAC80;

/* Stores two limits, using 64 and 16 when the arguments are zero. */
void func_00285788(int first, int second) {
    int first_limit = 64;
    int second_limit = 16;
    if (first != 0) first_limit = first;
    if (second != 0) second_limit = second;
    D_001BAC80.first = first_limit;
    D_001BAC80.second = second_limit;
}

extern int D_001A8A5C __attribute__((sda));

/* Returns the value of D_001A8A5C. */
int func_002857B0(void) {
    return D_001A8A5C;
}
