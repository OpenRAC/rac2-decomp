#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void func_PAL_002A7650(void *, int, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void *func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);
extern int moby_transform_point_by_attachment(void *, void *, void *, void *);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void moby_set_state(u8 *, int, int);
extern void moby_mark_spawned(void *);
extern u8 g_sound_state[];
extern u8 g_hero_position[];
extern float D_L07_001B0AAC __attribute__((sda));

void func_PAL_L07_003E9FD0(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x68);
    int slot;
    u8 *rec;
    u8 *pos;
    u8 *toward;
    union { Quad q; f32 f[4]; } a;
    f32 b[4] __attribute__((aligned(16)));
    f32 c[4] __attribute__((aligned(16)));
    int count;

    if (st[0x2E] != 2) {
        func_PAL_002A7650(obj, 0, 1);
    }
    slot = *(s32 *)(st + 0x264);
    if (slot != -1) {
        rec = g_sound_state + slot * 0x70;
        if (*(u8 **)(rec + 0x88) == obj && rec[0x74] != 0) {
            snd_stop_voice(slot);
        }
    }
    *(s32 *)(st + 0x264) = -1;
    PlayMobySound(0, 0, obj);
    pos = obj + 0x10;
    a.q = 0;
    a.f[2] = 0.5f;
    FastVecAdd(&a, &a, pos);
    func_PAL_L00_003FB330(&a, 0, 0, 0, 0, 0x14, 0x2D, 1, D_L07_001B0AAC, 20.0f, 1, 0, 0, *(s32 *)(st + 0x260));
    FastVecSub(b, pos, g_hero_position);
    b[2] = 0.0f;
    vec_fast_normalize_helper(b, b, 0.080000006f);
    toward = *(u8 **)(st + 0x260);
    if (toward != 0) {
        moby_transform_point_by_attachment(obj, toward, pos, c);
        FastVecAdd(b, b, c);
    }
    func_PAL_002B15D8(obj, 3, b, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    count = *(u16 *)(st + 0x21A) - 1;
    *(u16 *)(st + 0x21A) = count;
    if ((s16)count != -1) {
        *(s16 *)(st + 0x88) = 0;
        *(s32 *)(obj + 0x98) = 0;
        *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(obj, 8, 4);
        st[0x2E] = 1;
        *(f32 *)(st + 0x20) = *(s16 *)(st + 0x24);
    } else {
        moby_mark_spawned(obj);
    }
}

extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void vec_random_direction(void *, float, float);
extern int math_random_int_range(int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, float, unsigned char, unsigned char, int);
extern float D_L07_001B0AD8 __attribute__((sda));
extern float D_L07_001B0AB0 __attribute__((sda));
extern float D_L07_001B0AB4[] __attribute__((sda));
extern int D_L07_001B0AD0[] __attribute__((sda));
extern float D_L07_001B0AC0[] __attribute__((sda));
extern int D_L07_001B0AC8 __attribute__((sda));

/* Emit two particles at opposite local offsets, including platform motion. */
void func_PAL_L07_003EA1F8(char *arg)
{
    float carryDelta[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(arg + 0x68);
    int side;

    qzero_nc(angles);
    if (*(void **)(state + 0x260)) {
        moby_transform_point_and_rotation_by_parent(arg, *(void **)(state + 0x260), arg + 0x10, angles, carryDelta, angles);
        FastVecSub(carryDelta, carryDelta, arg + 0x10);
    } else {
        qzero_nc(carryDelta);
    }
    for (side = 0; side < 2; side++) {
        int randomValue, randomByte;
        float scale;

        qzero_nc(position);
        position[2] = D_L07_001B0AD8;
        if (!side)
            position[2] = -position[2];
        vec_random_direction(velocity, D_L07_001B0AB0 * (0.020000001f),
                      D_L07_001B0AB4[0] * (0.020000001f));
        FastVecAdd(velocity, velocity, carryDelta);
        randomValue = ((s32)(math_random_int_range(D_L07_001B0AD0[0], D_L07_001B0AD0[1])) * 5 + 2) / 6;
        matrix_mul_vec3(position, position, arg + 0xC0);
        randomValue = (unsigned char)randomValue;
        FastVecAdd(position, position, arg + 0x10);
        scale = math_random_float_range(D_L07_001B0AC0[0], D_L07_001B0AC0[1]);
        randomByte = math_random_int_below(255);
        part_spawn_hero_relative(position, velocity, D_L07_001B0AC8, scale, randomValue, (unsigned char)randomByte, 0);
    }
}
