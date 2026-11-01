#include "include_asm.h"

#include "common.h"
typedef struct Scene {
    u8 pad00[0x30];
    s32 mode;
    s32 frame;
    u8 pad38[12];
    s16 count;
    u8 pad46[10];
    u8 *target;
    u8 pad54[0x138];
    u8 *objects[0];
} Scene;
extern s32 D_001A79F0;
extern Scene D_L10_001BD380;
extern u8 D_L10_00296E90[];
extern u8 D_L10_00296EB0[];
extern u8 D_L10_001A93E0[64] __attribute__((sda));
extern u8 D_L10_001B9680[];
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);

void func_PAL_L10_00318BA0(void) {
    f32 tmp[4] __attribute__((aligned(16)));
    s32 low, high, slot, i, j;
    u8 *obj;
    u8 *dst, *src;

    if (D_001A79F0 != 10) {
        return;
    }
    low = -1;
    high = 9999;
    slot = 0;
    if (D_L10_001BD380.mode == 1) {
        low = 1;
        high = 1033;
        slot = 3;
    } else if (D_L10_001BD380.mode == 2) {
        low = 1;
        high = 333;
        slot = 3;
    }
    if (low == -1) {
        return;
    }
    if (D_L10_001BD380.frame >= low && D_L10_001BD380.frame <= high) {
        D_L10_001BD380.target = D_L10_00296E90;
        obj = 0;
        for (i = 0; i < D_L10_001BD380.count; i++) {
            u8 *p = D_L10_001BD380.objects[i];
            if (*(s16 *)(p + 0xAA) == 0xD54) {
                obj = p;
                break;
            }
        }
        if (obj) {
            dst = D_L10_00296EB0;
            src = D_L10_001A93E0;
            for (j = 0; j < 4; j++) {
                u8 *out = dst + j * 16;
                func_00283098(out, src + j * 16, obj + 0xC0);
                func_00282CC0(out, out, obj + 0x10);
                func_00282CF0(tmp, D_L10_001B9680, out);
                func_00282F20(tmp, tmp, 0.15f);
                func_00282CC0(out, out, tmp);
            }
        }
        *(u8 **)(D_L10_001BD380.target + 0x68) = D_L10_001BD380.objects[slot];
    } else {
        D_L10_001BD380.target = 0;
    }
}
