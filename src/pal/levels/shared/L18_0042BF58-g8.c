#include "include_asm.h"

/* func_PAL_L18_0042BF58, the PAL copy of func_L18_004273F0: unit of its own, -G8 and -frac2-qcopy as the template. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

extern unsigned int D_L18_001FB320[];
extern char *D_L18_001B281C;
extern char *D_L18_001B281C_sda __attribute__((sda));
extern int D_L18_001B2838 __attribute__((sda));
extern int D_L18_001B125C __attribute__((sda));
extern int D_L18_001B2348;
extern char D_L18_002C0A90[];
extern char D_00189EA0[];
extern char *D_001FE480[];

extern void func_0026FEB8(char *fmt, int a1, int a2);
extern float func_L18_0035D5A8(void *a0, void *a1, void *a2, int a3, float f12);
extern void func_002A7750(u8 *a0, int a1, int a2);
extern void func_PAL_L18_0042BD70(u8 *a0);
extern float func_00282E80(void *a0, void *a1);

void func_PAL_L18_0042BF58(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 *best = 0;
    int found = 0;
    float best_d = 100000.0f;
    float vec[4];
    u16 *q;
    u8 *e;
    u8 *es;
    float d;

    if (*(int *)(state + 0x378) == -1) {
        if (*(int *)(state + 0x368) == -1) {
            func_0026FEB8(D_L18_002C0A90, *(s16 *)(obj + 0xB2), D_L18_001B2348);
        } else {
            func_L18_0035D5A8(vec, obj + 0x10, D_00189EA0, *(int *)(state + 0x368), 0.0f);
            found = 1;
        }
    } else {
        *(TI128 *)vec = *(TI128 *)(D_001FE480[*(int *)(state + 0x378)] + 0x10);
    }

    q = (u16 *)D_L18_001FB320[obj[0x21]];
    while (obj[0x21] != 0xFF && obj[0x21] <= D_L18_001B2838 && q != 0 &&
           ((q != 0 && (s16)q[-1] >= 0) || q == (u16 *)D_L18_001FB320[obj[0x21]])) {
        e = (u8 *)(D_L18_001B281C + ((*q & 0x7FFF) << 8));
        if (e == 0)
            break;
        es = *(u8 **)(e + 0x68);
        d = func_00282E80(e + 0x10, vec);
        if (es != 0 && (es[0x399] & 1) != 0 && d < best_d) {
            best_d = d;
            best = e;
        }
        q++;
    }

    if (best != 0) {
        u8 *bs;
        int hw;
        best[0x31] = 1;
        hw = D_L18_001B125C;
        *(u16 *)(best + 0x34) &= 0xFFFE;
        bs = *(u8 **)(best + 0x68);
        *(int *)(bs + 0x36C) = *(int *)(state + 0x36C);
        *(int *)(bs + 0x370) = *(int *)(state + 0x370);
        *(int *)(bs + 0x374) = *(int *)(state + 0x374);
        *(int *)(bs + 0x378) = *(int *)(state + 0x378);
        *(int *)(bs + 0x360) = *(int *)(state + 0x360);
        *(int *)(bs + 0x364) = *(int *)(state + 0x364);
        *(u16 *)(bs + 0x390) = ((s32)(hw) * 5 + 2) / 6;
        *(int *)(bs + 0x38C) = *(int *)(state + 0x378);
        bs[0x39A] = 1;
        bs[0x399] = 2;
        *(u16 *)(bs + 0x392) = state[0x398];
        if (found) {
            func_002A7750(best, 0, 4);
        } else if (bs[0x3EA] != 0 && *(int *)(bs + 0x3B4) != -1 &&
                   ((u8 *)((*(int *)(bs + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFE &&
                   ((u8 *)((*(int *)(bs + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFD) {
            func_PAL_L18_0042BD70(best);
        } else {
            func_002A7750(best, 0, 3);
        }
    }
}
