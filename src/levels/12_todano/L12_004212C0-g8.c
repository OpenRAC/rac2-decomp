#include "common.h"

typedef s32 Quadword __attribute__((mode(__TI__)));
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, u8, void *);
extern void vec_local_offset_to_world(void *, void *, f32, f32, f32);
extern void *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern s32 math_fast_float_d(void *);
extern void moby_set_state(void *, s32, s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern s32 math_random_int_range(s32, s32);
extern void part_l00_spawn_spark_burst(void *, void *, void *, f32, f32, s32, s32, f32, f32, f32);
/* The complete range record is 32 bytes; this unit uses -G32. */
extern f32 D_L12_001B1FD0[8] SDATA(D_L12_001B1FD0) __attribute__((sda));
extern f32 D_L12_001B1FC8[2] __attribute__((sda));
extern f32 D_L12_001B1FC0[2] __attribute__((sda));
extern s32 D_L12_001B2000 __attribute__((sda));
/* Retail reads Y/Z absolutely and X through GP,  and passes the same vector. */
extern f32 D_L12_001B1FF0[] __attribute__((sda));
extern f32 D_L12_001B1FF0_gp SDATA(D_L12_001B1FF0) __attribute__((sda));

/* Plays a flash and a big burst, then keeps throwing out puffs of sparks for a while before it stops. */
void big_burst_spark_emitter_update(u8 *self) {
    s32 *st = *(s32 **)(self + 0x68);
    f32 vec[4];
    switch (self[0x20]) {
    case 0:
        part_explode_object_into_pieces(self, D_L12_001B1FD0, D_L12_001B1FC8, D_L12_001B1FC0, 65535, 0, D_L12_001B2000, 0, 65535, 255, 0);
        *(s16 *)(self + 0x7c) = 0;
        vec_local_offset_to_world(self, vec, D_L12_001B1FF0_gp, D_L12_001B1FF0[1], D_L12_001B1FF0[2]);
        SpawnExplosion(vec, 0, 25, 20, 20, 20, 45, 0, 1, 1, 1, 0, *(f32 *)(self + 0x2c)*7.0f, 20.0f);
        st[0] = 20;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (math_fast_float_d(st)) {
            vec_local_offset_to_world(self, vec, D_L12_001B1FF0_gp, D_L12_001B1FF0[1], D_L12_001B1FF0[2]);
            SpawnExplosion(vec, 0, 25, 20, 20, 20, 45, 0, 0, 0, 0, 0, *(f32 *)(self + 0x2c)*3.5f, 20.0f);
            st[1] = 120;
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        if (math_fast_float_d(st + 1) || st[1] >= 91) {
            *(Quadword *)vec = 0;
            vec[1] = -0.0166666675f;
            vec[2] = 0.0500000045f;
            matrix_mul_vec3(vec, vec, self + 0xc0);
            part_l00_spawn_spark_burst(self, &D_L12_001B1FF0_gp, vec, 0.0f, 0.0333333351f, math_random_int_range(3, 6), 0, 0.5f, 15.0f, 2.0f);
            part_l00_spawn_spark_burst(self, &D_L12_001B1FF0_gp, vec, 0.0f, 0.0333333351f, math_random_int_range(3, 6), 1, 0.5f, 15.0f, 2.0f);
            st[1] = math_random_int_range(45, 90);
        }
        break;
    }
}
