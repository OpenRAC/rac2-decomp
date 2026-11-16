#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int g_space_ship_tilt_value __attribute__((sda));
extern char g_hero_position[];
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

/* Tilts and turns the ship's attached part to follow the ship, easing its roll toward the wanted angle. (PAL: 50 Hz timings) */
void space_ship_tilt_attached_part_pal(char *obj) {
    TI128 offset[1], basis[3], roll_a[1], dir[1], basis2[3], dir2[1];
    float zero_a, zero_b;
    char *vars = *(char **)(obj + 0x68);
    float heading;
    float rate_a;
    float rate_b;
    float rate_c;

    if ((unsigned)(*(unsigned char *)(*(char **)(vars + 0x440) + 0x43) - 1) < 3) {
        if (*(short *)(vars + 0x460) == 0)
            *(int *)(vars + 0x458) = 0;
        FastVecSub(offset, g_hero_position, *(char **)(vars + 0x440) + 0x10);
        heading = vec_get_heading_angle(*(char **)(vars + 0x440), offset, 0);
        rate_b = *(float *)(vars + 0x128) + *(float *)(vars + 0x128);
        rate_a = *(float *)(vars + 0x124);
        rate_c = *(float *)(vars + 0x12C);
        zero_a = 0;
        math_approach_target_with_direction_mode(&zero_a, heading, rate_a, rate_b, rate_c, vars + 0x458, 0);
        qzero_nc(roll_a);
        ((float *)roll_a)[2] = *(float *)(vars + 0x458);
        euler_rotation_basis(basis, roll_a);
        multiply_matrix3x3(*(char **)(vars + 0x440) + 0xC0, *(char **)(vars + 0x440) + 0xC0, basis);
        func_PAL_002A0F68(*(char **)(vars + 0x440));
        *(unsigned short *)(*(char **)(vars + 0x440) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(vars + 0x440));
        FastVecScale(dir, vars + 0x200, -1.0f);
        mat_align_to_dir(*(char **)(vars + 0x440) + 0xC0, dir, 0);
        *(short *)(vars + 0x460) = ((s32)(g_space_ship_tilt_value) * 5 + 2) / 6;
        return;
    }
    {
        short timer = *(short *)(vars + 0x460);

        if (timer != 0) {
            if (timer == ((s32)(g_space_ship_tilt_value) * 5 + 2) / 6)
                *(int *)(vars + 0x458) = 0;
            *offset = 0;
            ((float *)offset)[0] = 1.0f;
            ((float *)offset)[3] = 1.0f;
            moby_transform_joint_point(obj, 1, basis);
            qzero_nc(roll_a);
            matrix_mul_vec3(offset, offset, basis);
            heading = vec_get_heading_angle(*(char **)(vars + 0x440), offset, 0);
            rate_a = *(float *)(vars + 0x124) + *(float *)(vars + 0x124);
            rate_c = *(float *)(vars + 0x12C);
            rate_b = *(float *)(vars + 0x128) * 4.0f;
            zero_b = 0;
            math_approach_target_with_direction_mode(&zero_b, heading, rate_a, rate_b, rate_c, vars + 0x458, 0);
            qzero_nc(dir);
            ((float *)dir)[2] = *(float *)(vars + 0x458);
            euler_rotation_basis(basis2, dir);
            multiply_matrix3x3(*(char **)(vars + 0x440) + 0xC0, *(char **)(vars + 0x440) + 0xC0, basis2);
            func_PAL_002A0F68(*(char **)(vars + 0x440));
            *(unsigned short *)(*(char **)(vars + 0x440) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(vars + 0x440));
            FastVecScale(dir2, vars + 0x200, -1.0f);
            mat_align_to_dir(*(char **)(vars + 0x440) + 0xC0, dir2, 0);
            FastDecTimer((short *)(vars + 0x460));
        }
    }
}
