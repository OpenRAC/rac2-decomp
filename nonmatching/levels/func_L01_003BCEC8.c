/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss. Final state: exact only with qzero(state + 8), whose sq address is 8 mod 16; the owner ruled out breaking common.h's 16-byte contract, so it stays a near miss. */
/* func_L01_003BCEC8 (Oozla debris update). Tier opus-1 (Claude Opus 5.5), 29 October 2026.
 * Profile: -O2 -G8 -ffunction-sections (an L01_003BB9D0-g8.c unit: D_L01_001AFE30 is $gp).
 * Best qualified result: 632/636 bytes, 0/1 places (USA v1.01).
 *
 * The only difference is the collision reset's first quadword clear. Retail
 * builds the private block's +8 address and clears through it:
 *     addiu $a0, $s1, 0x8 ; sq $zero, 0x0($a0)     (0x003BD0DC)
 * SQ ignores the low four address bits, so on hardware this clears private
 * +0..+0xF (the velocity the constructor func_L01_003BCA38 copies to +0).
 * The aligned qzero(state) below emits `sq $zero, 0x0($s1)` without the
 * addiu: every other instruction, the frame and all relocations agree.
 *
 * Writing qzero(state + 8) instead gives 636/636 bytes and 1/1 places (also
 * linked level 01 earlier), but the address is 8 modulo 16, which breaks the
 * documented alignment contract of the common.h helpers; the later
 * qzero(state + 0x10) shows both cannot be aligned. Not used here: it needs a
 * maintainer decision on retail's unaligned quadword clear (an approved helper
 * or a documented exception), not another source wording.
 *
 * Semantics recovered against retail: state 0 destroys the object; state 1
 * timer expiry switches to state 2 and starts the 10-frame fade; state 2 fades
 * alpha from the timer and destroys at expiry. The tilt scale is loaded before
 * the tilt store, as retail schedules it.
 */
#include "common.h"
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float D_L01_001AFE30 __attribute__((sda));
extern char D_L01_001BF920[];

void func_L01_003BCEC8(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    float pos[4] __attribute__((aligned(16)));
    float saved, scale, tilt;

    qcopy(pos, obj + 0x10);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_0029F338(obj);
        return;
    case 1:
        if (func_00282948(s + 0x30)) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(10.0f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
            return;
        }
        break;
    case 2:
        if (func_00282948(s + 0x30)) {
            func_0029F338(obj);
            return;
        }
        /* Fade while the removal timer runs. */
        *(unsigned char *)(obj + 0x23) = func_00283CF0((float)*(int *)(s + 0x30) * 12.8f);
        break;
    }
    *(float *)(s + 0x40) = func_00283B98(*(float *)(s + 0x40), 0.034906592f);
    *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8),
                                           *(float *)(s + 0x18) * func_00283198(*(float *)(s + 0x40)));
    *(float *)(obj + 0xF0) += (*(float *)(s + 0x44) - *(float *)(obj + 0xF0)) * 0.02f;
    if (*(unsigned char *)(obj + 0x20) != 2) {
        tilt = func_00283180(*(float *)(s + 0x40)) * 0.17453295f;
        scale = D_L01_001AFE30;
        *(float *)(obj + 0xF4) = tilt;
        saved = *(float *)(s + 8);
        *(float *)(s + 8) = 0.0f;
        func_00282D30(s, s, scale);
        *(float *)(s + 8) = saved;
        func_00282CC0(obj + 0x10, obj + 0x10, s);
        *(float *)(s + 8) -= *(float *)(s + 0x38);
        if (*(float *)(s + 8) < *(float *)(s + 0x3C))
            *(float *)(s + 8) = *(float *)(s + 0x3C);
    } else {
        *(float *)(obj + 0xF4) += (0.17453295f - *(float *)(obj + 0xF4)) * 0.1f;
    }
    pos[2] += 1.0f;
    if (func_002761F8(pos, obj + 0x10, 2, obj, 0)) {
        qcopy(obj + 0x10, D_L01_001BF920);
        qzero(s); /* retail: the same SQ through s + 8 (see above) */
        *(int *)(s + 0x38) = 0;
        qzero(s + 0x10);
        if (*(unsigned char *)(obj + 0x20) != 2) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(10.0f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
        }
    }
}
