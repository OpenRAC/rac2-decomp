#include "names.h"
/* func_PAL_L07_003FB6B0, the PAL copy of func_L07_003F6F00: the same C, where scale func_002A7820(D_L07_001B1000, D_L07_001B1004); scale func_002A7820(D_L07_001B1008, D_L07_001B100C). */
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
void func_PAL_L07_003FB6B0(u8 *a0)
{
    f32 vel[4];
    f32 pos[4];
    s32 i;

    part_spawn_hero_relative(a0 + 0x10, vel, D_L07_001B0FF8, (u8)(((int)(math_random_int_range(D_L07_001B1000, D_L07_001B1004)) * 5 + 2) / 6),
                  (u8)math_random_int_below(0xFF), 0, D_L07_001B0FF0);
    vec_clear_128(vel);
    for (i = 0; i < D_L07_001B1010; i++) {
        vec_random_direction(pos, 0.0f, 0.5f);
        FastVecAdd(pos, pos, a0 + 0x10);
        vel[2] = -(math_random_float_range(D_L07_001B0FE8[0], D_L07_001B0FE8[1]) * 0.020000001f);
        part_spawn_hero_relative(pos, vel, D_L07_001B0FFC, (u8)(((int)(math_random_int_range(D_L07_001B1008, D_L07_001B100C)) * 5 + 2) / 6),
                      (u8)math_random_int_below(0xFF), 0, D_L07_001B0FF4);
    }
}

/* The three float pairs the level passes on, at $gp + 0x2830, + 0x2838 and + 0x2840;
   their addresses differ from level to level, so they carry no address. */
/* The state byte at 0x20 picks the path: 0 clears the moby list of class 1, 1 asks the
   spawner and marks the object, 2 replaces the moby and runs the level's setup. */
