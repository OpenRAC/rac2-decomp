#include "include_asm.h"

#include "common.h"
typedef s32 Quadword __attribute__((mode(__TI__)));
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, s32, s32, s32, s32, s32, u8, void *);
extern void vec_local_offset_to_world(void *, void *, f32, f32, f32);
extern void *SpawnExplosion_pal(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern s32 math_fast_float_d(void *);
extern void moby_set_state(void *, s32, s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern s32 math_random_int_range(s32, s32);
extern void part_l00_spawn_spark_burst_pal(void *, void *, void *, f32, f32, s32, s32, f32, f32, f32);
extern f32 g_big_burst_piece_positions[8] SDATA(D_L12_001B1FD0) __attribute__((sda));
extern f32 g_big_burst_piece_speeds[2] __attribute__((sda));
extern f32 g_spark_emitter_piece_params[2] __attribute__((sda));
extern s32 g_big_burst_piece_effect __attribute__((sda));
extern f32 g_big_burst_spark_offset[] __attribute__((sda));
extern f32 D_L12_001B1FF0_gp SDATA(D_L12_001B1FF0) __attribute__((sda));

/* Plays a flash and a big burst, then keeps throwing out puffs of sparks for a while before it stops (PAL: 50 Hz timings). */
void big_burst_spark_emitter_update_pal(u8 *self) {
    s32 *vars = *(s32 **)(self + 0x68);
    f32 spark_pos[4];
    switch (self[0x20]) {
    case 0:
        part_explode_object_into_pieces_pal(self, g_big_burst_piece_positions, g_big_burst_piece_speeds, g_spark_emitter_piece_params, 65535, 0, g_big_burst_piece_effect, 0, 65535, 255, 0);
        *(s16 *)(self + 0x7c) = 0;
        vec_local_offset_to_world(self, spark_pos, D_L12_001B1FF0_gp, g_big_burst_spark_offset[1], g_big_burst_spark_offset[2]);
        SpawnExplosion_pal(spark_pos, 0, 25, 20, 20, 20, 45, 0, 1, 1, 1, 0, *(f32 *)(self + 0x2c)*7.0f, 20.0f);
        vars[0] = 17;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (math_fast_float_d(vars)) {
            vec_local_offset_to_world(self, spark_pos, D_L12_001B1FF0_gp, g_big_burst_spark_offset[1], g_big_burst_spark_offset[2]);
            SpawnExplosion_pal(spark_pos, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0, *(f32 *)(self + 0x2c)*3.5f, 20.0f);
            vars[1] = 100;
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        if (math_fast_float_d(vars + 1) || vars[1] >= 76) {
            *(Quadword *)spark_pos = 0;
            spark_pos[1] = -0.020000001f;
            spark_pos[2] = 0.060000002f;
            matrix_mul_vec3(spark_pos, spark_pos, self + 0xc0);
            part_l00_spawn_spark_burst_pal(self, &D_L12_001B1FF0_gp, spark_pos, 0.0f, 0.040000003f, math_random_int_range(3, 6), 0, 0.5f, 15.0f, 2.0f);
            part_l00_spawn_spark_burst_pal(self, &D_L12_001B1FF0_gp, spark_pos, 0.0f, 0.040000003f, math_random_int_range(3, 6), 1, 0.5f, 15.0f, 2.0f);
            vars[1] = ((s32)(math_random_int_range(45, 90)) * 5 + 2) / 6;
        }
        break;
    }
}
