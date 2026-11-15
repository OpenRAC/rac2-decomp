/* Second spawner state machine: waits for the player, then emits while its target is alive and
   the level counter (D_L08_001B3AA0) is below 10. */

#include "common.h"


extern s32 D_L08_001B29DC __attribute__((sda));
extern f32 D_L08_001B250C __attribute__((sda));
extern s32 D_L08_001B3AA0 __attribute__((sda));
extern char D_L08_001A8F20[] MACRO_ADDR;
extern char *func_002A9640(s32 a, s32 b, s32 c);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_002B0A68(char *a0, f32 f12, f32 f13, s32 a1, char *a2,
                        f32 f14, f32 f15, s32 a3);
extern void func_L00_00326110(char *a0, s32 a1, f32 f12);
extern void func_002E5CF8(s32 a0, s32 a1, char *a2);
extern s32 func_002B3868(char *a0);
extern s32 func_00282948(char *a0);
extern void func_0029F338(char *a0);

void func_L08_0042FAC0(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    u8 state = *(u8 *)(a0 + 0x20);
    char *p;
    s32 n;
    u8 st;

    switch (state) {
    case 0:
        func_002A7750(a0, 1, -1);
        return;
    case 1:
        p = func_002A9640((s32)a0, 0x04010000, 0);
        if (p != 0 && *(s32 *)s1 == 0) {
            func_002A7750(a0, 2, -1);
            return;
        }
        *(u8 *)(a0 + 0xA8) = 0xFF;
        n = *(s32 *)(s1 + 4);
        if (n > 0) {
            char *e = (char *)(D_L08_001B29DC + (n << 8));

            if (e == 0) {
                return;
            }
            st = *(u8 *)(e + 0x20);
            if (st == 0xFE || (st == 0xFD || st == 3)) {
                func_002A7750(a0, 2, -1);
            }
        }
        return;
    case 2:
        if (*(u8 *)(a0 + 0x31) != 0 && D_L08_001B250C < 0.9f &&
            D_L08_001B3AA0 < 10) {
            func_002B0A68(a0, 3.0f, 6.0f, 15, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        } else {
            func_002B0A68(a0, 3.0f, 6.0f, 1, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        }
        func_L00_00326110(a0, 1, 0.0f);
        PlayMobySound(0, 0, a0);
        func_002A7750(a0, 3, -1);
        return;
    case 3:
        if (func_002B3868(a0) != 0) {
            s32 c;
            *(u8 *)(a0 + 0x31) = 0;
            c = D_L08_001B3AA0;
            *(u16 *)(a0 + 0x34) |= 1;
            *(s32 *)(a0 + 0x98) = 0;
            D_L08_001B3AA0 = c + 1;
            *(s32 *)(s1 + 8) = 0x78;
        }
        if (func_00282948(s1 + 8) != 0) {
            D_L08_001B3AA0 = D_L08_001B3AA0 - 1;
            func_0029F338(a0);
        }
        return;
    }
}
