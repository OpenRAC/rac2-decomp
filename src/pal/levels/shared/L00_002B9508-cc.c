/* func_PAL_L00_002B9508, the PAL copy of func_L00_002B9598: the same C, where rename-macro func_L00_002B4458 becomes func_PAL_L00_002B4380; lit 0.2f becomes 0.28800002f; rename func_00282CC0_3 becomes func_00282CC0; rename func_00282C88_5 becomes func_00282C88; rename func_00282E20_3 becomes func_00282E20; rename func_00282CF0_3 becomes func_00282CF0; rename func_00283248_5 becomes func_00283248; rename func_00282D30_4 becomes func_00282D30. */
#include "common.h"

#ifndef RAC2_T_TI_F41EB487E
#define RAC2_T_TI_F41EB487E
typedef int TI_F41eb487e __attribute__((mode(TI)));
#endif

extern void func_00282D30(void *a, void *b, float value);

extern void func_00282CF0(void *a, void *b, void *c);

extern void func_00282CC0(void *a, void *b, void *c);

#ifndef RAC2_T_VEC4_F41EB487E
#define RAC2_T_VEC4_F41EB487E
#endif

#ifndef RAC2_T_RESIDENTSTATE_F41EB487E
#define RAC2_T_RESIDENTSTATE_F41EB487E
typedef struct {
    u8 pad000[0x80];
    u8 area080[0x218 - 0x80];
    short h218;
    u8 pad21a[0x2a0 - 0x21a];
    TI_F41eb487e q2A0;
    u8 pad2b0[0x2c0 - 0x2b0];
    u8 area2C0[0x31c - 0x2c0];
    float f31C;
    u8 pad320[0x34e - 0x320];
    short h34E;
    u8 pad350[0x22c3 - 0x350];
    u8 b22C3;
} ResidentState_F41eb487e;
#endif

extern ResidentState_F41eb487e D_00189E20_5;

extern void func_00282C88(void *a);

extern float func_00283248(float a, float b);

extern float func_00282E20(void *p);

typedef struct {
    u8 pad0[0x88];
    float f88;
    u8 pad8c[0xc];
    float f98;
    u8 pad9c[0x54];
    float vf0[4];
    u8 pad100[0x40];
    float v140[4];
    u8 pad150[0x20];
    float f170;
    u8 pad174[0x2c];
    float f1a0;
    u8 pad1a4[0xc];
    float f1b0;
    u8 pad1b4[0x4];
    int f1b8;
    u8 pad1bc[0xe4];
    float v2a0[4];
    u8 pad2b0[0x68];
    float f318;
    u8 pad31c[0x4];
    float f320;
    float f324;
    u8 pad328[0xd8];
    float f400;
    float f404;
    u8 pad408[0x658];
    float va60[4];
    float fa70;
    u8 pada74[0x1820];
    int f2294;
    u8 pad2298[0x220];
    float f24b8;
} State9598;
extern State9598 D_00189E20_9598;
extern void func_L00_002B39F0(int, float);
extern void func_L00_002B3EF8(int, float, float, float);
extern void func_L00_002B54F8(float, float);
extern void ref_L00_002B9598_0(int);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282C48(float);
extern int D_00138354;

