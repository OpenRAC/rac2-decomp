/* func_PAL_L04_00412AA0, the PAL copy of func_L04_0040E460: the same C, where rename func_L04_0040C0C0 becomes func_PAL_L04_00410678. */
#include "common.h"

extern char D_00189EA0[];
extern signed char *D_L04_001B24DC __attribute__((sda));
extern void func_L04_0040E248(int, unsigned char *);
extern void func_00282D30(void *, void *, float);
/* Integer and float arguments keep their order within each EE register bank. */
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int D_L04_001B2008[] __attribute__((sda));
extern int D_00138320;
extern float D_L04_001BDC30;
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002AA2E8(void *, float, float);
extern int func_00282948(void *);
extern int func_002829A8(void *);
extern void func_L00_00322BE0(void *, int);
extern void func_L00_00322A98(void *, void *);
extern void func_L00_00322AC0(void *, float, int, int);
extern void func_L00_00322EC8(void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002E59B0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern int func_L01_00355BA0(int, int);
extern void func_0027AB40(void);
extern int func_002A8600(void *, int, int, int);
extern int func_002A86E8(void *, void *, int, int);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
/* Frozen Batch A A04-table-select-76; acknowledged claim 8c4d82cfbf43e138ed35e757fdaeee3e7c4651fa684549ba9d5e8ac22c56d111. */
typedef unsigned char BatchA_A04_u8;

typedef unsigned int BatchA_A04_u32;

extern BatchA_A04_u32 D_001A79F0[] __attribute__((sda));

extern BatchA_A04_u8 D_001395B8[];

/* Steps the record's phase at +0x1FC down by 0.1 (wrapping up by 8 once it reaches -8) and
   draws the effect with it. */
void func_L04_00404068(void *arg0);

extern float func_00282C48(float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L04_00404068(void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
/* func_L04_004045E0 is in L04_00402D90-follower.c. */

/* func_L04_00407078 is in L04_00402D90-debris.c. */

/* func_L04_004073E8 is in L04_00402D90-trail.c. */

extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_00283CF0(float);
/* A04-table-select-76 freshly exact-verified under family reservation */
BatchA_A04_u32 func_L04_0040A1D0(BatchA_A04_u8 *a0);

/* A04-table-select family, incrementing form: bumps the state-selected byte */
/* shared native body of family A04-table-select: reads the state-selected byte */
/* A04-table-select family, incrementing form (second slot pair) */
extern BatchA_A04_u8 *D_001B26F0 __attribute__((sda));

/* Sweeps the 0x800 packed 64-byte records, redrawing the four live kinds */
/* func_L04_0040A628 is in L04_00402D90-racers-g8.c. */

/* func_L04_0040A958 is in L04_00402D90-reset-g8.c. */

extern signed char *D_L04_001B24DC __attribute__((sda));

/* Retail reaches its record base off $gp (a small-data symbol), and the three
   state words at 0x48 of the record and of the indexed record. */
/* func_L04_0040AC98 reaches its global off $gp, so its body lives in
   L04_00402D90-g8.c. */

/* func_L04_0040ACA8 reaches one of its globals absolutely and another off $gp,
   so its body lives in L04_00402D90-g8.c. */

/* func_L04_0040BA68 reaches its small globals off $gp, so its body lives in
   L04_00402D90-select-g8.c. */

typedef unsigned int L04Quad __attribute__((mode(TI)));
/* The EE assigns the point, parameter and mode to a0-a2, and the two
 * float arguments to f12-f13, independently of their C interleaving. */
void func_PAL_L04_00410678(L04Quad *position, L04Quad *direction, int count, int mode);

extern void func_L04_0040CE30();

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern float func_00283CE0(int);

/* The five floats come first and the two ints last: the floats then go to
   f12-f16 and the ints to a1 and a2, and the int argument is set up after
   the float ones, as the retail code has it. */
/* The emitter table the object points at: the slot id at 0x644, then the
   four rows of four heights from 0x660 on. */
/* Walks the four rows of the emitter table: every row's height is lowered by
   the shared floor, the three threshold vectors are nudged by the row's share
   and handed to the particle scheduler, and a row that sinks too far is lifted
   back to the floor. */
void func_L04_0040CE30(char *a0);

extern BatchA_A04_u8 D_00188660[];

/* Releases the callback records this moby still holds: every handle slot that is set
   names a record of the callback table, and the one that belongs to this moby is
   handed to the release helper. Each slot is cleared afterwards. */
void func_L04_0040E248(int a0, BatchA_A04_u8 *a1);

/* Inlining puts the literal rate straight into $f12, so each call loads it again. */
static inline void CallL00_00322AC0(void *state, float rate, int level, int slot)
{
    func_L00_00322AC0(state, rate, level, slot);
}

void func_PAL_L04_00412AA0(unsigned char *m)
{
    float delta[4], rotation[16];
    unsigned char *item, *other;
    int red, green, blue;
    int period = 42;
    int alpha = 128;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    unsigned char *state;
    int *data;
    float wave, active, angle, sine, radius;
    unsigned int color;
    angle = func_00283CE0(period);
    red = D_L04_001B2008[0] % period;
    {
        float phase = (float)red;
        wave = func_00283198(((phase / angle) * 2.0f) * 3.1415927f + -3.1415927f);
    }
    red = func_00283CF0(wave * 48.0f) + 104;
    green = func_00283CF0(wave * 64.0f) + 208;
    blue = func_00283CF0(wave * 24.0f) + 60;
    if (green > 255) green = 255;
    if (*(int *)(p + 0x278)) {
        func_002AA2E8(p + 0x27c, 0.20000002f, 0.008f);
        func_002AA2E8(p + 0x28c, 97.0f, 0.96631575f);
        if (*(int *)(p + 0x278)) func_00282948(p + 0x278);
        func_L00_00322BE0(p + 0x4e0, 1);
        state = p + 0x4e0;
    } else {
        if ((m[0x20] == 3 || (D_00138320 & 10)) && *(int *)(p + 0x338) < 25 && *(int *)(p + 0x33c) > 0) {
            *(int *)(p + 0x338) = 200;
            --*(int *)(p + 0x33c);
            if (m[0x20] != 3) func_002E5DA0(0, 0, m, 0x474);
            if (!func_002E59B0(m, *(int *)(p + 0x714))) {
                if (m[0x20] != 3) *(int *)(p + 0x714) = func_002E5CF8(15, 4, m);
                else {
                    *(int *)(p + 0x714) = func_002E5CF8(24, 5, m);
                    func_L01_00355BA0(*(int *)(p + 0x714), 0x400);
                }
            }
            if (*(unsigned char **)(p + 0x4c4)) {
                unsigned char *child = *(unsigned char **)(p + 0x4c4);
                unsigned char *childState = *(unsigned char **)(child + 0x68);
                if (*(float *)(p + 0x27c) <= 0.020000001f) *(int *)(childState + 0x1c0) = 0;
            }
            if (!*(int *)(p + 0x640)) {
                func_L00_00322A98(m, p + 0x4e0);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 64, 1);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 48, 2);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 32, 3);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 16, 4);
                *(int *)(p + 0x640) = 1;
            }
        }
        state = p + 0x4e0;
        if (func_00282948(p + 0x338)) {
            active = 0.0f;
            func_L00_00322EC8(state);
            *(int *)(p + 0x640) = 0;
        } else {
            active = 1.0f;
            func_L00_00322BE0(state, 1);
        }
        func_002AA2E8(p + 0x27c, active * 0.120000005f, 0.002f);
        if (*(float *)(p + 0x27c) < 0.0f) *(float *)(p + 0x27c) = 0.0f;
        if (active > 0.5f) func_002AA2E8(p + 0x28c, 97.0f, 0.96631575f);
        else func_002AA2E8(p + 0x28c, 80.0f, 0.2439867f);
    }
    if (m[0x20] != 3) {
        float viewAngle = *(float *)(p + 0x28c);
        viewAngle *= 0.008726647f;
        sine = func_00283198(viewAngle);
        sine /= func_00283180(viewAngle);
        D_L04_001BDC30 = sine;
        func_0027AB40();
    }
    if (*(int *)(p + 0x25c) != -1) {
        func_002A8600(&item, *(int *)(p + 0x25c), 0, 0);
        if (item) do {
            if (*(short *)(item + 0xaa) == 0xa99) {
                data = *(int **)(item + 0x68);
                func_00282CF0(delta, item + 0x10, m + 0x10);
                if (*data == 0 && *(int *)(p + 0x33c) < 3 && func_L00_002EE290(delta) < 1.0f) {
                    ++*(int *)(p + 0x33c);
                    if (m[0x20] != 3) func_002E5DA0(0, 0, m, 0xa99);
                    func_PAL_L04_00410678((L04Quad *)(item + 0x10), (L04Quad *)(p + 0x290), 8, 0);
                    *data = 250;
                }
            }
            func_002A86E8(&item, item, 0, 0);
        } while (item);
    }
    if (*(int *)(p + 0x254) != -1) {
        func_002A8600(&other, *(int *)(p + 0x254), 0, 0);
        if (other) {
            /* One four-term OR would be rebalanced by fold, so the terms join in steps. */
            unsigned int high = (alpha << 24) | (blue << 16);
            high |= green << 8;
            color = high | red;
            do {
                if (*(short *)(other + 0xaa) == 0x474) radius = 1.25f;
                else if (*(short *)(other + 0xaa) == 0xcef) radius = 3.75f;
                else goto next;
                *(unsigned short *)(other + 0x34) |= 16;
                *(unsigned int *)(other + 0x78) = color;
                if (!func_002829A8(other + 0xbc)) goto next;
                func_00282CF0(delta, other + 0x10, D_00189EA0);
                if (func_00282DB0(delta, delta) > 20.0f) goto next;
                func_00283388(rotation);
                func_00283698(rotation, other + 0xc0);
                func_002830C0(delta, delta, rotation);
                if (!(func_00282C48(delta[0]) < 2.8f) || !(func_00282C48(delta[1]) < radius) || !(func_00282C48(delta[2]) < 1.5f)) goto next;
                data = *(int **)(other + 0x68);
                *(int *)(p + 0x278) += *data;
                if (!func_002E59B0(m, *(int *)(p + 0x714))) {
                    if (m[0x20] != 3) *(int *)(p + 0x714) = func_002E5CF8(15, 4, m);
                    else {
                        *(int *)(p + 0x714) = func_002E5CF8(24, 5, m);
                        func_L01_00355BA0(*(int *)(p + 0x714), 0x400);
                    }
                }
                if (m[0x20] != 3) func_002E5CF8(12, 0, m);
                *(int *)(p + 0x650) = *data;
                other[0xbc] = 50;
                if (*(unsigned char **)(p + 0x4c4)) {
                    unsigned char *child = *(unsigned char **)(p + 0x4c4);
                    unsigned char *childState = *(unsigned char **)(child + 0x68);
                    if (*(float *)(p + 0x27c) <= 0.020000001f) *(int *)(childState + 0x1c0) = 0;
                }
                if (!*(int *)(p + 0x640)) {
                    func_L00_00322A98(m, p + 0x4e0);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 64, 1);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 48, 2);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 32, 3);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 16, 4);
                    *(int *)(p + 0x640) = 1;
                }
next:
                func_002A86E8(&other, other, 0, 0);
            } while (other);
        }
    }
}

/* func_L04_0040EC80 is in L04_00402D90-aim.c. */

/* func_L04_0040EF50 is in L04_00402D90-g8.c. */

