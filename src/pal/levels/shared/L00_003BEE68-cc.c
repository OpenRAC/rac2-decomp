/* func_PAL_L00_003BEE68, the PAL copy of func_L00_003BB1F8: the same C, where rename func_L00_003BD510 becomes func_PAL_L00_003C11A0; scale (char *)func_002A7820_1(8, 20); rename func_002EE178_1 becomes func_00282D30; rename func_802EE3D0_1 becomes func_00282F20; rename func_802EE138_1 becomes func_00282CF0; rename func_002A7878_2 becomes func_002A7878; rename func_002A7820_1 becomes func_002A7820. */
#include "common.h"

extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_002833F0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00300248(void *, void *);
extern float func_00282DF0(void *);
extern void func_002ACF68(void *, void *, void *, int, float);
extern int func_00277258(void *, int, void *, float);
extern char *D_L00_001BF218;
extern char *D_0018C0B0;
extern char D_L00_001BF230[];
typedef struct { float x, y, z; int unused; float position[4]; } EffectLightRecord;
extern EffectLightRecord D_L00_001C6F40[];
extern float func_00282DB0(void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_PAL_L00_003C11A0(float *, float *, int, int);
extern void func_002E5CF8(int, int, void *);
extern void func_L00_003BC998(char *, char *);

extern void func_802EE138_1(float *off, float *v, char *p);

extern void func_802EE3D0_1(float *dst, float *src, float angle);

extern void func_002EE178_1(char *dst, char *src, float scale);
/* The vector the aim helpers read, at 0x001B8C80. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector D_L00_001B8C80;

/* The 128-bit unit four of these bodies copy whole. */
/* Measured partial layouts; original type and game roles are unknown. */
#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
#endif

/* Measured partial layouts; original type and game roles are unknown. */
extern float func_002A7878_2(float a, float b);

extern unsigned int func_002A7820_1(int a, int b);

/* Pass the owner and its pointer at offset 0x68 to the explicitly bound helper; original game role is unknown. */
/* Calls the measured no-argument callee. */
/* Implemented in L00_003B9CB8-state-g8.c. */

/* Integrates motion, reflects a collision, updates the light and emits trail slots. */
char *func_PAL_L00_003BEE68(char *self)
{
    float saved[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float projection[4] __attribute__((aligned(16)));
    float remainder[4] __attribute__((aligned(16)));
    char *ctx = *(char **)(self + 0x68);
    char *hit = 0;
    char *p;
    EffectLightRecord *light;
    int light_index;
    float f;
    *(float *)(self + 0xF0) = func_00283B98(*(float *)(self + 0xF0), 0.062831864f);
    *(float *)(self + 0xF4) = func_00283BE0(*(float *)(self + 0xF4), 0.015707966f);
    *(int *)(self + 0xFC) = 0;
    func_002833F0(self + 0xC0, self + 0xF0);
    qcopy(saved, self + 0x10);
    func_00282CC0(self + 0x10, ctx, self + 0x10);
    func_002FEE70(*(int *)(ctx + 0x50), ctx, 0);
    func_00300190(self + 0x10, self + 0x10);
    func_00300248(ctx, ctx);
    if (func_00282DF0(ctx) != 0.0f && func_00282DF0(ctx + 0x20) != 0.0f)
        func_002ACF68(ctx, ctx, ctx + 0x20, 0, 0.075f);
    if (func_00277258(self + 0x10, 0, self, *(float *)(ctx + 0x4C))) {
        p = D_L00_001BF218;
        if (p && p != D_0018C0B0 && *(short *)(p + 0xAA) != 0x5CA)
            hit = (*(unsigned short *)(p + 0x34) & 0x1000) ? p : 0;
        qcopy(self + 0x10, D_L00_001BF230);
        func_002EE178_1((char *)normal, D_L00_001BF230 + 0x10, 0.0009765625f);
        func_802EE3D0_1(normal, normal, 1.0f);
        func_00283028(ctx, ctx, normal);
        f = func_00282DB0(ctx, normal);
        func_002EE178_1((char *)projection, (char *)normal, f);
        func_802EE138_1(remainder, (float *)ctx, (char *)projection);
        func_002EE178_1(ctx, (char *)projection, 0.85f);
        func_00282CC0(ctx, remainder, ctx);
        func_002EE178_1(ctx + 0x20, ctx + 0x20, 0.95f);
        func_PAL_L00_003C11A0(D_L00_001BF230 - 0x10, normal, 6, 0x72FF);
        func_PAL_L00_003C11A0(D_L00_001BF230 - 0x10, normal, 6, 0xFF0000);
        func_002E5CF8(1, 0, self);
    }
    light_index = *(int *)(ctx + 0x5C);
    if (light_index != -1) {
        light = D_L00_001C6F40 + light_index;
        qcopy(light->position, self + 0x10);
        light->position[3] = 4.0f;
        light->x = 0.25f;
        light->y = 0.14f;
        light->z = 1.0f;
        light->unused = 0;
        f = func_002A7878_2(-0.1f, 0.1f);
        light->x += f;
        light->y += f;
        light->z += f;
    }
    if (*(float *)(self + 0x10) < 2.0f || *(float *)(self + 0x10) > 1021.0f ||
        *(float *)(self + 0x14) < 2.0f || *(float *)(self + 0x14) > 1021.0f ||
        *(float *)(self + 0x18) < 2.0f || *(float *)(self + 0x18) > 1021.0f) {
        qcopy(self + 0x10, saved);
        self[0x20] = 3;
    }
    if (*(int *)(ctx + 0x58) < 8)
        func_L00_003BC998(self, (((int)((char *)func_002A7820_1(8, 20)) * 5 + 2) / 6));
    return hit;
}

/* Opens the block, lays seven oriented sprites over it from two helper draws and the shared
   colour word, then runs the two slot-table passes and closes the block. */
/* Claims the first free one of the thirty 0xA0-byte records at D_L00_0023DDA0 for self:
   counts it in self's data, copies self's position, draws three triples from the ranges
   below, stores count, target and the timer, and starts it at target (offset through
   func_L00_003252A8 when func_002AB1F0 finds target's info). */
/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
/* Implemented in L00_003B9CB8-ribbons.c. */

/* Measured partial layout of one 0xB0-byte record of the table at D_L00_0023F060. */
typedef struct Rac2Native_003BC998_Slot {
    unsigned char prefix_00[0x50];
    float f_50;
    float f_54;
    float f_58;
    float f_5C;
    float f_60;
    float f_64;
    float f_68;
    float f_6C;
    float f_70;
    float f_74;
    float f_78;
    float f_7C;
    float f_80;
    float f_84;
    float f_88;
    float f_8C;
    float f_90;
    float f_94;
    void *w_98;
    void *w_9C;
    void *owner_A0;
    unsigned char tail_A4[0xC];
} Rac2Native_003BC998_Slot;

extern Rac2Native_003BC998_Slot D_L00_0023F060[];

/* Claims the first free record of the sixteen 0xB0-byte records at D_L00_0023F060, keeps the
   owner's pointer in it and fills the drawn values. The base and the output pointer are kept
   in their own variables, and the two owner words are stored in the order 0x9C, 0x98, so that
   cc1 keeps the table base and the output pointer in registers and fills the delay slots the
   way retail does. */
void func_L00_003BC998(char *owner, char *arg1);

/* Near miss: nonmatching/levels/func_L00_003BCDC0.c - every instruction present but the
   loop test is `sltu` here against retail's `slt`, and the base is derived from the end
   pointer instead of being materialised on its own. */

/* Emits count pairs of sparks at position, moving along direction turned by a random rotation;
   position is jittered a little before each pair. Both arms of the random-bit test are the same
   code: retail keeps the test, so it stays. */
void func_PAL_L00_003C11A0(float *position, float *direction, int count, int color);

/* func_L00_003BD7E0 is in L00_003B9CB8-update.c. */

/* Normalises and combines two temporary vectors from a state block, dispatches on the combined result and conditionally scales the output vector. */
/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
/* The four floats are declared before the two other arguments, which sets the order this caller
   evaluates them in (the registers are the same either way). */
extern void func_002833F0(void *out, void *in);

/* Copies the caller's 16-byte block into a stack scratch area, runs the three-argument starter on
   it, then fills the scratch area's upper half from the state block's 0xB4 float and the pair
   helper before folding the starter's result against the state's own reading of that float. One
   `char scratch[0x50]` gives retail's frame. The 16-byte clear is retail's `sq $zero,0($sp)`:
   with the scheduling barrier of zero_ti_store_barrier.py it takes retail's place, and so does
   the prologue's save order. */
/* shared native body of family a04928c6 */
/* Twenty rounds of four bound helpers on three 16-byte scratch vectors, the first of which
   starts as the second argument's record; each round ends with the eleven-argument emitter. */
/* Two-state gate on the record's byte 0x20 (the same body as func_L09_003C8CD8, which
   the level 09 file already carries). In state 0, as long as the live word the sub-object
   opens with is not -1, the record is stamped 0xFF, the shared eight-argument starter is
   run on the sub-object's track block and the record flips to state 1. In state 1 the
   sub-object's first float is scaled by 2*pi/21600 (a per-frame 1/100 s turn rate) and
   folded into the record's own angle before its track block is stepped again. */
/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
/* The 0x68 context block starts with two words and a halfword that this body clears. */
/* Runs 20 local iterations; the first two calls each pass integer 2 to the same bound target; on each non-null final result, stores a short at +10, an int at +36, and bytes at +42 and +43. */
/* func_L00_003C58E8 is in L00_003C58E8-qcopy.c. */

/* Implemented in L00_003C58E8.c. */

/* one float gate followed by five integer gates; every failing gate */
