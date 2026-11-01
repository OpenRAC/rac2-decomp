#include "include_asm.h"

#include "common.h"
extern void func_002A7750(u8 *a0, u8 a1, s32 a2);
extern int func_002E5E58(int a0, unsigned int a1, void *a2);
extern void func_PAL_002B1588(int a0, int a1);
extern s32 D_L11_001B30C8;
extern s32 D_L11_001AED00 __attribute__((sda));
extern s32 D_L11_001AED04 __attribute__((sda));
extern s32 D_L11_001AED08 __attribute__((sda));
extern s32 D_L11_001A903C;
extern u8 D_001A7A72 NOT_SDA;
extern u8 D_001A7A74 NOT_SDA;

void func_PAL_L11_0039B240(u8 *arg0) {
    u8 *v1 = arg0;
    int s0 = v1[0x20];
    int enabled;

    if (s0 != 1) {
        if (s0 < 2) {
            if (s0 == 0) {
                v1[0x30] = 0xFF;
                D_L11_001AED08 = 0;
                func_002A7750(v1, 1, -1);
            }
        }
        return;
    }
    enabled = D_L11_001AED00;
    if (D_L11_001B30C8 >= 6 && D_L11_001AED04 == 0 &&
        enabled != 0 && D_001A7A72 == 0) {
        D_001A7A72 = 1;
        func_002E5E58(1, 0, 0);
        func_PAL_002B1588(0x1233, -1);
        D_L11_001A903C = 1;
    }
    if (D_L11_001AED08 < 12)
        return;
    if (D_001A7A74 != 0)
        return;
    D_001A7A74 = 1;
    func_002E5E58(1, 0, 0);
    func_PAL_002B1588(0x1233, -1);
    D_L11_001A903C = 1;
}
