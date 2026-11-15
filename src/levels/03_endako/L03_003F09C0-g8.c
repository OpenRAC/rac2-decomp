#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

/* These bodies reach D_L03_001B2A1C with `lw $a2,0x3A2C($gp)`, which only a
 * -G8 unit emits; the same symbol is reached with an absolute `lui`/`lw` pair
 * inside func_L03_003F66D8 and func_L03_0041D128, so those stay in the -G0 file. */
extern u8 *D_L03_001B2A1C __attribute__((sda));

/* The two words the entity's state is chosen by, both reached through $gp. */
extern s32 D_L03_001B108C __attribute__((sda));
extern u32 D_L03_001B1058 __attribute__((sda));

extern void moby_set_state(void *entity, int a, int b);
extern int math_random_int_below(int id);

/* The engine's particle and light helpers, called with the level's own copies. */
extern void math_fast_float_d(void *target);
extern void FastDecTimer(void *target);
extern void moby_update_eased_node(void *entity, void *target, int a, float f0, float f1);
extern void vec_transform_by_object_or_given(void *entity, void *out, void *target, int a);
extern void moby_transform_joint_to_world(void *entity, int a, void *out);
extern u8 *SpawnSpinningSparkParticle(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern int FloatToInt(float f);
extern void value_set_and_smooth(void *entity, float *target, float f, int a, int b);

/* The level's own float, reached through $gp. */
extern float D_L03_001B1BF0 __attribute__((sda));

/* Two more of the level's floats, at +0x2C10 and +0x2C14 from $gp. */
extern f32 D_L03_001B1C00 __attribute__((sda));
extern f32 D_L03_001B1C04 __attribute__((sda));

extern void hero_copy_field_to_moby(u8 *a0);
extern s32 flag_is_third_pending_set();
extern void moby_set_flag_bit(unsigned char *entity, int enabled);

/* What the engine builds a particle from: two words, then two floats. */
typedef struct {
    s32 a;
    s32 b;
    f32 c;
    f32 d;
} ParticleSetup;

/* The stream table itself is `lui $v0,0x20 ; addiu $v0,$v0,-0x4A60` (absolute). */
extern u8 *D_L03_001FB5A0[];

/* Picks the entity's next behaviour.  A global word chooses it when it is not
 * negative; else the state's own counters do, each one running down as it is
 * used.  Every behaviour sets up its timers and calls. */
void boss_choose_next_behaviour(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    s32 sel;

    if (D_L03_001B108C >= 0) {
        sel = D_L03_001B108C;
    } else if (state[0x30A] != 0) {
        state[0x30A]--;
        sel = 1;
    } else if (state[0x309] != 0) {
        state[0x309]--;
        sel = 0;
    } else if (state[0x30B] != 0) {
        state[0x30B]--;
        sel = 2;
    } else {
        sel = math_random_int_below(state[0x308] + 1);
    }

    switch (sel) {
    case 0:
        moby_set_state(entity, 7, 3);
        if (state[0x308] >= 2) {
            *(float *)(state + 0x2F8) = 0.6981318f;
            *(float *)(state + 0x2FC) = -0.6981318f;
        } else if (math_random_int_below(2) != 0) {
            *(float *)(state + 0x2F8) = 0.6981318f;
        } else {
            *(float *)(state + 0x2FC) = -0.6981318f;
        }
        state[0x30B] = 1;
        break;
    case 1:
        *(u32 *)(state + 0x2E4) = 300;
        moby_set_state(entity, 9, 4);
        state[0x309] = math_random_int_below(2) + 1;
        break;
    case 2:
        *(u32 *)(state + 0x2E4) = D_L03_001B1058;
        moby_set_state(entity, 12, 5);
        state[0x309] = 1;
        break;
    }
}

/* Walks the entity's stream, storing 1 at +0x2D6 of every record whose halfword
 * at +0xAA is 0xFFC.  Twin of func_L01_003B5290 (same file layout, level 1). */
void sweeper_bot_mark_stream(u8 *entity) {
    u8 *list;
    u8 *p;
    u8 *base;

    if (entity[0x21] == 0xFF)
        return;
    list = D_L03_001FB5A0[entity[0x21]];
    if (list == 0)
        return;
    p = list;
    base = D_L03_001B2A1C;
    for (;;) {
        u8 *q = base + ((*(unsigned short *)p & 0x7FFF) << 8);

        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xFF3 /* Megacorp Sweeper Bot */) {
                *(short *)(*(u8 **)(q + 0x68) + 0x2D6) = 1;
            }
        }
        if (*(short *)p < 0)
            break;
        p += 2;
    }
}

