#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 row[4]; } SnivelakMatrix;
extern void anim_start_blended_pal(void *, s32, s32, s32);
extern void *CreateMoby(s32);
extern float math_interpolate_between_limits(s32, s32, float, float);
extern void vec_store_transformed_entry(void *, s32, float, float, void *);
extern void moby_init_child_from_parent(void *, void *);
extern void math_approach_target_with_braking(void *, float, float, float, float);
extern u8 *SpawnExplosion_pal(void *, s32, s32, s32, s32, s32, s32, s32, float, float,
                          s32, s32, s32, void *);
extern u8 g_particle_template[] __attribute__((sda));
extern float g_snivelak_shot_angles __attribute__((sda));
extern float g_snivelak_shot_times __attribute__((sda));
extern float g_snivelak_shot_size_factor __attribute__((sda));

/* Creates a small shot object owned by another object, starting at the given position and facing (PAL: 50 Hz rates). */
u8 *snivelak_spawn_shot_from_matrix_pal(u8 *owner, SnivelakMatrix *matrix)
{
    u8 *shot;
    u8 *state;
    u8 *shot_pos;
    float scale;
    s32 count;
    TI128 *dest;
    TI128 *source;
    shot = CreateMoby(0xF4E);
    if (shot) {
        scale = math_interpolate_between_limits(0, 15, 0.125f, 0.3f);
        vec_store_transformed_entry(shot, 0, scale, 0.0f, g_particle_template);
        state = *(u8 **)(shot + 0x68);
        *(s32 *)(state + 0x68) = -1;
        moby_init_child_from_parent(shot, owner);
        shot_pos = shot + 0x10;
        qcopy(shot_pos, matrix->row);
        SpawnExplosion_pal(shot_pos, 0, 0, 0, 0, 20, 45, 1, 2.0f, 20.0f, 1, 0, 0, 0);
        dest = (TI128 *)state;
        source = matrix->row;
        count = 3;
        do { qcopy(dest, source); source++; dest++; } while (--count >= 0);
        math_approach_target_with_braking(state + 0x50, 1.0f, 1.0f,
                      g_snivelak_shot_angles * 0.00040000002f,
                      g_snivelak_shot_times * 0.020000001f);
        if (shot[0x43] != 1) anim_start_blended_pal(shot, 1, 0, 1);
        *(float *)(shot + 0x2C) = *(float *)(*(u8 **)(shot + 0x24) + 0x24) * g_snivelak_shot_size_factor;
    }
    return shot;
}
