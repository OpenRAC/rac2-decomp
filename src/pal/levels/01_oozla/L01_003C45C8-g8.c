#include "common.h"

extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern void func_L01_003BFDC8(void *, int, int, int);

/* Small data reached through $gp: these are only one instruction at -G8. */
extern int D_L01_001AFED4 __attribute__((sda));
extern int D_L01_001AFED8 __attribute__((sda));
extern int D_L01_001AFEDC __attribute__((sda));

typedef struct L01_003C0760_OWNED {
    char pad0[0x2DC];
    unsigned short f2DC;
} L01_003C0760_OWNED;

typedef struct L01_003C0760_OBJ {
    char pad0[0x68];
    L01_003C0760_OWNED *f68;
} L01_003C0760_OBJ;

/* func_PAL_L01_003C45C8, the PAL copy of func_L01_003C0760: the same C, with the stored time
 * scaled for 50 Hz. */
void func_PAL_L01_003C45C8(L01_003C0760_OBJ *a0)
{
    L01_003C0760_OBJ *p = a0;
    L01_003C0760_OWNED *q = p->f68;
    int r = func_002A7820(7, 12);

    func_L01_003BFDC8(p, 8, 0, r);
    func_002A7750(p, 3, 3);
    q->f2DC = (D_L01_001AFED4 * 5 + 2) / 6;
}

typedef struct L01_003C07C8_OWNED {
    char pad0[0x2DA];
    unsigned short f2DA;
} L01_003C07C8_OWNED;

typedef struct L01_003C07C8_OBJ {
    char pad0[0x68];
    L01_003C07C8_OWNED *f68;
} L01_003C07C8_OBJ;

/* func_PAL_L01_003C4650, the PAL copy of func_L01_003C07C8: the same C, with the stored time
 * scaled for 50 Hz. */
void func_PAL_L01_003C4650(L01_003C07C8_OBJ *a0)
{
    L01_003C07C8_OBJ *p = a0;
    L01_003C07C8_OWNED *q = p->f68;
    int r = func_002A7820(9, 11);

    func_L01_003BFDC8(p, 13, 0, r);
    func_002A7750(p, 2, 3);
    q->f2DA = (D_L01_001AFED8 * 5 + 2) / 6;
}

typedef struct L01_003C0830_OWNED {
    char pad0[0x2DE];
    unsigned short f2DE;
} L01_003C0830_OWNED;

typedef struct L01_003C0830_OBJ {
    char pad0[0x68];
    L01_003C0830_OWNED *f68;
    char pad1[0x9C - 0x6C];
    int f9C;
} L01_003C0830_OBJ;

/* func_PAL_L01_003C46D8, the PAL copy of func_L01_003C0830: the same C, with the stored time
 * scaled for 50 Hz. */
void func_PAL_L01_003C46D8(L01_003C0830_OBJ *a0)
{
    L01_003C0830_OBJ *p = a0;
    L01_003C0830_OWNED *q = p->f68;
    int r = func_002A7820(7, 11);

    func_L01_003BFDC8(p, 14, 0, r);
    func_002A7750(p, 4, 3);
    p->f9C = p->f9C | 0x30;
    q->f2DE = (D_L01_001AFEDC * 5 + 2) / 6;
}
