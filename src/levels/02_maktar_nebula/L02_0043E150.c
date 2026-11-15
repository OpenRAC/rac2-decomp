#include "names.h"
/* Runs the timed effect state machine and emits the initial and debris bursts. The debris helper's float parameters interleave with the pointers: this caller's argument setup is the evidence. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(u8 *,s32,s32);
extern u8 *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float,
                           int, int, int, void *);

struct Pair43E150 {
    float a;
    float b;
};

extern const struct Pair43E150 D_L02_001B29B0;
extern const struct Pair43E150 D_L02_001B29B8;
extern const TI128 D_L02_001B29C0[2];
extern void part_explode_object_into_pieces(void *, void *, void *, void *, s32, s32, s32, s32, s32, unsigned char, s32);
extern void vec_local_offset_to_world(char *, char *, float, float, float);
extern int math_fast_float_d(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int math_random_int_range(int, int);
extern void part_l00_spawn_spark_burst(void *,void *,float,void *,float,int,unsigned char,float,float,float);
/* Runs a short timed effect: it starts with a big burst, then a smaller one, then keeps throwing out debris at random times. */
void debris_burst_update(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    int state_id = moby[0x20];
    struct Pair43E150 params_a = D_L02_001B29B0;
    struct Pair43E150 params_b = D_L02_001B29B8;
    TI128 table_copy[2];
    float zero_vec[4] __attribute__((aligned(16)));
    float effect_pos[4] __attribute__((aligned(16)));

    table_copy[0] = D_L02_001B29C0[0];
    table_copy[1] = D_L02_001B29C0[1];
    *(TI128 *)zero_vec = 0;
    switch (state_id) {
    case 0:
        part_explode_object_into_pieces(moby, table_copy, &params_b, &params_a, 0xFFFF, 0, -1, 0x10, 0xFFFF, 0xFF, 0);
        *(u32 *)(moby + 0x98) = *(u32 *)(*(u8 **)(moby + 0x24) + 0x10);
        *(u16 *)(moby + 0x7C) = 0;
        vec_local_offset_to_world((char *)moby, (char *)effect_pos, zero_vec[0], zero_vec[1], zero_vec[2]);
        SpawnExplosion(effect_pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, *(float *)(moby + 0x2C) * 7.0f,
                      20.0f, 1, 1, 1, 0);
        *(s32 *)state = 0x14;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (math_fast_float_d(state) != 0) {
            vec_local_offset_to_world((char *)moby, (char *)effect_pos, zero_vec[0], zero_vec[1], zero_vec[2]);
            SpawnExplosion(effect_pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0,
                          *(float *)(moby + 0x2C) * 3.5f, 20.0f, 0, 0, 0, 0);
            *(s32 *)(state + 4) = 0x78;
            moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (math_fast_float_d(state + 4) != 0 || *(s32 *)(state + 4) >= 0x5B) {
            *(TI128 *)effect_pos = 0;
            effect_pos[1] = -0.016666668f;
            effect_pos[2] = 0.050000004f;
            matrix_mul_vec3(effect_pos, effect_pos, moby + 0xC0);
            part_l00_spawn_spark_burst(moby,zero_vec,0.0f,effect_pos,0.033333335f,math_random_int_range(3,6),0,0.5f,15.0f,2.0f);
            part_l00_spawn_spark_burst(moby,zero_vec,0.0f,effect_pos,0.033333335f,math_random_int_range(3,6),1,0.5f,15.0f,2.0f);
            *(s32 *)(state + 4) = math_random_int_range(0x2D, 0x5A);
        }
        break;
    }
}
