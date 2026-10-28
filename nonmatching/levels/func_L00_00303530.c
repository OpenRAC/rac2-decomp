/* func_L00_00303530 - 540 bytes.  Worker attempt, 27 October 2026 (draft below).

   draft.c is a full src/levels/shared/L00_00303530-g8.c (needs cflags line
   `-O2 -G8 -ffunction-sections`; marker removed from L00_002FC7A0.c).
   548 vs 540 B; everything matches except the table block at
   0x3035D0-0x3035E4 (5 lines): retail does `addu a1,T,idx*8; daddu
   v1,a1,zero; lw a3,0x52C8(a1); lw a1,0x529C(T); lw a2,0x52CC(v1)` (pointer
   copied, 52C8 loaded before 529C, then add a3+a1); mine loads 529C first and
   uses one pointer (2 insns fewer, so the beq offset also differs).
   Tricks that mattered: D_001B24D4 as `int[] sda` (lui/lw per use, no hoist),
   D_001B2614 separate from D_001B2600[], loop `do{}while(--n)`,
   `ref_L00_00303530_00[]` for the level data at 0x1C9340 (L00),
   D_001B3618/D_001B34E0 as sda (gp).
   Tried: struct for the table (worse), int* e, locals x/y. */

#include "include_asm.h"

extern int ref_L00_00303530_00[];
extern int D_001B2600[];
extern int D_001B2614;
extern int D_001B24D4[] __attribute__((sda));
extern int D_001B3618 __attribute__((sda));
extern unsigned char *D_001B34E0 __attribute__((sda));
extern char D_0014B540[];

extern void func_L00_0035F8D0(int, int, int, int, int);
extern void func_002E5FE0(void);
extern void func_002B7170(void);
extern void func_002FC3C0(unsigned long);
extern void func_L00_002FD400(void);
extern int func_002B7C80(int, int, int);
extern void func_0011AEA0(int);
extern void func_0029D4D0(int, int);
extern void func_L00_00300090(int, int);
extern void func_L00_00300378(int);
extern void func_002F0468(void *);
extern void func_002F0FA0(void);
extern void func_L00_003032F0(void);
extern void func_L00_0032D208(int);
extern void func_L00_00303418(int);
extern void func_002B6E78(int, int, int);
extern int func_002B49C8(int);
extern void func_002B72E8(int);

void func_L00_00303530(int idx, int arg) {
    int base, s0, s1, i, n;
    unsigned short *p;
    int *e;
    int x, y;

    if (ref_L00_00303530_00[0] == idx)
        return;
    func_L00_0035F8D0(0, 0, 0, 0, 0);
    func_002E5FE0();
    func_002B7170();
    func_002FC3C0(1);
    ref_L00_00303530_00[0] = idx;
    s1 = D_001B2600[0];
    D_001B3618 = D_001B2600[D_001B2614];
    func_L00_002FD400();
    e = (int *)(D_0014B540 + idx * 8);
    x = e[0x52C8 / 4];
    y = *(int *)(D_0014B540 + 0x529C);
    func_002B7C80(s1, x + y, e[0x52CC / 4]);
    s0 = s1 + *(int *)s1;
    func_0011AEA0(0);
    s1 = s1 + *(int *)(s1 + 4);
    func_0029D4D0(s0, ref_L00_00303530_00[2]);
    func_0029D4D0(s1, ref_L00_00303530_00[1]);
    func_0011AEA0(0);
    func_L00_00300090(ref_L00_00303530_00[2], ref_L00_00303530_00[4]);
    func_L00_00300378(ref_L00_00303530_00[1]);
    n = D_001B24D4[0];
    if (n > 0) {
        p = (unsigned short *)(D_001B34E0 + 0x36);
        do {
            *p = 0xFFFF;
            p += 0x20;
        } while (--n != 0);
    }
    i = 0;
    if (D_001B24D4[0] > 0) {
        do {
            unsigned short *q = (unsigned short *)0x70003000;
            int k = 0;
            while (i < D_001B24D4[0] && k < 0x3FF) {
                *q++ = i++;
                k++;
            }
            *q = 0xFFFF;
            func_002F0468((void *)0x70003000);
        } while (i < D_001B24D4[0]);
    }
    func_002F0FA0();
    func_L00_003032F0();
    func_L00_0032D208(idx);
    func_L00_00303418(idx);
    func_002B6E78(arg, 1, 0x400);
    if (func_002B49C8(2))
        func_002B72E8(0);
}
