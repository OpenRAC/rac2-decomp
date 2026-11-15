#include "include_asm.h"

#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union {
    Q q;
    float f[4];
} Vector;
extern int D_L20_001A8F00, D_L20_001B2AC8;
extern int D_L20_001BDCF0[];
typedef struct {
    char pad[0x80];
    float pos[4];
} Hero;
extern Hero g_hero_state;
extern char g_hero_position[];
extern float D_L20_001B1FE0 __attribute__((sda));
extern float D_L20_001B1FE4 __attribute__((sda));
extern float D_L20_001B1FE8 __attribute__((sda));
extern float D_L20_001B1FF0 __attribute__((sda));
extern float D_L20_001B1FF8 __attribute__((sda));
extern float D_L20_001B1FFC __attribute__((sda));
extern float D_L20_001B2000 __attribute__((sda));
extern float D_L20_001B2004 __attribute__((sda));
extern float D_L20_001B1FF4;
extern Vector D_L20_001B2010 SDATA(D_L20_001B2010);
extern void func_PAL_L20_00445668(char *), moby_mark_spawned(char *);
extern int flag_set_second_pending(char *), math_random_int_below(int), moby_dispatch_action_by_kind(char *, void *);
extern void func_PAL_002A7650(char *, int, int), part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void moby_enter_state_six(char *), moby_set_state(char *, int, int);
extern int flag_set_first_pending(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern float vec_distance_xy(void *, void *);
extern int func_PAL_002B5BA8(char *, void *, float);
extern int yeedil_small_enemy_can_attack(char *);
extern float moby_get_anim_value(char *);
extern int func_PAL_L01_00323068(char *, void *);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(char *, float);
extern int func_PAL_002AF6C0(char *, float);
extern void matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern int coll_sweep_from_object(void *, void *, int, int, float, float, float, int, int);
extern void euler_rotation_basis(void *, void *);
extern s32 func_PAL_00273A10(char *);
extern float vec_length_xy(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern f32 ApproachValue(void *, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_advance_frame_counter(char *);

void func_PAL_L20_00444F68(char *obj) {
    Vector v;
    Q matrix[3];
    float length;
    char *st = *(char **)(obj + 0x68);
    int hit;

    func_PAL_L20_00445668(obj);
    if (D_L20_001A8F00 == 2) {
        if (D_L20_001BDCF0[0] >= 5) moby_mark_spawned(obj);
        return;
    }
    switch (*(u8 *)(obj + 0x95)) {
    case 0:
        break;
    case 1:
        if (flag_set_second_pending(obj)) *(int *)(st + 0x284) = math_random_int_below(2);
        break;
    case 2:
        hit = moby_dispatch_action_by_kind(obj, st + 0x140);
        if (hit & 1) {
            *(int *)(st + 0x280) = 0;
            func_PAL_002A7650(obj, 0, 3);
            part_queue_moby_for_glow(obj, 0, moby_enter_state_six);
        } else if (hit & 2) moby_set_state(obj, 3, 1);
        break;
    }
    switch (*(u8 *)(obj + 0x20)) {
    case 2: {
        float distance;
        if (flag_set_first_pending(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) func_PAL_002A7E68(obj, 2, 0, 17);
            *(float *)(st + 0x78) = D_L20_001B1FE0 * 0.020000001f;
            *(float *)(st + 0x288) = 1.0471977f;
        }
        distance = vec_distance_xy(obj + 0x10, g_hero_position);
        if (distance < D_L20_001B1FF0) *(float *)(st + 0x288) = 2.0943954f;
        else if (D_L20_001B1FF4 < distance) *(float *)(st + 0x288) = 1.0471977f;
        if (*(int *)(st + 0xD0) == 50) {
            *(int *)(st + 0xD0) = 0;
            *(int *)(st + 0x284) = (*(int *)(st + 0x284) + 1) & 1;
        }
        func_PAL_002B5BA8(obj, g_hero_position, *(int *)(st + 0x284) ? *(float *)(st + 0x288) : - *(float *)(st + 0x288));
        if ((D_L20_001B2AC8 & 15) == (((int)obj >> 8) & 15) && yeedil_small_enemy_can_attack(obj)) {
            *(int *)(st + 0x280) = 1;
            moby_set_state(obj, 3, -1);
        }
        break;
    }
    case 3:
        if (flag_set_first_pending(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) func_PAL_002A7E68(obj, 2, 0, 8);
            *(float *)(st + 0x78) = D_L20_001B1FE4 * 0.020000001f;
        }
        func_PAL_002B5BA8(obj, g_hero_position, 0.0f);
        if (*(float *)(st + 0x11C) < D_L20_001B1FF8) moby_set_state(obj, 4, -1);
        break;
    case 4: {
        float distance;
        if (flag_set_first_pending(obj)) {
            if (*(u8 *)(obj + 0x43) != 4) func_PAL_002A7E68(obj, 4, (int)D_L20_001B1FFC, 8);
        }
        distance = moby_get_anim_value(obj);
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && distance >= 9.0f && distance <= 17.0f) {
            float accel = D_L20_001B2004 * 0.00040000002f;
            float speed = D_L20_001B2000 * 0.020000001f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            func_PAL_L01_00323068(obj, g_hero_position);
        } else {
            moby_start_effect_from_entry(obj, mat_fast_helper_a(
                g_hero_state.pos[0] - *(float *)(obj + 0x10),
                g_hero_state.pos[1] - *(float *)(obj + 0x14)));
        }
        {
            float accel = D_L20_001B1FE8 * 0.00040000002f;
            float speed = D_L20_001B1FE4 * 0.020000001f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
        }
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && func_PAL_002AF6C0(obj, 14.0f)) {
            matrix_mul_vec3(&v, &D_L20_001B2010, obj + 0xC0);
            FastVecAdd(&v, &v, obj + 0x10);
            coll_sweep_from_object(obj, &v, 0x04000001, 0, 0.333f, 2.0f, 1.0f, 1, 0);
        }
        if ((*(u8 *)(obj + 0x60) & 2) && vec_distance_xy(obj + 0x10, g_hero_position) > D_L20_001B1FF8) moby_set_state(obj, 3, -1);
        break;
    }
    case 7:
        *(char **)(obj + 0x68) = st + 0x210;
        func_PAL_00273A10(obj);
        *(char **)(obj + 0x68) = st;
        coll_sweep_from_object(obj, obj + 0x10, 0x04000000, 0, 0.5f, 5.0f, 1.0f, 1, 0);
        qzero_nc(&v);
        v.f[2] = *(float *)(st + 0x288) * 0.019867549f;
        euler_rotation_basis(matrix, &v);
        matrix_mul_vec3(st + 0x210, st + 0x210, matrix);
        length = vec_length_xy(st + 0x210);
        if (length < 0.060000002f) {
            ApproachValue(&length, 0.0f, 0.004f);
            if (length <= 0.0f) moby_set_state(obj, 1, 1);
            else vec_fast_normalize_helper(st + 0x210, st + 0x210, length);
        }
        if (*(float *)(obj + 0x18) < *(float *)(st + 0x180)) {
            *(int *)(obj + 0x98) = 0;
            *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
            moby_set_state(obj, 6, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(obj)) {
            char *data = *(char **)(obj + 0x24);
            int flags = *(int *)(data + 0x10);
            *(int *)(obj + 0x9C) = 2;
            *(int *)(obj + 0x98) = flags;
            *(u16 *)(obj + 0x34) = *(u16 *)(data + 0x44) | 0x1000;
            matrix_mul_vec3(&v, st + 0x230, obj + 0xC0);
            FastVecAdd(obj + 0x10, &v, obj + 0x10);
            *(float *)(obj + 0x18) = coll_probe_ground_height_below(obj + 0x10, 0, 0.5f);
            qzero(obj + 0xF0);
            *(float *)(obj + 0xF8) = mat_fast_helper_a(
                g_hero_state.pos[0] - *(float *)(obj + 0x10),
                g_hero_state.pos[1] - *(float *)(obj + 0x14));
            if (*(u8 *)(obj + 0x43) != 3) func_PAL_002A7E68(obj, 3, 0, 4);
        }
        if (*(u8 *)(obj + 0x60) & 2) moby_set_state(obj, 2, 1);
        break;
    case 5:
    case 6:
        break;
    }
    moby_advance_frame_counter(obj);
}
