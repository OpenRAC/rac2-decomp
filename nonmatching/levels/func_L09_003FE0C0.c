/* Retained C, 30 October 2026; not matching and no exact-C credit.
 * Profile: game -O2 -G0 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier -fno-gcse. US: 524/532 bytes, 0/1.
 * Corrects the old draft: the ray uses copied block +0x330, not original
 * +0x390. The joint helper's full matrix is stored in state +0x340;
 * both stack vectors retain 16 bytes. The two hit-table pointer reads are
 * explicit volatile accesses matching the two measured lw operations;
 * no volatile locals or extra memory operations are introduced. The
 * candidate reload is not placed in retail's likely delay slots.
 * Regalloc normal/dump objects agree. GCSE forwards final +0x330 through
 * an extra pseudo crossing two calls; -fno-gcse removes that extra saved
 * register and recovers the 0x60 frame. The remaining s0/s1/s2 permutation,
 * paired angle-store order, duplicate positive loop guard and likely slots
 * do not match. Scope and jump-thread controls tie; stop that route.
 * Next: independent register-lifetime and loop-entry evidence.
 */
#include "common.h"

extern float func_00282E80(void *, void *);
extern void func_00282CF0(void *, const void *, const void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern int func_00283DB8(char *, float);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_0029FC20(char *, int, void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L09_003FD7D0(unsigned char *);

extern unsigned char *volatile D_L09_001C3EC0[];

typedef int qword __attribute__((mode(TI)));

int func_L09_003FE0C0(unsigned char *a0, int a1) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);
    float v[8];
    int done = 0;

    if (func_00282E80(a0 + 0x10, s1 + 0x140) <
        (float)*(short *)(a0 + 0x32) * 2.0f) {
        unsigned char *blk;
        float x;
        float y;
        float r;
        int n;
        int i;
        unsigned char *volatile *p;

        func_0029FC20(a0, 1, s1 + 0x340);
        done = 1;
        blk = s1 + 0x390;
        func_00282CF0(v, blk, s1 + 0x370);
        x = func_00283248(v[0], v[1]);
        y = -func_00283248(func_00282E20(v), v[2]);
        r = func_00283BE0(x, *(float *)(a0 + 0xF8));
        *(float *)(s1 + 0x3DC) = r;
        *(float *)(s1 + 0x278) = r;
        r = func_00283BE0(y, *(float *)(a0 + 0xF4));
        *(float *)(s1 + 0x3E0) = r;
        *(float *)(s1 + 0x274) = r;
        *(qword *)(s1 + 0x330) = *(qword *)blk;
        blk = s1 + 0x330;
        if (a1 != 0) {
            *(qword *)(v + 4) = *(qword *)blk;
            v[7] = *(float *)(s1 + 0x434) * 1.4f;
            if (func_00283DB8((char *)(v + 4), (float)*(short *)(a0 + 0x32)) != -1) {
                func_L00_002E6EF8((void (*)(void *))func_L09_003FD7D0, a0);
            }
        }
        n = func_00277F48(blk, 0, 0, 0, *(float *)(s1 + 0x434) * 0.9f);
        if (n > 0) {
            for (i = n, p = D_L09_001C3EC0; i != 0; i--, p++) {
                unsigned char *entry = *p;
                int kind;
                if (entry == 0)
                    continue;
                kind = *(short *)(entry + 0xAA);
                if (kind != 0xCB && kind != 0x76C && kind != 0xEB0)
                    continue;
                entry = *p;
                *(unsigned char **)(s1 + 0x3AC) = entry;
                *(int *)(s1 + 0x44C) = *(short *)(entry + 0xAA);
            }
        }
        if (a1 != 0) {
            *(int *)(s1 + 0x42C) |= 2;
        }
    }
    return done;
}
