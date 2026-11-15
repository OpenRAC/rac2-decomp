#include "names.h"
/* func_PAL_L20_003A28D8, the PAL copy of func_L20_0039F968: the same C. */
/* func_PAL_L20_003A28D8 is a unit of its own: the history-copy loop needs -frac2-mult-add-no-flatten
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
extern Vector D_L20_00234880[][25];
extern Vector D_L20_00235500[];
extern int D_L20_001B3870[] __attribute__((sda));
extern float D_L20_001AED3C __attribute__((sda));
extern float D_L20_001AED40 __attribute__((sda));
extern float D_L20_001AED50 __attribute__((sda));
extern float D_L20_001AED58 __attribute__((sda));
extern unsigned int D_L20_001AED44 __attribute__((sda));
extern unsigned int D_L20_001AED48 __attribute__((sda));
extern unsigned int D_L20_001AED4C __attribute__((sda));
extern float D_L20_001AED54 __attribute__((sda));
extern unsigned char D_L20_001FFB40[];

void func_PAL_L20_003A28D8(unsigned char *object) {
    Vector points[25];
    Vector origin, offset, rotation;
    int i = 0;
    int *counts = D_L20_001B3870;
    unsigned char *level = D_L20_001FFB40;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *particle;
    int j, last;
    float length, limit;
    FastVecScale(&offset, object + 0xE0, D_L20_001AED3C);
    FastVecAdd(&origin, object + 0x10, &offset);
    for (; i < 8; ++i) {
        if (level_is_resident_flag_clear()) {
            Vector *head;
            int historyIndex;
            ++counts[i];
            if (counts[i] > 24) counts[i] = 25;
            last = counts[i] - 1;
            for (historyIndex = last; historyIndex > 0; --historyIndex)
                qcopy_nc(&D_L20_00234880[i][historyIndex], &D_L20_00234880[i][historyIndex - 1]);
            head = D_L20_00234880[i];
            math_build_axis_angle_quat(&rotation, (int)&D_L20_00235500[i], D_L20_001AED58 * 0.017453294f);
            vec_rotate_by_quaternion(head, head, &rotation);
            vec_add_random_offset(head->f, 0.125f);
            length = FastVecLength(head);
            limit = D_L20_001AED40 * 1.1f;
            if (limit < length) FastVecScale(head, head, limit / length);
            else {
                limit = D_L20_001AED40 * 0.9f;
                if (length < limit) FastVecScale(head, head, limit / length);
            }
        }
        last = counts[i] - 1;
        if (last < 0) last = 0;
        {
            int n = 0;
            for (j = last; j > 0; --j) {
                FastVecAdd(&points[n], &origin, &D_L20_00234880[i][j]);
                points[n].f[3] = 0.5f;
                ++n;
            }
        }
        FastVecAdd(&points[last], &origin, D_L20_00234880[i]);
        points[last].f[3] = 0.05f;
        if (level_is_resident_flag_clear()) {
            int top = counts[i] - 1;
            Vector *tip = &points[top];
            particle = part_spawn_bluish_fade(tip, 8, 0, 1);
            if (particle) {
                float size = D_L20_001AED50 * 210000.0f;
                *(unsigned int *)(particle + 4) = D_L20_001AED44 | *(unsigned int *)(state + 4);
                *(float *)(particle + 0xC) = size;
                particle[2] = (*(unsigned char **)(level + 0xF8))[1];
            }
            particle = part_spawn_bluish_fade(tip, 8, 0, 1);
            if (particle) {
                *(float *)(particle + 0xC) = D_L20_001AED50 * 63000.00390625f;
                *(unsigned int *)(particle + 4) = 0x407F7F7F;
            }
        }
        gfx_draw_ribbon_strip(points, 25, 14, 14, D_L20_001AED48, D_L20_001AED48 & 0xFFFFFF,
                          D_L20_001AED4C | *(unsigned int *)(state + 4), D_L20_001AED4C,
                          0, counts[i] - 1, counts[i], 0.1f, 0.2f, D_L20_001AED54);
    }
}
