/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* sol-high worker, USA v1.01, pinned game compiler -O2 -G8 -ffunction-sections.
 * Requalified 29 October 2026: 1648/1652 bytes, 0/2 places (levels 05 and 25).
 * The first loop agrees structurally. At +0x32C the second loop's class
 * comparison swaps v0/v1. In the final loop, 0x7fffffff is materialized in a3
 * instead of hoisted into s5, leaving the body four bytes short and changing
 * argument scheduling. All required declarations are below; use a -g8.c unit.
 * Diagnostic GCC dumps identify the cause: GCSE CONST-PROP replaces the color
 * pseudo in the a3 assignment with 2147483647 before loop optimization. Disabling
 * GCSE restores the s5 hoist but worsens to 1660 bytes and changes earlier loops,
 * register allocation and table addressing. -frac2-gcse-unsplit-edges ties the
 * default. Canonical and ABI-preserving interleaved particle prototypes change
 * only argument scheduling; nesting the spin RNG ties its explicit temporary.
 * Reversing the second comparison and arms changes block order; reading the
 * class into a local before the state pointer ties. Incomplete SDATA array views
 * preserve the baseline without assuming four-byte table extents.
 * Next: evidence for source structure preventing the color's cross-block
 * constant propagation while retaining GCSE for the earlier loops.
 * 0x230000 is a collision mask, not a level address. No linked build claimed.
 * 1 November 2026: `long color` keeps the constant in s5 (cprop cannot replace the
 * SImode subreg) and fixes the frame slots: 14 rows off, but 1656 bytes, because a
 * DImode li is one RTL insn and retail splits lui/ori around the entry test. A
 * literal argument and locals set inside the loop tie the int draft. Still open:
 * an SImode shape that survives cprop, and the v0/v1 swap at the 0x956 comparison.
 */
