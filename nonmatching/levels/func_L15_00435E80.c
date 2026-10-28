/* func_L15_00435E80 - 524 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L15_00435E80 (524 B), in L15_004328E8.c (needs `#include "common.h"`
   for qcopy; func_002ED688 is declared `int` there, use a cast). Fully
   decoded: clear 128 x 0x60-byte slots (D_L15_0026C420[i].f0), list =
   D_L15_001FB320[a0[0x21]], per id spawn/prime a mob (D_001B261C[0] +
   id*256), qcopy positions, call chain, `while (*p++ >= 0)`.
   Draft: 508 B vs 524, ~69 masked lines. D_001B261C read as `extern u8
   *D_001B261C[] __attribute__((sda))` [0] gives retail's repeated lui/lw
   reload. Remaining: saved-register numbering (retail s0=idx s1=state s2=row
   s3=vec s4=ret s5=p s6=a0 s7=table; mine has state/row swapped), and retail
   shares one reload of D_001B261C (a2) between the qcopy dest and the
   func_002EE678 call in the second block (qcopy's memory clobber makes mine
   reload; qcopy_nc made the registers worse), and retail copies the list
   pointer `daddu $s5,$v1,$zero` after the null test.
   Tried: indexed vs pointer clear loop (indexed is right), list var + copy
   (worse, 86), qcopy_nc (worse). */

typedef struct { int f0; u8 pad[0x5C]; } Slot_L15_0026C420;
extern Slot_L15_0026C420 D_L15_0026C420[128];
extern u16 *D_L15_001FB320[];
extern u8 *D_L15_001FE480[];
extern u8 *D_001B261C[] __attribute__((sda));
extern void func_00283360(void *);
extern void func_00282C88(void *);
extern void func_002EE678(void *, int);
extern void func_002EE920(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002A77E0(int);

void func_L15_00435E80(u8 *a0) {
    int i;
    u16 *p;
    u8 *m;
    u8 *s1;
    u8 *s4;
    u8 *s2;
    int idx;
    int n;

    for (i = 0; i < 128; i++) {
        D_L15_0026C420[i].f0 = 0;
    }
    p = D_L15_001FB320[a0[0x21]];
    if (p == 0) {
        return;
    }
    do {
        idx = (*p & 0x7FFF) << 8;
        m = D_001B261C[0] + idx;
        s1 = *(u8 **)(m + 0x68);
        s4 = (u8 *)func_002ED688(m);
        m = D_001B261C[0] + idx;
        *(short *)(m + 0x7C) = 0x3F;
        qcopy(m + 0x10, s1 + 0x430);
        func_00283360(m + 0xC0);
        *(int *)(s1 + 0x27C) = 0;
        func_00282C88(s1 + 0x400);
        a0[0x23] = 0x7F;
        *(u16 *)(a0 + 0x34) &= 0xFFF7;
        (D_001B261C[0] + idx)[0x20] = 1;
        s2 = D_L15_001FE480[*(int *)(s1 + 0x448)];
        *(int *)(s1 + 0x44C) = 1;
        qcopy(D_001B261C[0] + idx + 0x10, s2 + 0x10);
        m = D_001B261C[0] + idx;
        *(int *)(m + 0x1C) = 0;
        func_002EE678(m, 2);
        n = *(int *)(s1 + 0x44C);
        *(int *)(s1 + 0x44C) = n + 1;
        func_002EE920(D_001B261C[0] + idx, s2 + n * 16 + 0x10);
        func_00282CF0(s4 + 0x90, s4 + 0x60, D_001B261C[0] + idx + 0x10);
        func_00282F20(s4 + 0x90, s4 + 0x90, 0.016666668f);
        *(int *)(s4 + 0x130) = 2000000;
        *(int *)(s1 + 0x450) = 0;
        *(int *)(s1 + 0x454) = func_002A77E0(2);
    } while (*(short *)p++ >= 0);
}
