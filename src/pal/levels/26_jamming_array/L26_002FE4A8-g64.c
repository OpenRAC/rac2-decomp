#include "include_asm.h"

#include "common.h"
extern int g_current_map_index[] __attribute__((sda));
typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap38[0x44-0x38];
    short count;
    char gap46[0x50-0x46];
    char *output;
    char gap54[0x18C-0x54];
    char *parts[4];
} Hero;
extern Hero D_L26_001BC880;
extern char D_L26_0027E310[];
extern float D_L26_001A93E0[4][4] __attribute__((sda));
extern void vec_fast_to_int_helper(void *, void *);
extern void quaternion_to_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);

void func_PAL_L26_002FE4A8(void) {
    float matrix[12];
    float rotation[12];
    char *child;
    int index;

    float *out;
    float *vertex;
    float scale;
    int count;
    if (g_current_map_index[0] != 26) return;
    child = 0;
    index = -1;
    switch (D_L26_001BC880.mode) {
    case 0:
        child = D_L26_001BC880.parts[2];
        index = 1;
        break;
    case 1:
        index = 1;
        child = D_L26_001BC880.parts[2];
        break;
    }
    if (index != -1 && child != 0 && D_L26_001BC880.parts[index] != 0) {
        D_L26_001BC880.output = D_L26_0027E310;
        out = (float *)(D_L26_0027E310 + 0x20);
        vertex = D_L26_001A93E0[0];
        vec_fast_to_int_helper(*(char **)(child + 0x58) + 0x10, rotation);
        quaternion_to_rotation_basis(rotation, matrix);
        scale = *(float *)(child + 0x2C) / *(float *)(*(char **)(child + 0x24) + 0x24);
        count = 3;
        do {
            matrix_mul_vec3(out, vertex, matrix);
            vertex += 4;
            FastVecScale(out, out, scale);
            FastVecAdd(out, out, child + 0x10);
            out += 4;
        } while (--count >= 0);
        *(char **)(D_L26_001BC880.output + 0x68) = D_L26_001BC880.parts[index];
    }
    if (D_L26_001BC880.timer >= 0x4A9) D_L26_001BC880.output = 0;
}
