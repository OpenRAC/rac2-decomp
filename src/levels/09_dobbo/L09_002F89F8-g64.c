#include "common.h"

/* The four-vector template uses GP addressing; the camera position is absolute. */
typedef struct {
    float x, y, z, w;
} Vec;
typedef struct {
    char pad[0x30];
    int mode, count;
    char pad38[0x18];
    char *dest;
    char pad54[0x138];
    int values[3];
    char *object;
} Context;

extern int g_current_map_index[] __attribute__((sda));
extern Context D_L09_001BD700;
extern char D_L09_00281210[];
extern Vec D_L09_001B9A00 __attribute__((nosda));
extern float D_L09_001A93E0 __attribute__((sda));
extern Vec D_L09_001A93F0[4] __attribute__((sda));
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* While the level is in state 9, places four glow corners around the object, spun about Z and nudged by the camera. */
void glow_place_state_nine_corners(void) {
    char matrix[0x30] __attribute__((aligned(16)));
    Vec rotation, temp;
    int minimum, index, i;
    int maximum = 9999;
    char *object;
    if (g_current_map_index[0] != 9)
        return;
    minimum = -1;
    index = 0;
    if (D_L09_001BD700.mode == 3) {
        minimum = 1;
        index = 2;
    }
    object = D_L09_001BD700.object;
    if (minimum != -1) {
        if (D_L09_001BD700.count < minimum)
            goto fail;
        if (maximum < D_L09_001BD700.count)
            goto fail;
        {
            D_L09_001BD700.dest = D_L09_00281210;
            qzero_nc(&rotation);
            rotation.z = D_L09_001A93E0;
            euler_rotation_basis(matrix, &rotation);
            for (i = 0; i < 4; i++) {
                matrix_mul_vec3(D_L09_001BD700.dest + 0x20 + i * 16, &D_L09_001A93F0[i], matrix);
                FastVecAdd(D_L09_001BD700.dest + 0x20 + i * 16, D_L09_001BD700.dest + 0x20 + i * 16, object + 0x10);
                FastVecSub(&temp, &D_L09_001B9A00, D_L09_001BD700.dest + 0x20 + i * 16);
                vec_scale_to_length(&temp, &temp, 0.05f);
                FastVecAdd(D_L09_001BD700.dest + 0x20 + i * 16, D_L09_001BD700.dest + 0x20 + i * 16, &temp);
            }
            *(int *)(D_L09_001BD700.dest + 0x68) = D_L09_001BD700.values[index];
        }
        return;
fail:
        D_L09_001BD700.dest = 0;
    }
}
