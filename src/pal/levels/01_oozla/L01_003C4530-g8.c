#include "common.h"

extern int func_001163B0(void);
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern void func_L01_003BFDC8(void *, int, int, int);

/* Small data reached through $gp: this is only one instruction at -G8. */
extern int D_L01_001AFED4 __attribute__((sda));

typedef struct L01_003C06E8_OWNED {
    char pad0[0x2DC];
    unsigned short f2DC;
} L01_003C06E8_OWNED;

typedef struct L01_003C06E8_OBJ {
    char pad0[0x68];
    L01_003C06E8_OWNED *f68;
} L01_003C06E8_OBJ;

/* func_PAL_L01_003C4530, the PAL copy of func_L01_003C06E8: the same C, with the stored time
 * scaled for 50 Hz. */
void func_PAL_L01_003C4530(L01_003C06E8_OBJ *a0)
{
    L01_003C06E8_OBJ *p = a0;
    L01_003C06E8_OWNED *q = p->f68;
    int v = (func_001163B0() & 1) + 6;
    int r = func_002A7820(10, 15);

    func_L01_003BFDC8(p, v, 0, r);
    func_002A7750(p, 1, 3);
    q->f2DC = (D_L01_001AFED4 * 5 + 2) / 6;
}
