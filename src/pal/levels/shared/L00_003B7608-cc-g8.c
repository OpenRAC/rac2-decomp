#include "names.h"
/* func_PAL_L00_003B7608, the PAL copy of func_L00_003B3C40: the same C, where rename func_002BDCE8 becomes func_PAL_002BE9A8; scale D_L00_001AF904; wrap D_L00_001AF908 / func_00283CE0(angle) (({e}) * 1.2f). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern char *part_spawn_spinning_spark_pal(char *, float, float, float, float, int, char *, int, int);
extern char g_camera_l00_position[];
extern char g_default_vector[] MACRO_ADDR;
extern float g_spark_burst_speed __attribute__((sda));
extern int g_spark_burst_color __attribute__((sda));
extern int g_spark_burst_angle_count __attribute__((sda));
extern float g_spark_burst_depth __attribute__((sda));
extern float g_spark_second_speed __attribute__((sda));
extern int g_spark_second_color __attribute__((sda));
extern int g_spark_second_alpha __attribute__((sda));

/* Throws a spinning spark away from the camera, and now and then a smaller second one. (PAL: 50 Hz
 * timings) */
void part_spawn_spark_burst_away_from_camera_pal(char *object)
{
    union { Quad q; float f[4]; } position;
    float to_camera[4], offset[4], spawn_pos[4], velocity[4];
    int angle;
    int spin;
    float step;
    char *effect;
    position.q = 0;
    position.f[2] = g_spark_burst_depth;
    FastVecSub(to_camera, g_camera_l00_position, object + 0x10);
    math_apply_axis_rotation_to_quat(offset, &position, to_camera, math_random_angle());
    FastVecAdd(spawn_pos, object + 0x10, offset);
    spin = math_random_int_below(0x10);
    if (math_random_int_below(2))
        spin = -spin;
    angle = (((int)(g_spark_burst_angle_count) * 5 + 2) / 6);
    step = ((g_spark_burst_depth / IntToFloat(angle)) * 1.2f);
    vec_scale_to_length(velocity, offset, -step);
    effect = part_spawn_spinning_spark_pal((char *)spawn_pos, 0.5f, 1.0f, 0.99f, g_spark_burst_speed * 210000.0f, spin, (char *)velocity, g_spark_burst_color, 0);
    if (effect) {
        char *sub = effect + 0x20;
        *(short *)(effect + 0xA) = angle;
        *(int *)(sub + 4) = 3;
        sub[0xA] = 0x7F;
        sub[0xB] = *(unsigned char *)(effect + 0xA);
    }
    if (math_random_int_below(3) == 0) {
        vec_scale_to_length(to_camera, to_camera, -0.5f);
        FastVecAdd(spawn_pos, object + 0x10, to_camera);
        effect = part_spawn_spinning_spark_pal((char *)spawn_pos, 0.1f, 1.0f, 0.8f, g_spark_second_speed * 210000.0f, spin, g_default_vector, (g_spark_second_color & 0xFFFFFF) | (g_spark_second_alpha << 24), 0);
        if (effect) {
            char *sub = effect + 0x20;
            *(short *)(effect + 0xA) = 0x32;
            effect[3] = 0x44;
            *(int *)(sub + 4) = 3;
            sub[0xA] = *(unsigned char *)&g_spark_second_alpha;
            sub[0xB] = *(unsigned char *)(effect + 0xA);
        }
    }
}