/* Same walk as func_L03_0041D0A8 after seeding two state halfwords. */
void rivet_bot_mark_stream(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *list;
    u8 *p;
    u8 *base;

    *(short *)(state + 0x336) = 1;
    *(short *)(state + 0x330) = 0xF0;
    if (entity[0x21] == 0xFF)
        return;
    list = D_L03_001FB5A0[entity[0x21]];
    if (list == 0)
        return;
    p = list;
    base = D_L03_001B2A1C;
    for (;;) {
        u8 *q = base + ((*(unsigned short *)p & 0x7FFF) << 8);

        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xFFC /* Megacorp Rivet Bot */) {
                *(short *)(*(u8 **)(q + 0x68) + 0x336) = 1;
            }
        }
        if (*(short *)p < 0)
            break;
        p += 2;
    }
}

/* Sets the entity's two blend channels up, then fires two particles: the engine builds
 * each one from the state's direction, a random count and a colour, and the caller fills
 * the record's own fields in.  The two blocks fill the FIRST particle's header again, and
 * the second one keeps its own pointer to the sub-record: both are the original's own
 * wording, and the compiler's schedule depends on it. */
void part_fire_blend_particles(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    float buf[4];
    ParticleSetup setup;
    float vec[4];
    u16 timer;
    s32 count;
    f32 f;
    u8 *particle;
    u8 *particle2;
    u8 *data;
    u8 *data2;

    math_fast_float_d(state + 0x34C);
    FastDecTimer(state + 0x330);
    FastDecTimer(state + 0x332);
    moby_update_eased_node(entity, state + 0x220, 0, 0.03f, 0.3f);
    moby_update_eased_node(entity, state + 0x2A0, 1, 0.03f, 0.3f);
    timer = *(u16 *)(entity + 0x96);
    if (timer <= 0xFFFE)
        *(u16 *)(entity + 0x96) = timer + 1;
    vec_transform_by_object_or_given(entity, buf, state + 0x1A0, 0);
    f = buf[1] * D_L03_001B1BF0;
    *(float *)(entity + 0xF0) = f;
    /* The four words the engine reads the particle's setup from, in the order the
     * original stores them. */
    setup.a = 0;
    setup.c = -0.02f;
    setup.d = 1.0f;
    setup.b = 0;
    count = math_random_int_below(16);
    if (math_random_int_below(2))
        count = -count;
    moby_transform_joint_to_world(entity, 4, vec);
    vec[2] += 0.1f;
    particle = SpawnSpinningSparkParticle(vec, 0.1f, 1.0f, 0.9f, count, &setup,
                             105000.0f, 0xDF204080, 0);
    if (particle != 0) {
        data = particle + 0x20;
        *(u16 *)(particle + 0xA) = 5;
        particle[9] = FloatToInt(4.0f) + 0x70;
        *(u32 *)(data + 4) = 2;
        data[0xA] = 0xDF;
        data[0xB] = particle[0xA];
    }
    particle2 = SpawnSpinningSparkParticle(vec, 0.1f, 1.0f, 0.9f, count, &setup,
                              105000.0f, 0xDF204080, 0);
    data2 = particle2;
    if (data2 != 0) {
        *(u16 *)(particle + 0xA) = 5;
        data2 += 0x20;
        particle[9] = FloatToInt(4.0f) + 0x70;
        *(u32 *)(data2 + 4) = 2;
        data2[0xA] = 0xDF;
        data2[0xB] = particle[0xA];
    }
    if (entity[0x31] != 0)
        value_set_and_smooth(entity, (float *)(state + 0x360), 2.5f, 5, 1);
}

