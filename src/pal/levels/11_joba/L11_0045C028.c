#include "include_asm.h"

#include "common.h"
extern void *func_002B60B0(u8 *, float, float, float, float);
extern void func_002A7750(char *, int, int);
extern s32 func_PAL_002B3F18(char *, char *, char *);
extern void func_002A0488(void *, u8, u8, u8);

/* The func_L02_003F17B0 reset for the level-11 mover: the same turn rates, its own state
   layout, and the path follower (func_PAL_002B3F18) restarted in place of the two child
   slots. */
void func_PAL_L11_0045C028(char *arg0, int arg1) {
    char *state = *(char **)(arg0 + 0x68);

    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(u16 *)(state + 0x256) = 0;
    *(u16 *)(state + 0x88) = 0;
    func_002B60B0((u8 *)arg0, 0.0064000003f, 0.16000001f,
                  0.0016755164f, 0.12566373f);
    func_002A7750(arg0, 3, 0);
    *(int *)(arg0 + 0x98) = *(int *)(*(char **)(arg0 + 0x24) + 0x10);
    *(u8 *)(state + 0x6A) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(u8 *)(arg0 + 0x31) = 1;
    *(u8 *)(arg0 + 0x7F) = 0;
    *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x1000) & 0xFFB8;
    *(u16 *)(state + 0x258) = arg1;
    *(int *)(state + 0x200) = 0;
    func_PAL_002B3F18(arg0, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(arg0, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}

