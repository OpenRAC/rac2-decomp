#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
extern void moby_set_state();
extern void FastVecAdd(void *, void *, void *);
typedef int TI128 __attribute__((mode(TI)));
extern void *part_find_owned_effect_slot(void *, int, int);
extern u8 g_unlock_flag_c __attribute__((sda));
extern u8 g_message_sequence_flags[];
extern u8 g_message_queue[];
extern s32 req_push_queue(u8 *, s32);
extern s32 req_launch_queued(u8 *);
extern void moby_mark_spawned(u8 *);
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern void *part_find_owned_effect_slot(void *, int, int);
extern void matrix_mul_vec3(void *, void *, void *);
struct Pair42E2F8 {
    float a;
    float b;
};
extern const struct Pair42E2F8 g_spark_pod_sizes_a;
extern const struct Pair42E2F8 g_spark_pod_sizes_b;
extern const TI128 g_spark_pod_colors[2];
extern s32 g_hovering_object_count __attribute__((sda));
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, s32, s32, s32, s32, s32, unsigned char, s32);
extern void *part_spawn_object_following_effect(void *, void *, int, int, int, int, int, int, float, float);
extern void part_spawn_scaled_bolts_pal(void *, int, float);
extern void *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_PAL_L00_00328480(void *,void *,int,int,void *,u32,void *,float,float,float,float);
extern void func_PAL_L02_00433B90(u8 *, float, float);
extern u8 g_moby_nibble_table[];
extern int g_current_map_index __attribute__((sda));

void func_PAL_L02_00433808(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    struct Pair42E2F8 a = g_spark_pod_sizes_a;
    struct Pair42E2F8 b = g_spark_pod_sizes_b;
    TI128 c[2];
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));

    c[0] = g_spark_pod_colors[0];
    c[1] = g_spark_pod_colors[1];
    switch (a0[0x20]) {
    case 0:
        *(TI128 *)d = 0;
        d[2] = 4.0f;
        part_spawn_object_following_effect(d, a0, 0x28208080, -1, 0, -1, 0, 0x60, 409500.0f, 0.0f);
        part_spawn_object_following_effect(d, a0, 0x20208080, -1, 1, -1, 0, 0x60, 367500.0f, 0.75f);
        if (*(s32 *)state != 0)
            g_hovering_object_count = g_hovering_object_count - 1;
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(a0, 0x4010000, 0) != 0 && *(s32 *)state == 0) {
            g_hovering_object_count = g_hovering_object_count - 1;
            moby_set_state(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces_pal(a0, c, &b, &a, 0xB, 0, 1, 5, 0xFFFF, 0xFF, 0);
        part_spawn_scaled_bolts_pal(a0, 1, 4.0f);
        *(TI128 *)d = 0;
        d[1] = -0.120000005f;
        d[2] = 0.060000002f;
        matrix_mul_vec3(d, d, a0 + 0xC0);
        cam_moby_create_pal(a0, 1, *(s16 *)(a0 + 0xAA), 1, a0 + 0x10, a0 + 0xF0, d, 0xFF, 0.0f, 15.0f);
        *(TI128 *)e = 0;
        e[1] = 0.2f;
        e[2] = 4.3f;
        matrix_mul_vec3(e, e, a0 + 0xC0);
        FastVecAdd(e, e, a0 + 0x10);
        *(TI128 *)f = 0;
        f[1] = 0.060000002f;
        f[2] = 0.030000001f;
        matrix_mul_vec3(f, f, a0 + 0xC0);
        func_PAL_L00_00328480(a0,e,4,1,f,0x50404040,0,0.25f,5.0f,0.5f,1.0f);
        func_PAL_L02_00433B90(a0, 0.020000001f, 0.28000003f);
        moby_mark_spawned(a0);
        break;
    }
}



