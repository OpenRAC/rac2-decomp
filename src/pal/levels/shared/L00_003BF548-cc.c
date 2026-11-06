/* func_PAL_L00_003BF548, the PAL copy of func_L00_003BB8B8: the same C. */
#include "common.h"

extern void func_002833F0(void *, void *);
extern void func_00282CC0(void *, void *, void *);
typedef struct { float x, y, z; int unused; float position[4]; } EffectLightRecord;
extern EffectLightRecord D_L00_001C6F40[];
extern void func_L00_003BD510(float *, float *, int, int);
extern void func_L00_003BC998(char *, char *);

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
/* Pass the owner and its pointer at offset 0x68 to the explicitly bound helper; original game role is unknown. */
/* Calls the measured no-argument callee. */
/* Implemented in L00_003B9CB8-state-g8.c. */

/* Integrates motion, reflects a collision, updates the light and emits trail slots. */
/* Opens the block, lays seven oriented sprites over it from two helper draws and the shared
   colour word, then runs the two slot-table passes and closes the block. */
extern int D_L00_0023DDA0[];
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_00282C88(void *);
extern char *func_002AB1F0(char *);
extern void func_L00_003252A8(char *, void *, int);
extern void func_00282D30(void *, void *, float);

/* Claims the first free one of the thirty 0xA0-byte records at D_L00_0023DDA0 for self:
   counts it in self's data, copies self's position, draws three triples from the ranges
   below, stores count, target and the timer, and starts it at target (offset through
   func_L00_003252A8 when func_002AB1F0 finds target's info). */
void func_PAL_L00_003BF548(char *self, char *target, int count)
{
    char *pool = (char *)D_L00_0023DDA0;
    char *position = self + 0x10;
    char *target_position = target + 0x10;
    char *data = *(char **)(self + 0x68);
    char *p;
    char *info;
    float v[4];
    int i;
    for (i = 0; i < 30; i++) {
        p = pool + i * 0xA0;
        if (*(int *)(p + 0x8C) == 0) {
            float max_angle, min_angle;
            float max_scale, min_scale;
            float max_dist, min_dist;
            *(char **)(p + 0x8C) = self;
            (*(int *)(data + 0x54))++;
            qcopy(p + 0x20, position);
            min_angle = -3.14159274101257324219f;
            max_angle = 3.14159274101257324219f;
            min_scale = 0.001f;
            max_scale = 0.005f;
            min_dist = 3.25f;
            max_dist = 4.75f;
            *(float *)(p + 64) = func_002A7878(min_angle, max_angle);
            *(float *)(p + 68) = func_002A7878(min_angle, max_angle);
            *(float *)(p + 72) = func_002A7878(min_angle, max_angle);
            *(float *)(p + 100) = func_002A7878(min_angle, max_angle);
            *(float *)(p + 104) = func_002A7878(min_angle, max_angle);
            *(float *)(p + 108) = func_002A7878(min_angle, max_angle);
            *(float *)(p + 76) = func_002A78D8(min_scale, max_scale);
            *(float *)(p + 80) = func_002A78D8(min_scale, max_scale);
            *(float *)(p + 84) = func_002A78D8(min_scale, max_scale);
            *(float *)(p + 112) = func_002A78D8(min_scale, max_scale);
            *(float *)(p + 116) = func_002A78D8(min_scale, max_scale);
            *(float *)(p + 120) = func_002A78D8(min_scale, max_scale);
            *(float *)(p + 88) = func_002A7878(min_dist, max_dist);
            *(float *)(p + 92) = func_002A7878(min_dist, max_dist);
            *(float *)(p + 96) = func_002A7878(min_dist, max_dist);
            *(float *)(p + 124) = func_002A7878(min_dist, max_dist);
            *(float *)(p + 128) = func_002A7878(min_dist, max_dist);
            *(float *)(p + 132) = func_002A7878(min_dist, max_dist);
            func_00282C88(p);
            func_00282C88(p + 0x10);
            *(int *)(p + 0x94) = count;
            *(int *)(p + 0x98) = count;
            *(char **)(p + 0x90) = target;
            *(int *)(p + 0x9C) = 0;
            *(int *)(p + 0x88) = 17;
            info = func_002AB1F0(target);
            if (info) {
                func_L00_003252A8(target, v, 1);
                func_00282D30(v, v, *(float *)(info + 0x10));
                func_00282CC0(p + 0x30, v, target + 0x10);
            } else {
                qcopy(p + 0x30, target_position);
            }
            break;
        }
    }
}

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
void func_L00_003BD510(float *position, float *direction, int count, int color);

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
