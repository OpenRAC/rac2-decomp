#include "names.h"
/* func_PAL_L05_003D3098, the PAL copy of func_L05_003CF350: the same C, where rename func_002BDCE8 becomes func_PAL_002BE9A8. */
#include "common.h"
extern char *part_find_owned_effect_slot(char *, unsigned int, int);
extern int moby_class_id_to_table_index(int);
extern float g_shot_reach_table[] SDATA(D_L05_001AFB68);
extern int g_burst_kind_table[] SDATA(D_L05_001AFB80);
extern int g_burst_inner_count_table[] SDATA(D_L05_001AFB98);
extern int g_burst_particle_count_table[] SDATA(D_L05_001AFBB0);
extern int g_burst_outer_count_table[] SDATA(D_L05_001AFBC8);
extern float g_burst_speed_size __attribute__((sda));
extern float g_burst_offset_length __attribute__((sda));
extern float g_burst_angle_rate __attribute__((sda));
extern float g_burst_spread_scale __attribute__((sda));
extern char g_origin_vec[];
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern float math_random_signed_float_range(float, float);
extern char *func_L05_003CEFA0(char *, void *, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_range(int, int);
extern int func_001163B0(void);
extern char *part_spawn_spinning_spark_pal(void *, int, float, float, float, float, void *, int, int);
/* Spawns three particle bursts at obj when func_002A9640 returns a record, unless the record is
   type 1 and obj is class 0x956. Returns 1 if it spawned them. */
int shot_spawn_impact_bursts_pal(char *obj)
{
    float pos[4], base[4], offset[4], center[4], vel[4];
    unsigned char *r;
    char *p, *s;
    int index, i, j, k, big;
    float radius, speed, angle, count, spread, size, a, b;
    int full;

    r = part_find_owned_effect_slot(obj, 0x230000, 0);
    full = 255;
    *(unsigned char *)(obj + 0xa8) = full;
    if (r) {
        unsigned short id = *(unsigned short *)(obj + 0xaa);

        if ((unsigned char)r[0x28] != 1 || (short)id != 0x956) {
            index = moby_class_id_to_table_index((short)id);
            {
                int kind = g_burst_kind_table[index];

                radius = g_shot_reach_table[index] * 0.5f;
                speed = g_burst_speed_size * 0.020000001f;
                if ((unsigned char)r[0x28] == 0)
                    speed *= 3.0f;
                vec_scale_to_length(base, r + 0x10, speed);
                if ((unsigned char)r[0x28] != 0 && math_random_int_below(4) == 0) {
                    FastVecSub(offset, obj + 0x10, g_origin_vec);
                    FastVecCross(center, offset, g_origin_vec + 0x250);
                    math_apply_axis_rotation_to_quat(offset, center, offset, math_random_angle());
                    vec_scale_to_length(offset, offset, g_burst_offset_length * 0.020000001f);
                    FastVecAdd(base, base, offset);
                }
                for (i = 0; i < g_burst_outer_count_table[index]; i++) {
                    char *p, *s;
                    float size, a, b;

                    pos[0] = *(float *)(obj + 0x10) + math_random_signed_float_range(0.0f, radius);
                    pos[1] = *(float *)(obj + 0x14) + math_random_signed_float_range(0.0f, radius);
                    pos[2] = *(float *)(obj + 0x18) + math_random_signed_float_range(0.0f, radius);
                    p = func_L05_003CEFA0(obj, pos, kind);
                    if (p) {
                        s = *(char **)(p + 0x68);
                        size = g_burst_speed_size * 0.010000001f;
                        a = math_random_angle();
                        b = math_random_angle();
                        vec_build_spherical_offset(center, size, a, b);
                        FastVecAdd(s + 0x10, base, center);
                        p[0x20] = 2;
                    }
                }
            }
            {
                int kind = 0x955;

                size = g_burst_speed_size * 0.010000001f;
                if (*(short *)(obj + 0xaa) == 0x956) {
                    size += size;
                    kind = 0x971;
                }
                for (j = 0; j < g_burst_inner_count_table[index]; j++) {
                    pos[0] = *(float *)(obj + 0x10) + math_random_signed_float_range(0.0f, radius);
                    pos[1] = *(float *)(obj + 0x14) + math_random_signed_float_range(0.0f, radius);
                    pos[2] = *(float *)(obj + 0x18) + math_random_signed_float_range(0.0f, radius);
                    p = func_L05_003CEFA0(obj, pos, kind);
                    big = 0x956;
                    if (p) {
                        s = *(char **)(p + 0x68);
                        if (*(short *)(obj + 0xaa) == big) {
                            FastVecSub(center, pos, obj + 0x10);
                            vec_scale_to_length(center, center, size);
                        } else {
                            a = math_random_angle();
                            b = math_random_angle();
                            vec_build_spherical_offset(center, size, a, b);
                        }
                        FastVecAdd(s + 0x10, base, center);
                        p[0x20] = 3;
                    }
                }
            }
            spread = g_shot_reach_table[index] * g_burst_spread_scale;
            angle = g_burst_angle_rate * 0.020000001f;
            count = (float)g_burst_particle_count_table[index];
            qcopy(center, obj + 0x10);
            if ((unsigned char)r[0x28] == 0) {
                vec_scale_to_length(base, g_origin_vec + 0x230, speed * 0.5f);
                vec_scale_to_length(vel, g_origin_vec + 0x230, 0.5f);
                FastVecAdd(center, center, vel);
                angle = 0.060000002f;
                if (*(short *)(obj + 0xaa) == 0x955) {
                    count = 40.0f;
                    radius = 0.1f;
                    angle = 0.040000003f;
                    spread *= 3.0f;
                }
            } else
                qzero(base);
            {
                int color = full | 0x7fffff00;

                for (k = 0; (float)k < count; k++) {
                    int spin;

                    pos[0] = center[0] + math_random_signed_float_range(0.0f, radius);
                    pos[1] = center[1] + math_random_signed_float_range(0.0f, radius);
                    pos[2] = center[2] + math_random_signed_float_range(0.0f, radius);
                    a = math_random_angle();
                    b = math_random_angle();
                    vec_build_spherical_offset(vel, angle, a, b);
                    FastVecAdd(vel, vel, base);
                    spin = math_random_int_range(-3, 3);
                    p = part_spawn_spinning_spark_pal(pos, spin, 0.0f, 1.0f, 1.0f, spread * 210000.0f, vel, color, 0);
                    if (p) {
                        *(short *)(p + 0xa) = 100;
                        s = p + 0x20;
                        p[8] = math_random_int_below(255);
                        if ((unsigned short)(*(unsigned short *)(obj + 0xaa) - 0x953) < 3)
                            p[3] = (func_001163B0() & 1) ? 0x44 : 0x48;
                        else
                            p[3] = 0x44;
                        *(int *)(s + 4) = 2;
                        s[0xa] = 127;
                        s[0xb] = p[0xa];
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}
