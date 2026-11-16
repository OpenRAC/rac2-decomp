#include "common.h"

typedef int Q __attribute__((mode(TI)));
typedef union {
    Q q;
    float f[4];
} Vector;
extern int g_hero_vehicle_mode, g_frame_l20_counter;
extern int g_level_l20_progress_stage[];
typedef struct {
    char pad[0x80];
    float pos[4];
} Hero;
extern Hero g_hero_state;
extern char g_hero_position[];
extern float g_yeedil_small_speed_a __attribute__((sda));
extern float g_yeedil_small_speed_b __attribute__((sda));
extern float g_yeedil_small_accel_a __attribute__((sda));
extern float g_yeedil_small_near_distance __attribute__((sda));
extern float g_yeedil_small_leave_distance __attribute__((sda));
extern float g_yeedil_small_blend_frames __attribute__((sda));
extern float g_yeedil_small_speed_c __attribute__((sda));
extern float g_yeedil_small_accel_b __attribute__((sda));
extern float g_yeedil_small_far_distance;
extern Vector g_yeedil_small_local_vec SDATA(D_L20_001B2010);
extern void yeedil_small_enemy_init_damage(char *), moby_mark_spawned(char *);
extern int flag_set_second_pending(char *), math_random_int_below(int), moby_dispatch_action_by_kind(char *, void *);
extern void SetDeathBits(char *, int, int), part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void moby_enter_state_six(char *), moby_set_state(char *, int, int);
extern int flag_set_first_pending(char *);
extern void anim_start_blended(char *, int, int, int);
extern float vec_distance_xy(void *, void *);
extern int moby_turn_toward_target_and_step(char *, void *, float);
extern int yeedil_small_enemy_can_attack(char *);
extern float moby_get_anim_value(char *);
extern int moby_l01_turn_toward_target(char *, void *);
extern float mat_fast_helper_a(float, float);
extern int moby_start_effect_from_entry(char *, float);
extern int math_is_value_within_step(char *, float);
extern void matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern int coll_sweep_from_object(void *, void *, int, int, float, float, float, int, int);
extern void euler_rotation_basis(void *, void *);
extern s32 cam_moby_update(char *);
extern float vec_length_xy(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern f32 ApproachValue(void *, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_advance_frame_counter(char *);

/* Runs the small Yeedil enemy each frame (moby class 4510). It circles the hero, chases, shoots when lined up, and falls over when it is hurt. */
void yeedil_small_enemy_update(char *obj) {
    Vector v;
    Q matrix[3];
    float length;
    char *st = *(char **)(obj + 0x68);
    int hit;

    yeedil_small_enemy_init_damage(obj);
    if (g_hero_vehicle_mode == 2) {
        if (g_level_l20_progress_stage[0] >= 5) moby_mark_spawned(obj);
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
            SetDeathBits(obj, 0, 3);
            part_queue_moby_for_glow(obj, 0, moby_enter_state_six);
        } else if (hit & 2) moby_set_state(obj, 3, 1);
        break;
    }
    switch (*(u8 *)(obj + 0x20)) {
    case 2: {
        float distance;
        if (flag_set_first_pending(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) anim_start_blended(obj, 2, 0, 20);
            *(float *)(st + 0x78) = g_yeedil_small_speed_a * 0.0166666675f;
            *(float *)(st + 0x288) = 1.0471977f;
        }
        distance = vec_distance_xy(obj + 0x10, g_hero_position);
        if (distance < g_yeedil_small_near_distance) *(float *)(st + 0x288) = 2.0943954f;
        else if (g_yeedil_small_far_distance < distance) *(float *)(st + 0x288) = 1.0471977f;
        if (*(int *)(st + 0xD0) == 60) {
            *(int *)(st + 0xD0) = 0;
            *(int *)(st + 0x284) = (*(int *)(st + 0x284) + 1) & 1;
        }
        moby_turn_toward_target_and_step(obj, g_hero_position, *(int *)(st + 0x284) ? *(float *)(st + 0x288) : - *(float *)(st + 0x288));
        if ((g_frame_l20_counter & 15) == (((int)obj >> 8) & 15) && yeedil_small_enemy_can_attack(obj)) {
            *(int *)(st + 0x280) = 1;
            moby_set_state(obj, 3, -1);
        }
        break;
    }
    case 3:
        if (flag_set_first_pending(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) anim_start_blended(obj, 2, 0, 10);
            *(float *)(st + 0x78) = g_yeedil_small_speed_b * 0.0166666675f;
        }
        moby_turn_toward_target_and_step(obj, g_hero_position, 0.0f);
        if (*(float *)(st + 0x11C) < g_yeedil_small_leave_distance) moby_set_state(obj, 4, -1);
        break;
    case 4: {
        float distance;
        if (flag_set_first_pending(obj)) {
            if (*(u8 *)(obj + 0x43) != 4) anim_start_blended(obj, 4, (int)g_yeedil_small_blend_frames, 10);
        }
        distance = moby_get_anim_value(obj);
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && distance >= 9.0f && distance <= 17.0f) {
            float accel = g_yeedil_small_accel_b * 0.00027777778f;
            float speed = g_yeedil_small_speed_c * 0.0166666675f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            moby_l01_turn_toward_target(obj, g_hero_position);
        } else {
            moby_start_effect_from_entry(obj, mat_fast_helper_a(
                g_hero_state.pos[0] - *(float *)(obj + 0x10),
                g_hero_state.pos[1] - *(float *)(obj + 0x14)));
        }
        {
            float accel = g_yeedil_small_accel_a * 0.00027777778f;
            float speed = g_yeedil_small_speed_b * 0.0166666675f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
        }
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && math_is_value_within_step(obj, 14.0f)) {
            matrix_mul_vec3(&v, &g_yeedil_small_local_vec, obj + 0xC0);
            FastVecAdd(&v, &v, obj + 0x10);
            coll_sweep_from_object(obj, &v, 0x04000001, 0, 0.333f, 2.0f, 1.0f, 1, 0);
        }
        if ((*(u8 *)(obj + 0x60) & 2) && vec_distance_xy(obj + 0x10, g_hero_position) > g_yeedil_small_leave_distance) moby_set_state(obj, 3, -1);
        break;
    }
    case 7:
        *(char **)(obj + 0x68) = st + 0x210;
        cam_moby_update(obj);
        *(char **)(obj + 0x68) = st;
        coll_sweep_from_object(obj, obj + 0x10, 0x04000000, 0, 0.5f, 5.0f, 1.0f, 1, 0);
        qzero_nc(&v);
        v.f[2] = *(float *)(st + 0x288) * 0.0166666675f;
        euler_rotation_basis(matrix, &v);
        matrix_mul_vec3(st + 0x210, st + 0x210, matrix);
        length = vec_length_xy(st + 0x210);
        if (length < 0.0500000045f) {
            ApproachValue(&length, 0.0f, 0.0027777778f);
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
            if (*(u8 *)(obj + 0x43) != 3) anim_start_blended(obj, 3, 0, 5);
        }
        if (*(u8 *)(obj + 0x60) & 2) moby_set_state(obj, 2, 1);
        break;
    case 5:
    case 6:
        break;
    }
    moby_advance_frame_counter(obj);
}

