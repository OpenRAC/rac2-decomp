/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections -frac2-zero-ti-por -g.
 * 928/944 bytes after genuine GP array addresses and helper-return repair; particle argument and final counter-update scheduling differ.
 * Reopen with typed integer/FP interleaving justified by the helper physical contract and state-branch source layout.
 * ABI/bounds: Three complete vector unions. Breakup helper has eleven GPR/stack arguments. 002E1680 is void: its nonpositive-count path returns without a value; 00273730 returns a particle pointer. GP views preserve complete arrays.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } DebrisVector;
extern int D_L01_001AEC38 MACRO_ADDR;
extern int D_L01_001B3468;
extern int D_L01_001B3468_gp SDATA(D_L01_001B3468);
extern float D_L01_001B2090 __attribute__((sda));
extern float D_L01_001B208C __attribute__((sda));
extern int D_L01_001B15E0;
extern float D_L01_001B1600[] SDATA(D_L01_001B1600);
extern float D_L01_001B15F8[] SDATA(D_L01_001B15F8);
extern float D_L01_001B15F0[] SDATA(D_L01_001B15F0);
extern float D_L01_001B1620 __attribute__((sda));
extern float D_L01_001B1624, D_L01_001B1628;
extern unsigned char D_L01_001A8F60[];
extern void func_002A7750(void *, int, int);
extern int func_002A9640(void *, int, int);
extern void func_L00_0032A258(void *, void *, void *, void *, int, int, int, int, int, u8, void *);
extern float func_002A7878(float, float);
extern void *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_L01_002E1680(void *, void *, int, int, int, float, float, float);
extern void func_002B0A68(void *, int, void *, int, float, float, float, float);
extern void func_L00_00326110(void *, int, float);
extern int func_002E5CF8(int, int, void *);
extern int func_002B3868(void *);
extern int func_00282948(void *);
extern void func_0029F338(void *);

void func_L01_0040F5A8(unsigned char *m)
{
    DebrisVector velocity, jitter, position;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    switch (m[0x20]) {
    case 0:
        D_L01_001AEC38 = D_L01_001AEC38 + 1;
        func_002A7750(m, 1, -1);
        break;
    case 1:
        if (func_002A9640(m, 0x4010000, 0) && !*(int *)p) {
            D_L01_001AEC38 = D_L01_001AEC38 - 1;
            func_002A7750(m, 2, -1);
        }
        m[0xa8] = 255;
        break;
    case 2:
        if (m[0x31] && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f
            && D_L01_001B3468_gp < D_L01_001B15E0) {
            func_L00_0032A258(m, D_L01_001B1600, D_L01_001B15F8, D_L01_001B15F0,
                65535, 0, 0, 6, 65535, 255, 0);
            jitter.q = 0;
            jitter.f[0] = func_002A7878(-1.0f, 1.0f) * 0.016666668f;
            jitter.f[1] = func_002A7878(-1.0f, 1.0f) * 0.016666668f;
            jitter.f[2] = 0.083333336f;
            velocity.q = jitter.q;
            func_00273730(m, 2, *(short *)(m + 0xaa), 0, m + 0x10, m + 0xf0,
                &velocity, 255, func_002A7878(180.0f, 360.0f), 15.0f);
            jitter.q = 0;
            jitter.f[1] = -0.0150000006f;
            func_L00_00324F18(m, &position, D_L01_001B1620, D_L01_001B1624, D_L01_001B1628);
            func_00283098(&jitter, &jitter, m + 0xc0);
            func_L01_002E1680(&position, &jitter, 10, 0x80808080, 0, 0.0066666672937572002f, 1.0f, 1.03f);
            func_002A7750(m, 3, -1);
        } else {
            func_002B0A68(m, 17, D_L01_001A8F60, 255, 1.0f, 3.0f, 2.0f, 5.0f);
            func_L00_00326110(m, 1, 0.0f);
            func_002E5CF8(0, 0, m);
            func_002A7750(m, 3, -1);
        }
        break;
    case 3:
        if (func_002B3868(m)) {
            *(u16 *)(m + 0x34) |= 1;
            m[0x31] = 0;
            *(int *)(m + 0x98) = 0;
            *(int *)(p + 8) = 120;
            D_L01_001B3468 = D_L01_001B3468 + 1;
        }
        if (func_00282948(p + 8)) {
            D_L01_001B3468_gp = D_L01_001B3468_gp - 1;
            func_0029F338(m);
        }
        break;
    }
}
