#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

/* func_L23_00428CF8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -frac2-no-annulled-wide-stores keeps its 16-byte clear out of a branch-likely's annulled slot. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

typedef int TI128 __attribute__((mode(TI)));

typedef struct Hit_00428CF8 {
    u8 pad00[0x18];
    u8 f18;
    u8 f19;
    u16 f1A;
    u8 pad1C[0x14];
} Hit_00428CF8;

extern float g_fast_shot_spin_degrees __attribute__((sda));

extern u8 g_last_ray_hit[];

extern s32 g_hero_moby __attribute__((nosda));

extern void moby_set_state(u8 *, s32, s32);

extern void FastVecAdd(void *, void *, void *);

extern void make_hit_descriptor(void *, u8 *, s32, void *, float);

extern s32 CollLine(void *, void *, s32, u8 *, s32);

extern s32 coll_test_point(void *, s32, u8 *, float);

extern s32 coll_process_hit(float, void *, s32, u8 *, void *);

extern void FastVecScale(void *, void *, float);

extern void vec_clear_128(void *);

extern s32 snd_start_in_slot(s32, s32, s32);

extern char *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);

extern void moby_mark_spawned(u8 *);

extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

extern void gfx_add_draw_callback_third(void *, u8 *);

extern void part_draw_sign_band_sparkles(u8 *);

/* Per-frame handler of a moving object: steps the state-0 object by its velocity, bounces or
   finishes on a hit, and in every other state rotates the two matrices and clamps the counter. */
/* Per-frame update of a fast flying shot. It moves, hits things, plays hit effects and
   removes itself after a short time. */
void fast_shot_update(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float move[4];
    Hit_00428CF8 hit1;
    float vec[4];
    Hit_00428CF8 hit2;
    s32 counter;

    if (moby[0xBC] == 0) {
        *(s32 *)(vars + 0x24) = *(s32 *)(vars + 0x24) + 1;
        if (*(s32 *)(vars + 0x24) > 0xF0) {
            if (moby[0xBC] == 0) {
                moby_set_state(moby, 1, -1);
            }
        }
        switch (moby[0x20]) {
        case 0:
            FastVecAdd(move, moby + 0x10, vars);
            make_hit_descriptor(&hit1, moby, 0x80003, vars, *(float *)(vars + 0x14));
            hit1.f1A = *(u16 *)(moby + 0xAA);
            if (CollLine(moby + 0x10, move, 0, moby, 0) != 0 || coll_test_point(moby + 0x10, 0, moby, 0.3f) != 0) {
                u8 *base = g_last_ray_hit;

                if (*(u8 **)(base + 0x18) != 0) {
                    s16 hitClass = *(s16 *)(*(u8 **)(base + 0x18) + 0xAA);

                    if (hitClass != 0x7E5 /* moby class 2021 */ && hitClass != MOBY_CLASS_MOTHERSHIP_BOSS_PART && hitClass != 0xF7E /* moby class 3966 */) {
                        *(TI128 *)vec = *(TI128 *)vars;
                        FastVecScale(vec, vec, 1.5f);
                        vec[2] = 1.0f;
                        vec[3] = 5627.9248046875f;
                        make_hit_descriptor(&hit2, moby, 0x90003, vec, *(float *)(vars + 0x14));
                        hit2.f19 = 1;
                        hit2.f1A = *(u16 *)(moby + 0xAA);
                        hit2.f18 = 0;
                        if (*(s32 *)(base + 0x18) == g_hero_moby) {
                            snd_start_in_slot(0x20, 0, 0);
                        }
                        coll_process_hit(0.6f, moby + 0x10, 0, moby, &hit2);
                        if (moby[0xBC] == 0) {
                            moby_set_state(moby, 1, -1);
                        }
                        return;
                    }
                } else {
                    *(TI128 *)vec = *(TI128 *)vars;
                    FastVecScale(vec, vec, 3.0f);
                    vec[2] = 1.0f;
                    vec[3] = 5627.9248046875f;
                    make_hit_descriptor(&hit2, moby, 0x90003, vec, *(float *)(vars + 0x14));
                    hit2.f19 = 1;
                    hit2.f1A = *(u16 *)(moby + 0xAA);
                    hit2.f18 = 0;
                    if (moby[0xBC] == 0) {
                        moby_set_state(moby, 1, -1);
                    }
                    return;
                }
            }
            if (moby[0xBC] == 0) {
                *(TI128 *)(moby + 0x10) = *(TI128 *)move;
            }
            FastVecScale(vec, vars, -0.5f);
            vec_clear_128(&hit2);
            break;
        case 1:
            SpawnExplosion(moby + 0x10, 0, 25, 25, 25, 25, 0, 0, 1.0f, 20.0f, 1, 0, 0, 0);
            moby_mark_spawned(moby);
            return;
        }
    }
    math_apply_axis_rotation_to_quat(moby + 0xE0, moby + 0xE0, moby + 0xD0, g_fast_shot_spin_degrees * 0.017453294f);
    math_apply_axis_rotation_to_quat(moby + 0xC0, moby + 0xC0, moby + 0xD0, g_fast_shot_spin_degrees * 0.017453294f);
    gfx_add_draw_callback_third((void *)part_draw_sign_band_sparkles, moby);
    counter = *(s32 *)(vars + 0x2C) + 2;
    *(s32 *)(vars + 0x2C) = counter;
    if (counter > 0x40) {
        *(s32 *)(vars + 0x2C) = 0x40;
    } else if (counter < 0) {
        *(s32 *)(vars + 0x2C) = 0;
    }
}
