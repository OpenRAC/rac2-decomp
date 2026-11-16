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
extern Context g_glow_context;
extern char g_glow_dest_buffer[];
extern Vec g_camera_l09_position __attribute__((nosda));
extern float g_glow_rotation __attribute__((sda));
extern Vec g_glow_corner_vectors[4] __attribute__((sda));
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
    if (g_glow_context.mode == 3) {
        minimum = 1;
        index = 2;
    }
    object = g_glow_context.object;
    if (minimum != -1) {
        if (g_glow_context.count < minimum)
            goto fail;
        if (maximum < g_glow_context.count)
            goto fail;
        {
            g_glow_context.dest = g_glow_dest_buffer;
            qzero_nc(&rotation);
            rotation.z = g_glow_rotation;
            euler_rotation_basis(matrix, &rotation);
            for (i = 0; i < 4; i++) {
                matrix_mul_vec3(g_glow_context.dest + 0x20 + i * 16, &g_glow_corner_vectors[i], matrix);
                FastVecAdd(g_glow_context.dest + 0x20 + i * 16, g_glow_context.dest + 0x20 + i * 16, object + 0x10);
                FastVecSub(&temp, &g_camera_l09_position, g_glow_context.dest + 0x20 + i * 16);
                vec_scale_to_length(&temp, &temp, 0.05f);
                FastVecAdd(g_glow_context.dest + 0x20 + i * 16, g_glow_context.dest + 0x20 + i * 16, &temp);
            }
            *(int *)(g_glow_context.dest + 0x68) = g_glow_context.values[index];
        }
        return;
fail:
        g_glow_context.dest = 0;
    }
}
