#include "common.h"

extern int math_random_int_range(int min, int max);

extern int math_random_int_below(int mode);

/* It returns the particle it spawns. Declared so, its call sets $v0, which ends the read of the
   random byte there: the argument moves then keep retail's order, and the loop's count comes
   back in $v1. */
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);

extern void vec_clear_128(void *);

extern void vec_random_direction(void *, float, float);

extern void FastVecAdd(void *, void *, void *);

extern float math_random_float_range(float, float);

/* The burst's tuning words, one declaration per word: a word retail reads through $gp is `sda`
   (its .extern comes before this function); a word it reads bare (`lui`/`lw` in the destination,
   or `$at` for a float) is a plain extern, whose .extern only comes at the end of the file. The
   fall-speed range at D_L07_001B0FE8 is one plain 8-byte object: cc1 counts the load of its
   second word (a symbol plus an offset) as two instructions, so that load stays out of the delay
   slot of func_002A7878's call and the first word's load fills it, in the $gp form the assembler
   gives a slot. */
extern f32 D_L07_001B0FE8[2];
extern f32 D_L07_001B0FF0 __attribute__((sda));
extern f32 D_L07_001B0FF4;
extern s32 D_L07_001B0FF8 __attribute__((sda));
extern s32 D_L07_001B0FFC;
extern s32 D_L07_001B1000 __attribute__((sda));
extern s32 D_L07_001B1004;
extern s32 D_L07_001B1008;
extern s32 D_L07_001B100C;
extern s32 D_L07_001B1010 __attribute__((sda));

/* Spawns a particle at the object's position (+0x10) with the first colour and size, then
   D_L07_001B1010 more, each at a point from func_002A7A00 added to that position and falling at
   a random speed from the range at D_L07_001B0FE8 (per frame at 60 Hz), with the second colour
   and size. Each kind byte is random in a range (D_L07_001B1000 then D_L07_001B1008), the next
   byte random up to 0xFF. The velocity goes to the first spawn before func_00282C88 clears it. */
/* Spawns a puff of falling particles around an object. */
void part_spawn_falling_puff(u8 *moby)
{
    f32 vel[4];
    f32 pos[4];
    s32 i;

    part_spawn_hero_relative(moby + 0x10, vel, D_L07_001B0FF8, (u8)math_random_int_range(D_L07_001B1000, D_L07_001B1004),
                  (u8)math_random_int_below(0xFF), 0, D_L07_001B0FF0);
    vec_clear_128(vel);
    for (i = 0; i < D_L07_001B1010; i++) {
        vec_random_direction(pos, 0.0f, 0.5f);
        FastVecAdd(pos, pos, moby + 0x10);
        vel[2] = -(math_random_float_range(D_L07_001B0FE8[0], D_L07_001B0FE8[1]) * 0.016666668f);
        part_spawn_hero_relative(pos, vel, D_L07_001B0FFC, (u8)math_random_int_range(D_L07_001B1008, D_L07_001B100C),
                      (u8)math_random_int_below(0xFF), 0, D_L07_001B0FF4);
    }
}

extern void moby_set_state(u8 *a0, u8 a1, s32 a2);

extern void *part_find_owned_effect_slot(char *a0, int a1, int a2);

extern int PlayMobySound(int index, int a1, char *a2);

extern void part_explode_object_into_pieces(void *a0, void *a1, void *a2, void *a3, int a4, int a5,
                               int a6, int a7, int a8, u8 a9, int a10);

extern void moby_mark_spawned(void *object);

/* The three float pairs the level passes on, at $gp + 0x2830, + 0x2838 and + 0x2840;
   their addresses differ from level to level, so they carry no address. */
extern f32 ref_L07_00410B48_00[2] __attribute__((sda));
extern f32 ref_L07_00410B48_01[2] __attribute__((sda));
extern f32 ref_L07_00410B48_02[2] __attribute__((sda));

/* The state byte at 0x20 picks the path: 0 clears the moby list of class 1, 1 asks the
   spawner and marks the object, 2 replaces the moby and runs the level's setup. */
/* Updates a moby (class 4769): it waits for a condition, then spawns an effect and removes itself. */
void effect_l07_spawner_update(u8 *moby0)
{
    u8 *moby = moby0;
    u8 *vars = *(u8 **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x04010000, 0) == 0)
            goto done;
        if (*(int *)vars != 0)
            goto done;
        moby_set_state(moby, 2, -1);
    done:
        moby[0xA8] = 0xFF;
        break;
    case 2:
        PlayMobySound(0, 0, moby);
        part_explode_object_into_pieces(moby, ref_L07_00410B48_02, ref_L07_00410B48_01,
                          ref_L07_00410B48_00, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        moby_mark_spawned(moby);
        break;
    }
}
