/* func_L18_00428048 (180 bytes; levels 18, 19, 20): the per-frame tick of an object's
   controller block: rearms its timer, steps two countdowns (FastDecTimer returns a value;
   declaring the callees void moves the counter into $v0), and hands it on. */
#include "common.h"


extern int D_L18_001B1254 __attribute__((sda));
extern int D_L18_001B1258 __attribute__((sda));
extern int D_L18_001B125C __attribute__((sda));
extern f32 D_L18_001B12FC __attribute__((sda));

extern int func_002A7820(int, int);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern void func_002B0990(char *, char *, int, int, float);

void func_L18_00428048(char *self) {
    char *s0 = *(char **)(self + 0x68);

    if (*(u8 *)(s0 + 0x39A) != 0) {
        *(u8 *)(s0 + 0x39A) = 0;
        if (*(s16 *)(s0 + 0x390) < D_L18_001B1254) {
            *(s16 *)(s0 + 0x390) = func_002A7820(D_L18_001B1258, D_L18_001B125C);
        }
    }
    FastDecTimer(s0 + 0x392);
    FastDecTimer(s0 + 0x396);
    *(u16 *)(s0 + 0x394) += 1;
    func_00282948(*(void **)(s0 + 0x3A8));
    if (*(u16 *)(self + 0x96) <= 0xFFFE) {
        *(u16 *)(self + 0x96) += 1;
    }
    func_002B0990(self, s0 + 0x2C0, 1, 1, D_L18_001B12FC);
}
