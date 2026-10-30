/* 30 October 2026 retained reconstruction, not a match.
 * Profile: -O2 -G0 -ffunction-sections. USA v1.01: 524/524 bytes, 0/1.
 * The clear loop addresses offset0x40 of128 records with stride0x60 from D_L15_0026C3E0.
 * Modeling that real field recovers the retail size and entry loop. List-null-test
 * allocation and root/state reloads still differ, first at+0x70. A separate list variable
 * grows to532 bytes.
 * Older source and trial history remain in Git and the private workspace.
 */
#include "common.h"
extern int func_002ED688(unsigned char *);
typedef struct { u8 prefix[0x40]; int active; u8 tail[0x1C]; } GornEffectSlot;
extern GornEffectSlot D_L15_0026C3E0[];
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
        D_L15_0026C3E0[i].active = 0;
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
