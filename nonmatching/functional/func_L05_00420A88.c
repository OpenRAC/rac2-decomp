/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* Complete C reconstruction; not linked and no matching credit.
 * 2026-10-30, game -O2 -G8 -ffunction-sections -frac2-zero-ti-por -g:
 * 928/928 bytes, USA v1.01 0/1; USA v2.00 and PAL identities absent.
 * Only four non-relocation words differ: first-vector x/y constants and stores
 * use f2/f1 rather than retail f1/f2. The real three 16-byte vector spans, zero
 * stores, separate count/induction lifetimes and incomplete GP address aliases
 * restore all remaining instructions and the 0x90 frame. Regalloc's instrumented
 * object equals its normal object: constant pseudos 92/93/94 have live lengths
 * 12/10/8 and get f2/f1/f0. Six source/profile trials; union and array forms tie.
 * Reopen with independent FP priority/lifetime evidence. Reordering stores or
 * scalar coordinate temporaries changed instruction order without matching it.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern int D_L05_001B1364 __attribute__((sda));
extern int D_L05_001B13F4 __attribute__((sda));
extern int D_L05_001B13D8 __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
extern int D_L05_00221D10[];
extern int D_L05_001B2048;
extern char *D_001B251C;
extern char D_L05_001B1380[] SDATA(D_L05_001B1380);
extern char D_L05_001B1370[] SDATA(D_L05_001B1370);
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern char **func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L05_0037B280(char *, int);
extern void func_L05_0037CEE0(char *, void *, float);
extern void func_L05_0037D608(char *, void *, float);
extern int func_00282948(void *);
extern void func_L05_00442828(void *, void *, int);
extern void func_L05_00445B58(void *, void *);
extern void func_L05_004222D8(void);
extern int func_0029B3E0(int, int);
extern void func_L00_003294F0(char *, int);
extern void func_L05_00379F48(int);
extern void func_002AD7B8(int);
extern void func_L05_00420788(char *, int);

void func_L05_00420A88(char *actor)
{
    Vector a;
    Vector b;
    Vector c;
    char *state = *(char **)(actor + 0x68);
    char **item;
    int count;

    if (D_L05_001B1364 == 0) {
        D_L05_00221D10[11] = 0;
        D_L05_001B1364 = 1;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        item = func_L05_00379EB8();
        count = func_L00_004272A0();
        a.q = 0;
        a.f[0] = 487.0f;
        a.f[1] = 526.0f;
        a.f[2] = 531.0f;
        if (count > 0) {
            int n = count;
            do {
                switch (*(short *)(*item + 0xAA)) {
                case 0x957:
                case 0x97C:
                case 0xF76:
                    func_L05_0037B280(*item, 1);
                    func_L05_0037CEE0(*item, &a, 64.0f);
                    func_L05_0037D608(*item, &a, 64.0f);
                    break;
                }
                item++;
            } while (--n != 0);
        }
    }
    if (D_L05_00221D10[4] != 0 || D_L05_001B2048 < 6)
        return;
    if (D_L05_00221D10[5] <= 0) {
        if (func_00282948(state + 0x58) == 0)
            return;
        *(int *)(state + 0x58) = 120;
        func_L05_00442828(D_L05_001B1380, D_L05_001B1370, 200);
        a.q = 0;
        b.q = 0;
        c.q = 0;
        actor[0x20] = 3;
        a.f[0] = 593.5f;
        a.f[1] = 599.0f;
        a.f[2] = 566.0f;
        b.f[0] = 512.5f;
        b.f[1] = 530.0f;
        b.f[2] = 540.0f;
        c.f[0] = 438.0f;
        c.f[1] = 487.0f;
        c.f[2] = 535.0f;
        func_L05_00445B58(&a, &c);
        item = func_L05_00379EB8();
        count = func_L00_004272A0();
        if (count > 0) {
            int n = count;
            do {
                switch (*(short *)(*item + 0xAA)) {
                case 0x957:
                case 0x97C:
                case 0xF76:
                    func_L05_0037B280(*item, 1);
                    func_L05_0037CEE0(*item, &a, 10.0f);
                    func_L05_0037D608(*item, &b, 20.0f);
                    break;
                }
                item++;
            } while (--n != 0);
        }
    } else if (D_L05_001B13F4 != 0) {
        if (func_00282948(state + 0x58) != 0) {
            *(int *)(state + 0x58) = 25;
            D_L05_001B1350++;
            func_L05_004222D8();
            func_0029B3E0(0, -1);
            D_L05_001B1350--;
            func_L00_003294F0(D_001B251C + (*(int *)(state + 0x2C) << 8), 1);
            D_L05_001B13D8 = 0;
            D_L05_001B13F4 = 0;
            func_L05_00379F48(1);
            func_002AD7B8(6);
        }
    } else if (func_00282948(state + 0x58) != 0) {
        func_L05_00420788(actor, 0);
    }
}
