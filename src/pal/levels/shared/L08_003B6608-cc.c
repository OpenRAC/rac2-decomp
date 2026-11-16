/* func_PAL_L08_003B6608, the PAL copy of func_L08_003B2F70: the same C, where rename func_002ABBB8 becomes func_PAL_002AC718. */
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern u8 *g_hero_moby;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern Collision ref_L08_0039DBE8_03;
extern Material ref_L08_0039DBE8_04[];
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_range(int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(char *, char *, char *);

typedef struct {
    float dir[4];                 /* 0x00 */
    float f10;                    /* 0x10 */
    int f14;                      /* 0x14 */
    int owner;                    /* 0x18 */
    short h1C, h1E;               /* 0x1C */
    float f20;                    /* 0x20 */
    int f24, f28;                 /* 0x24 */
} Bolt_L08_003B2DB0;
typedef struct {
    char pad0[0x10];
    float pos[4];                 /* 0x10 */
    char pad20[0x23 - 0x20];
    u8 b23;                       /* 0x23 */
    char pad24[0x2C - 0x24];
    float scale;                  /* 0x2C */
    u8 b30, b31;                  /* 0x30 */
    short h32;                    /* 0x32 */
    u16 h34;                      /* 0x34 */
    char pad36[0x68 - 0x36];
    Bolt_L08_003B2DB0 *state;     /* 0x68 */
    char pad6C[0xF0 - 0x6C];
    int fF0;                      /* 0xF0 */
    float fF4, fF8;               /* 0xF4 */
} Moby_L08_003B2DB0;

extern char g_hero_position[];
extern Moby_L08_003B2DB0 *CreateMoby(int);
extern float fast_vec_dist(void *, void *);
extern void func_002A0F48(void *);

 /* GetEffectTex(int, int) */

/*
 * Four parallel callback lists, each a (function, argument) pair of
 * arrays with its own count, plus a "register" and a "run them all"
 * function per list. The counts are reached with retail's one-register
 * macro form, so they are MACRO_ADDR.
 */
typedef void (*DrawCallback_r002F2D10)(void *);

extern DrawCallback_r002F2D10 r1_D_0018DC40_002F2D10[];

/* rac1-decomp src/game/draw.c: func_001F49B0 */
/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_0027F640 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
extern u8 *g_moby_array __attribute__((sda));
/* Counts the 0x100-byte records between the two pointers whose halfword at +0xAA equals A0
   and whose byte at +0x20 is neither 0xFE nor 0xFD. */
/* Switches three flags of one record; -1 leaves a group alone, 0 clears it and anything
   else sets it. */
void moby_set_visibility_flags(void *a0v, s32 a1, s32 a2, s32 a3);

extern u8 *g_moby_array __attribute__((sda));
extern void moby_set_visibility_flags(void *, s32, s32, s32);

/* Runs func_L08_00328B80 on every object named by entry a0 of the 0x1FB660 table: a u16
   list whose low 15 bits select the object and whose high bit ends the walk. The list
   pointer is read under two names (the guard keeps the fresh load, the walk needs a
   callee-saved register across the call). */
/* Splits a four-float vector: two components give an angle, 0x45AFDF66 marks an
   already-resolved vector. */
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
/* The float varargs entry: 2.95.3 spills $a2-$a3, $t0-$t3 (eight bytes each)
   and $f12-$f18; the work is done by the shared worker on that save area. */
/* func_L08_00363320 is in L08_00363320-g8.c. */

extern Material ref_L08_0039E000_00[];
extern Collision ref_L08_0039E000_01;
Moby_L08_003B2DB0 *SpawnDirectedEffectObject(int owner, float *pos, float *dir, int life);

typedef struct {
    Vec vector;
    void *object;
    int flags;
    u8 enabled, kind;
    u16 group;
    float radius;
    int active;
} CollisionInput;
extern Vec ref_L08_003B2F70_00, ref_L08_003B2F70_01, ref_L08_003B2F70_02;
extern int PlayMobySound(int, int, void *);
extern float vec_distance_xy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int FastDecTimer(short *);
extern void moby_mark_spawned(void *);
extern float FastVecLength(void *);
extern u8 *part_spawn_velocity_particle(void *, void *, int, int, float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int coll_process_hit(void *, float, int, void *, void *);
void bolt_effect_update_pal(char *obj) {
    struct { Vec old; CollisionInput collision; Vec velocity, random; } frame;
    CollisionInput *input;
    Bolt_L08_003B2DB0 *state = *(Bolt_L08_003B2DB0 **)(obj + 0x68);
    float distance = fast_vec_dist(obj + 0x10, g_hero_position);
    qcopy(&frame.old, obj + 0x10);
    FastVecAdd(obj + 0x10, obj + 0x10, (char *)state);
    if (!state->f28 && state->f24 && state->f20 < distance && distance < 3.0f) {
        PlayMobySound(0, 0, obj);
        state->f28 = 1;
    }
    if (distance < state->f20) state->f24 = 1;
    state->f20 = distance;
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f ||
        vec_distance_xy(obj + 0x10, &ref_L08_003B2F70_00) > 255.0f) goto destroy;
    input = 0;
    if (!*(u8 *)(obj + 0xBC)) {
        frame.collision.flags = 0x70001;
        frame.collision.radius = 3.0f;
        frame.collision.object = obj;
        frame.collision.active = 1;
        qcopy(&frame.collision.vector, state);
        FastVecSub(&frame.collision.vector, obj + 0x10, g_hero_position);
        vec_fast_normalize_helper(&frame.collision.vector, &frame.collision.vector, 1.0f);
        input = &frame.collision;
        frame.collision.vector.f[2] = 1.0f;
        frame.collision.vector.f[3] = 5627.9248046875f;
        frame.collision.enabled = 1;
        frame.collision.kind = 3;
        frame.collision.group = *(u16 *)(obj + 0xAA);
    }
    if (FastDecTimer(&state->h1C) && !*(u8 *)(obj + 0xBC)) {
        *(u8 *)(obj + 0xBC) = 1;
        state->h1C = state->h1E / 4;
    } else if (state->h1C <= 0 && *(u8 *)(obj + 0xBC)) {
destroy:
        moby_mark_spawned(obj);
        return;
    }
    if (!CollLine(&frame.old, obj + 0x10, 0, (void *)state->owner, input)) return;
    qcopy(obj + 0x10, &ref_L08_003B2F70_01);
    if (!*(u8 *)(obj + 0xBC)) {
        int n;
        for (n = 0; n < 5; n++) {
            frame.random.q = 0;
            frame.random.f[0] = math_random_float_range(-1.0f, 1.0f);
            frame.random.f[1] = math_random_float_range(-1.0f, 1.0f);
            frame.random.f[2] = math_random_float_range(-1.0f, 1.0f);
            frame.velocity.q = frame.random.q;
            vec_fast_normalize(&frame.random, state, &ref_L08_003B2F70_02);
            vec_scale_to_length(&frame.velocity, &frame.velocity, FastVecLength(&frame.random) * 0.5f);
            FastVecAdd((char *)&frame.velocity, (char *)&frame.random, (char *)&frame.velocity);
            vec_scale_to_length(&frame.velocity, &frame.velocity, math_random_float_range(0.060000002f, 0.120000005f));
            part_spawn_velocity_particle(obj + 0x10, &frame.velocity, 0x7F2F4F6F, math_random_int_range(8, 12), 60000.0f);
        }
    }
    SpawnExplosionEffects_pal(obj, state, 0, 0.0f, 0.0f, 4, 3, 6, 1.1f, 0.6f, 1.0f, 0.9f, -1, 0.0f,
        0, 1, -1, 0, 0x810001);
    coll_process_hit(obj + 0x10, 1.1f, 16, obj, input);
    moby_mark_spawned(obj);
}

/* Defined in L08_003C63F0-g8.c. */

/* Keeps a child object at points 7 and 8 of obj: spawns a missing one,
 * otherwise moves it there and copies the parent's orientation. */
/* func_L08_003CD488 lives in the -g8 sibling file (it reads the level's scalars
   through $gp). */

extern u8 *g_hero_moby;
extern void func_002A0F48();

/* func_L08_003CD600 and func_L08_003CD6C8 are matched in L08_003CD600-qcopy.c. */

/* Defined in L08_003CD648.c. */

