#include "include_asm.h"

#include "common.h"
typedef int L06_7270TI __attribute__((mode(TI)));
extern void moby_set_state(unsigned char *, int, int);
extern void mat_apply_offset_to_object(void *, float, float, float);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern void matrix_mul_vec3(void *, const void *, const void *);
extern void func_PAL_002B15D8(char *, int, float *, unsigned char, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(void *);

void func_PAL_L06_0045C390(unsigned char *m)
{
    int *v = *(int **)(m + 0x68);
    int state = m[0x20];
    float t[4] __attribute__((aligned(16)));
    unsigned char *r;
    unsigned char *o;

    switch (state) {
    case 0:
        *v = 0;
        moby_set_state(m, 1, -1);
        break;
    case 1:
        mat_apply_offset_to_object(m, 0.0f, 0.0f, 0.020943955f);
        r = part_find_owned_effect_slot(m, 0x4010000, 0);
        if (r != 0) {
            o = *(unsigned char **)(r + 0x20);
            if (o != 0 && *(short *)(o + 0xAA) == 0x12C4) {
                *v = state;
            }
            moby_set_state(m, 2, -1);
        }
        m[0xA8] = 0xFF;
        break;
    case 2:
        *(L06_7270TI *)t = 0;
        if (*v != 0) {
            t[0] = -0.20000002f;
        } else {
            t[0] = 0.20000002f;
        }
        matrix_mul_vec3(t, t, m + 0xC0);
        func_PAL_002B15D8((char *)m, 7, t, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        PlayMobySound(0, 0, (char *)m);
        moby_mark_spawned(m);
        break;
    }
}
