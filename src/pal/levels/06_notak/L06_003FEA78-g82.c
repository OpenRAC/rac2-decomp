#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int,
                               int, int, int);
extern void moby_compute_local_point(char *, float *, float, float, float);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, char *);
extern u8 g_sound_state[];
extern void *D_L06_002E1DA0[];
extern void initialize_path_moby_group_pal(int);
extern void update_path_moby_spacing_pal(char *);
extern int coll_point_inside_region(void *, int);
extern int math_fast_float_d(void *);
extern int math_random_int_below(int);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void euler_rotation_basis(void *, void *);
extern void part_l01_spawn_spark_burst_pal(float *, float *, int, int, int, float, float, float);
extern int g_moby_l06_group_count __attribute__((sda));
extern char *D_L06_001B281C_abs[3] __attribute__((sda));
extern unsigned short *g_group_l06_id_lists[];
extern char g_hero_l06_position[];
extern int g_switch_explode_param_a __attribute__((sda));
extern int g_switch_explode_param_b __attribute__((sda));
extern int g_switch_explode_param_c __attribute__((sda));
typedef int TI128 __attribute__((mode(TI)));
#define GROUP (*(unsigned char *)(s1 + 0x21))
#define FOR_EACH_ID(id_ptr) \
    for (id_ptr = D_L06_001FB3A0[GROUP]; \
         GROUP != 0xFF && GROUP <= D_L06_001B2838 && id_ptr != 0 && \
         ((id_ptr != 0 && (short)id_ptr[-1] >= 0) || id_ptr == D_L06_001FB3A0[GROUP]); \
         id_ptr++)

/* Updates a switch-like object (moby classes 2155 and 2157) that controls a group of other mobys, turning them on and off (PAL: 50 Hz timings). */
void group_switch_update_pal(char *moby)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&done, &&c4};
    char *s1 = moby;
    char *state;
    unsigned short *id_ptr;
    char *member;
    char *sound_slot;
    char *member_b;
    unsigned short *id_ptr_b;
    int cls;
    unsigned int state_index;
    float velocity[4];
    float point[4];

    state_index = *(unsigned char *)(s1 + 0x20);
    state = *(char **)(s1 + 0x68);
    if (state_index < 5)
        goto *D_L06_002E1DA0[state_index];
    goto done;
c0:
    *(unsigned char *)(s1 + 0x30) = 0xFE;
    initialize_path_moby_group_pal(*(unsigned char *)(s1 + 0x21));
    goto done;
c1:
    if (*(int *)(state + 0x64) != -1 && coll_point_inside_region(g_hero_l06_position, *(int *)(state + 0x64)) != 0) {
        FOR_EACH_ID(id_ptr) {
            member = D_L06_001B281C_abs[0] + ((*id_ptr & 0x7FFF) << 8);
            if (member == 0)
                break;
            *(unsigned char *)(member + 0x31) = 0;
            *(unsigned short *)(member + 0x34) |= 1;
        }
        moby_set_state(s1, 4, -1);
    }
    update_path_moby_spacing_pal(s1);
    sound_slot = g_sound_state + *(int *)(state + 0x54) * 0x70;
    if (*(int *)(sound_slot + 0x88) != (int)s1 || *(unsigned char *)(sound_slot + 0x74) == 0)
        *(int *)(state + 0x54) = PlayMobySound(0, 4, s1);
    if (*(unsigned char *)(s1 + 0x31) == 0)
        goto done;
    if (math_fast_float_d(state + 0x44)) {
        if (*(unsigned short *)(s1 + 0x34) & 0x10) {
            *(unsigned short *)(s1 + 0x34) &= 0xFFEF;
            *(int *)(state + 0x44) = *(int *)(state + 0x48);
        } else {
            *(unsigned short *)(s1 + 0x34) |= 0x10;
            *(int *)(state + 0x44) = 4;
        }
    }
    if (part_find_owned_effect_slot(s1, 0x4010000, 0)) {
        cls = *(short *)(s1 + 0xAA) == 0x86B ? 2 : 3;
        part_explode_object_into_pieces_pal(s1, &g_switch_explode_param_a, &g_switch_explode_param_b, &g_switch_explode_param_c, 0xFFFF, 1, cls, 0, 0xFFFF,
                          0xFF, 0);
        *(short *)(s1 + 0x7C) = (1 << cls) - 0x8000;
        SpawnExplosion_pal(s1 + 0x10, 0, 0x19, 0x14, 0x14, 0x14, 0x14, 1, 1.0f, 20.0f, 1, 0, 0, 0);
        moby_set_state(s1, 2, -1);
        *(int *)(state + 0x38) = 0;
        *(int *)(state + 0x14) = 0;
        *(int *)(state + 0x58) = 0x96;
        *(int *)(s1 + 0x98) = 0;
    }
    *(unsigned char *)(s1 + 0xA8) = 0xFF;
    *(float *)(s1 + 0xF8) = FastAddRotations(*(float *)(s1 + 0xF8), 3.141593f);
    euler_rotation_basis(s1 + 0xC0, s1 + 0xF0);
    goto done;
c4:
    if (coll_point_inside_region(g_hero_l06_position, *(int *)(state + 0x64)) == 0) {
        FOR_EACH_ID(id_ptr_b) {
            member_b = D_L06_001B281C_abs[0] + ((*id_ptr_b & 0x7FFF) << 8);
            if (member_b == 0)
                break;
            *(unsigned char *)(member_b + 0x31) = 1;
            *(unsigned short *)(member_b + 0x34) &= 0xFFFE;
        }
        moby_set_state(s1, 1, -1);
    }
    goto done;
c2:
    *(float *)(s1 + 0xF4) = (*(float *)(s1 + 0xF4) - 0.7853982f) * 0.94f + 0.7853982f;
    euler_rotation_basis(s1 + 0xC0, s1 + 0xF0);
    *(float *)(s1 + 0x18) = *(float *)(s1 + 0x18) - 0.024000002f;
    if (math_random_int_below(4) == 0 && *(short *)(s1 + 0xAA) == 0x86B) {
        *(TI128 *)velocity = 0;
        velocity[2] = 0.10000001f;
        moby_compute_local_point(s1, point, -1.5f, 0.0f, 1.0f);
        part_l01_spawn_spark_burst_pal(point, velocity, 1, 0x40F0E0D0, 0, 0.050000004f, 2.0f, 1.02f);
    }
    if (math_fast_float_d(state + 0x58)) {
        *(unsigned char *)(s1 + 0x31) = 0;
        *(unsigned short *)(s1 + 0x34) |= 1;
        moby_set_state(s1, 3, -1);
    }
done:
    return;
}