extern float g_level_shared_float;
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern char *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern int moby_apply_damage_to_object(char *, char *, int);
extern int weapon_select_aim_target(char *, int, void *, int, float, float);

/* Sets up the small enemy when it first appears. Each frame it also handles being hit, dying, and remembering the hero position. */
void yeedil_small_enemy_init_damage(char *obj) {
    char *st = *(char **)(obj + 0x68);
    Vector a;
    Vector b;

    if (*(unsigned char *)(obj + 0x20) == 0) {
        *(float *)(st + 0x170) = 0.5f;
        *(unsigned char *)(st + 0x150) = 5;
        *(int *)(st + 0x188) = 2;
        *(float *)(st + 0x174) = 0.6f;
        *(float *)(st + 0x17C) = 0.15f;
        *(float *)(st + 0x84) = 0.05f;
        *(float *)(st + 0x54) = 0.3f;
        *(float *)(st + 0x50) = 0.5f;
        *(float *)(st + 0x58) = 0.4f;
        *(float *)(st + 0x5C) = 2.0f;
        *(float *)(st + 0x60) = 1.57079649f;
        *(float *)(st + 0x80) = 0.785398245f;
        {
            float angle = math_random_signed_float_range(18.0f, 22.0f) * 0.0174532942f;
            float speed = g_yeedil_small_speed_b * 0.0166666675f;
            float accel = g_yeedil_small_accel_a * 0.00027777778f;

            *(short *)(st + 0x132) = 0x78;
            *(short *)(st + 0x134) = 0xB4;
            *(float *)(st + 0x12C) = angle;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            *(float *)(st + 0x74) = accel;
        }
        *(int *)(st + 0x88) |= 0x200;
        *(unsigned char *)(st + 0x48) = FloatToInt(8.0f);
        *(unsigned char *)(st + 0x4A) = FloatToInt(12.0f);
        *(unsigned char *)(st + 0x29) = 1;
        if (*(short *)(st + 0x24) == 0) {
            *(short *)(st + 0x24) = 3;
            *(float *)(st + 0x20) = 3.0f;
        }
        *(int *)(obj + 0x98) = 0;
        *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(obj, 6, 3);
        if (*(unsigned char *)(obj + 0x43) != 0) {
            anim_start_blended(obj, 0, 0, 0);
        }
    }

    *(float *)(st + 0x180) = g_level_shared_float;
    if (*(unsigned char *)(obj + 0x20) == 6) {
        return;
    }
    if (*(unsigned char *)(st + 0x2E) == 2) {
        *(int *)(obj + 0x98) = 0;
        *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(obj, 6, 3);
    }
    *(unsigned char *)(st + 0x2E) = 1;

    if (*(unsigned char *)(obj + 0x20) == 7 && *(float *)(st + 0x20) > 0.0f) {
        char *hit = part_find_owned_effect_slot(obj, 0x10000, 0);
        float damage = moby_update_aim_target_strength(obj, hit);

        ApproachValue(st + 0x20, 0.0f, damage);
        *(unsigned char *)(obj + 0xA8) = 0xFF;
        if (*(float *)(st + 0x20) <= 0.0f) {
            *(float *)(obj + 0xF4) = 0.0f;
            *(float *)(obj + 0xF0) = 0.0f;
            matrix_mul_vec3(&a, st + 0x230, obj + 0xC0);
            euler_rotation_basis(obj + 0xC0, obj + 0xF0);
            matrix_mul_vec3(&b, st + 0x230, obj + 0xC0);
            FastVecSub(&b, &b, &a);
            FastVecSub(obj + 0x10, obj + 0x10, &b);
        }
    } else {
        moby_apply_damage_to_object(obj, st + 0x140, 0);
    }
    weapon_select_aim_target(obj, *(int *)(st + 0x270), 0, 0, 64.0f, 0.0f);

    if (*(int *)(st + 0x204) == 0) {
        char *g = (char *)&g_hero_state;

        *(char **)(st + 0x200) = *(char **)(g + 0x2290);
        qcopy(st + 0x1F0, *(char **)(g + 0x2290) + 0x10);
        *(int *)(st + 0x204) = 1;
    }
}

