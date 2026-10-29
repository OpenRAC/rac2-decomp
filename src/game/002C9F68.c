/* Carried from rac3-decomp (src/levels/shared/L01_0047DBB0.c, func_L01_0047DCB8): the
   same instructions with rac2's offsets. Uploads D_001A7344 * 1536 bytes from the source
   at +0x20 of D_001F2840 to GS memory in 16 KB blocks (to the top of the 0x3FB000 area when
   the mode at +0xD0 is 2 or more, else at D_001A72D4), counts the call in D_001B1598 and
   clears the mode. */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    u8 pad0[0x20];
    s32 src;
    u8 pad24[0xD0 - 0x24];
    s32 mode;
} UploadRequest;

extern UploadRequest D_001F2840;
extern s32 D_001B1598 MACRO_ADDR;
extern s32 D_001A7344 MACRO_ADDR;
extern s32 D_001A72D4 __attribute__((sda));
extern void func_002FC3C0(s32);
extern int func_001261F0(s32);
extern void func_00126470(void *, s16, s32, s32, s32, s32, s32, s32);
extern void func_0011AEA0(s32);
extern void func_00126730(void *, s32);
extern void func_001244B8(s32, s32);

void func_002C9F68(void) {
    TI128 buf[7];
    s32 size;
    s32 dst;
    s32 src;

    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598++;
    size = D_001A7344 * 1536;
    src = D_001F2840.src;
    dst = D_001A72D4;
    if (D_001F2840.mode >= 2) {
        dst = 0x3FB000 - size;
    }
    for (; size >= 0; size -= 16384) {
        func_00126470(buf, dst >> 8, 1, 0, 0, 0, 64, 64);
        dst += 16384;
        func_0011AEA0(0);
        func_00126730(buf, src);
        src += 16384;
        func_001244B8(0, 0);
    }
    D_001F2840.mode = 0;
}