/* initialises three 16-byte records, folds a resident 32-byte quad into the first of them, then for the stored mode 2 runs a four-argument fallback and for mode 1 with a short or low field re-copies the resident quad; finally scales and copies the two remaining records through three more calls */
/* reads a scalar through DATA0 and, when it exceeds 0.001f, re-normalises the vector at DATA0 (and DATA0-112) from the elapsed float, clamping the amount at zero; otherwise it runs the plain refresh entry point. */
void func_PAL_L00_002B9508(void)
{
    float desired[4] __attribute__((aligned(16)));
    float original[4] __attribute__((aligned(16)));
    float previous[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float correction[4] __attribute__((aligned(16)));
    float x, limit, t, angle, scale, step, length, adjustment;
    func_L00_002B39F0(0, 1.0f);
    func_L00_002B3EF8(0, 0.028800001f, 0.28800002f, 0.07330384f);
    if (D_00189E20_9598.f2294 == 19) {
        if (D_00189E20_9598.f24b8 < 0.2f) D_00189E20_9598.f1a0 = D_00189E20_9598.f98;
        D_00189E20_9598.f1b0 = 0.4f;
    } else if (D_00189E20_9598.f2294 == 21) D_00189E20_9598.f1b0 = 0.0f;
    desired[0] = func_00283180(D_00189E20_9598.f1a0) * D_00189E20_9598.f1b0 * 0.11800001f;
    desired[1] = func_00283198(D_00189E20_9598.f1a0) * D_00189E20_9598.f1b0 * 0.11800001f;
    desired[2] = 0.0f;
    qcopy_nc(original, desired);
    if (D_00189E20_9598.fa70 > 0.0f) {
        func_L00_002B54F8(0.7f, 0.0f);
        qcopy_nc(previous, D_00189E20_9598.va60);
        func_00282CC0(desired, desired, D_00189E20_9598.va60);
        func_00282C88(D_00189E20_9598.va60);
    }
    x = -(D_00189E20_9598.vf0[0] * desired[0] + D_00189E20_9598.vf0[1] * desired[1]);
    if (x > 0.0f) {
        x /= func_00282E20(desired);
        x /= func_00282E20(D_00189E20_9598.vf0);
    }
    if (x > 1.0f) x = 1.0f;
    if (x < 0.0f) x = 0.0f;
    limit = D_00189E20_9598.f1b0 * 0.00098f;
    limit += x * 0.00080000004f;
    if (D_00138354) limit = 0.00044000003f;
    if (D_00189E20_9598.f2294 == 19 && D_00189E20_9598.f1b8 < 12 && D_00189E20_9598.f170 < 0.060000002f)
        limit = 0.0044f;
    if (D_00189E20_9598.f170 > 0.11800001f) limit = 0.0052000005f;
    if (D_00189E20_9598.fa70 > 0.0f) {
        x = -func_00282DB0(original, previous);
        length = func_00282DF0(original);
        if (length > 0.0f) x /= length;
        length = func_00282E20(previous);
        adjustment = (length - x) / length * 0.0012f;
        if (D_00189E20_9598.f24b8 < 0.3f && adjustment < 0.0012f) adjustment = 0.0012f;
        if (limit < adjustment) limit = adjustment;
    }
    func_00282CF0(delta, desired, D_00189E20_9598.v140);
    delta[2] = 0.0f;
    if (func_00282DF0(delta) > limit) func_00282F20(delta, delta, limit);
    func_00282CC0(D_00189E20_9598.vf0, D_00189E20_9598.v140, delta);
    if (D_00189E20_9598.f320 > 0.087266475f) {
        angle = func_00283248(D_00189E20_9598.v2a0[0], D_00189E20_9598.v2a0[1]);
        scale = D_00189E20_9598.f320 * 0.20371832f;
        step = D_00189E20_9598.f320 * 0.004329014f;
        delta[0] = func_00283180(angle) * scale;
        delta[1] = func_00283198(angle) * scale;
        delta[2] = 0.0f;
        func_00282CF0(correction, delta, D_00189E20_9598.vf0);
        correction[2] = 0.0f;
        if (func_00282DF0(correction) > step) func_00282F20(correction, correction, step);
        func_00282CC0(D_00189E20_9598.vf0, D_00189E20_9598.vf0, correction);
    }
    qcopy_nc(delta, D_00189E20_9598.vf0);
    delta[2] = 0.0f;
    D_00189E20_9598.f400 = func_00282DB0(delta, desired);
    t = func_00282DF0(desired);
    if (t > 0.0f) D_00189E20_9598.f400 /= t * 0.11800001f;
    ref_L00_002B9598_0(0);
    if (D_00189E20_9598.f404 < 0.017453294f && D_00189E20_9598.f324 > 0.087266475f)
        func_00282D30(D_00189E20_9598.vf0, D_00189E20_9598.vf0, func_00283180(D_00189E20_9598.f324));
    D_00189E20_9598.f404 = D_00189E20_9598.f324;
    if (func_00282C48(D_00189E20_9598.f88 - D_00189E20_9598.f318) < 0.15f) D_00189E20_9598.f88 = D_00189E20_9598.f318;
}

/* The resident block the slot table lives in, and the two vector helpers. */
extern float func_00283248(float a, float b);

/* Transform the direction into resident space and return its selected angle delta. */
/* The resident id this forwards, and the helper it calls. */
/* Forward the sound index, flags and resident object pointer; return the result. */
/* Claims the first free slot of the eight 8-byte entries at resident +0x23EC: a slot whose
   leading short is clear takes the three arguments, a pending marker and its two extra
   fields, and the search stops at the first one taken. */
/* The eight 8-byte entries func_L00_002B9C58 claims at resident +0x23EC. */
/* Ticks the timer of each of the eight entries; one whose timer reports 2 is cleared and
   fires: id 0x16 calls func_L00_002A61C8 with the resident byte at +0x149D, any other id
   goes to func_L00_002B9B88 with the entry's argument. */
/* The resident block, as far as func_L00_002B9D60 touches it. */
/* Reset the hero position and direction, the resident movement state and the related level objects. */
/* queries a resident table with a stack request and blends a vector back into the resident record */
/* The resident fields func_L00_002BA508 reads and writes. */
typedef struct {
    u8 pad0[0x184];
    float f184;
    u8 pad188[0x1B8 - 0x188];
    int i1B8;
    u8 pad1bc[0x278 - 0x1BC];
    float f278;
    u8 pad27c[0x280 - 0x27C];
    float f280;
    u8 b284;
    u8 pad285[0xC04 - 0x285];
    float fC04;
    float fC08;
    u8 padc0c[0x1220 - 0xC0C];
    char *p1220;
    u8 pad1224[0x123A - 0x1224];
    u8 b123A;
    u8 pad123b[0x1500 - 0x123B];
    int i1500;
    u8 pad1504[0x1A30 - 0x1504];
    u8 area1A30[0x2290 - 0x1A30];
    char *p2290;
    int i2294;
} ResidentState_A508;

extern ResidentState_A508 D_00189E20_A508;

/* The level vector at +0x150 of the block func_L00_002BA410 queries. */
extern void func_00282C88(void *m);
/* Once per hero state, set up the object at resident +0x1220 (the special case uses a stored angle
   and the level vector at +0x150 of the block func_L00_002BA410 queries, otherwise the unit scale
   and the parent transform) and pass the composed transform to the object at +0xF0.
   Does nothing once the byte at +0x123A is set. */
