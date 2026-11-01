#include "include_asm.h"

typedef unsigned char u8;
typedef int s32;
extern char D_L18_001A8F20[] __attribute__((sda));
extern void func_002A7750(u8 *, u8, s32);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int func_002E5DA0(int, int, char *, int);

/* Enters the hit state once, optionally spawning the impact effect and sound. */
s32 func_PAL_L18_003FF648(u8 *self, s32 effect) {
    if (self[0x20] != 2) {
        func_002A7750(self, 2, -1);
        *(s32 *)(*(u8 **)(self + 0x68) + 0x28) = effect;
        if (effect) {
            func_PAL_002AC718(self, D_L18_001A8F20, self + 0x10, 0.0f, 0.0f, 5, 3, 8,
                          5.0f, 4.900000095367432f, 32.0f, 2.0f, -1, 0.0f, 1, 1, -1, 0, 0x810001);
            func_002E5DA0(1, 0, (char *)self, 0x1152);
        }
        return 0;
    }
    return 1;
}

