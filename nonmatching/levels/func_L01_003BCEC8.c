/* Retained debris-state reconstruction, 2026-10-28: 604/636B,0/1US.
 * One semantic trial, no tuning through the measured unaligned transfer.
 * Retail +214 A0=private+8; +218 SQ zero,0(A0) rounds effective address down
 * to16B. The approved helper requires aligned addresses. This draft models
 * aligned private storage (as the neighboring matched constructor expects)
 * and clears its first complete16B instead; it cannot reproduce retail's
 * different +8 address expression without violating that helper contract.
 * L01_003BCA38 writes full private vectors at0/10/20 and scalar40/44, but
 * actual allocator alignment is not independently proved here. No C credit.
 * Do not replace the aligned zero by an unaligned TI cast or qzero(state+8).
 * Private extent48B covers timer30, gravity38/3C, angles40/44. Scratch16B.
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
extern int func_002761F8(void *, void *, int, void *, void *);
extern float D_L01_001AFE30_gp SDATA(D_L01_001AFE30);
extern float D_L01_001BF920[];

void func_L01_003BCEC8(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float previous[4] __attribute__((aligned(16)));
    float value, z;
    qcopy(previous, object + 0x10);
    switch (object[0x20]) {
    case 1:
        if (func_00282948(state + 0x30)) {
            object[0x20] = 2;
            goto settle;
        }
        break;
    case 2:
        if (func_00282948(state + 0x30)) {
            func_0029F338(object);
            return;
        }
        object[0x23] = func_00283CF0((float)*(int *)(state + 0x30) * 12.800000190734863f);
        break;
    }
    value = func_00283B98(*(float *)(state + 0x40), 0.03490659222006798f);
    *(float *)(state + 0x40) = value;
    value = func_00283198(value);
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), *(float *)(state + 0x18) * value);
    value = *(float *)(object + 0xF0);
    *(float *)(object + 0xF0) = value + (*(float *)(state + 0x44) - value) * 0.02f;
    if (object[0x20] != 2) {
        *(float *)(object + 0xF4) = func_00283180(*(float *)(state + 0x40)) * 0.174532949924469f;
        z = *(float *)(state + 8);
        *(int *)(state + 8) = 0;
        func_00282D30(state, state, D_L01_001AFE30_gp);
        *(float *)(state + 8) = z;
        func_00282CC0(object + 0x10, object + 0x10, state);
        value = *(float *)(state + 8) - *(float *)(state + 0x38);
        *(float *)(state + 8) = value;
        if (value < *(float *)(state + 0x3C))
            *(float *)(state + 8) = *(float *)(state + 0x3C);
    } else {
        value = *(float *)(object + 0xF4);
        *(float *)(object + 0xF4) = value + (0.174532949924469f - value) * 0.1f;
    }
    previous[2] += 1.0f;
    if (func_002761F8(previous, object + 0x10, 2, object, 0)) {
        qcopy(object + 0x10, D_L01_001BF920);
        /* Retail SQ private+8 rounds down to private+0. The constructor
         * copies full vectors to private+0/+10 under the reviewed alignment
         * contract; the raw allocator alignment was not independently proved.
         * Use aligned ownership here; this intentionally cannot claim the
         * retail address-building instructions as a matching C candidate. */
        qzero(state);
        *(int *)(state + 0x38) = 0;
        qzero(state + 0x10);
        if (object[0x20] != 2) {
            object[0x20] = 2;
settle:
            *(int *)(state + 0x30) = func_00283CF0(10.0f);
            *(u16 *)(object + 0x34) |= 0x2000;
        }
    }
}
