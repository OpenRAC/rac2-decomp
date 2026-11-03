/* func_L00_003AD7C8: 612 bytes retail; this C is 616 bytes and every instruction matches except
 * the three globals at D_L00_001AF7C0..7CC (0/27 places because of them).
 * Compiled with -O2 -G8 -ffunction-sections (the L00_003A8E28-g8.c profile).
 * Retail reaches them in the assembler-macro form (lui $at,hi; swc1 f0,-0x83C($at); addiu a1,$gp,0x7D0;
 * the three stores each re-lui $at), which is what -mno-split-addresses produces; the default
 * profile emits lui $v0 / swc1 0($v0) with a shared base and costs 4 bytes. Nothing else differs
 * after fixing register allocation (s0 load before the early return, colour stores before
 * func_0027C878, the sd zero at +0x70 before the first float store).
 * Unblock: a -mno-split-addresses, -G8 unit for this function (config/cflags.txt line, not allowed
 * for the worker). Untested with that flag.
 */
#include "include_asm.h"
#include "common.h"

extern int D_L00_001A8F00;
extern int D_L00_001B19C8;
extern float D_L00_001AF7C0 __attribute__((sda));
extern float D_L00_001AF7C4 NOT_SDA;
extern float D_L00_001AF7C8 NOT_SDA;
extern float D_L00_001AF7CC NOT_SDA;
extern float func_00282C10(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern void func_00283410(void *, void *);
extern void func_00283788(void *, void *, void *);
extern long long func_0027C878(int);
extern void func_00280B90(void *, void *, int);

void func_L00_003AD7C8(char *a0)
{
    char pkt[144];
    float m[16];
    float m2[16];
    float vec[4];
    char *s0;
    int i;

    s0 = *(char **)(a0 + 0x68);
    if (D_L00_001A8F00 == 2) {
        return;
    }
    for (i = 0; i < 2; i++) {
        int odd = i & 1;
        float f;
        long long id;

        vec[0] = func_00283B98(-func_00283248(func_00282C10(*(float *)(s0 + 0x20) * *(float *)(s0 + 0x20) +
                                                          *(float *)(s0 + 0x28) * *(float *)(s0 + 0x28)),
                                              *(float *)(s0 + 0x24)),
                               1.5707964f);
        vec[1] = func_00283248(*(float *)(s0 + 0x28), *(float *)(s0 + 0x20));
        vec[2] = 0;
        vec[3] = 0;
        D_L00_001AF7C0 = 0;
        f = func_00283C28(func_00283CE0(D_L00_001B19C8 % 180) * 0.03490658849f);
        if (odd) {
            f = -f;
        }
        D_L00_001AF7C4 = f;
        D_L00_001AF7C8 = 0;
        D_L00_001AF7CC = 0;
        func_00283410(m2, &D_L00_001AF7C0);
        func_00283410(m, vec);
        func_00283788(m, m, m2);
        qcopy(m + 12, s0 + 0x10);
        *(int *)(pkt + 0x40) = 0x80808080;
        *(int *)(pkt + 0x44) = 0x80808080;
        *(int *)(pkt + 0x48) = 0x80808080;
        *(int *)(pkt + 0x4C) = 0x80808080;
        id = func_0027C878(odd ? 0x12 : 0x11);
        *(long long *)(pkt + 0x70) = 0;
        *(float *)(pkt + 0x00) = -1.0f;
        *(int *)(pkt + 0x04) = 0;
        *(float *)(pkt + 0x08) = 1.0f;
        *(float *)(pkt + 0x0C) = 1.0f;
        *(float *)(pkt + 0x10) = 1.0f;
        *(int *)(pkt + 0x14) = 0;
        *(float *)(pkt + 0x18) = 1.0f;
        *(float *)(pkt + 0x1C) = 1.0f;
        *(float *)(pkt + 0x20) = -1.0f;
        *(int *)(pkt + 0x24) = 0;
        *(float *)(pkt + 0x28) = -1.0f;
        *(float *)(pkt + 0x2C) = 1.0f;
        *(float *)(pkt + 0x30) = 1.0f;
        *(int *)(pkt + 0x34) = 0;
        *(float *)(pkt + 0x38) = -1.0f;
        *(float *)(pkt + 0x3C) = 1.0f;
        *(int *)(pkt + 0x50) = 0;
        *(float *)(pkt + 0x54) = 1.0f;
        *(float *)(pkt + 0x58) = 1.0f;
        *(float *)(pkt + 0x5C) = 1.0f;
        *(int *)(pkt + 0x60) = 0;
        *(int *)(pkt + 0x64) = 0;
        *(float *)(pkt + 0x68) = 1.0f;
        *(int *)(pkt + 0x6C) = 0;
        *(long long *)(pkt + 0x78) = id;
        *(long long *)(pkt + 0x80) = 0xFF9000000260LL;
        *(long long *)(pkt + 0x88) = 0x8000000048LL;
        func_00280B90(pkt, m, 1);
    }
}
