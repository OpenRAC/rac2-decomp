#include "include_asm.h"

#include "common.h"
extern int func_PAL_00273A10(char *);
extern void func_002A7750(char *, int, int);
extern int func_00277F48(float, void *, int, void *, int);
extern float func_00282E80(void *, void *);
extern void func_0029F338(void *);
extern int D_L03_001B2548;
extern char *D_L03_001C3E40[];
extern int D_L03_001B0580 __attribute__((sda));

void func_PAL_L03_003D4480(char *a0)
{
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        if (func_PAL_00273A10(a0)) {
            func_002A7750(a0, 1, -1);
            *(u16 *)(a0 + 0x34) |= 0x2000;
        }
        break;
    case 1:
        if ((D_L03_001B2548 & 15) == (((int)a0 >> 8) & 15)) {
            int count = func_00277F48(0.2f, a0 + 0x10, 0, a0, 0);
            if (count > 0) {
                int remaining = count;
                char **p = D_L03_001C3E40;
                do {
                    int type = *(s16 *)(*p + 0xAA);
                    if (type == 0xFF3 || type == 0xFFD)
                        func_002A7750(a0, 3, -1);
                    --remaining;
                    ++p;
                } while (remaining);
            }
        }
        if (func_00282E80(a0 + 0x10, &D_L03_001B0580) < 0.3f)
            func_002A7750(a0, 3, -1);
        {
            u32 timer = *(u16 *)(a0 + 0x96);
            u32 old = timer++;
            *(u16 *)(a0 + 0x96) = timer;
            if (old > 500 && !*(u8 *)(a0 + 0x31))
                func_002A7750(a0, 2, -1);
        }
        break;
    case 2:
    case 3: {
        int amount = *(u8 *)(a0 + 0x20) == 2 ? 2 : 8;
        int alpha = *(u8 *)(a0 + 0x23);
        if (alpha < amount) func_0029F338(a0);
        else *(u8 *)(a0 + 0x23) = alpha - amount;
        break;
    }
    }
}
