/* Closer B, 2026-11-01: the slot rotation is gcse table size (see MATCHING-BLOCKERS 1). 269 buckets here;
 * forcing 245, 249 or 259 leaves 5 lines, so retail has about 10 to 20 fewer insns at gcse. */
/* Retained nonmatching C; GPT-6.1 Sol (high), measured 29 October 2026.
 * Current checkout profile: -O2 -G8 -ffunction-sections; use a separate -g8.c unit.
 * USA v1.01 check.py: 2532/2532 bytes, 0/27 places; first difference +0x144.
 * Relative to the earlier Sol draft, assigning the final rand result before
 * applying %= 4 fixes all final signed-modulo register differences. The only
 * remaining visible non-relocation differences are 39 stack loads/stores:
 * normal uses 0x148 instead of retail 0x12C, and the seven point/attachment
 * pointer spill slots rotate by four bytes. The frame remains 0x1C0.
 * Full workspace struct and explicit normal alignment are byte-identical to
 * the best source. Explicit late normal-pointer capture changes spill ordering
 * without closing it; capturing all workspace pointers early worsens allocation.
 * Separating center/samples gives 2536/2532 bytes. No forced register/volatile
 * accesses, instruction patches, padding or additional runtime operations used.
 * Final checker: 0 of 27 places match. Ten check.py runs and two allocator
 * diagnostic runs including initial wrong-profile check and final recheck;
 * no linked build or other-release checks. Original INCLUDE_ASM restored.
 * Reopen with evidence for address-expression/pseudo creation and spill order;
 * the modulo expression is resolved. Required declarations follow below.
 */

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
extern float D_L00_0023B510[4][32];
extern float D_L00_002947B0[5][4];
extern float D_L00_001B2850[4] MACRO_ADDR;
extern float D_L00_001AF5F0 __attribute__((sda));
extern float D_L00_001AF5F4 __attribute__((sda));
extern float D_L00_001AF5D8 __attribute__((sda));
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_L00_003A2138(int, float *, int);
extern void func_002A3F10(void *, int, int *, void *);
extern float func_00283198(float), func_00283180(float), func_00283B98(float, float);
extern void func_002830C0(void *, void *, void *);
extern void func_L00_003A2BB8(char *, int, char *, char *);
extern void func_L00_003A25D8(int, int, int, int, float);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern void func_L00_003A2258(void *, void *, void *, void *);
extern void func_L00_003A2408(char *, void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_001163B0(void);
extern void func_L00_003A2C60(void *, int, float);
extern void func_0029FCC0(char *, int, char *);

/* Transform the weapon's animated attachment points and draw its beam network. */
void func_L00_003A1580(void *object)
{
    float points[5][4], attachments[5][4], matrix[4][4];
    float normal[4], side[4], endpoint[4], muzzle[4];
    char *moby = object;
    char *state;
    int lookup, i;
    func_002FC560(0x47, 0x53001ULL);
    state = *(char **)(moby + 0x68);
    func_L00_003A2138((int)moby, D_L00_0023B510[0], 4);
    lookup = 0;
    func_002A3F10(moby, 1, &lookup, matrix);
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
    D_L00_002947B0[1][0] = func_00283198(D_L00_001AF5F0) * 0.015f + 0.4f;
    D_L00_002947B0[1][2] = func_00283180(D_L00_001AF5F0) * 0.0149f;
    D_L00_002947B0[1][1] = -func_00283180(D_L00_001AF5F4) * 0.0151f;
    D_L00_001AF5F0 = func_00283B98(D_L00_001AF5F0, 0.4188790917f);
    D_L00_001AF5F4 = func_00283B98(D_L00_001AF5F4, 0.4130613208f);
    for (i = 0; i < 5; i++)
        func_002830C0(attachments[i], D_L00_002947B0[i], matrix);
    func_L00_003A2BB8(moby, 0, (char *)points[0], (char *)attachments[0]);
    func_L00_003A25D8((int)moby, (int)points[0], 0x7F7F2020, 0x40, 0.11f);
    func_L00_003A25D8((int)moby, (int)points[0], 0x7FFF4040, 0x78, 0.05f);
    func_L00_003A2BB8(moby, 0, (char *)points[1], (char *)attachments[1]);
    if (D_L00_001B2850[3] == -1.0f) {
        qcopy(D_L00_001B2850, points[1]);
        D_L00_001B2850[3] = 0.0f;
    } else {
        int changed = 0;
        func_002AA458(D_L00_001B2850, points[1], &changed, 0.25f, 0.2000000179f, 0.5f);
    }
    func_L00_003A25D8((int)moby, (int)D_L00_001B2850, 0x7F00397F, 0x40, *(float *)(state + 0xC) * 0.1856249869f);
    func_L00_003A25D8((int)moby, (int)D_L00_001B2850, 0x7F0072FF, 0x78, *(float *)(state + 0xC) * 0.08437500149f);
    func_L00_003A2BB8(moby, 1, (char *)points[2], (char *)attachments[2]);
    func_L00_003A25D8((int)moby, (int)points[2], 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)points[2], 0x7FFF4040, 0x78, 0.025f);
    func_L00_003A2BB8(moby, 2, (char *)points[3], (char *)attachments[3]);
    func_L00_003A25D8((int)moby, (int)points[3], 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)points[3], 0x7FFF4040, 0x78, 0.025f);
    func_L00_003A2BB8(moby, 3, (char *)points[4], (char *)attachments[4]);
    func_L00_003A25D8((int)moby, (int)points[4], 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)points[4], 0x7FFF4040, 0x78, 0.025f);
    func_L00_003A2258(moby, points[0], D_L00_001B2850, D_L00_0023B510[0]);
    func_L00_003A2408(moby, D_L00_001B2850, normal, *(float *)(state + 0xC) * 0.35f);
    func_00282CF0(side, D_L00_001B2850, points[2]);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, *(float *)(state + 0xC) * 0.45f);
    func_00282CC0(endpoint, side, D_L00_001B2850);
    func_L00_003A2258(moby, points[2], endpoint, D_L00_0023B510[1]);
    func_L00_003A25D8((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        func_L00_003A2C60(endpoint, 1, 0.0f);
    func_00282CF0(side, D_L00_001B2850, points[3]);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, *(float *)(state + 0xC) * 0.45f);
    func_00282CC0(endpoint, side, D_L00_001B2850);
    func_L00_003A2258(moby, points[3], endpoint, D_L00_0023B510[2]);
    func_L00_003A25D8((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        func_L00_003A2C60(endpoint, 1, 0.0f);
    func_00282CF0(side, D_L00_001B2850, points[4]);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, 1.0f);
    func_00282DD8(side, side, normal);
    func_00282F20(side, side, *(float *)(state + 0xC) * 0.45f);
    func_00282CC0(endpoint, side, D_L00_001B2850);
    func_L00_003A2258(moby, points[4], endpoint, D_L00_0023B510[3]);
    func_L00_003A25D8((int)moby, (int)endpoint, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)endpoint, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        func_L00_003A2C60(endpoint, 1, 0.0f);
    func_0029FCC0(moby, 1, (char *)muzzle);
    func_L00_003A2258(moby, muzzle, points[2], D_L00_0023B510[3]);
    func_L00_003A25D8((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    func_0029FCC0(moby, 2, (char *)muzzle);
    func_L00_003A2258(moby, muzzle, points[3], D_L00_0023B510[2]);
    func_L00_003A25D8((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    func_0029FCC0(moby, 3, (char *)muzzle);
    func_L00_003A2258(moby, muzzle, points[4], D_L00_0023B510[1]);
    func_L00_003A25D8((int)moby, (int)muzzle, 0x7F7F2020, 0x40, 0.055f);
    func_L00_003A25D8((int)moby, (int)muzzle, 0x7FFF4040, 0x78, 0.025f);
    if (func_001163B0() % 11 == 0) {
        int selected = func_001163B0();
        selected %= 4;
        func_L00_003A2C60(points[selected + 1], 1, 0.001f);
    }
    func_002FC560(0x47, 0x5360BULL);
}