/* Sets the entity up for a shot: the state's own counter, its two blend rates and the
 * frame the shot was prepared on. */
s32 entity_prepare_shot(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    f32 f0;
    f32 f1;
    s32 v0;

    if (*(s32 *)(state + 0x284) == -1) return 0;
    if (entity[0x20] != 9) return 0;

    if (flag_is_third_pending_set() == 0) {
        entity[0xA8] = 0xFF;
        f1 = D_L03_001B1C00 * 0.00027777778450399637f;
        f0 = D_L03_001B1C04 * 0.016666668f;
        v0 = *(s16 *)(state + 0x24);
        *(u16 *)(state + 0x98) = 0;
        *(f32 *)(state + 0x138) = f0;
        *(f32 *)(state + 0x33C) = 6.0f;
        *(f32 *)(state + 0x134) = f1;
        *(f32 *)(state + 0x130) = f1;
        *(f32 *)(state + 0x20) = (f32)v0;
        entity[0xA8] = 0xFF;
        *(u32 *)(entity + 0x98) = *(u32 *)(*(u8 **)(entity + 0x24) + 0x10);
        hero_copy_field_to_moby(entity);
        moby_set_flag_bit(entity, 1);
        return 1;
    }
    return 0;
}

/* The level's own runtime block: two counters the engine writes and the two
 * pointers it keeps. */
typedef struct {
    u8 pad00[0x30];
    s32 field30;
    s32 field34;
    u8 pad38[0x158];
    u8 *field190;
    u8 *field194;
} L03Block;

extern L03Block D_L03_001BD680;

/* The level's mode word, reached through $gp. */
extern s32 D_L03_001A8F00 __attribute__((sda));

extern void func_3133D0(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_3240F0(u8 *a0);
extern void func_324138(u8 *a0, s32 a1);

/* Per-frame update of a scripted light moby: when the level is in mode 2 it flashes a colour and follows a timed cutscene step. */
void scripted_light_update(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    s32 old, next, base, rem;
    s32 arg1, arg2, arg3;

    switch (entity[0x20]) {
    case 0:
        entity[0x30] = 0xFF;
        entity[0x20] = 1;
        return;
    case 1: {
        s32 mode = D_L03_001A8F00;

        if (mode == 2) {
            if (D_L03_001BD680.field30 == 5) {
                if (D_L03_001BD680.field34 < 10) {
                    *(u16 *)(D_L03_001BD680.field194 + 0x7C) = 0x3F;
                }
            }
            if (D_L03_001BD680.field30 == 7) {
                u8 *obj = D_L03_001BD680.field190;
                if (D_L03_001BD680.field34 < 0x427) goto other;
                if (D_L03_001BD680.field34 >= 0x471) goto other;
                old = *(s32 *)state;
                next = old + 1;
                *(s32 *)state = next;
                base = (next > -1) ? next : old + 4;
                base = (base >> 2) << 2;
                rem = next - base;
                if (rem < 3) {
                    arg1 = 0;
                    arg2 = 0;
                    arg3 = 0;
                } else {
                    arg1 = 0xB0;
                    arg2 = 0xB0;
                    arg3 = 0xF0;
                }
                func_3133D0(obj, arg1, arg2, arg3);
                return;
            other:
                if (D_L03_001BD680.field34 < 0x44C) {
                    *(s32 *)(state + 4) = func_3240F0(obj);
                } else {
                    func_324138(obj, *(s32 *)(state + 4));
                }
            }
        }
        return;
    }
    }
}
