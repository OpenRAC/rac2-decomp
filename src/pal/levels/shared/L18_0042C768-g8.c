#include "include_asm.h"

#include "common.h"
extern int D_L18_001B1254 __attribute__((sda));
extern int D_L18_001B1258 __attribute__((sda));
extern int D_L18_001B125C __attribute__((sda));
extern f32 D_L18_001B12FC __attribute__((sda));
extern int func_002A7820(int, int);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern void func_PAL_002B14F8(char *, char *, int, int, float);

void func_PAL_L18_0042CC40(char *self) {
    char *s0 = *(char **)(self + 0x68);

    if (*(u8 *)(s0 + 0x39A) != 0) {
        *(u8 *)(s0 + 0x39A) = 0;
        if (*(s16 *)(s0 + 0x390) < ((s32)(D_L18_001B1254) * 5 + 2) / 6) {
            *(s16 *)(s0 + 0x390) = ((s32)(func_002A7820(D_L18_001B1258, D_L18_001B125C)) * 5 + 2) / 6;
        }
    }
    func_00282978(s0 + 0x392);
    func_00282978(s0 + 0x396);
    *(u16 *)(s0 + 0x394) += 1;
    func_00282948(*(void **)(s0 + 0x3A8));
    if (*(u16 *)(self + 0x96) <= 0xFFFE) {
        *(u16 *)(self + 0x96) += 1;
    }
    func_PAL_002B14F8(self, s0 + 0x2C0, 1, 1, D_L18_001B12FC);
}
