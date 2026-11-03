/* 2026-11-03 w02 source-contract/lifetime review (USA v1.01 only).
 * Profile: -O2 -G8 -ffunction-sections.
 * Current check.py: 1304/1304 bytes, 0/2 places, first mismatch +0x154.
 * The particle helper now has its actual pointer return. Named offset-count lifetime gives1288/1304; a real named emission-mode lifetime ties the1304-byte candidate with four spill-offset differences.
 * Reopen: A new GCSE reaching-address count/lifetime that swaps third-vector and m+0x10 spill slots without changing other instructions.
 * No linked or cross-release match is claimed. Earlier notes follow.
 */
/* sol-high, USA v1.01, -O2 -G8 -ffunction-sections.
 * Best check.py: 1304/1304 bytes, 0/2 places, first mismatch +0x154.
 * Four words differ: the third-vector pointer and m+0x10 pointer spill
 * to sp+0x8c and sp+0x88 respectively, opposite retail. Their two reloads
 * differ accordingly. All other operations, including f20/f21, agree.
 * Making the offset table const fixes all five initial copy-order mismatches
 * in the earlier draft. Copy temporaries, a grouped vector struct, a TI/float
 * union for the third vector, and qcopy_nc for its transfer leave the same
 * four words. Explicit third-vector pointers change allocation more broadly.
 * -g leaves the baseline unchanged; -fno-expensive-optimizations worsens it.
 * Next useful experiment: explain the two hoisted address spill priorities.
 * All required declarations are below; integrate only in a -g8.c unit.
 */
#include "common.h"
typedef unsigned int EffectQuad __attribute__((mode(TI)));
extern const EffectQuad D_L04_001B0980[3];
extern unsigned char D_L04_002BDAC0[], D_L04_002BDB20[];
extern int D_L04_001B097C __attribute__((sda));
extern unsigned char D_00188660[];
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern float func_0033BB18(float, float);
extern void *func_L00_0033C0D0(void *, void *, void *, void *, int);
extern void func_002E59F8(int);
void func_L04_0040C368(unsigned char *m)
{
    EffectQuad offsets[3];
    float velocity[4];
    float point[4], first[4], second[4], third[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    unsigned char *parameters;
    float strength, scale, fade, spread;
    int i, handle;
    *(EffectQuad *)velocity = 0;
    offsets[0] = D_L04_001B0980[0];
    offsets[1] = D_L04_001B0980[1];
    offsets[2] = D_L04_001B0980[2];
    if (m[0xbc] == 3 || m[0xbc] == 4) D_L04_001B097C = 0;
    strength = *(float *)(p + 0x27c) * 9.999999f;
    if (strength > 1.0f) strength = 1.0f;
    else if (strength < 0.0f) strength = 0.0f;
    scale = *(float *)(p + 0x30c) * 3.0f;
    if (scale > 1.0f) scale = 1.0f;
    else if (scale < 0.5f) scale = 0.5f;
    for (i = 0; i < 3; i++) {
        if (i == 1) parameters = D_L04_002BDB20;
        else parameters = D_L04_002BDAC0;
        func_00283098(&point, &offsets[i], m + 0xc0);
        func_00282CC0(&point, &point, m + 0x10);
        ((float *)&point)[3] = 0.0f;
        qcopy(first, point);
        qcopy(second, point);
        qcopy(third, point);
        spread = strength * 0.01f;
        spread += 0.005f;
        func_002ACB48(&first, spread);
        func_002ACB48(&second, spread);
        func_002ACB48(&third, strength * 0.009f + 0.005f);
        if (strength > 0.0f || D_L04_001B097C > 0 || *(int *)(p + 0x278) > 0) {
            if (strength == 0.0f && *(int *)(p + 0x278) == 0) {
                fade = (float)D_L04_001B097C * 0.033333335f;
                D_L04_001B097C--;
            } else {
                fade = 1.0f;
                D_L04_001B097C = 30;
            }
            spread = strength * 0.01f;
            spread += 0.01f;
            func_002ACB48(&first, spread);
            func_002ACB48(&second, spread);
            ((float *)&velocity)[0] = (func_0033BB18(3.0f, 5.25f) + strength * 2.0f) * 0.016666668f;
            ((float *)&velocity)[0] = -((float *)&velocity)[0];
            ((float *)&velocity)[0] *= scale;
            ((float *)&velocity)[0] *= fade;
            func_L00_0033C0D0(m, &first, &velocity, parameters + 0x30, 1);
            ((float *)&velocity)[0] = (func_0033BB18(1.0f, 2.25f) + strength * 3.0f) * 0.016666668f;
            ((float *)&velocity)[0] = -((float *)&velocity)[0];
            ((float *)&velocity)[0] *= scale;
            ((float *)&velocity)[0] *= fade;
            func_L00_0033C0D0(m, &second, &velocity, parameters + 0x40, 1);
            func_L00_0033C0D0(m, &point, &velocity, parameters + 0x50, 1);
        } else {
            handle = *(int *)(p + 0x714);
            if (handle != -1) {
                unsigned char *record = D_00188660 + handle * 0x70;
                if (*(unsigned char **)(record + 0x88) == m && record[0x74]) func_002E59F8(handle);
            }
            *(int *)(p + 0x714) = -1;
            ((float *)&velocity)[0] = (func_0033BB18(1.5f, 2.5f) + strength * 1.5f) * 0.016666668f;
            ((float *)&velocity)[0] = -((float *)&velocity)[0];
            ((float *)&velocity)[0] *= scale;
            func_L00_0033C0D0(m, &first, &velocity, parameters, 1);
            ((float *)&velocity)[0] = (func_0033BB18(1.5f, 2.5f) + strength * 2.45f) * 0.016666668f;
            ((float *)&velocity)[0] = -((float *)&velocity)[0];
            ((float *)&velocity)[0] *= scale;
            func_L00_0033C0D0(m, &second, &velocity, parameters + 0x10, 1);
            ((float *)&velocity)[0] = (func_0033BB18(1.5f, 2.5f) + strength * 3.25f) * 0.016666668f;
            ((float *)&velocity)[0] = -((float *)&velocity)[0];
            ((float *)&velocity)[0] *= scale;
            func_L00_0033C0D0(m, &third, &velocity, parameters + 0x20, 1);
        }
    }
}