#include "common.h"
extern char *func_334CB8(char *, unsigned int, int);
extern int func_L05_003CFC28(int);
extern float D_L05_001AFB68[] SDATA(D_L05_001AFB68);
extern int D_L05_001AFB80[] SDATA(D_L05_001AFB80);
extern int D_L05_001AFB98[] SDATA(D_L05_001AFB98);
extern int D_L05_001AFBB0[] SDATA(D_L05_001AFBB0);
extern int D_L05_001AFBC8[] SDATA(D_L05_001AFBC8);
extern float D_L05_001AFBDC __attribute__((sda));
extern float D_L05_001AFBE0 __attribute__((sda));
extern float D_L05_001AFBE8 __attribute__((sda));
extern float D_L05_001AFBEC __attribute__((sda));
extern char D_L05_001B96C0[];
extern void func_3068F8(void *, void *, float);
extern void func_306660(void *, void *, void *);
extern void func_306748(void *, void *, void *);
extern void func_306630(void *, void *, void *);
extern int func_332AB8(int);
extern float func_332C18(void);
extern void func_338380(void *, void *, void *, float);
extern float func_332BB0(float, float);
extern char *func_L05_003CEFA0(char *, void *, int);
extern void func_33B330(void *, float, float, float);
extern int func_332AF8(int, int);
extern int func_001163B0(void);
extern char *func_347040(void *, int, void *, float, float, float, float, int, int);
int func_L05_003CF350(char *obj)
{
    float pos[4], base[4], offset[4], center[4], vel[4];
    unsigned char *r;
    char *p, *s;
    int index, i, j, k;
    float radius, speed, angle, count, jitter, spread, size, a, b;
    r = func_334CB8(obj, 0x230000, 0);
    *(unsigned char *)(obj + 0xa8) = 255;
    if (r) {
    unsigned short id = *(unsigned short *)(obj + 0xaa);
    if ((unsigned char)r[0x28] != 1 || (short)id != 0x956) {
    index = func_L05_003CFC28((short)id);
    { int kind = D_L05_001AFB80[index];
    radius = D_L05_001AFB68[index] * 0.5f;
    speed = D_L05_001AFBDC * 0.01666666753590107f;
    if ((unsigned char)r[0x28] == 0) speed *= 3.0f;
    func_3068F8(base, r + 0x10, speed);
    if ((unsigned char)r[0x28] != 0 && func_332AB8(4) == 0) {
        func_306660(offset, obj + 0x10, D_L05_001B96C0);
        func_306748(center, offset, D_L05_001B96C0 + 0x250);
        func_338380(offset, center, offset, func_332C18());
        func_3068F8(offset, offset, D_L05_001AFBE0 * 0.01666666753590107f);
        func_306630(base, base, offset);
    }
    for (i = 0; i < D_L05_001AFBC8[index]; i++) {
        char *p, *s; float size, a, b;
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, radius);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, radius);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, radius);
        p = func_L05_003CEFA0(obj, pos, kind);
        if (p) {
            s = *(char **)(p + 0x68);
            size = D_L05_001AFBDC * 0.008333333767950535f;
            a = func_332C18(); b = func_332C18();
            func_33B330(center, size, a, b);
            func_306630(s + 0x10, base, center);
            p[0x20] = 2;
        }
    }
    }
    { int kind = 0x955;
    size = D_L05_001AFBDC * 0.008333333767950535f;
    if (*(short *)(obj + 0xaa) == 0x956) { size += size; kind = 0x971; }
    for (j = 0; j < D_L05_001AFB98[index]; j++) {
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, radius);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, radius);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, radius);
        p = func_L05_003CEFA0(obj, pos, kind);
        if (p) {
            s = *(char **)(p + 0x68);
            if (0x956 == *(short *)(obj + 0xaa)) {
                func_306660(center, pos, obj + 0x10);
                func_3068F8(center, center, size);
            } else {
                a = func_332C18(); b = func_332C18();
                func_33B330(center, size, a, b);
            }
            func_306630(s + 0x10, base, center);
            p[0x20] = 3;
        }
    }
    }
    spread = D_L05_001AFB68[index] * D_L05_001AFBEC;
    angle = D_L05_001AFBE8 * 0.01666666753590107f;
    count = (float)D_L05_001AFBB0[index];
    qcopy(center, obj + 0x10);
    if ((unsigned char)r[0x28] == 0) {
        func_3068F8(base, D_L05_001B96C0 + 0x230, speed * 0.5f);
        func_3068F8(vel, D_L05_001B96C0 + 0x230, 0.5f);
        func_306630(center, center, vel);
        angle = 0.05000000447034836f;
        if (*(short *)(obj + 0xaa) == 0x955) {
            count = 40.0f; radius = 0.1f; angle = 0.03333333507180214f; spread *= 3.0f;
        }
    } else qzero(base);
    { long color = 0x7fffffff;
    for (k = 0; (float)k < count; k++) {
        int spin;
        pos[0] = center[0] + func_332BB0(0.0f, radius);
        pos[1] = center[1] + func_332BB0(0.0f, radius);
        pos[2] = center[2] + func_332BB0(0.0f, radius);
        a = func_332C18(); b = func_332C18();
        func_33B330(vel, angle, a, b);
        func_306630(vel, vel, base);
        spin = func_332AF8(-3, 3);
        p = func_347040(pos, spin, vel, 0.0f, 1.0f, 1.0f, spread * 210000.0f, color, 0);
        if (p) {
            *(short *)(p + 0xa) = 120;
            s = p + 0x20;
            p[8] = func_332AB8(255);
            if ((unsigned short)(*(unsigned short *)(obj + 0xaa) - 0x953) < 3)
                p[3] = (func_001163B0() & 1) ? 0x44 : 0x48;
            else p[3] = 0x44;
            *(int *)(s + 4) = 2;
            s[0xa] = 127;
            s[0xb] = p[0xa];
        }
    }
    }
    return 1;
    }
    }
    return 0;
}
