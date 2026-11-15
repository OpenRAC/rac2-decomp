#include "include_asm.h"
#include "common.h"

extern char D_0018C318[];
extern char D_00138180[];
extern int D_L00_001A8FB4 __attribute__((section(".sdata")));
extern s32 func_00282978(s32);
extern void func_L00_002FC008(void);

void func_L00_002CB218(void)
{
    char *b;
    char *o;
    u64 w;

    FastDecTimer(D_0018C318);
    FastDecTimer(D_0018C318 + 2);
    b = D_0018C318 - 0x24F8;
    if (0x37 == *(int *)(b + 0x2294))
        return;
    if (*(u8 *)(b + 0x22BC) != 0)
        return;
    if (D_L00_001A8FB4 != 0)
        return;
    o = D_00138180;
    if (*(int *)(o + 0x1A4) & 0x10)
        *(short *)(b + 0x24F8) = 20;
    w = *(u32 *)(b + 0x24F8);
    if (w == 0)
        return;
    if (*(int *)(o + 0x1B8) & 0x10) {
        if (*(short *)(b + 0x24FA) == 0) {
            *(short *)(b + 0x24FA) = 20;
            return;
        }
        *(int *)(b + 0x2538) = 1;
        func_L00_002FC008();
    }
}
