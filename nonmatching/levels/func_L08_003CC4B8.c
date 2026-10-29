/* Bounded near miss, 2026-10-28: default game profile664/664 bytes.
 * Five forms fix full C0 frame, persistent constants, byte-angle truncation
 * and branchless angle selection. Remaining first+0x14 swaps s2/s3 roles,
 * plus initial random-loop load/branch scheduling. -g and -fno-regmove each
 * worsen to672 bytes, so neither is retained. Reopen with an actual cursor
 * lifetime and macro-load scheduling witness, without extra accesses.
 * All five local vectors retain16-byte allocation. Random XYZ-only velocity
 * W is copied to ctor3150 motion, then never used by updater3280: its vector
 * add takes motion as the second input and computesXYZ only. No fakeW store.
 * Tuning prefix reads are56 bytes with scalar fields at their real offsets;
 * the explicit GP view retains the whole incomplete owner extent.
 */
#include "common.h"

struct EmitterTuning {
    float initial_low, initial_high, extra_low, extra_high;
    unsigned char lifetime, unknown11[3];
    unsigned int initial_color, extra_color;
    float initial_scale, extra_scale;
    unsigned int tint_a, tint_b;
    int unknown2c, flags, index;
};
extern struct EmitterTuning D_L08_001AFEEC[];
extern struct EmitterTuning D_L08_001AFEEC_gp[] SDATA(D_L08_001AFEEC);
#define T (D_L08_001AFEEC_gp[0])
extern unsigned int D_L08_001B2508 __attribute__((sda));
extern unsigned char D_L08_001B9B00[];
extern void func_0029FCC0(char *, int, char *);
extern int func_002A77E0(int);
extern void func_002A7A00(float *, float, float);
extern void *func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern void *func_002C2FD8(float, void *, int, unsigned char, int, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);

/* The random helper definesXYZ. Its fourth lane is copied by the particle
 * constructor and ignored as the second input of updater002C3280's XYZ add.
 * Keep the full16-byte transfer object without fabricating a fourth store. */
void func_L08_003CC4B8(unsigned char *object)
{
    float position[4], velocity[4], extra[4], spawn[4], step[4];
    int i;
    func_0029FCC0((char *)object, 0, (char *)position);
    if (!func_002A77E0(4)) {
        unsigned char life, frame;
        func_002A7A00(velocity, T.initial_low * 0.016666667f, T.initial_high * 0.016666667f);
        life = T.lifetime;
        frame = func_002A77E0(255);
        func_002C3150(position, velocity, T.initial_color, life, frame, 0, T.initial_scale);
        for (i = 2; i >= 0; --i) {
            func_002A7A00(extra, T.extra_low * 0.016666667f, T.extra_high * 0.016666667f);
            func_00282CC0(velocity, velocity, extra);
            life = T.lifetime;
            frame = func_002A77E0(255);
            func_002C3150(position, velocity, T.extra_color, life, frame, 0, T.extra_scale);
        }
    }
    {
    float inv = 0.0039215689f, half = 0.5f, base = 3.0f;
    func_00282CF0(spawn, D_L08_001B9B00, position);
    func_00282F20(spawn, spawn, -0.3f);
    func_00282F20(step, spawn, 0.1f);
    func_00282CC0(spawn, spawn, position);
    for (i = 0; i < 4; ++i) {
        int color;
        int angle;
        float blend;
        float scale;
        blend = func_00282C48(half - func_00283CE0(255 - ((D_L08_001B2508 + i*20) & 255)) * inv);
        color = func_00283D38(T.tint_a, T.tint_b, blend);
        angle = (unsigned char)D_L08_001B2508;
        if (i & 2) angle *= 2;
        if (i & 1) angle = 255 - angle;
        angle &= 255;
        scale = func_00283CE0(i) + base;
        scale *= *(float *)(object + 0x2c) / *(float *)(*(unsigned char **)(object + 0x24) + 0x24);
        func_002C2FD8(scale, spawn, color, (unsigned char)angle, T.index, T.flags, 2, 0);
        func_00282CC0(spawn, spawn, step);
    }
    }
}
