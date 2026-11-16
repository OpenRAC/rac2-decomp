#include "names.h"
/* func_L20_0039F968 is a unit of its own: the history-copy loop needs -frac2-mult-add-no-flatten
   (docs/build/compiler-notes.md) so its source cursor keeps retail's i*400 + (D - 16) grouping. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void FastVecScale(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern int level_is_resident_flag_clear(void);
extern void math_build_axis_angle_quat(void *, int, float);
extern void vec_rotate_by_quaternion(void *, const void *, const void *);
extern void vec_add_random_offset(float *, float);
extern float FastVecLength(const void *);
extern unsigned char *part_spawn_bluish_fade(void *, int, int, int);
extern void gfx_draw_ribbon_strip(void *, int, int, int, unsigned int, unsigned int, unsigned int, unsigned int,
                             int, int, int, float, float, float);
extern Vector g_orb_arm_vectors[][25];
extern Vector g_electric_orb_basis_vectors[];
extern int g_orb_trail_counts[] __attribute__((sda));
extern float g_electric_trail_offset_scale __attribute__((sda));
extern float g_electric_basis_length __attribute__((sda));
extern float g_electric_trail_size __attribute__((sda));
extern float g_electric_trail_angle __attribute__((sda));
extern unsigned int g_electric_particle_color __attribute__((sda));
extern unsigned int g_electric_ribbon_color_a __attribute__((sda));
extern unsigned int g_electric_ribbon_color_b __attribute__((sda));
extern float g_electric_trail_param __attribute__((sda));
extern unsigned char g_orb_trail_levels[];

/* Updates and draws the eight lightning trails of the electric orb, adding sparks at their tips. */
void electric_orb_update_trails(unsigned char *object) {
    Vector points[25];
    Vector origin, offset, rotation;
    int i = 0;
    int *counts = g_orb_trail_counts;
    unsigned char *level = g_orb_trail_levels;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *particle;
    int j, last;
    float length, limit;
    FastVecScale(&offset, object + 0xE0, g_electric_trail_offset_scale);
    FastVecAdd(&origin, object + 0x10, &offset);
    for (; i < 8; ++i) {
        if (level_is_resident_flag_clear()) {
            Vector *head;
            int historyIndex;
            ++counts[i];
            if (counts[i] > 24) counts[i] = 25;
            last = counts[i] - 1;
            for (historyIndex = last; historyIndex > 0; --historyIndex)
                qcopy_nc(&g_orb_arm_vectors[i][historyIndex], &g_orb_arm_vectors[i][historyIndex - 1]);
            head = g_orb_arm_vectors[i];
            math_build_axis_angle_quat(&rotation, (int)&g_electric_orb_basis_vectors[i], g_electric_trail_angle * 0.017453294f);
            vec_rotate_by_quaternion(head, head, &rotation);
            vec_add_random_offset(head->f, 0.125f);
            length = FastVecLength(head);
            limit = g_electric_basis_length * 1.1f;
            if (limit < length) FastVecScale(head, head, limit / length);
            else {
                limit = g_electric_basis_length * 0.9f;
                if (length < limit) FastVecScale(head, head, limit / length);
            }
        }
        last = counts[i] - 1;
        if (last < 0) last = 0;
        {
            int n = 0;
            for (j = last; j > 0; --j) {
                FastVecAdd(&points[n], &origin, &g_orb_arm_vectors[i][j]);
                points[n].f[3] = 0.5f;
                ++n;
            }
        }
        FastVecAdd(&points[last], &origin, g_orb_arm_vectors[i]);
        points[last].f[3] = 0.05f;
        if (level_is_resident_flag_clear()) {
            int top = counts[i] - 1;
            Vector *tip = &points[top];
            particle = part_spawn_bluish_fade(tip, 10, 0, 1);
            if (particle) {
                float size = g_electric_trail_size * 210000.0f;
                *(unsigned int *)(particle + 4) = g_electric_particle_color | *(unsigned int *)(state + 4);
                *(float *)(particle + 0xC) = size;
                particle[2] = (*(unsigned char **)(level + 0xF8))[1];
            }
            particle = part_spawn_bluish_fade(tip, 10, 0, 1);
            if (particle) {
                *(float *)(particle + 0xC) = g_electric_trail_size * 63000.00390625f;
                *(unsigned int *)(particle + 4) = 0x407F7F7F;
            }
        }
        gfx_draw_ribbon_strip(points, 25, 14, 14, g_electric_ribbon_color_a, g_electric_ribbon_color_a & 0xFFFFFF,
                          g_electric_ribbon_color_b | *(unsigned int *)(state + 4), g_electric_ribbon_color_b,
                          0, counts[i] - 1, counts[i], 0.1f, 0.2f, g_electric_trail_param);
    }
}