extern int g_yeedil_small_group_limit __attribute__((sda));
extern int g_group_count __attribute__((sda));
extern unsigned short *g_group_l20_id_lists[];
extern char *g_group_l20_member_table;

/* Returns 0 when D_L20_001B2020 or more other objects of this object's group (the
   0x7FFF-masked id list at D_L20_001FBB20[obj[0x21]]) are busy (state +0x280) or are
   closer to D_00189EA0 than it; 1 otherwise.  The loop is the group-iteration form used
   by func_00325DA0. */
/* Decides whether this enemy may start attacking. It says no if too many others in its group are already attacking or are closer to the hero. */
int yeedil_small_enemy_can_attack(char *obj) {
    float dist;
    int closer = 0;
    int busy = 0;
    unsigned short *p;
    char *e;

    dist = vec_distance_xy(obj + 0x10, g_hero_position);
    for (p = g_group_l20_id_lists[*(u8 *)(obj + 0x21)];
         *(u8 *)(obj + 0x21) != 0xFF && *(u8 *)(obj + 0x21) <= g_group_count && p != 0 &&
         ((p != 0 && (short)p[-1] >= 0) || p == g_group_l20_id_lists[*(u8 *)(obj + 0x21)]);
         p++) {
        e = g_group_l20_member_table + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e != obj && *(u8 *)(e + 0x20) != 6) {
            if (*(int *)(*(char **)(e + 0x68) + 0x280) != 0)
                busy++;
            if (busy >= g_yeedil_small_group_limit)
                return 0;
            if (dist > vec_distance_xy(e + 0x10, g_hero_position))
                closer++;
            if (closer >= g_yeedil_small_group_limit)
                return 0;
        }
    }
    return 1;
}
