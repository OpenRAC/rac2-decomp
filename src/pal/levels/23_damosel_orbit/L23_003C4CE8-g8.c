#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int g_child_orientation_timer __attribute__((sda));
extern char g_hero_position[];
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_copy_joint_transform_to_object(void *, void *, int, int);
extern void moby_transform_joint_point(void *, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float vec_get_heading_angle(void *, void *, int);
extern float math_approach_target_with_direction_mode(void *, float, float, float, float, void *, int);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void FastVecScale(void *, void *, float);
extern void mat_align_to_dir(void *, void *, void *);
extern int FastDecTimer(short *);
extern void FastVecSub(void *, void *, void *);

extern float g_mothership_surface_radius MACRO_ADDR;
extern int g_enemy_timer_base __attribute__((sda));
extern TI128 g_coll_line_hit_point_2[];
extern char g_camera_position[];
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void func_L22_002F3B38(void *, void *, void *);
extern int CollLine(void *, void *, int, int, int);

#define F(i, k) (((float *)&loc[i])[k])

/* func_PAL_L23_003C4CE8, the PAL copy of func_L23_003C1420: the same C, with the follow timer scaled to 50 Hz. */
/* Looks for a point to move to by casting a ray ahead; on a wall hit picks a point away from it and starts a timed dodge. Returns 1 if one was found. (PAL) */
int enemy_probe_ahead_point_pal(char *moby) {
    TI128 loc[8];
    char *vars = *(char **)(moby + 0x68);
    int random_index;
    TI128 *hit_ptr;
    TI128 *normal_ptr;
    TI128 *target_ptr;
    TI128 *dest_ptr;

    loc[1] = 0;
    F(1, 2) = *(float *)(vars + 0x54) + *(float *)(vars + 0x50);
    loc[2] = 0;
    F(2, 0) = 4.0f;
    loc[0] = loc[1];
    random_index = math_random_int_below(8);
    F(2, 1) = (float)random_index * 0.4285714626f + -1.5f;
    F(2, 2) = *(float *)(vars + 0x54) + *(float *)(vars + 0x50);
    loc[1] = loc[2];
    FastVecScale(&loc[0], moby + 0xE0, F(0, 2));
    FastVecAdd(&loc[0], &loc[0], moby + 0x10);
    matrix_mul_vec3(&loc[1], &loc[1], moby + 0xC0);
    FastVecAdd(&loc[1], &loc[1], moby + 0x10);
    if (CollLine(&loc[0], &loc[1], 0x12, 0, 0) != 0) {
    hit_ptr = &g_coll_line_hit_point_2[2];
    normal_ptr = &loc[2];
    qcopy(normal_ptr, hit_ptr);
    loc[5] = 0;
    F(5, 0) = 0.0009765625f;
    F(5, 1) = 0.0009765625f;
    F(5, 2) = 0.0009765625f;
    func_L22_002F3B38(normal_ptr, normal_ptr, &loc[5]);
    hit_ptr -= 2;
    vec_scale_to_length(normal_ptr, normal_ptr, 1.0f);
    FastVecSub(&loc[3], &loc[0], hit_ptr);
    { float d = FastVecDot(&loc[3], normal_ptr);
    FastVecScale(&loc[4], normal_ptr, d); }
    FastVecSub(&loc[6], &loc[3], &loc[4]);
    vec_scale_to_length(&loc[6], &loc[6], -30.0f);
    target_ptr = (TI128 *)(vars + 0x2D0);
    FastVecAdd(target_ptr, moby + 0x10, &loc[6]);
    dest_ptr = &loc[7];
    FastVecSub(dest_ptr, target_ptr, g_camera_position);
    vec_scale_to_length(dest_ptr, dest_ptr, g_mothership_surface_radius);
    FastVecAdd(dest_ptr, dest_ptr, g_camera_position);
    qcopy(target_ptr, dest_ptr);
    random_index = g_enemy_timer_base;
    *(short *)(vars + 0x26C) = 1;
    *(unsigned short *)(vars + 0x26E) = ((s32)(g_enemy_timer_base + math_random_int_range(-random_index / 2, random_index / 2)) * 5 + 2) / 6;
    vec_scale_to_length(normal_ptr, normal_ptr, 10.0f);
    FastVecAdd(normal_ptr, normal_ptr, hit_ptr);
    return 1;
    }
    return 0;
}

/* Turns the linked child part toward the hero (or toward its joint) with a timed twist and aligns it to the enemy's direction. (PAL) */
void child_update_orientation_pal(char *moby) {
    TI128 hero_dir[1], joint_matrix[3], twist_a[1], back_dir[1], twist_matrix[3], back_dir_2[1];
    float zero_a, zero_b;
    char *vars = *(char **)(moby + 0x68);
    float heading;
    float min_speed;
    float max_speed;
    float accel;

    if (*(unsigned char *)(moby + 0x95) == 2 || *(short *)(vars + 0x2A6) != 0)
        moby_transform_joint_to_world(moby, 1, *(char **)(vars + 0x2A0) + 0x10);
    else
        moby_copy_joint_transform_to_object(moby, *(char **)(vars + 0x2A0), 1, 0);
    if (*(unsigned char *)(moby + 0x95) == 2) {
        if (*(short *)(vars + 0x2A6) == 0)
            *(int *)(vars + 0x2AC) = 0;
        FastVecSub(hero_dir, g_hero_position, *(char **)(vars + 0x2A0) + 0x10);
        heading = vec_get_heading_angle(*(char **)(vars + 0x2A0), hero_dir, 0);
        max_speed = *(float *)(vars + 0x68) + *(float *)(vars + 0x68);
        min_speed = *(float *)(vars + 0x64);
        accel = *(float *)(vars + 0x6C);
        zero_a = 0;
        math_approach_target_with_direction_mode(&zero_a, heading, min_speed, max_speed, accel, vars + 0x2AC, 0);
        qzero_nc(twist_a);
        ((float *)twist_a)[2] = *(float *)(vars + 0x2AC);
        euler_rotation_basis(joint_matrix, twist_a);
        multiply_matrix3x3(*(char **)(vars + 0x2A0) + 0xC0, *(char **)(vars + 0x2A0) + 0xC0, joint_matrix);
        func_PAL_002A0F68(*(char **)(vars + 0x2A0));
        *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(vars + 0x2A0));
        FastVecScale(back_dir, vars + 0x280, -1.0f);
        mat_align_to_dir(*(char **)(vars + 0x2A0) + 0xC0, back_dir, 0);
        *(short *)(vars + 0x2A6) = ((s32)(g_child_orientation_timer) * 5 + 2) / 6;
        return;
    }
    {
        short v = *(short *)(vars + 0x2A6);

        if (v != 0) {
            if (v == ((s32)(g_child_orientation_timer) * 5 + 2) / 6)
                *(int *)(vars + 0x2AC) = 0;
            *hero_dir = 0;
            ((float *)hero_dir)[0] = 1.0f;
            ((float *)hero_dir)[3] = 1.0f;
            moby_transform_joint_point(moby, 1, joint_matrix);
            qzero_nc(twist_a);
            matrix_mul_vec3(hero_dir, hero_dir, joint_matrix);
            heading = vec_get_heading_angle(*(char **)(vars + 0x2A0), hero_dir, 0);
            min_speed = *(float *)(vars + 0x64) + *(float *)(vars + 0x64);
            accel = *(float *)(vars + 0x6C);
            max_speed = *(float *)(vars + 0x68) * 4.0f;
            zero_b = 0;
            math_approach_target_with_direction_mode(&zero_b, heading, min_speed, max_speed, accel, vars + 0x2AC, 0);
            qzero_nc(back_dir);
            ((float *)back_dir)[2] = *(float *)(vars + 0x2AC);
            euler_rotation_basis(twist_matrix, back_dir);
            multiply_matrix3x3(*(char **)(vars + 0x2A0) + 0xC0, *(char **)(vars + 0x2A0) + 0xC0, twist_matrix);
            func_PAL_002A0F68(*(char **)(vars + 0x2A0));
            *(unsigned short *)(*(char **)(vars + 0x2A0) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(vars + 0x2A0));
            FastVecScale(back_dir_2, vars + 0x280, -1.0f);
            mat_align_to_dir(*(char **)(vars + 0x2A0) + 0xC0, back_dir_2, 0);
            FastDecTimer((short *)(vars + 0x2A6));
        }
    }
}
