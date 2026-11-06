/* func_PAL_002C7598, the PAL copy of func_002C6868: the same C, where wrap (control- becomes scale - 1.0f) (({e}) * 1.2f); rename func_00282D30_12 becomes func_00282D30; rename func_00282CC0_17 becomes func_00282CC0; rename func_00283CE0_2 becomes func_00283CE0. */
#include "common.h"
extern float func_002A78D8(float, float);
/* Copy the xyz components and clear the fourth word. Adapted from RAC1. */

extern int func_00277F48(float, void *, int, int, int);
extern char D_00189EA0[];

extern int func_00283D38(int,int,float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern unsigned char *D_001F25F4, *D_001F26A8;
extern int func_002A9568(int, int, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7940(void);
extern int func_002AAE98(float, float, float, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern int func_002A8860(void *, int);
extern void func_0029FCC0(void *, int, void *);

/* Qwen draft (branch qwen/autonomy, c8b09022), checked by tools/check.py */
void func_002B9180(void *);

int func_00282978(short *);

extern int func_00282978_9(char *p);

extern void func_002B9180_13(char *self);

extern float func_00283CE0_2(int v);

extern int func_00283CF0_6(float f);

extern void func_00282CC0_17(char *dst, char *src, char *vec);

extern void func_00282D30_12(char *dst, char *table, float scale);

typedef struct { unsigned int f0, f4, f8, f12, f16, f20; } T;

struct T {
    float a;
    float b;
    int c;
    int d;
    float e;
};

#ifndef RAC2_T_S16_F570CFB4B
#define RAC2_T_S16_F570CFB4B
#endif

#ifndef RAC2_T_OBJ_F7CACD225
#define RAC2_T_OBJ_F7CACD225
#endif

#ifndef RAC2_T_VEC16_F9A4B4D8B
#define RAC2_T_VEC16_F9A4B4D8B
#endif

#ifndef RAC2_T_V4_FC3CB9262
#define RAC2_T_V4_FC3CB9262
#endif

/* func_002BF728 uses the quadword-copy profile in 002BF728-qcopy.c. */

extern int func_002A77E0(int);
extern void func_00282CC0(char *, char *, char *);
extern float func_00283180(float);
extern float func_00283198(float);
/* Advances one object: the halfword at offset 10 is capped at 12 and, when the
   sub-object's float at 0x30 is below the object's float at 0x18, the word at
   offset 4 is cleared; the packed byte in that word is then rescaled by the
   halfword, the float at offset 12 grows by 840.0f and is limited by the
   sub-object's float at 0x3C, the object's vector is moved by the sub-object's
   motion triple and the last pair of floats is written back from the angle
   kept in the sub-object. */
extern int func_002761F8(void *, void *, int, void *, void *);
extern void *func_002C19D8(void *, float, void *, float, int);
/* func_002BFE80 is defined in 002BFE80-dbg.c. */

extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float D_001B5340[];
/* func_002C01F8 is in 002BF6F0-c01f8-g8.c. */

/* func_002C02F0 uses the quadword-copy profile in 002C02F0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
/* func_002C0CC0 uses the quadword-copy profile in 002C0CC0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
/* Updates one byte-addressed object by packing a converted short-ratio value with three bytes, applying the bound helper sequence to three stored floats, and accumulating one byte and one float. */
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern unsigned char *D_001F25F4;

void *func_002C19D8(void *position, float size, void *owner, float spin, int color);

/* func_002C1B38 is in the -G8 sibling. */

extern float func_00282C48(float);

extern void func_00282CC0(char *, char *, char *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);

/* func_002C1FC0 is defined in 002BF6F0-g8.c. */

/* Tests the halfword at offset 10 through a helper; on zero it stores a scaled int at offset 4 and a 210000.0f-scaled interpolation of two floats at offset 12, otherwise calls a second helper. */
/* Move a particle while tweening its size and alpha, then apply gravity. */
extern int func_00277F48(float, void *, int, int, int);

extern float func_00283CE0(int);

extern int func_002AAE98(float, float, float, float);

#ifndef RAC2_T_VEC16_F5621621C
#define RAC2_T_VEC16_F5621621C
#endif

/* Updates one object: it copies its vector into a local, adds the two motion
   floats and hands the result with the motion's third float to a helper, then
   bails out through the second helper when the halfword at offset 10 is
   taken. Otherwise it packs a colour from the halfword and pushes the object
   through a vector helper with the table at D_001BF000. The two words the
   first helper writes (n and f) are the retail's scratch out-parameters: it
   never reads them back. The words at offsets 0x20 and 0x34 are 32-bit in the
   object and the helpers take them as pointers, so they are cast on the way
   out. */
extern int func_00283CF0(float);

/* A drifting spark: moves by its velocity, spins, slows its fall and fades over its last
   64 frames; it frees itself when the count runs out. */
/* func_002C2A88 uses the quadword-copy profile in 002C2A88-qcopy.c. */

extern char D_00189EA0[];
/* rac1-decomp src/overlays/shared/alpha_fade_particle_updates.c: func_002C2FD8 */
/* spawns particle type 0x3B from a position, colour index and flags */
extern void func_00282CC0(char *, char *, char *);

/* Creates a particle at POS moving by VEL; in mode 1 it also keeps its offset from the
   resident view origin. */
/* func_002C3150 uses the quadword-copy profile in 002C3150-qcopy.c. */

/* advances three floats of a sub-object by a resident offset triple, calls a three-pointer update, subtracts the offsets back out, rejects the result when any coordinate leaves the 2.0..1021.0 band, and otherwise rescales a 24-bit handle by the ratio of two helper lookups over a signed halfword index */
/* func_002C3430 uses the hazard-label profile in 002C3430-fade.c. */

/* func_002C38E0 is in the -G8 sibling. */

/* Advances a spark, stops it on collision, and decays its RGBA channels. */
/* func_002C3D80 uses the quadword-copy profile in 002C3D80-qcopy.c. */

/* func_002C3F88 uses the quadword-copy profile in 002C3F88-qcopy.c. */

/* Updates an attached spark and emits children; mode 1 orbits its owner.
 * The interleaved prototype preserves each EE argument register bank. */
/* Follows a selected attachment, randomizes its rotation, and fades by lifetime. */
extern float func_002A78D8(float, float);
extern float func_00283CE0(int);

/* decrements a signed short counter and, at zero, rotates a 24-bit identifier beside it and reloads the counter; calls a helper when the identifier's top byte is clear */
/* Pulls toward a target, blends colour by distance, then advances through
 * three timed movement/fade phases. */
/* func_002C4B50 is in 002BF6F0-c4b50.c. */

/* func_002C4D18 is in 002BF6F0-c4b50.c. */

extern float func_00283CE0_2(int v);
extern int func_00283CF0_6(float f);
extern void func_00282CC0_17(char *dst, char *src, char *vec);
extern int func_00282978_9(char *p);
extern void func_002B9180_13(char *self);

/* The particle update: the quad at 0x20 is copied to the stack, the value of
   the helper at 0xA is divided by the copy's fourth float, the two scaled
   results are packed into the word at 4 and the byte at 8. */
/* func_002C5120 is in 002BF6F0-c5120-g8.c. */

/* func_002C56B0 uses the quadword-copy profile in 002C56B0-qcopy.c. */

/* func_002C5B70 uses the quadword-copy profile in 002C5B70-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
/* func_002C6360 is in the -G8 sibling (its two globals are read through $gp). */

extern float func_00283198(float);
extern int func_00283CF0(float);

/* func_002C65A0 is in 002BF6F0-c65a0.c. */

/* If a probe call on a sub-object returns zero, folds a byte counter into the top byte of a packed word, rebuilds a 16-byte vector from two sub-records for a helper, then clamps a running float against a limit and accumulates two sub-record fields into the object. */
typedef struct {
    int *colors;
    short *sizes;
    short *times;
    short last_index;
    short reserved0E;
    short lifetime;
    short reserved12;
    float scale;
} ParticleKeyframes;
extern int func_002A9568(int, int, float);

void func_PAL_002C7598(char *self)
{
    char *motion = self + 0x20;
    ParticleKeyframes *control = *(ParticleKeyframes **)(motion + 0x10);
    short elapsed;
    float duration, factor;
    func_00282D30_12(motion, motion, (((control->scale - 1.0f)) * 1.2f) + 1.0f);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(unsigned char *)(self + 8) += *(unsigned char *)(motion + 0x18);
    elapsed = control->lifetime - *(short *)(self + 0xA);
    if (control->times[*(short *)(motion + 0x14) + 1] < elapsed &&
        *(short *)(motion + 0x14) < control->last_index)
        ++*(short *)(motion + 0x14);
    duration = func_00283CE0_2(control->times[*(short *)(motion + 0x14) + 1] -
        control->times[*(short *)(motion + 0x14)]);
    factor = (float)(elapsed -
        control->times[*(short *)(motion + 0x14)]) / duration;
    *(int *)(self + 4) = func_002A9568(
        control->colors[*(short *)(motion + 0x14)],
        control->colors[*(short *)(motion + 0x14) + 1], factor);
    *(float *)(self + 0xC) =
        ((float)control->sizes[*(short *)(motion + 0x14)] +
         factor * (float)(control->sizes[*(short *)(motion + 0x14) + 1] - control->sizes[*(short *)(motion + 0x14)])) * 1000.0f;
    if (func_00282978((short *)(self + 0xA)))
        func_002B9180(self);
}

/* Follows a sound emitter's moby: fades its volume byte (the top byte of +4) up by 4
   toward the target while the moby is visible and active, else down by 4 to zero,
   then places the emitter at the moby (or at its joint, pulled 0.4 of the way toward
   the camera). A dead or dying moby (state 0xFE/0xFD) or none lets the emitter finish
   and frees it. */
extern float D_001B5340[];
extern int func_002A8860(void *, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);

/* Follows the particle's target (or one of its joints): the alpha fades towards the limit
   while the target is shown and out otherwise; a missing or dying target fades the particle
   out and frees it. The second read of the colour word is the retail copy kept by GCSE. */
/* func_002C7050 is defined in 002BF6F0-trail-g8.c. */

/* Delay movement and the size/alpha tween until the secondary timer fires. */
