#include "include_asm.h"


#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void moby_set_state(u8 *,s32,s32);
extern u8 *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float,
                           int, int, int, void *);
struct Pair43E150 {
    float size_a;
    float size_b;
};
extern const struct Pair43E150 g_debris_burst_params_a;
extern const struct Pair43E150 g_debris_burst_params_b;
extern const TI128 g_debris_burst_colors[2];
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, s32, s32, s32, s32, s32, unsigned char, s32);
extern void vec_local_offset_to_world(char *, char *, float, float, float);
extern int math_fast_float_d(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int math_random_int_range(int, int);
extern void part_l00_spawn_spark_burst_pal(void *,void *,float,void *,float,int,unsigned char,float,float,float);

/* Updates the debris burst: breaks into pieces, then sets off a chain of explosions and smoke. (PAL: 50 Hz timings) */
void debris_burst_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    int state_id = moby[0x20];
    struct Pair43E150 size_a = g_debris_burst_params_a;
    struct Pair43E150 size_b = g_debris_burst_params_b;
    TI128 colors[2];
    float origin[4] __attribute__((aligned(16)));
    float world_pos[4] __attribute__((aligned(16)));

    colors[0] = g_debris_burst_colors[0];
    colors[1] = g_debris_burst_colors[1];
    *(TI128 *)origin = 0;
    switch (state_id) {
    case 0:
        part_explode_object_into_pieces_pal(moby, colors, &size_b, &size_a, 0xFFFF, 0, -1, 0x10, 0xFFFF, 0xFF, 0);
        *(u32 *)(moby + 0x98) = *(u32 *)(*(u8 **)(moby + 0x24) + 0x10);
        *(u16 *)(moby + 0x7C) = 0;
        vec_local_offset_to_world((char *)moby, (char *)world_pos, origin[0], origin[1], origin[2]);
        SpawnExplosion_pal(world_pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(float *)(moby + 0x2C) * 7.0f,
                      20.0f, 1, 1, 1, 0);
        *(s32 *)vars = 0x11;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (math_fast_float_d(vars) != 0) {
            vec_local_offset_to_world((char *)moby, (char *)world_pos, origin[0], origin[1], origin[2]);
            SpawnExplosion_pal(world_pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0,
                          *(float *)(moby + 0x2C) * 3.5f, 20.0f, 0, 0, 0, 0);
            *(s32 *)(vars + 4) = 0x64;
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (math_fast_float_d(vars + 4) != 0 || *(s32 *)(vars + 4) >= 0x4C) {
            *(TI128 *)world_pos = 0;
            world_pos[1] = -0.020000001f;
            world_pos[2] = 0.060000002f;
            matrix_mul_vec3(world_pos, world_pos, moby + 0xC0);
            part_l00_spawn_spark_burst_pal(moby,origin,0.0f,world_pos,0.040000003f,math_random_int_range(3,6),0,0.5f,15.0f,2.0f);
            part_l00_spawn_spark_burst_pal(moby,origin,0.0f,world_pos,0.040000003f,math_random_int_range(3,6),1,0.5f,15.0f,2.0f);
            *(s32 *)(vars + 4) = ((s32)(math_random_int_range(0x2D, 0x5A)) * 5 + 2) / 6;
        }
        break;
    }
}

